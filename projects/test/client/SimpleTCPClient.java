package client;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Scanner;

public class SimpleTCPClient {
    public static void main(String[] args) {
        Socket socket = null;
        DataOutputStream outputStream = null;
        String serverAddr = "localhost";
        int port = 8030;
        try {
            socket = new Socket(serverAddr,port);
            System.out.println("Enter words: ");
            Scanner scanner = new Scanner(System.in);
            String string = scanner.nextLine();

            outputStream = new DataOutputStream(socket.getOutputStream());
            outputStream.writeBytes(string);

        } catch (IOException e) {
            e.printStackTrace();
        } finally{
            try {
                outputStream.close();
                socket.close();
            } catch (IOException e1) {
                e1.printStackTrace();
            }
        }
    }
}
