<?php declare(strict_types=1); // strict requirement

    function addNumbers(float $a, float $b) : float {
        return $a + $b;
    }
    echo addNumbers(1.2, 5.2); 

    function DB_Dude(string $filename)
    {
        echo("debug: $filename <br>"); // <br> is CRLF

        $file = fopen( $filename, "r" );
        
        if( $file == false ) {
            echo ( "Error in opening file" );
            exit();
        }
         
        $filesize = filesize( $filename );
        $filetext = fread( $file, $filesize );
        fclose( $file );
         
        echo ( "File size : $filesize bytes" );
        echo ( "<pre>$filetext</pre>" );
    }

    function DB_Dude2(int $key)
    {
        $output_pl = shell_exec("/usr/bin/perl   ./scrape.pl");
        $output_py = shell_exec("/usr/bin/python ./scrape.py");
        return $output_py;
    }

    $sumPHP = 42;
    function Get_Sum(int $inc) {
        global $sumPHP;
        $sumPHP+=$inc;
        return $sumPHP;
    }

    class Student {
        public function __construct($first_name, $last_name) {
            $this->first_name = $first_name;
            $this->last_name = $last_name;
        }
        public function say_name() {
            echo "My name is " . $this->first_name . " " . $this->last_name . ".\n";
        }
        public function get_age() : int {
            return 42;
        }
    }


?>

<html>
    <head>
        <title>Dude PHP!!</title>
    </head>

    <body>

        <?php 
            echo DB_Dude("tmp.txt"); 
            echo DB_Dude2(42); 

            $alex = new Student("Alexy", "Jones");
            $alex->say_name();
            echo $alex->get_age();

            //phpinfo(); 
         ?>

        <script type="text/javascript">

            var sumJS = 0;
            sumJS = <?php echo Get_Sum(7); ?>;
            alert("dude, you suck " + sumJS + " ...");
            for (let i = 0; i < 4; i++) {
                var inc = i; // need to marshall this to PHP??
                <?php $phpInc = 1; ?>
                sumJS = <?php echo Get_Sum($phpInc); ?>;
                document.write("<br>" + i + " = " + sumJS);
            }

        </script>


    </body>

</html>

