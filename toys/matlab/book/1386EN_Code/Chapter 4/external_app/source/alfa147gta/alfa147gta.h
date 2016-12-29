#ifndef ALFA147GTA_H
#define ALFA147GTA_H

#include <QMainWindow>
#include <QTimer>
#include "spline.hpp"

using namespace magnet::math;

namespace Ui {
class Alfa147gta;
}

class Alfa147gta : public QMainWindow
{
    Q_OBJECT

public:
    explicit Alfa147gta(QWidget *parent = 0);
    ~Alfa147gta();

    double throttle;
    double currentSpeed;
    int targetSpeed;
    double engineRPM;
    double engineTRQ;
    int gear;

    static const double gearRatio[];

    // simulation-related
    void setupSim();
    void vehicleSpeedToGear();
    void vehicleSpeedToEngineRPM();
    void engineRPMToEngineTorque();
    double engineTorqueToWheelForce();
    double ambientResistances();
    double brakingForce();
    void newton2(double force);

    // plot-related
    void setupPlot();

    // avoid horrible things
    void resetFiles();


private slots:
    void on_runButton_clicked();
    void on_stopButton_clicked();
    void on_targetSpeedSlider_sliderMoved(int position);
    void simulationSlot();
    void plotSlot();

private:
    Ui::Alfa147gta *ui;
    QTimer simTimer;
    QTimer plotTimer;
    Spline spline;


};

#endif // ALFA147GTA_H
