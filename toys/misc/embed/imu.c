#include <stdio.h>
#include <math.h>
#include <stdint.h>

struct quaternion {
    double w, x, y, z;
};

struct vector_int {
    int32_t x;
    int32_t y;
    int32_t z;
};

struct vector_float {
    float x;
    float y;
    float z;
};

struct vector_axes {
    float roll;
    float pitch;
    float yaw;};

// driver code
void GetAccel(struct vector_int *v, const uint8_t* packet) { // input raw fifo 64-byte data
    v->x = (packet[28] << 8) | packet[29];
    v->y = (packet[32] << 8) | packet[33];
    v->z = (packet[36] << 8) | packet[37];
}

void GetGyro(struct vector_int *v, const uint8_t* packet) { // input raw fifo 64-byte data
    v->x = (((uint32_t)packet[16] << 24) | ((uint32_t)packet[17] << 16) | ((uint32_t)packet[18] << 8) | packet[19]);
    v->y = (((uint32_t)packet[20] << 24) | ((uint32_t)packet[21] << 16) | ((uint32_t)packet[22] << 8) | packet[23]);
    v->z = (((uint32_t)packet[24] << 24) | ((uint32_t)packet[25] << 16) | ((uint32_t)packet[26] << 8) | packet[27]);
}

// input quaternion
void GetGravity(struct vector_float *v, struct quaternion *q) {
    v->x = 2 * (q->x*q->z - q->w*q->y);
    v->y = 2 * (q->w*q->x + q->y*q->z);
    v->z = q->w*q->w - q->x*q->x - q->y*q->y + q->z*q->z;
}

// input quaternion
void GetEuler(struct vector_float *v, struct quaternion *q) {
    v->x = atan2(2*q -> x*q->y - 2*q->w*q->z, 2*q-> w*q->w + 2*q->x*q->x - 1); // psi
    v->y = -asin(2*q -> x*q->z + 2*q->w*q->y);                                        // theta
    v->z = atan2(2*q -> y*q->z - 2*q->w*q->x, 2*q-> w*q->w + 2*q->z*q->z - 1); // phi
}

// input quaternion and gravity
void GetYawPitchRoll(struct vector_axes *v, struct quaternion *q, struct vector_float *gravity) {
    // yaw: (about Z axis)
    v->yaw = atan2(2*q->x*q->y - 2*q->w*q->z, 2*q->w*q->w + 2*q->x*q->x - 1);
    // pitch: (nose up/down, about Y axis)
    v->pitch = atan(gravity->x / sqrt(gravity->y * gravity->y + gravity->z * gravity->z));
    // roll: (tilt left/right, about X axis)
    v->roll = atan(gravity->y / sqrt(gravity->x * gravity->x + gravity->z * gravity->z));
}

void GetQuaternion(struct quaternion *q, const uint8_t* packet) {
    int16_t data[4];
    data[0] = (((uint32_t)packet[0] << 24) | ((uint32_t)packet[1] << 16) | ((uint32_t)packet[2] << 8) | packet[3]);
    data[1] = (((uint32_t)packet[4] << 24) | ((uint32_t)packet[5] << 16) | ((uint32_t)packet[6] << 8) | packet[7]);
    data[2] = (((uint32_t)packet[8] << 24) | ((uint32_t)packet[9] << 16) | ((uint32_t)packet[10] << 8) | packet[11]);
    data[3] = (((uint32_t)packet[12] << 24) | ((uint32_t)packet[13] << 16) | ((uint32_t)packet[14] << 8) | packet[15]);

    q->w = (float)data[0] / 16384.0f;
    q->x = (float)data[1] / 16384.0f;
    q->y = (float)data[2] / 16384.0f;
    q->z = (float)data[3] / 16384.0f;
}

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

// utilities
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

// https://github.com/jrowberg/i2cdevlib/blob/master/Arduino/MPU6050/MPU6050_6Axis_MotionApps20.h

