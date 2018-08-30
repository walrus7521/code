import java.io.*;
import java.net.*;

public class HttpClient {
    public static void main(String[] args) {
        try {
            if ((args.length != 1) && (args.length != 2)) {
                throw new IllegalArgumentException("Wrong number of args");
            }

            OutputStream to_file;
            if (args.length == 2) to_file = new FileOutputStream(args[1]);
            else to_file = System.out;

            URL url = new URL(args[0]);
            String protocol = url.getProtocol();
            if (!protocol.equals("http")) {
                throw new IllegalArgumentException("Must use 'http:' protocol");
            }

            String host = url.getHost();
            int port = url.getPort();
            if (port == -1) port = 80;
            String filename = url.getFile();

            Socket socket = new Socket(host, port);

            InputStream from_server = socket.getInputStream();
            PrintWriter to_server = new PrintWriter(socket.getOutputStream());

            to_server.print("GET " + filename + "\n\n");
            to_server.flush();

            byte[] buffer = new byte[4096];
            int bytes_read;
            while ((bytes_read = from_server.read(buffer)) != -1) {
                to_file.write(buffer, 0, bytes_read);
            }

            socket.close();
            to_file.close();

        } catch (Exception e) {
            System.err.println(e);
            System.err.println("Usage: java HttpClient <URL> [<filename>]");
            System.err.println("    e.g.: java HttpClient http://127.0.0.1:4444");
        }
    }
}
