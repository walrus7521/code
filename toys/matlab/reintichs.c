#include <stdio.h>
#include <math.h>

float sigen(float time)
{
    float u;
    u = sin(time);
    return u;
}

#define FALSE (0)
#define TRUE  (1)

float reintichs(float input, int hold, int run, float IC, float lower_sat_limit, float upper_sat_limit, int reset_on_init)
{
    int input_hold;
    static float delay = 0.0f;
    float K_Ts = 0.01;
    float output;

    // evaluate hold logic
    if ((upper_sat_limit < lower_sat_limit)    ||
        (delay > upper_sat_limit && input > 0) ||
        (delay < lower_sat_limit && input < 0) ||
         FALSE != hold)
    {
        input_hold = TRUE;
    }
    else
    {
        input_hold = FALSE;
    }

    // evaluate run and reset states
    if (FALSE == run || !reset_on_init)
    {
        delay = IC;
        reset_on_init = TRUE;
    }
    else
    {
        // evaluate hold
        if (FALSE == input_hold)
        {
            // run the filter
            delay = (input * K_Ts) + delay;
        }
        else
        {
            // do nothing - here for coding guidelines compliance
        }
    }

    // respond to changing upper and lower rails
    if (delay > upper_sat_limit)
    {
        delay = upper_sat_limit;
    }
    else
    if (delay < lower_sat_limit)
    {
        delay = lower_sat_limit;
    }    

    // assign the output
    output = delay;
    return output;
}

int main()
{
    int i = 0;
    float t, input, IC, lower_sat_limit, upper_sat_limit, output;
    int hold, run, reset_on_init;

    printf("M = [...\n");
    for (i = 0; i < 64; i++) {
        t = 0.3 * i;
        input = sigen(t);
        hold = 0;
        run = 1;
        reset_on_init = 1;
        IC = 0.0;
        lower_sat_limit = -2.0;
        upper_sat_limit =  2.0;

        output = reintichs(input, hold, run, IC, lower_sat_limit, upper_sat_limit, reset_on_init);
        
        //float Time, u1, u2, u3, u4, u5, u6, y1;
        //float time, input, run, ic, hold, ul, ll, out;
        printf("%5.2f, %6.2f, %02d, %4.2f, %02d, %4.2f, %4.2f, %5.4f; ...\n",
                t, input, run, IC, hold, upper_sat_limit, lower_sat_limit, output);
    }
    printf("];\n");
    return 0;
}
