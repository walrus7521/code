#include "alfa147gta.h"
#include "ui_alfa147gta.h"
#include <QDebug>
#include <QFileDialog>
#include "spline.hpp"
extern "C" {
#include <stdio.h>
}

#define WHEELRADIUS 0.2922
#define FRONTAREA 2.2
#define MASS 1360
#define RHO 1.2041
#define CD 0.32
#define FINALRATIO 3.7330
#define PI 3.141592653589793238463


const double Alfa147gta::gearRatio[] = {3.5, 2.235, 1.52, 1.156, 0.971, 0.818};

Alfa147gta::Alfa147gta(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Alfa147gta)
{
    using namespace magnet::math;
    ui->setupUi(this);

    // this is the cubic interpolation spline for the LUT
    spline.addPoint(1000,200);
    spline.addPoint(1500,220);
    spline.addPoint(2000,242);
    spline.addPoint(2500,258);
    spline.addPoint(3000,260);
    spline.addPoint(3500,261);
    spline.addPoint(4000,268);
    spline.addPoint(4500,285);
    spline.addPoint(5000,300);
    spline.addPoint(5500,296);
    spline.addPoint(6000,290);
    spline.addPoint(6500,250);
    spline.addPoint(7000,220);
    spline.setLowBC(Spline::PARABOLIC_RUNOUT_BC);
    spline.setHighBC(Spline::PARABOLIC_RUNOUT_BC);

    setupPlot();
    setupSim();
}

void Alfa147gta::setupPlot()
{
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
    QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
#endif

    // include this section to fully disable antialiasing for higher performance:

    /*
    ui->customPlot->setNotAntialiasedElements(QCP::aeAll);
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);
    ui->customPlot->xAxis->setTickLabelFont(font);
    ui->customPlot->yAxis->setTickLabelFont(font);
    ui->customPlot->legend->setFont(font);
    */

    // SPEEDS
    ui->speedPlot->addGraph(); // blue line for current speed
    ui->speedPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->speedPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    ui->speedPlot->graph(0)->setAntialiasedFill(false);

    ui->speedPlot->addGraph(); // red line for target speed
    ui->speedPlot->graph(1)->setPen(QPen(Qt::red));
    ui->speedPlot->graph(0)->setChannelFillGraph(ui->speedPlot->graph(1)); // diff between speeds

    ui->speedPlot->addGraph(); // blue dot
    ui->speedPlot->graph(2)->setPen(QPen(Qt::blue));
    ui->speedPlot->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->speedPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->speedPlot->addGraph(); // red dot
    ui->speedPlot->graph(3)->setPen(QPen(Qt::red));
    ui->speedPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
    ui->speedPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->speedPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->speedPlot->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->speedPlot->xAxis->setAutoTickStep(false);
    ui->speedPlot->xAxis->setTickStep(1);
    ui->speedPlot->yAxis->setRange(0,250);
    ui->speedPlot->yAxis->setLabel("Speed [km/h]");
    ui->speedPlot->yAxis->setAutoTickStep(false);
    ui->speedPlot->yAxis->setTickStep(20);

    // THROTTLE
    ui->throttlePlot->addGraph(); // blue line for throttle
    ui->throttlePlot->graph(0)->setPen(QPen(Qt::blue));
    ui->throttlePlot->addGraph(); // blue dot
    ui->throttlePlot->graph(1)->setPen(QPen(Qt::blue));
    ui->throttlePlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->throttlePlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->throttlePlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->throttlePlot->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->throttlePlot->xAxis->setAutoTickStep(false);
    ui->throttlePlot->xAxis->setTickStep(1);
    ui->throttlePlot->yAxis->setRange(0,100);
    ui->throttlePlot->yAxis->setLabel("Throttle [%]");
    ui->throttlePlot->yAxis->setAutoTickStep(false);
    ui->throttlePlot->yAxis->setTickStep(10);

    // GEAR
    ui->gearPlot->addGraph(); // blue line for gear
    ui->gearPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->gearPlot->addGraph(); // blue dot
    ui->gearPlot->graph(1)->setPen(QPen(Qt::blue));
    ui->gearPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->gearPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);

    ui->gearPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->gearPlot->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->gearPlot->xAxis->setAutoTickStep(false);
    ui->gearPlot->xAxis->setTickStep(1);
    ui->gearPlot->yAxis->setRange(0,6);
    ui->gearPlot->yAxis->setLabel("Gear");
    ui->gearPlot->yAxis->setAutoTickStep(false);
    ui->gearPlot->yAxis->setTickStep(1);

    // setup a timer that repeatedly calls Alfa147GTA::simulationSlot
    connect(&simTimer, SIGNAL(timeout()), this, SLOT(simulationSlot()));
    // and another timer that repeatedly calls  Alfa147GTA::plotSlot
    connect(&plotTimer, SIGNAL(timeout()), this, SLOT(plotSlot()));
}

