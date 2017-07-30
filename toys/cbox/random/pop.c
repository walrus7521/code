#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_ARGS 8
#define LINE_SIZE 256

enum {
    STATE_USER   = 0,
    STATE_PASS   = 1,
    STATE_LIST   = 2,
    STATE_RETR   = 3,
    STATE_QUIT   = 4,
    MAX_STATES
};

int actionUser(char **args);
int actionPass(char **args);
int actionList(char **args);
int actionRetr(char **args);
int actionQuit(char **args);

struct
{
    int  currentState;
    char *command;
    int  stateIfSucceed;
    int  stateIfFailed;
    int  (*action)(char **);
} actionTable[] =
{
    {STATE_USER, "USER", 1, 3, actionUser},
    {STATE_PASS, "PASS", 2, 3, actionPass},
    {STATE_LIST, "LIST", 2, 3, actionList},
    {STATE_RETR, "RETR", 2, 4, actionRetr},
    {STATE_QUIT, "QUIT y/n", 4, 2, actionQuit},
    {0, 0, 0, 0, 0}
};

void show(char **args)
{
    while (*args != NULL) {
        printf("arg: %p, %s\n", *args, *args);
        *args++;
    }
}

void get_command(char **data, char *cmd)
{
    char *buffer = malloc(LINE_SIZE);
    char *line = buffer;
    printf("$ %s ", cmd);
    if (fgets(buffer, LINE_SIZE, stdin) != NULL) {
        int index = 0;
        int len = strlen(buffer);
        line[len-1] = '\0';
        printf("%s\n", line);
        char *token = strtok(line, " ");
        while (token != NULL) {
            data[index++] = strdup(token);
            token = strtok(NULL, " ");
        }
        data[index] = NULL;
    }
    free(buffer);
}

int actionUser(char **args) { 
    printf("actionUser\n");
    if (strcmp(args[0], "bartb") == 0) {
        printf("actionUser: success\n");
        return actionTable[STATE_USER].stateIfSucceed;
    } else {
        printf("actionUser: failed\n");
        return actionTable[STATE_USER].stateIfFailed;
    }
}
int actionPass(char **args) { 
    printf("actionPass\n");
    if (strcmp(args[0], "donkey") == 0) {
        printf("actionPass: success\n");
        return actionTable[STATE_PASS].stateIfSucceed;
    } else {
        printf("actionPass: failed\n");
        return actionTable[STATE_PASS].stateIfFailed;
    }
}
int actionList(char **args) { 
    printf("actionList\n");
    if (NULL == args[0]) {
        printf("actionList: failed\n");
        return actionTable[STATE_LIST].stateIfFailed;
    } else {
        printf("actionList: success\n");
        return actionTable[STATE_LIST].stateIfSucceed;
    }
}
int actionRetr(char **args) { 
    printf("actionRetr\n");
    if (NULL == args[0]) {
        printf("actionRetr: failed\n");
        return actionTable[STATE_RETR].stateIfFailed;
    } else {
        printf("actionRetr: success\n");
        return actionTable[STATE_RETR].stateIfSucceed;
    }
}
int actionQuit(char **args) { 
    printf("actionQuit\n");
    if (strcmp(args[0], "y") == 0) {
        printf("actionQuit: success\n");
        exit(0);
    } else {
        printf("actionQuit: failed\n");
        return actionTable[STATE_QUIT].stateIfFailed;
    }
}

int main()
{
    int command;
    char** args = calloc(MAX_ARGS, LINE_SIZE);
    int state = STATE_USER;
    while (true) {
        get_command(args, actionTable[state].command);
        state = actionTable[state].action(args);
    }
}

