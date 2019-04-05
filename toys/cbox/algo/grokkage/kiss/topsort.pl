#!/usr/bin/perl

my $n = 4;
my @a = ([ 0,  1,  1,  0 ], 
         [ 0,  0,  0,  1 ], 
         [ 0,  0,  0,  1 ], 
         [ 0,  0,  0,  0 ]);

sub topsort {
    $i, $j, $k, @indeg[32], @flag[32], $count=0;

    for ($i = 0; $i < $n; $i++) {
        @indeg[$i]=0;
        @flag[$i]=0;
    }

    for($i = 0; $i < $n; $i++) {
        for($j = 0; $j < $n; $j++) {
            @indeg[$i] += $a[$j][$i];
        }
    }

    print"\ntopsort: ";
    while ($count < $n) {
        for ($k = 0; $k < $n; $k++) {
            if ((@indeg[$k] == 0) && (@flag[$k] == 0)) {
                printf("%d ", ($k+1));
                @flag[$k] = 1;
            }
 
            for($i = 0; $i < $n; $i++) {
                if ($a[$i][$k] == 1) {
                    @indeg[$k]--;
                }
            }
        }
        $count++;
    }
   
}

topsort;