Alfa147gta::~Alfa147gta()
{
    delete ui;
}

void Alfa147gta::on_runButton_clicked()
{
    // clear the files
    resetFiles();
    // reset the sim signals
    setupSim();
    // disable the sim time box
    ui->doubleSpinBox->setReadOnly(true);
    // disable the run button
    ui->runButton->setEnabled(false);
    // enable the stop button
    ui->stopButton->setEnabled(true);
    // clear previous plot data
    ui->speedPlot->graph(0)->clearData();
    ui->speedPlot->graph(1)->clearData();
    ui->gearPlot->graph(0)->clearData();
    ui->throttlePlot->graph(0)->clearData();
    // start the simulation timer and plot timer
    simTimer.start(ui->doubleSpinBox->value()*1000); // use the update interval defined by the user
    plotTimer.start(10); // update every 10 ms
}

void Alfa147gta::on_stopButton_clicked()
{
    // stop the timers
    simTimer.stop();
    plotTimer.stop();
    // clear the files
    resetFiles();
    // enable the sim time box
    ui->doubleSpinBox->setReadOnly(false);
    // enable the run button
    ui->runButton->setEnabled(true);
    // disable the stop button
    ui->stopButton->setEnabled(false);
}

void Alfa147gta::on_targetSpeedSlider_sliderMoved(int position)
{
    targetSpeed = position;
    ui->targetSpeedLabel->setText(QString::number(position));
}


void Alfa147gta::setupSim()
{
    throttle = 0;
    currentSpeed = 0;
    targetSpeed = 0;
    engineRPM = 0;
    engineTRQ = 0;
    gear = 1;
}

void Alfa147gta::simulationSlot()
{
    // read new throttle input
    QString throttleFilePath = ui->throttleInput->text();
    QFile throttleFile(throttleFilePath);
    if(throttleFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&throttleFile);
        QString tmp;
        double temp;
        while (1)
        {
            tmp = in.readLine();
            if(tmp == NULL)
                break;
            bool ok;
            temp = tmp.toDouble(&ok);
            if(ok)
                throttle = temp;
            else qDebug("conversion failed");
        }
    }

    // 1) determine the gear we're in
    vehicleSpeedToGear();
    // 2) determine the current RPM
    vehicleSpeedToEngineRPM();
    // 3) determine the available torque
    engineRPMToEngineTorque();
    // 4) determine the wheel force
    double engineForce = engineTorqueToWheelForce();
    // 5) determine the resistance forces;
    double ambientResistance = ambientResistances();
    // 6) compute the new speed by integrating with the previous one
    newton2(engineForce - ambientResistance - brakingForce());

    // Write vehiclespeed in km/h to file
    QFile speedFile(ui->currentSpeedInput->text());
    if(speedFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&speedFile);
        out << (currentSpeed*3.6);
        out.flush();
    }
    QFile targetFile(ui->targetSpeedInput->text());
    if(targetFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&targetFile);
        out << targetSpeed;
        out.flush();
    }

    // close every opened file
    if (speedFile.isOpen()) speedFile.close();
    if (targetFile.isOpen()) targetFile.close();
}

void Alfa147gta::vehicleSpeedToGear()
{
    double speedkmph = currentSpeed * 3.6; // from m/s to km/h

    if(speedkmph < 39) gear = 1;
    else if(speedkmph < 60) gear = 2;
    else if(speedkmph < 86) gear = 3;
    else if(speedkmph < 110) gear = 4;
    else if(speedkmph < 130) gear = 5;
    else gear = 6;
}

void Alfa147gta::vehicleSpeedToEngineRPM()
{
    engineRPM = ((currentSpeed/WHEELRADIUS)*30/PI)*FINALRATIO*gearRatio[gear-1];
}

