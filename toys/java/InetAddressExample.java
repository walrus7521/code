import java.util.Enumeration;
import java.net.*;

public class InetAddressExample {
    public static void main(String[] args) {
        try {
            Enumeration<NetworkInterface> interfaceList = NetworkInterface.getNetworkInterfaces();
            if (interfaceList == null) {
                System.out.println("-- no interfaces found --");
            } else {
                while (interfaceList.hasMoreElements()) {
                    NetworkInterface iface = interfaceList.nextElement();
                    System.out.println("Interface " + iface.getName() + ":");
                    Enumeration<InetAddress> addrList = iface.getInetAddresses();
                    if (!addrList.hasMoreElements()) {
                        System.out.println("\t(no addresses for this interface)");
                    }
                    while (addrList.hasMoreElements()) {
                        InetAddress address = addrList.nextElement();
                        System.out.println("\tAddress "
                                + ((address instanceof Inet4Address ? "(v4)"
                                   : (address instanceof Inet6Address ? "(v6)"
                                   : "(?)"))));
                        System.out.println(": " + address.getHostAddress());
                    }
                }
            }
        } catch (SocketException se) {
            System.out.println("Error getting interfaces: " + se.getMessage());
        }
    }
}
