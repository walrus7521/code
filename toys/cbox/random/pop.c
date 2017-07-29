#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_ARGS 8
#define LINE_SIZE 256

enum {
    STATE_NOAUTH    = 0,
    STATE_USER      = 1,
    STATE_PROCESS   = 2,
    STATE_INVALID   = 3,
    STATE_QUIT      = 4,
    MAX_STATES
};

int actionUser(char **args);
int actionQuit(char **args);
int actionPass(char **args);
int actionList(char **args);

struct
{
    int  currentState;
    char *command;
    int  stateIfSucceed;
    int  stateIfFailed;
    int  (*action)(char **);
} actionTable[] =
{
    {0, "USER", 1, 3, actionUser},
    {0, "QUIT", 4, 4, actionQuit},
    {1, "PASS", 2, 3, actionPass},
    {1, "QUIT", 4, 4, actionQuit},
    {2, "LIST", 2, 2, actionList},
    {2, "RETR", 2, 2, actionList},
    {2, "QUIT", 4, 4, actionList},
    {0, 0, 0, 0, 0}
};

void show(char **args)
{
    while (*args != NULL) {
        printf("arg: %p, %s\n", *args, *args);
        *args++;
    }
}

int actionUser(char **args) { 
    if (strcmp(args[0], actionTable[0].command) == 0) {
        printf("actionUser: success\n");
        return actionTable[0].stateIfSucceed;
    } else {
        printf("actionUser: failed\n");
        return actionTable[0].stateIfFailed;
    }
}
int actionQuit(char **args) { 
    printf("actionQuit\n");
    return 0; 
}
int actionPass(char **args) { 
    printf("actionPass\n");
    return 0; 
}
int actionList(char **args) { 
    return 0; 
    printf("actionList\n");
}


#if 0
start:
get command
if  command is "USER" then
  username = argument
  get command
  if  command is "PASS" then
    password = argument
    if valid(username,password) then
      while true
        get command
        if command is "LIST" then
          performLIST
        elsif command is "RETR" then
          performRETR(argument)
        elsif command is "QUIT" then
          return
        end if
      end while
    end if
  end if
end if


int state = 0;
while (true)
{
    command = next command;
    switch (state)
    {
        case 0:
            if (command.equals("USER"))
            {
                username = argument;
                state = 1;
            }
            else if (command.equals("QUIT"))
                state = 4;
            else
                error("Unknown: " + command);
            break;
        case 1:
            if (command.equals("PASS"))
            {
                if (valid(username, argument))
                    state = 2;
                else
                {
                    error("Unauthorized");
                    state = 3;
                }
            }
            else
                error("Unknown: " + command);
            break;
...
#endif

void get_command(char **cmd)
{
    char *buffer = malloc(LINE_SIZE);
    char *line = buffer;
    printf("$ ");
    if (fgets(buffer, LINE_SIZE, stdin) != NULL) {
        int index = 0;
        int len = strlen(buffer);
        line[len-1] = '\0';
        printf("%s\n", line);
        char *token = strtok(line, " ");
        while (token != NULL) {
            cmd[index++] = strdup(token);
            token = strtok(NULL, " ");
        }
        cmd[index] = NULL;
    }
    free(buffer);
}
    
int main()
{
    int command;
    char** cmd = calloc(MAX_ARGS, LINE_SIZE);
    int state = STATE_NOAUTH;
    while (true) {
        get_command(cmd);
        state = actionTable[state].action(cmd);
        switch (state) {
            case STATE_NOAUTH:
            case STATE_USER:
            case STATE_PROCESS:
            case STATE_INVALID:
            case STATE_QUIT:
            default:
                break;
        }
    }
}

