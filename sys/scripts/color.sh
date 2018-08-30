#!/bin/bash

err_out()
{
    echo "fatal error [function: $1, line: $2, status: $3]"
    exit 1
}

echo -e "\e[1;30mThis is gray text\e[0m"
echo $LINENO
echo -e "\e[1;31mThis is red text\e[0m"
echo -e "\e[1;32mThis is green text\e[0m"
echo -e "\e[1;33mThis is yellow text\e[0m"
echo -e "\e[1;34mThis is blue text\e[0m"
echo -e "\e[1;35mThis is purple text\e[0m"
echo -e "\e[1;36mThis is cyan text\e[0m"
echo -e "\e[1;37mThis is white text\e[0m"
echo -e "\e[1;40mThis is white w/gray bgd\e[0m"
echo -e "\e[1;41mThis is white w/red bgd\e[0m"
echo -e "\e[1;42mThis is white w/green bgd\e[0m"
echo -e "\e[1;43mThis is white w/yellow bgd\e[0m"
echo -e "\e[1;44mThis is white w/blue bgd\e[0m"
echo $LINENO
echo -e "\e[1;45mThis is white w/purple bgd\e[0m"
echo -e "\e[1;46mThis is white w/cyan bgd\e[0m"
echo -e "\e[1;47mThis is white w/white bgd\e[0m"


#red_msg()
#{
#    MSG="\e[1;31m$1\e[0m"
#    echo -e $MSG
#}

GRAY=30
RED=31
BLUE=34
GREEN=32
YELLOW=33
PURPLE=35
CYAN=36
WHITE=37
WHITE_ON_GRAY=40
WHITE_ON_RED=41
WHITE_ON_GREEN=42
WHITE_ON_YELLOW=43
WHITE_ON_BLUE=44
WHITE_ON_PURPLE=45
WHITE_ON_CYAN=46
WHITE_ON_WHITE=47

msg()
{
    MSG="\e[1;$1m$2\e[0m"
    echo -e $MSG
}

msg $RED "wusup dawg"
msg $BLUE "blue dawg"
msg $GREEN "its a green day"

func() {
    fun="func"
    err="dude"
    line=$LINENO
    err_out $fun $line $err
}

func


