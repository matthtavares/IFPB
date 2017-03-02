
/**
 * Servidor escutando a hora do dia na porta 6013.
 *
 * Figura 3.19
 *
 * @author Gagne, Galvin, Silberschatz
 * Fundamentos de Sistemas Operacionais - Oitava Ediзгo
 * Copyright John Wiley & Sons - 2011.
 */

import java.net.*;
import java.io.*;

public class DataServer
{
    public static void main(String[] args)  {
        try {
            ServerSocket sock = new ServerSocket(6013);

            // agora escuta conexхes
            while (true) {
                Socket client = sock.accept();
                // temos uma conexгo

              BufferedReader  input = new BufferedReader(new InputStreamReader(client.getInputStream()));
                //PrintWriter output = new PrintWriter(client.getOutputStream())
                String message = input.readLine();
                System.out.println(message);

                PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
                // grava a data no socket


                pout.println("Ola enfermeira");
                  pout.println("Ola enfermeira");
                    pout.println("Ola enfermeira");


                // fecha o socket e volta a escutar conexхes
                //client.close();
            }
        }
        catch (IOException ioe) {
                System.err.println(ioe);
        }
    }
}
