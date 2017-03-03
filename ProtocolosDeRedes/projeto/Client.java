/**
   * Java ECHO client with UDP sockets example
   * Silver Moon (m00n.silv3r@gmail.com)
*/

import java.io.*;
import java.net.*;

public class Client
{
    public static void main(String args[])
    {
        DatagramSocket sock = null;
        int port = 7777;
        String s;
        byte[] b;
        byte[] fbuffer = new byte[1024];
        DatagramPacket dp;

        BufferedReader cin = new BufferedReader(new InputStreamReader(System.in));

        try
        {
            sock = new DatagramSocket();

            InetAddress host = InetAddress.getByName("172.28.128.4");

            // Starting conection
            int rccount = 0;

            while( rccount < 3 ){
              echo("Sending ACK...");
              // Write ACK
              s = (String)"ACK";
              b = s.getBytes();
              // Send ACK
              dp = new DatagramPacket(b , b.length , host , port);
              sock.send(dp);

              rccount++;
            }

            echo("Digite o nome do arquivo: ");
            s = (String)cin.readLine();
            b = s.getBytes();
            dp = new DatagramPacket(b , b.length , host , port);
            sock.send(dp);

            // Create a file object
            FileInputStream file = new FileInputStream(s);

            // Get file size
            int leituras = (int)(file.getChannel().size() + 1024 - 1) / 1024;

            // Send file size
            dp = new DatagramPacket(Integer.toString(leituras).getBytes(), Integer.toString(leituras).getBytes().length , host , port);
            sock.send(dp);

            int len = 0;
            while( ((len = file.read(fbuffer)) != -1) ){
                dp = new DatagramPacket(fbuffer, len, host, port);
                sock.send(dp);
                fbuffer = null;
                fbuffer = new byte[1024];
            }

            // while(leituras > 0)
            // {
            //     // //take input and send the packet
            //     // echo("Enter message to send : ");
            //     // s = (String)cin.readLine();
            //     // b = s.getBytes();

            //     // dp = new DatagramPacket(b , b.length , host , port);
            //     // sock.send(dp);

            //     // //now receive reply
            //     // //buffer to receive incoming data
            //     // byte[] buffer = new byte[65536];
            //     // DatagramPacket reply = new DatagramPacket(buffer, buffer.length);
            //     // sock.receive(reply);

            //     // byte[] data = reply.getData();
            //     // s = new String(data, 0, reply.getLength());

            //     // //echo the details of incoming data - client ip : client port - client message
            //     // echo(reply.getAddress().getHostAddress() + " : " + reply.getPort() + " - " + s);

            //     leituras--;
            // }

            file.close();
        }

        catch(IOException e)
        {
            System.err.println("IOException " + e);
        }
    }

    //simple function to echo data to terminal
    public static void echo(String msg)
    {
        System.out.println(msg);
    }
}
