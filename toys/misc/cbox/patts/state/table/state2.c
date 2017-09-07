#include <stdio.h>
#include <unistd.h>

// brute force approach

void stater()
{
    int state = 0;
    int should_go_to_next_state = 1;
    int should_go_back = 0;
    int should_go_back_two = 1;
    while (state < 3)
    {
        switch (state)
        {
            case 0:
                // Do State 0 Stuff
                if (should_go_to_next_state)
                {
                    printf("0 -> 1\n");
                    state++;
                }
                break;
            case 1:
                // Do State 1 Stuff    
                if (should_go_back) 
                {
                    printf("1 -> 0\n");
                    state--;
                }    
                else if (should_go_to_next_state) 
                {
                    printf("1 -> 2\n");
                    state++;
                }
                break;
            case 2:
                // Do State 2 Stuff    
                if (should_go_back_two) 
                {
                    printf("2 -> 0\n");
                    state -= 2;
                }    
                else if (should_go_to_next_state) 
                {
                    printf("2 -> 3\n");
                    state++;
                }
                break;
            default:
                break;
        }
        sleep(2);
    }
}

int main()
{
    stater();
}
