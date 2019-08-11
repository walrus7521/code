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

    $sumPHP = 42.5;

?>

<html>
 <head>
  <title>PHP Test2</title>
 </head>
 <body>
 <?php 
    echo DB_Dude("tmp.txt"); 
    echo DB_Dude2(42); 

    $alex = new Student("Alex", "Jones");
    $alex->say_name();
    echo $alex->get_age();

 ?>

    <script type="text/javascript">
        var sumJS;
        sumJS = <?php echo $sumPHP ?>;
        alert("dude, you suck " + sumJS + " balls");
        document.write("<br> dude, you suck " + sumJS + " balls");
    </script>


 </body>
</html>

