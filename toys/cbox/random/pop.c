#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

enum {
    STATE_NOAUTH    = 0,
    STATE_USER      = 1,
    STATE_PROCESS   = 2,
    STATE_INVALID   = 3,
    STATE_QUIT      = 4,
    MAX_STATES
};

int actionUser(char **args) { return 0; }
int actionQuit(char **args) { return 0; }
int actionPass(char **args) { return 0; }
int actionList(char **args) { return 0; }

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


int get_command(char **args, int state)
{
    int tlen = sizeof(actionTable)/sizeof(actionTable[0]);
    int i;
    if (strcmp(args[0], actionTable[i].command) == 0) {
        return actionTable[state].stateIfSucceed;
    } else {
        return actionTable[state].stateIfFailed;
    }
    return 1;
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

#define MAX_ARGS 8
#define LINE_SIZE 256
int main()
{
    char *buffer = malloc(LINE_SIZE);
    char *line = buffer;
    int state = STATE_NOAUTH;
    int command;
    printf("$ ");
    while (fgets(buffer, LINE_SIZE, stdin) != NULL) {
        int index = 0;
        int len = strlen(buffer);
        char **data;
        data = calloc(MAX_ARGS, LINE_SIZE);
        line[len-1] = '\0';
        printf("%s\n", line);
        //printf("%d: line: %s", (int) read, pline);
        char *token = strtok(line, " ");
        while (token != NULL) {
            data[index++] = strdup(token);
            token = strtok(NULL, " ");
        }
        command = get_command(data);
        printf("$ ");
    }
    free(buffer);
}

