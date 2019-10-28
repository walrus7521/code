#!/usr/bin/env perl

use strict;
use warnings;

my @finders = (
    # MCP
    "TELEMETRY_LOG_STRUCT",
    "MCP_COEFF_STRUCT",
    "CONFIG_MCP_STRUCT",
    # ADP
    "TELEMETRY_LOG_STRUCT_ADP",
    "ADP_CLAW_COEFF_STRUCT",
    "CONFIG_ADP_STRUCT"
);

my @types = (
    "STRUCT",
    "Flags",
    "F32",
    "U8",
    "U16",
    "U32",
    "S8",
    "S16",
    "S32",
    "BOOLEAN"
);

my %native_types = (
    "float"          => "F32",
    "signed char"    => "S8",
    "signed short"   => "S16",
    "signed long"    => "S32",
    "unsigned char"  => "U8",
    "unsigned short" => "U16",
    "unsigned long"  => "U32",
);

my @file = (<stdin>);

sub find_type {
    my $line = shift;
    my $type = "INVALID";
    foreach(@types) {
        if ($line =~ /$_/i) {
            $type = $_;
            last;
        }
    }
    return $type;
}

sub go_native {
    my $line = shift;
    my $type = "INVALID";
    (my $typ) = ($line =~ /.* \|\W+(\w+)/);
    foreach my $ln (@file) {
        if ($ln =~ /FieldDecl.*$typ/) {
            for my $native (keys %native_types) {
                if ($ln =~ /\b$native\b/i) { # match whole word
                    $type = $native_types{$native};
                }
            }
        }
    }
    return $type;
}

foreach my $find_file (@finders) {
    for (my $i = 0; $i < scalar(@file); $i++) {
        my $line = $file[$i];
        if ($line =~ /(\d+) \| (\bstruct \b)?(\b$find_file\b)/) {
            if (defined($2)) { $line =~ s/struct //g; } # remove struct keyword 
            do {
                if (find_type($line) eq "INVALID") {
                    my $ty = go_native($line);
                    my ($pre, $white, $var_type, $var_name) = ($line =~ /(.*) \| (\W+) (\w+)\W+(\w+)/);
                    printf("$pre | $white $ty $var_name\n");
                } else {
                    printf("$line");
                }
            } while ($line = $file[++$i] and $line !~ /sizeof/);
            printf("$line\n");
        }
    }
}

