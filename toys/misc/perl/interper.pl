#!/usr/bin/perl

# this is faster (written in C) than Text::CSV which was written in Perl
use Text::CSV_XS;

@header;

sub read_csv {
    my $line = 0;
    my $csv = Text::CSV_XS->new;
    my @data;
    while (<STDIN>) {
        if ($line eq 0) {
            print "here\n";
            $csv->parse($_);
            push @header, [$csv->fields];
        } else {
            $csv->parse($_);
            push @data, [$csv->fields];
        }
        $line++;
    }
    return \@data;
}

sub write_csv {
}

my $data = read_csv;

foreach (@header) {
    print "$_->[0], $_->[1], $_->[2], $_->[3], $_->[4], $_->[5], $_->[6], $_->[7], $_->[8], \n";
}

my $row = 0;
foreach (@$data) {
    print "Speed $_->[0], FpPro $_->[2]\n";
    $matrix[$row][0] = sprintf("%f", $_->[0]);
    $matrix[$row][1] = sprintf("%f", $_->[1]);
    $matrix[$row][2] = sprintf("%f", $_->[2]);
    $matrix[$row][3] = sprintf("%f", $_->[3]);
    $matrix[$row][4] = sprintf("%f", $_->[4]);
    $matrix[$row][5] = sprintf("%f", $_->[5]);
    $matrix[$row][6] = sprintf("%f", $_->[6]);
    $matrix[$row][7] = sprintf("%f", $_->[7]);
    $matrix[$row][8] = sprintf("%f", $_->[8]);
    $row++;
}

for ($row = 0; $row < 4; $row++) {
    for ($col = 1; $col < 9; $col++) {
        printf("[%d][%d] => %f\n", $row, $col, $matrix[$row][$col]);
        $linterp[$row][$col] = ($matrix[$row][$col] - $matrix[$row+1][$col]) / ($matrix[$row][0] - $matrix[$row+1][0])
    }
}

for ($row = 0; $row < 4; $row++) {
    for ($col = 1; $col < 9; $col++) {
        printf("2dl[%d][%d] => %f\n", $row, $col, $linterp[$row][$col]);
    }
}
#$linterp[][];
# col 2dlinterp is a column of data (iterate the row)
#    LINTERP_STRUCT p = { 4, {{  0.0f, 6.0f,  0.07500f},
#                             { 40.0f, 9.0f, -0.17500f},
#                             { 80.0f, 2.0f,  0.03750f},
#                             {120.0f, 3.5f,  0.02917f},
#                             {  0.0f, 0.0f,  0.00000f}, {0}}};
#
for ($col = 1; $col < 9; $col++) {
    printf("LINTERP_STRUCT p = { %d, {\n");
    for ($row = 0; $row < 4; $row++) {
        printf("{%.5f, %.5f, %.5f},\n", $matrix[$row][0], $matrix[$row][$col], $linterp[$row][$col]);
    }
    printf("{0.0000, 0.0000, 0.0000},\n");
}


