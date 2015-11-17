#!/bin/bash

# usage get_alua $device_name
# device_name => sda, without /dev prepended
get_alua_state()
{
    dev=$1
    state="disabled"
    IFS=$'\n' alua=`sg_rtpg  /dev/$dev 2> /dev/null`;
    for s in $alua
    do
        rx="target port group asymmetric access state : 0x([[:digit:]]+)"
        if [[ "$s" =~ $rx ]] ; then
            state="${BASH_REMATCH[1]}"
            echo "alua state: $state"
        fi
    done
}

get_dev_name() 
{
    #dm = $1
    #major_minor = $2
    echo "name: $1 mj_mn: $2"
    #printf "get name for %s [%s]\n", dm, major_minor;
    #cmd = "ls -lsa /sys/class/block/" dm "/slaves"
    #printf "cmd %s\n", cmd;
    #while (cmd | getline line) {
    #    if (match(line, "sd.*target.*block(.*)", ary)) {
    #        #printf "device: %s\n", ary[1];
    #        cmd2 = "cat /sys/class/block/" dm "/slaves" ary[1] "/dev";
    #        #printf "cmd2: %s\n", cmd2;
    #        cmd2 | getline line2;
    #        #printf "compare %s <=> %s\n", line2, major_minor;
    #        if (line2 == major_minor) {
    #            #printf "got a match: major minor: %s\n", line2;
    #            return "/dev" ary[1];
    #        }
    #    }
    #}
    #close(cmd);
    #return "disabled"
}

let state=0 #global variable yuk
prdevstatus2()
{
    IFS=$'\n' mplist=`multipath -ll 2>/dev/null`
    for s in $mplist
    do
        rx="(mpath.*)\((.*)\) (dm-[[:digit:]]) "
        if [[ "$s" =~ $rx ]] ; then
            name="${BASH_REMATCH[1]}"
            id="${BASH_REMATCH[2]}"
            dev="${BASH_REMATCH[3]}"
            echo "path: $name, id: $id, dev: $dev"
        fi
        rx="size=([[:digit:]]+[G|M]) "
        if [[ "$s" =~ $rx ]] ; then
            size="${BASH_REMATCH[1]}"
            echo "size: $size"
        fi
        rx="policy='(.*)' prio=([[:digit:]]+) status=([[:alpha:]]+)"
        if [[ "$s" =~ $rx ]] ; then
            policy="${BASH_REMATCH[1]}"
            priority="${BASH_REMATCH[2]}"
            status="${BASH_REMATCH[3]}"
            echo "policy: $policy, priority: $priority, status: $status"
        fi
        rx="- ([[:print:]]+:[[:print:]]+:[[:print:]]+:[[:print:]]) ([[:alpha:]]+) ([[:digit:]]+):([[:digit:]]+)"
        if [[ "$s" =~ $rx ]] ; then
            path="${BASH_REMATCH[1]}"
            dev="${BASH_REMATCH[2]}"
            mj="${BASH_REMATCH[3]}"
            mn="${BASH_REMATCH[4]}"
            if [[ "$path" =~ ".*#" ]] ; then
                echo "dev: faulty"
            else
                get_alua_state $dev
                case "$state" in
                    "00")
                        state="active"
                        ;;
                    "01")
                        ;;
                    "02")
                        ;;
                    "03")
                        state="unavailable"
                        ;;
                    *)
                        state="unknown"
                        ;;
                esac
                echo "path: $path, dev: $dev, mj:mn [$mj:$mn], alua: $state"
            fi
            echo ""
        fi
    done
    echo ""
}

prdevstatus()
{
    IFS=$'\n' mplist=`dmsetup table 2>/dev/null`
    for s in $mplist
    do
        IFS=' ' a=( $s )
        name=${a[0]}
        nr_paths=${a[10]}
        echo "path: $name, num paths: $nr_paths, dev: $dev"
        for ((i=0,n=12;i<nr_paths;i++,n+=2)); do
            dev=${a[$n]}
            echo "dev[$i]: = $dev"
            get_dev_name $name, $dev
        done
    done
}

usage()
{
    echo ""
    echo "qs-alua is a multipath ALUA utility for displaying and monitoring paths"
    echo ""
    echo "Usage:"
    echo "	qs-alua <command>"
    echo "      commands:   "
    echo "          portinfo"
    echo "          monpoolstatus"
    echo "          mondevstatus"
    echo "          monpaths"
    echo "          printdg"
    echo ""
    echo "Examples:"
    echo "	qs-alua pools"
    echo ""
    echo "Optional:" 
    echo ""
}

# TODO:
# 
#   portinfo -f       => 
#   monpoolstatus -f  => zpool status, qs pool-list
#   mondevstatus -f   => qs-iofence devstatus
#   monpaths          => systool -c fc_host -v
#   printdg & preferred port status
#

#must specify an operation
if [ "$1" == "" ]; then
    usage
    exit 1
else
    OPERATION=$1
fi

echo "$OPERATION"
case "$OPERATION" in

    "portinfo")
        LOGGING=""
        EXECUTED=$OPERATION
        ;;

    "monpoolstatus")
        LOGGING=""
        EXECUTED=$OPERATION
        ;;

    "mondevstatus")
        LOGGING=""
        EXECUTED=$OPERATION
        ;;

    "monpaths")
        LOGGING=""
        EXECUTED=$OPERATION
        ;;

    "printdg")
        LOGGING=""
        EXECUTED=$OPERATION
        ;;
        
    *)
        echo "???"
        ;;

esac

exit

