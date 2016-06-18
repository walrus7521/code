#include <stdio.h>
#include <math.h>

// from wiki
// setpoint = x
// previous_error = 0
// integral = 0 
// start:
//   error = setpoint - measured_value
//   integral = integral + error*dt
//   derivative = (error - previous_error)/dt
//   output = Kp*error + Ki*integral + Kd*derivative
//   previous_error = error
//   wait(dt)
//   goto start


//This is the PID definition, Kp, Ki and Kd are proportional, integral and differential gains
//float PID_Out = Kp * actual_error + Ki * SUM(previous_errors) + Kd * (actual_error - last_error);
//Define the error
//float actual_error = set_point - measured_value;
 
//Variables
float actual_error, error_previous, P, I, D, Kp, Ki, Kd ;
float PID_Controller (float set_point, float measured_value)
{
    error_previous = actual_error;  //error_previous holds the previous error
    actual_error = set_point - measured_value; 
    // PID 
    P  = actual_error;   //Current error
    I += error_previous;  //Sum of previous errors
    D  = actual_error - error_previous;  //Difference with previous error
    return Kp*P + Ki*I + Kd*D;   //adjust Kp, Ki, Kd empirically or by using online method such as ZN
}

void PID_Init()
{
    actual_error = 0.0f;
    I = 0.0f;
    Kp = 20.0f;
    Ki = 0.1f;
    Kd = 100.0f;
}

#if 0
// http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/

/*working variables*/
unsigned long lastTime;
double Input, Output, Setpoint;
double errSum, lastErr;
double kp, ki, kd;
void Compute()
{
   /*How long since we last calculated*/
   unsigned long now = millis();
   double timeChange = (double)(now - lastTime);
  
   /*Compute all the working error variables*/
   double error = Setpoint - Input;
   errSum += (error * timeChange);
   double dErr = (error - lastErr) / timeChange;
  
   /*Compute PID Output*/
   Output = kp * error + ki * errSum + kd * dErr;
  
   /*Remember some variables for next time*/
   lastErr = error;
   lastTime = now;
}
void SetTunings(double Kp, double Ki, double Kd)
{
   kp = Kp;
   ki = Ki;
   kd = Kd;
}
#endif

// http://www.embedded.com/design/prototyping-and-development/4211211/PID-without-a-PhD
typedef struct
{
  double dState;      	// Last position input
  double iState;      	// Integrator state
  double iMax, iMin;  	
  // Maximum and minimum allowable integrator state
  double pGain, // proportional gain
         iGain, // integral gain
         dGain; // derivative gain
} PID;

double UpdatePID(PID * pid, double error, double position)
{
    double pTerm, dTerm, iTerm;

    // calculate the proportional term
    pTerm = pid->pGain * error;   

    // calculate the integral state with appropriate limiting
    pid->iState += error;

    if (pid->iState > pid->iMax) {
        pid->iState = pid->iMax;
    } else 
    if (pid->iState < pid->iMin) {
        pid->iState = pid->iMin;
    }

    pTerm = pid->pGain * error;   
    iTerm = pid->iGain * pid->iState;  // calculate the integral term
    dTerm = pid->dGain * (position - pid->dState);
    pid->dState = position;
    return pTerm + iTerm - dTerm;
}

void init(PID *pid)
{
    pid->iMin   = 1;
    pid->iMax   = 5;
    pid->pGain  = 20;
    pid->iGain  = 0.1;
    pid->dGain  = 100.0;
    pid->iState = 0;
    pid->dState = 0;
}

void sim1()
{
    float control, set_point = 10.0f, measure, error;
    int i;
    PID pid;
    init(&pid);
    for (i = 0; i < 32; i++) {
        measure = rand() % 10; 
        error = set_point - measure;
        control = UpdatePID(&pid, error, set_point);
        printf("measure: %f, control %f\n", measure, control);
    }

}

void sim2()
{
    float control, set_point = 10.0f, measure;
    int i;
    PID_Init();
    for (i = 0; i < 32; i++) {
        measure = rand() % 10; 
        control = PID_Controller (set_point, measure);
        printf("measure: %f, control %f\n", measure, control);
    }

}

int main()
{
    printf("method 1\n");
    sim1();
    printf("method 2\n");
    sim2();
}
