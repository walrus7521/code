import java.io.*;
import java.util.*;
import java.lang.*;

class stuff {
    public static void main(String[] args) throws IOException {
        String epath = System.getenv("PATH");
        System.setProperty("dude", "42");
        String zone = System.getProperty("dude");
        System.out.println("path: " + epath + "\n\ndude:" + zone + '\n');

        Properties props = System.getProperties();
        Enumeration names = props.propertyNames();
        String key = "";
        while (names.hasMoreElements()) {
            key = (String) names.nextElement();
            System.out.println(key + "=" + props.getProperty(key));
        }
    }
}