void Alfa147gta::engineRPMToEngineTorque()
{
    engineTRQ = throttle*spline(engineRPM);
}

double Alfa147gta::engineTorqueToWheelForce()
{
    return (engineTRQ*gearRatio[gear-1]*FINALRATIO)/WHEELRADIUS;
}

double Alfa147gta::ambientResistances()
{
    return currentSpeed*(currentSpeed+30)*0.5*CD*RHO*FRONTAREA;
}

double Alfa147gta::brakingForce()
{
    if(currentSpeed > targetSpeed)
        return 12600;
    else return 0;
}

void Alfa147gta::newton2(double force)
{
    // compute the acceleration
    double a = force/MASS;
    // a = v*t, then v = a*t
    double deltaV = a*ui->doubleSpinBox->value();
    // add that to the current speed. The current speed is in m/s
    currentSpeed += (deltaV);
    if(currentSpeed < 0) currentSpeed = 0;
}

void Alfa147gta::plotSlot()
{
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
    double key = 0;
#else
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
#endif
    ui->centralWidget->setStyleSheet("QWidget {background-image: url(Alfa_Romeo_147_GTA.jpg) }");

    // SPEEDS
    // add data to lines: 0 current speed 1 target speed
    ui->speedPlot->graph(0)->addData(key,currentSpeed*3.6);
    ui->speedPlot->graph(1)->addData(key, targetSpeed);
    // set dots 2 current 3 target
    ui->speedPlot->graph(2)->clearData();
    ui->speedPlot->graph(2)->addData(key,currentSpeed*3.6);
    ui->speedPlot->graph(3)->clearData();
    ui->speedPlot->graph(3)->addData(key,targetSpeed);
    // remove data outside visible range
    ui->speedPlot->graph(0)->removeDataBefore(key-10);
    ui->speedPlot->graph(1)->removeDataBefore(key-10);
    // rescale value (vertical) axis to fit the current data:
    ui->speedPlot->graph(0)->rescaleValueAxis();
    ui->speedPlot->graph(1)->rescaleValueAxis(true);
    // make key axis range scroll with the data (at a constant range size of 10):
    ui->speedPlot->xAxis->setRange(key+0.25, 10, Qt::AlignRight);
    ui->speedPlot->yAxis->setRange(0,250);
    ui->speedPlot->replot();

    // THROTTLE
    // add data to lines
    ui->throttlePlot->graph(0)->addData(key,throttle*100);
    // set dots 2 current 3 target
    ui->throttlePlot->graph(1)->clearData();
    ui->throttlePlot->graph(1)->addData(key,throttle*100);
    // remove data outside visible range
    ui->throttlePlot->graph(0)->removeDataBefore(key-10);
    // rescale value (vertical) axis to fit the current data:
    ui->throttlePlot->graph(0)->rescaleValueAxis();
    // make key axis range scroll with the data (at a constant range size of 10):
    ui->throttlePlot->xAxis->setRange(key+0.25, 10, Qt::AlignRight);
    ui->throttlePlot->yAxis->setRange(0,100);
    ui->throttlePlot->replot();

    // GEAR
    // add data to lines
    ui->gearPlot->graph(0)->addData(key,gear);
    // set dots 2 current 3 target
    ui->gearPlot->graph(1)->clearData();
    ui->gearPlot->graph(1)->addData(key,gear);
    // remove data outside visible range
    ui->gearPlot->graph(0)->removeDataBefore(key-10);
    // rescale value (vertical) axis to fit the current data:
    ui->gearPlot->graph(0)->rescaleValueAxis();
    // make key axis range scroll with the data (at a constant range size of 10):
    ui->gearPlot->xAxis->setRange(key+0.25, 10, Qt::AlignRight);
    ui->gearPlot->yAxis->setRange(0,6);
    ui->gearPlot->replot();
}

void Alfa147gta::resetFiles()
{
    QFile throttleFile(ui->throttleInput->text());
    if(throttleFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&throttleFile);
        out << 0;
        out.flush();
        throttleFile.close();
    }
    QFile speedFile(ui->currentSpeedInput->text());
    if(speedFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&speedFile);
        out << 0;
        out.flush();
        speedFile.close();
    }
    QFile targetFile(ui->targetSpeedInput->text());
    if(targetFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&targetFile);
        out << 0;
        out.flush();
        targetFile.close();
    }
}
