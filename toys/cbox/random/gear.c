#include <stdio.h>

typedef enum {
    GEAR_DOWN = 0, 
    WTG_FOR_TKOFF, 
    RAISING_GEAR, 
    GEAR_UP, 
    LOWERING_GEAR,
    MAX_STATE
} State_Type;

typedef enum {
    UP,
    DOWN,
    MADE
} Gear_State;

typedef enum {
    ON,
    OFF
} Pump_Motor_State;

typedef enum {
    LIGHTS_ON,
    LIGHTS_OFF
} Gear_Light_State;

typedef enum {
    PUMPING_UP,
    PUMPING_DOWN
} Pump_Direction;

Pump_Direction pump_direction;
Gear_Light_State gear_lights;
Pump_Motor_State pump_motor;
Gear_State nosegear_is_up;
Gear_State nosegear_is_down;
Gear_State leftgear_is_up;
Gear_State leftgear_is_down;
Gear_State rightgear_is_up;
Gear_State rightgear_is_down;
Gear_State gear_lever;
Gear_State prev_gear_lever;
Gear_State squat_switch;

/* This table contains a pointer to the function to call in each
state.*/

State_Type curr_state;
float timer;

void init()
{
    curr_state = GEAR_DOWN;
    timer = 0.0;
    /* Stop all the hardware, turn off the lights, etc.*/
}

void gear_down()
{
    printf("gear_down\n");
    /* Raise the gear upon command, but not if the airplane is
    on the ground.*/
    if ((gear_lever == UP) && (prev_gear_lever == DOWN) && (squat_switch == UP)) {
        timer = 2.0;
        curr_state = WTG_FOR_TKOFF;
    }
    prev_gear_lever = gear_lever;
}

void raising_gear()
{
    printf("raising_gear\n");
    if ((nosegear_is_up == MADE) && (leftgear_is_up == MADE) && (rightgear_is_up == MADE)) {
        pump_motor = OFF;
        gear_lights = LIGHTS_OFF;
        curr_state = GEAR_UP;
    }
    // if the pilot changes his mind, start lowering the gear
    if (gear_lever == DOWN) {
        pump_direction = PUMPING_DOWN;
        curr_state = LOWERING_GEAR;
    }
}

void gear_up()
{
    printf("gear_up\n");
    if (gear_lever == DOWN) {
        curr_state = LOWERING_GEAR;
    }
}

void wait_for_takeoff()
{
    printf("wait_for_takeoff\n");
    if (timer <= 0.0) {
        curr_state = RAISING_GEAR;
    }
    // if we touch down again, or if the pilot changes his mind, start over
    if ((squat_switch == DOWN) || (gear_lever == DOWN)) {
        timer = 2.0;
        curr_state = GEAR_DOWN;
        // don't want to require that he toggle the lever again, this was
        // just a bounce
        prev_gear_lever = DOWN;
    }
}

void lowering_gear()
{
    printf("lowering_gear\n");
    if (gear_lever == UP) {
        curr_state = RAISING_GEAR;
    }
    if ((nosegear_is_down == MADE) && (leftgear_is_down == MADE) && (rightgear_is_down == MADE)) {
        curr_state = GEAR_DOWN;
    }
}


typedef void(*state_func)(void); 
state_func state_table[] = {gear_down, wait_for_takeoff, raising_gear, gear_up, lowering_gear};

void decrement_timer()
{
    timer -= 1.0;
}

void main()
{
    int i;
    for (i = 0; i < MAX_STATE; ++i) {
        state_table[i]();
    }
    init();
    /* The heart of the state machine is this one loop.
    The function corresponding to the current state is called
    once per iteration. */
    while (1)
    {
        state_table[curr_state]();
        decrement_timer();
        /* Do other functions, not related to this state machine.*/
    }
}

