#!/usr/bin/awk -f

# process file `names`
function name_errors(e) {
    if (e > 0) print "total errors: ", e
}

function add_name(nm) {
    name[nm] = 1;
}

function show_names() {
    for (i in name) {
        for (j in name) {
            print i, j
        }
    }
}


BEGIN           { }
    length($1) > 10 { e++; print "long name in line", NR }
    NF != 1         { e++; print "bad name count in line", NR }
    add_name($1)
END                 { name_errors(e); show_names() }

