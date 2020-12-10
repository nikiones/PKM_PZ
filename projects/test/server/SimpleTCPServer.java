package server;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class SimpleTCPServer {
    public static void main(String[] args) {
        Socket socket = null;
        ServerSocket servSocket = null;
        InputStreamReader inputStreamReader = null;
        BufferedReader bufferedReader = null;
        int port = 8030;
        try {
            servSocket = new ServerSocket(port);
            socket = servSocket.accept();
            System.out.println("Connection established [" + socket.getInetAddress() + "]");

            inputStreamReader = new InputStreamReader(socket.getInputStream());
            bufferedReader = new BufferedReader(inputStreamReader);

            String s = bufferedReader.readLine();
            String words[];

            words = s.split(" ");

            System.out.println("Words from client: " + s);
            System.out.println("Number of words: " + words.length);
            System.out.println("Longest word: " + findLongestWord(words));

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                bufferedReader.close();
                inputStreamReader.close();
                socket.close();
            } catch (IOException e1) {
                e1.printStackTrace();
            }
            try {
                servSocket.close();
            } catch (IOException e2) {
                e2.printStackTrace();
            }
        }
    }

    private static String findLongestWord(String[] strings){
        String result = "";
        for(String word : strings){
            if(word.length() > result.length()){
                result = word;
            }
        }
        return result;
    }
}
