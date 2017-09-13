#include <stdio.h>
#include <math.h>

#define ACCELEROMETER_SENSITIVITY 8192.0
#define GYROSCOPE_SENSITIVITY 65.536
 
//#define M_PI 3.14159265359        
 
#define dt 0.01                         // 10 ms sample rate!    
 
void ComplementaryFilter(short accData[3], short gyrData[3], double *pitch, double *roll)
{
    double pitchAcc, rollAcc;               
 
    // Integrate the gyroscope data -> int(angularSpeed) = angle
    *pitch += ((double)gyrData[0] / GYROSCOPE_SENSITIVITY) * dt; // Angle around the X-axis
    *roll -= ((double)gyrData[1] / GYROSCOPE_SENSITIVITY) * dt;    // Angle around the Y-axis
 
    // Compensate for drift with accelerometer data if !bullshit
    // Sensitivity = -2 to 2 G at 16Bit -> 2G = 32768 && 0.5G = 8192
    int forceMagnitudeApprox = abs(accData[0]) + abs(accData[1]) + abs(accData[2]);
    if (forceMagnitudeApprox > 8192 && forceMagnitudeApprox < 32768)
    {
    // Turning around the X axis results in a vector on the Y-axis
        pitchAcc = atan2f((double)accData[1], (double)accData[2]) * 180 / M_PI;
        *pitch = *pitch * 0.98 + pitchAcc * 0.02;
 
    // Turning around the Y axis results in a vector on the X-axis
        rollAcc = atan2f((double)accData[0], (double)accData[2]) * 180 / M_PI;
        *roll = *roll * 0.98 + rollAcc * 0.02;
    }
}

struct quaternion {
    double w, x, y, z;
};

struct quaternion toQuaternion(double pitch, double roll, double yaw)
{
    struct quaternion q;

    // Abbreviations for the various angular functions
    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);
    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);

    q.w = cy * cr * cp + sy * sr * sp;
    q.x = cy * sr * cp - sy * cr * sp;
    q.y = cy * cr * sp + sy * sr * cp;
    q.z = sy * cr * cp - cy * sr * sp;

    return q;
}

void toEulerianAngle(const struct quaternion q, double *roll, double *pitch, double *yaw)
{
    // roll (x-axis rotation)
    double sinr = +2.0 * (q.w * q.x + q.y * q.z);
    double cosr = +1.0 - 2.0 * (q.x * q.x + q.y * q.y);
    *roll = atan2(sinr, cosr);

    // pitch (y-axis rotation)
    double sinp = +2.0 * (q.w * q.y - q.z * q.x);
        if (fabs(sinp) >= 1)
            *pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
        else
            *pitch = asin(sinp);

    // yaw (z-axis rotation)
    double siny = +2.0 * (q.w * q.z + q.x * q.y);
    double cosy = +1.0 - 2.0 * (q.y * q.y + q.z * q.z);  
    *yaw = atan2(siny, cosy);
}

int main()
{
    short accels[3] = {127, 34, 17}; // x,y,z
    short gyros[3] = {34, 31, 128}; // x,y,z
    double pitch;
    double roll;
    double yaw = 0.0;

    ComplementaryFilter(accels, gyros, &pitch, &roll);    
    printf("start pitch: %f, roll: %f, yaw: %f\n", pitch, roll, yaw);

    struct quaternion q = toQuaternion(pitch, roll, 0);
    printf("quat w: %f, x: %f, y: %f, z: %f\n", q.w, q.z, q.y, q.z);

    toEulerianAngle(q, &roll, &pitch, &yaw);
    printf("euler pitch: %f, roll: %f, yaw: %f\n", pitch, roll, yaw);
    
    
}

