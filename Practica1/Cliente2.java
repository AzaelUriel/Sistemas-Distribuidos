import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Cliente {
    public static void main(String[] args) {
        final String SERVER_IP = "127.0.0.1";  
        final int SERVER_PORT = 5000;

        try (Socket socket = new Socket(SERVER_IP, SERVER_PORT);
             DataOutputStream out = new DataOutputStream(socket.getOutputStream());
             DataInputStream in = new DataInputStream(socket.getInputStream());
             Scanner sc = new Scanner(System.in)) {

            while (true) {
                System.out.print("Ingrese un numero (0 para salir): ");
                int num = sc.nextInt();

                out.writeInt(num);
                out.flush();

                if (num == 0) {
                    System.out.println("Terminando conexion...");
                    break;
                }
                int respuesta = in.readInt();
                System.out.println("Servidor: " + respuesta);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
