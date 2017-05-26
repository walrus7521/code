  #!/bin/bash


Quit()
{
    echo Function: Quit
}

Wusup()
{
    echo Function: Wusup
    if [ -z "$1" ]                           # Is parameter #1 zero length?
    then
        echo "-Parameter #1 is zero length.-"  # Or no parameter passed.
    else
        echo "-Parameter #1 is \"$1\".-"
    fi

    variable1=${1-$DEFAULT}                  #  What does
    echo "variable1 = $variable1"            #+ parameter substitution show?
                                            #  ---------------------------
                                            #  It distinguishes between

    if [ "$2" ]
    then
        echo "-Parameter #2 is \"$2\".-"
    fi

    variable2=${2-$DEFAULT}                  #  What does
    echo "variable2 = $variable2"            #+ parameter substitution show?

}

Hello()
{
    echo Function: Hello
}


# this appears to be a hash
OPTIONS="Hello Wusup Quit"
select opt in $OPTIONS; do
    if [ "$opt" = "Quit" ]; then
        Quit
        #echo done
        exit
    elif [ "$opt" = "Wusup" ]; then
        Wusup "Dude" 42
        #echo Wusup
    elif [ "$opt" = "Hello" ]; then
        Hello
        #echo Hello World
    else
        clear
        echo bad option
    fi
done
