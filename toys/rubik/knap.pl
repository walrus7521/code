#!/usr/bin/perl

use POSIX;

$capacity = 4; # lbs

#               name,     wt,  value
my @items = ( ['guitar', '1', '1500'], 
              ['stereo', '4', '3000'], 
              ['laptop', '3', '2000'], 
              ['iphone', '1', '2000'] ); 

$num_rows = @items;
$num_cols = @{ $items[0] };

# capacity columns independent of column index
@col_wts = (1, 2, 3, 4);

@grid = ( [1, 0, 0, 0],
          [0, 1, 0, 0], 
          [0, 0, 1, 0], 
          [0, 0, 0, 1], 
        );

# integer version
sub TO_INDEX {
    $x = shift;
    return (ceil($x-1)) # round
}

sub max {
    $x = shift;
    $y = shift;
    if ($x > $y) {
        return $x;
    }
    return $y;
}

sub prev_max {
    $row = shift;
    $col = shift;
    if ($row >= 1) {
        return $grid[$row-1][$col]
    }
    return 0;
}

sub show_items {
    # Printing items from the array 
    printf("rows: %d\n", $num_rows);
    printf("cols: %d\n", $num_cols);
    foreach my $row (@items) {
        print($row->[0], " ", $row->[1], " ", $row->[2], "\n");
    }
}

sub show_grid {
    for (my $row = 0; $row < $num_rows; $row++) {
        for (my $col = 0; $col < $capacity; $col++) {
            print($grid[$row][$col], " ");
        }
        print("\n");
    }
}

sub knap {
    for (my $row = 0; $row < $num_rows; $row++) {

        $name      = $items[$row][0];
        $wt_item   = int($items[$row][1]);
        $val_item  = int($items[$row][2]);

        for (my $col = 0; $col < $capacity; $col++) {

            $col_wt = $col_wts[$col];
            $old_max_value = prev_max($row, $col);
            $max_val = max($old_max_value, $val_item);

            print("=======================\n");
            print($name, ': ', $row, ' ', $col, ' ', $val_item, "\n");

            if ($wt_item < $col_wt) {
                $residual_wt = $col_wt - $wt_item;
                $residual_wt_col = TO_INDEX($residual_wt);
                print('res: ', $residual_wt, 'col: ', $residual_wt_col, "\n");
                $new_max_value = $val_item + prev_max($row, $residual_wt_col);
                if ($new_max_value > $old_max_value) {
                    $grid[$row][$col] = $new_max_value;
                }
                else {
                    $grid[$row][$col] = $old_max_value;
                }
            }
            elsif ($wt_item == $col_wt) {
                $grid[$row][$col] = $max_val;
            }
            else { # wt_item > col_wt
                $grid[$row][$col] = $old_max_value;
            }
            show_grid()        
        }
    }
}

sub main() {
#   show_items();
    knap();
    print("++++++++++++++++++++++++\n");
    show_grid();

}

main();




