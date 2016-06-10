

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
  double	iGain,    	// integral gain
        	pGain,    	// proportional gain
         	dGain;     	// derivative gain
} SPid;

double UpdatePID(SPid * pid, double error, double position)
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

void init(SPid *pid)
{
    pid->iMin   = 1;
    pid->iMax   = 5;
    pid->pGain  = 20;
    pid->iGain  = 0.1;
    pid->dGain  = 100.0;
    pid->iState = 0;
    pid->dState = 0;
}

double sample(SPid *pid)
{
    return 3.0;
}

void show(SPid *pid)
{
}

void sim1()
{
    SPid pid;
    init(&pid);
    show(&pid);    
}

void sim2()
{
}

int main()
{
}
