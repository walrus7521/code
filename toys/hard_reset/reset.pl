#!/usr/bin/env perl

use Data::Dumper;

# https://perldoc.perl.org/perlreftut.html
#
sub get_reset {
    sub hard_reset { print "reset\n"; }
}

sub create_entry {
    my ($year, $category, $name) = @_;
    # create anonymous array
    $entry = [$name, $category, $name];
    # add these to the 2 indices
    push( @{$year_index {$year}}, $entry); # by year
    push( @{$category_index{$category}}, $entry); # by category
}

sub create_lookup {
    my ($file) = @_;
    print("file: $file\n");
    open(F, $file) || die "can't open $file: $!";
    %category_index = (); %year_index = ();
    while ($line = <F>) {
        chomp $line;
        ($year, $category, $name) = split(/:/, $line);
        &create_entry($year,  $category, $name) if $name;
    }

}

sub print_all {
    foreach $year (sort keys %year_index) {
        print("year: $year\n");
        foreach $entry (@{$year_index{$year}}) {
            print("\t", $entry->[1], " : ", $entry->[2], "\n");
        }
    }
}

sub get_mats {
    my ($filename) = @_;
    open(F, $filename) || die "can't open $filename: $!";
    while ($line = <F>) {
        chomp($line);
        next if $line =~ /^\s*$/; # skip blank lines
        if ($line =~ /^([A-za-z]\w*)/) {
            $matrix_name = $1;
            #print("mat: $matrix_name\n");
        } else {
            my (@row) = split(/\s+/, $line);
            #print("@row\n");
            push(@{$matrix_name}, \@row);
        }
    }
    close(F);
}

sub mat_rows_cols_counts {
    my ($r_mat) = @_;
    my $num_rows = @$r_mat;
    my $num_cols = @{$r_mat->[0]};
    return ($num_rows, $num_cols);
}

sub mat_mul {
    my ($r_mat1, $r_mat2) = @_;
    my ($r_product);
    my ($r1, $c1) = mat_rows_cols_counts($r_mat1);
    my ($r2, $c2) = mat_rows_cols_counts($r_mat2);
    die "need same: $c1 and $r2" unless ($c1 == $r2);
    for ($i = 0; $i < $r1; $i++) {
        for ($j = 0; $j < $c2; $j++) {
            $sum = 0;
            for ($k = 0; $k < $c1; $k++) {
                $sum += $r_mat1->[$i][$k] * $r_mat2->[$k][$j];
            }
            $r_product->[$i][$j] = $sum;
            print("[$i, $j] = $sum\n");
        }
    }
    $r_product;
}

sub main() {
    #print("dude: "); <> or die "you suck";
    $a = 42;
    $ra = \$a;
    $$ra += 2;
    print("$a\n");

    %sue = (
        'name'      => 'Sue',
        'age'       => '45',
        'children'  => [
                            {
                                'name'  => 'John',
                                'age'   => '20'
                            },
                            {
                                'name'  => 'Peggy',
                                'age'   => '16'
                            }
                       ]
    );
    #print(values(%sue), "\n");
    print("child 1: ", $sue{children}[0]{age}, "\n");

    ## weird stuff
    $x = 10;
    $var = "x";
    $$var = 43; # var is not a ref, but resolves to the symbol 'x'
    print("$x\n");

    $uar = "x";
    @$uar = (1,2,3); # resolves to 'x'
    print("@x\n");

    ## very cool and useful
    $var_name = "debug_level";
    $value = 47;
    $$var_name = $value; # creates and resolves to scalar symbol 'debug_level'
    $var_name = "verbosity";
    $value = 17;
    $$var_name = $value; # creates and resolves to scalar symbol 'verbosity'
    print("debug_level = $debug_level verbosity: $verbosity\n");

    ${'the_dude'} = 117; # creates a scalar ref to 'the_dude'
    print("=> $the_dude\n");

    %foo = (
        a   => 10,
        str => "good"
    );
    print($foo{a}, " is ", $foo{str}, "\n");

    &get_mats("mats");
    $rm1 = \@MAT1;
    $rm2 = \@MAT2;
    print("@{$rm1->[0]}\n");
    print("@{$rm2->[0]}\n");
    $product = &mat_mul($rm1, $rm2);

    my $nrows = @$product;
    my $ncols = @{$product};

    print("product: $nrows, $ncols\n");
    print("       : @{$product->[0]}\n");
    print("       : @{$product->[1]}\n");

    %matrix = {};
    $matrix{0}{2} = 100;
    $matrix{1}{0} = 200;
    $matrix{2}{1} = 300;
    $rm3 = \%matrix;
    print("1: $rm3->{0}{2}\n");
    print("2: $rm3->{1}{0}\n");
    print("3: $rm3->{2}{1}\n");

    %base_hours = (
        mon => 0, tue => 12, wed => 24, thu => 36, fri => 48
    );
    $day = "ThU";
    $base = $base_hours{lc $day}; # lc is lower case
    print("$base\n");

    &create_lookup("data.txt");
    &print_all();
    print Dumper(\%year_index);}

&main();

