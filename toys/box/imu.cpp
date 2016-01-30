#include <iostream>
#include <cmath>

using namespace std;

/*
 * 3-axis accelerometer, G's
 * 2-axis gyro, deg/sec
 *
 * 6 degrees of freedom IMU
 * 
 * http://www.starlino.com/imu_guide.html
 */


/* accelerometer detects force opposite the inertial force vector
 */

/*
 * define R vector in xyz coordinate system
 */

double R;
double X, Y, Z;
double Rx, Ry, Rz; /* projections of R onto X, Y, and Z */

/* R^2 = Rx^2 + Ry^2 + Rz^2 */

/* devices will have a zero-G value */
#define ZERO_G  511 /* counts of ficticious device */
#define SENSITIVITY_ACCEL 150 /* counts per G */

double DRx, DRy, DRz; /* deltas from zero-G */

int main()
{
    /* counts read from a digital accelerometer 12-bits 
       0..1023
     */

    Rx = 586;
    Ry = 630;
    Rz = 561;

    DRx = Rx - ZERO_G;
    DRy = Ry - ZERO_G;
    DRz = Rz - ZERO_G;

    /* this is the direction of the inertial vector */
    DRx /= SENSITIVITY_ACCEL;
    DRy /= SENSITIVITY_ACCEL;
    DRz /= SENSITIVITY_ACCEL;
    
    cout << "DRx = " << DRx << endl;    
    cout << "DRy = " << DRy << endl;    
    cout << "DRz = " << DRz << endl;    

    /* now lets find the inclination wrt each axis 
     *
     * cos(Axr) = Rx / R;
     * cos(Ayr) = Ry / R;
     * cos(Azr) = Rz / R;
     *
     * R = sqrt( Rx^2 + Ry^2 + Rz^2);
     *
     * Axr = arccos(Rx/R);
     * Ayr = arccos(Ry/R);
     * Azr = arccos(Rz/R);
     *
     * define the direction cosines as:
     * cosX = cos(Axr) = Rx/R;
     * cosY = cos(Ayr) = Ry/R;
     * cosZ = cos(Azr) = Rz/R;
     *
     * 1 = sqrt(cosX^2 + cosY^2 + cosZ^2);
     *
     */
    double Axr, Ayr, Azr;

    R = sqrt((Rx*Rx) + (Ry*Ry) + (Rz*Rz));
    Axr = acos(Rx/R);
    Ayr = acos(Ry/R);
    Azr = acos(Rz/R);

    cout << "Axr = " << Axr << endl;    
    cout << "Ayr = " << Ayr << endl;    
    cout << "Azr = " << Azr << endl;    

    /* now for the gyro
     * gyros measure the rate of change of angles of rotation about the axes
     */

    double Rxz; /* projection of inertial vector R on xz-plane */
    double Ryz; /* projection of inertial vector R on yz-plane */
    
    /* by Pythagorean we get: */
    Rxz = sqrt((Rx*Rx) + (Rz*Rz));
    Ryz = sqrt((Ry*Ry) + (Rz*Rz));

    /* also, note that R^2 = Rxz^2 + Ry^2 = Ryz^2 + Rx^2 */

    /* define the angles between the Z axis & Rxz & Ryz vectors */
    double Axz; /* angle between Rxz and Z-axis --> aboot Y */
    double Ayz; /* angle between Ryz and Z-axis --> aboot X */

    /* take measurements from the gyro:
     * Axz1 and Axz2 at times t0 and t1
     */
    double Axz0;
    double Axz1;
    double t0, t1;
    double RateAxz = (Axz1 - Axz0)/(t1 - t0); /* degrees/sec */

}


