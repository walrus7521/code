#!/usr/bin/perl

use Data::HexDump;

#my $buf = "foo\0bar";
#print HexDump $buf;
#  or
#  my $f = new Data::HexDump;
#  $f->data($buf);
#  print $f->dump;
#  or
#  my $f = new Data::HexDump;
#  $f->file($file2dump);
#  $f->block_size(1024);

# (1) quit unless we have the correct number of command-line args
$num_args = $#ARGV + 1;
if ($num_args != 1) {
    print "\nUsage: dump.pl file_name\n";
    exit;
}
 
# (2) we got the command line args, so assume they are the
$file2dump=$ARGV[0];
 
print "dumping: $file2dump\n";

#my $file2dump = "20160204-115649_COMM_20_CAN_TX0_RX16.bin";
my $fh = new FileHandle $file2dump;
my $f = new Data::HexDump;
$f->fh($fh);
$f->block_size(1024);
print while $_ = $f->dump;
close $fh;


