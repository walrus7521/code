listmpdevs()
{
    dmsetup table | awk '
    
        function get_alua_state(dev) {
            #printf "get alua for: %s\n", dev;
            cmd = "sg_rtpg " dev;
            while (cmd | getline line) {
                #print ": %s\n", line;
                regex = "target.*port.*group.*asymmetric.*access.*state.*: (0x.*)";
                if (match(line, regex, ary)) {
                    #print "got a match";
                    state = ary[1];
                    switch (state) {
                        case "0x00": return "OPTIMIZED";
                        case "0x01": return "NON-OPTIMIZED";
                        case "0x02": return "STANDBY";
                        case "0x03": return "UNAVAILABLE";
                        case "0x04": return "LBA_DEPENDENT";
                        case "0x0e": return "OFFLINE";
                        case "0x0f": return "TRANSITIONING";
                        default:     return "UNKNOWN";
                    }
                    #return ary[1];
                }
            }
            return "DISABLED";
        }
    
        function get_dev_name(dm, major_minor) {
            #printf "get name for %s [%s]\n", dm, major_minor;
            cmd = "ls -lsa /sys/class/block/" dm "/slaves"
            #printf "cmd %s\n", cmd;
            while (cmd | getline line) {
                if (match(line, "sd.*target.*block(.*)", ary)) {
                    #printf "device: %s\n", ary[1];
                    cmd2 = "cat /sys/class/block/" dm "/slaves" ary[1] "/dev";
                    #printf "cmd2: %s\n", cmd2;
                    cmd2 | getline line2;
                    #printf "compare %s <=> %s\n", line2, major_minor;
                    if (line2 == major_minor) {
                        #printf "got a match: major minor: %s\n", line2;
                        return "/dev" ary[1];
                    }
                }
            }
            close(cmd);
            return "disabled"
        }
    
        function get_dev2(path) {
            ret="nodev"
            cmd = "ls -lsa /dev/mapper/ " path
            while (cmd | getline line) {
                regex = ".*" path ".*(dm-.*)";
                if (match(line, regex, ary)) {
                    ret = ary[1];
                    break;
                }
            }
            close(cmd);
            return ret
        }
    
        BEGIN{
            print "name", "start", "length", "dev", "select", "policy", "paths"
            print "====", "=====", "======", "===", "======", "======", "====="
        } {
            {path=$1} {start=$2} {len=$3} {pol=$4} {sel=$9} {np=$11}
            if (path ~ "mpath") {
                path2 = substr(path, 1, 6); # strip the colon!!
                nm = get_dev2(path2)
                if (nm != "nodev") {
                    print path, start, len, nm, pol, sel, np
                    for (i = 0; i < np; i++) {
                        switch (i) {
                            case 0: {
                                blk_nm = get_dev_name(nm, $13);
                                alua = get_alua_state(blk_nm);
                                printf "--> %s %s %s\n", $13, blk_nm, alua; break
                            }
                            case 1: {
                                blk_nm = get_dev_name(nm, $15);
                                alua = get_alua_state(blk_nm);
                                printf "--> %s %s %s\n", $15, blk_nm, alua; break
                            }
                       }
                    }
                }
            } else {
                print "bummer"
            }
            
        }' | column -t

}

listmpdevs
