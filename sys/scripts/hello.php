#!/usr/bin/php

<?php print "Hello World!\n"; ?>
<?php 
    $i = 0; 
    while ( $i < 4 ) { 
        print $i."n\n"; 
        sleep(1); 
        $i++; 
    } 
?>

<?php 
    fwrite(STDOUT, "Please enter your name:"); 
    $name = fread (STDIN, 8);
    print $name."\n"; 
    ?>


<?php
    $STDOUT = fopen("php://stdout", "w");
    fwrite($STDOUT, "Output #1.");
    fclose($STDOUT);
?>

<?php
    $lines = split("\n", file_get_contents("php://stdin", "r"));
    shuffle($lines);
    foreach ($lines as $line) {
        if ($line !== "") {
            echo "$line\n";
        }
    }
?>


