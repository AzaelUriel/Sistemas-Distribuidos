// ClienteEco.c
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[]) {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in servidor;
    char buffer[1024];
    char mensaje[1024];
    int recv_size;

    if (argc != 3) {
        printf("Uso: %s <host> <puerto>\n", argv[0]);
        return 1;
    }

    char *host = argv[1];
    int puerto = atoi(argv[2]);

    // Inicializar Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Fallo WSAStartup. Codigo: %d\n", WSAGetLastError());
        return 1;
    }

    // Crear socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("No se pudo crear socket: %d\n", WSAGetLastError());
        return 1;
    }

    // Configurar servidor
    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(puerto);
    servidor.sin_addr.s_addr = inet_addr(host);

    // Conectar
    if (connect(sock, (struct sockaddr *)&servidor, sizeof(servidor)) < 0) {
        printf("Error al conectar\n");
        return 1;
    }

    printf("Conectado al servidor. Escribe mensajes (\"adios\" para salir):\n");

    while (1) {
        // Leer del teclado
        printf("Tu: ");
        if (fgets(mensaje, sizeof(mensaje), stdin) == NULL) break;

        // Quitar salto de línea al final
        mensaje[strcspn(mensaje, "\n")] = '\0';

        // Enviar mensaje al servidor
        char mensajeConSalto[1024];
        snprintf(mensajeConSalto, sizeof(mensajeConSalto), "%s\n", mensaje);
        send(sock, mensajeConSalto, strlen(mensajeConSalto), 0);

        // Si el usuario escribe "adios", salimos
        if (strcmp(mensaje, "adios") == 0) {
            printf("Cerrando conexion...\n");
            break;
        }

        // Recibir respuesta
        recv_size = recv(sock, buffer, sizeof(buffer)-1, 0);
        if (recv_size > 0) {
            buffer[recv_size] = '\0';
            printf("Servidor: %s\n", buffer);
        }
    }

    // Cerrar conexión
    closesocket(sock);
    WSACleanup();

    return 0;
}
