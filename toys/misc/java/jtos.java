import java.io.*;
import java.util.*;
import java.lang.*;

interface gear {
    public void go();
}

class device extends Thread implements gear {
    public int i;
    public void go() {
        for (;;) {
            i++;
            yield();
        }
    }
    public void run() {
        go();
        //for (;;) {
        //    i++;
        //    yield();
        //}
    }
}

class jtos {
    public static void main(String[] args) throws IOException {
        device x = new device();
        x.start();
        System.out.println("keep hitting enter...\n");
        for (;;) {
            System.in.read();
            System.out.println(x.i);
        }
    }
}
