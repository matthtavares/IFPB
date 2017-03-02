/**
 * Programa cliente solicitando data atual ao servidor.
 *
 * Figura 3.20
 *
 * @author Gagne, Galvin, Silberschatz
 * Fundamentos de Sistemas Operacionais - Oitava Ediзгo.
 * Copyright John Wiley & Sons - 2011.
 */

import java.net.*;
import java.io.*;

public class DateClient
{
    public static void main(String[] args)  {
        try {
            // podeeria ser alterado para um nome ou endereзo IP que nгo fosse o do host local
            Socket sock = new Socket("172.28.128.3",6013);
            InputStream in = sock.getInputStream();
            BufferedReader bin = new BufferedReader(new InputStreamReader(in));

            PrintWriter output = new PrintWriter(sock.getOutputStream(),true);
            output.println("Cliente -> Servidor");

            String line;
            while( (line = bin.readLine()) != null )
                System.out.println(line);

            sock.close();
        }
        catch (IOException ioe) {
                System.err.println(ioe);
        }
    }
}
