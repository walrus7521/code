from shutil import copyfile
import re
import sys

src_was  = "DevBr/"
src_is   = "HdgHold/"
dest_was = "M:/prj/prs/HdgHoldMerge/TEST/WAS/."
dest_is  = "M:/prj/prs/HdgHoldMerge/TEST/IS/."

for line in sys.stdin:
    if line:
        line = line.rstrip()
        #print line
        cap = re.match(r'.*(SWDev.*)', line, re.I | re.S)
        if (cap):
            print cap.group(1)
            from_was = "c:/helitrak/" + src_was + cap.group(1)
            to_was = "M:/prj/prs/HdgHoldMerge/TEST/WAS/" + cap.group(1)
            from_is  = "c:/helitrak/" + src_is + cap.group(1)
            print "from was: " + from_was
            print "to was  : " + dest_was
            print "from is : " + from_is
            print "to is   : " + dest_is
            copyfile(from_was, to_was)
            #to   = $dest_was;
            #print "From: $from\n";
            #print "To  : $to\n";
            #copy($from, $to) or print "copy failed: $! -> $1\n";
            #copy("sourcefile","destinationfile") or die "Copy failed: $!";        
            #print "was: $from\n";

            #$from = "c:/helitrak/$src_is/$1";
            #$to   = $dest_is;
            #print "From: $from\n";
            #print "To  : $to\n";
            #copy($from, $to) or print "copy failed: $! -> $1\n";
            #print "is: $from\n\n";


#copyfile(src, dst)

#use File::Copy;

#$src_was  = "DevBr";
#$src_is   = "HdgHold";
#$dest_was = "WAS";
#$dest_is  = "IS";

#$from = "";
#$to = "";
#while (<>) {
#    if ($_ =~ m/(SWDev.*)/i) {
#        $from = "c:/helitrak/$src_was/$1";
#        $to   = $dest_was;
#        #print "From: $from\n";
#        #print "To  : $to\n";
#        copy($from, $to) or print "copy failed: $! -> $1\n";
#        #copy("sourcefile","destinationfile") or die "Copy failed: $!";        
#        #print "was: $from\n";
#
#        $from = "c:/helitrak/$src_is/$1";
#        $to   = $dest_is;
#        #print "From: $from\n";
#        #print "To  : $to\n";
#        copy($from, $to) or print "copy failed: $! -> $1\n";
#        #print "is: $from\n\n";
#        
#    }
#}
