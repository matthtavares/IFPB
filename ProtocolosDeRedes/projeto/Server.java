/**
  *  Java ECHO server with UDP sockets example
*/

import java.io.*;
import java.net.*;

public class Server
{
    public static void main(String args[])
    {
        DatagramSocket sock = null;

        try
        {
            // Creating variables
            byte[] data = null;
            String s = null;

            //1. creating a server socket, parameter is local port number
            sock = new DatagramSocket(7777);

            //buffer to receive incoming data
            byte[] buffer = new byte[1024];
            DatagramPacket incoming = new DatagramPacket(buffer, buffer.length);

            //2. Wait for an incoming data
            echo("Server socket created. Waiting for incoming data...");

            // request conections count
            int rccount = 0;

            while( rccount < 3 ){
              echo("Waiting conection...");

              // Receiving ACK
              sock.receive(incoming);
              data = incoming.getData();
              s = new String(data, 0, incoming.getLength());

              if( s.equals("ACK") )
                rccount++;
            }

            // Get file name
            sock.receive(incoming);
            data = incoming.getData();
            s = new String(data, 0, incoming.getLength());

            // Creating a binary file
            s = "byserver-" + s;
            FileOutputStream file = new FileOutputStream(s);
            // FileWriter fileWriter = new FileWriter(new File(s));

            sock.receive(incoming);
            data = incoming.getData();
            s = new String(data, 0, incoming.getLength());
            int escritas = Integer.parseInt(s);

            /** IF WANT TO CONECTION CLOSES
                AFTER SEND ALL DATA

            // // Set the max messages to receive
            // sock.receive(incoming);
            // data = incoming.getData();
            // s = new String(data, 0, incoming.getLength());
            // int maxr = Integer.parseInt(s);
            //
            // //communication loop
            // while(maxr > 0)
            */
            while(escritas > 0)
            {

                sock.receive(incoming);
                data = null;
                data = incoming.getData();
                file.write(data);

                // fileWriter.write(s);

                // //echo the details of incoming data - client ip : client port - client message
                // echo(incoming.getAddress().getHostAddress() + " : " + incoming.getPort() + " - " + s);

                // s = "OK : " + s;
                // DatagramPacket dp = new DatagramPacket(s.getBytes() , s.getBytes().length , incoming.getAddress() , incoming.getPort());
                // sock.send(dp);

                escritas--;
                //maxr--;
            }

            file.close();

            // fileWriter.flush();
            // fileWriter.close();
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
