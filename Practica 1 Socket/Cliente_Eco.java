import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Cliente_Eco {

    public static void main(String[] args) {
        final String SERVER_IP = "127.0.0.1";  
        final int SERVER_PORT = 5000;

        try (Socket socket = new Socket(SERVER_IP, SERVER_PORT);
             DataOutputStream out = new DataOutputStream(socket.getOutputStream());
             DataInputStream in = new DataInputStream(socket.getInputStream());
             Scanner sc = new Scanner(System.in)) {

            System.out.println("Conectado al servidor en " + SERVER_IP + ":" + SERVER_PORT);

            while (true) {
                System.out.print("Ingrese un número (0 para salir): ");
                int num = sc.nextInt();

                // Enviar entero
                out.writeInt(num);
                out.flush();

                if (num == 0) {
                    System.out.println("Terminando conexión...");
                    break;
                }

                // Recibir respuesta
                int respuesta = in.readInt();
                System.out.println("Servidor respondió: " + respuesta);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}