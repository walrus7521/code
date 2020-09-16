#!/usr/bin/perl

$KD_PATH = '"/Program Files (x86)/Windows Kits/10/Debuggers/x64/kd.exe"';
$SCRIPT = './analyze.kd';

sub run_kd_script {
    my $dump_file = shift;
    $script = '$$< ' . $SCRIPT;
    $cmd = $KD_PATH . ' -z ' . $dump_file . ' -c ' . $script;
    system($cmd);
    print("$cmd\n");
}

sub main() {
    run_kd_script("MEMORY.dmp");
}
    
main()

