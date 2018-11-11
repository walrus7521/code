import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
 

public class core {

    public static final double PI = 3.141;


    public static void main(String[] args) throws Exception {
        String inFile = null;
        if (args.length > 0) inFile = args[0];
        InputStream is = System.in;
        OutputStream os = System.out;
        if (inFile != null) is = new FileInputStream(inFile);
        char c;
        byte[] buf = new byte[256];
        String line;
        BufferedReader reader = new BufferedReader(new InputStreamReader(is));
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }

        System.out.println("hello");
    }
}
