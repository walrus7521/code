#!/usr/bin/env perl

@finders = (
    "TELEMETRY_LOG_STRUCT",
    "MCP_COEFF_STRUCT"
);

@file = ();

while ($line = <stdin>) {
    if ($line =~ /(\d+) \| @finders[0]/) {
        do {
            printf("$line");
            $line = <$stdin>;
        } while ($line = <stdin> and $line !~ /sizeof/);
        printf("$line\n");
    } elsif ($line =~ /(\d+) \| @finders[1]/) {
        do {
            printf("$line");
            $line = <$stdin>;
        } while ($line = <stdin> and $line !~ /sizeof/);
        printf("$line\n");
    }
}

