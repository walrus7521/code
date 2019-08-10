<?php
    function DB_Dude($filename)
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

    function DB_Dude2($key)
    {
        return $key;
    }
?>

<html>
 <head>
  <title>PHP Test2</title>
 </head>
 <body>
 <?php echo DB_Dude("tmp.txt"); ?>
 </body>
</html>

