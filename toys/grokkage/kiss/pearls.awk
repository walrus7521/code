#!/usr/bin/awk -f 

# process file `names`
function name_errors(e)
{
    if (e > 0) print "total errors: ", e
}

function add_name(nm)
{
    name[nm] = 1;
}

function show_names() 
{
    for (i in name) {
        for (j in name) {
            print i, j
        }
    }
}


BEGIN           { }
# name filter
#    length($1) > 10 { e++; print "long name in line", NR }
#    NF != 1         { e++; print "bad name count in line", NR }
#    add_name($1)
#    test_names($1, NR, NF);
# fsm
    run == 1 { print out[s,$1]; s = trans[s,$1] }
    run == 0 { if ($1 == "start") { run = 1; s = $2 }
               else { trans[$1,$2] = $3; out[$1,$2] = $4 }
             }
END {} #{ name_errors(e); show_names() }

