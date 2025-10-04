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

  
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Fallo WSAStartup. Codigo: %d\n", WSAGetLastError());
        return 1;
    }
//socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("No se pudo crear socket: %d\n", WSAGetLastError());
        return 1;
    }

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(puerto);
    servidor.sin_addr.s_addr = inet_addr(host);

    
    if (connect(sock, (struct sockaddr *)&servidor, sizeof(servidor)) < 0) {
        printf("Error al conectar\n");
        return 1;
    }

    printf("Conectado al servidor. Escribe mensajes (\"adios\" para salir):\n");

    while (1) {
        printf("Tu: ");
        if (fgets(mensaje, sizeof(mensaje), stdin) == NULL) break;

        mensaje[strcspn(mensaje, "\n")] = '\0';

      
        char mensajeConSalto[1024];
        snprintf(mensajeConSalto, sizeof(mensajeConSalto), "%s\n", mensaje);
        send(sock, mensajeConSalto, strlen(mensajeConSalto), 0);

       
        if (strcmp(mensaje, "adios") == 0) {
            printf("Cerrando conexión...\n");
            break;
        }
        recv_size = recv(sock, buffer, sizeof(buffer)-1, 0);
        if (recv_size > 0) {
            buffer[recv_size] = '\0';
            printf("Servidor: %s\n", buffer);
        }
    }
    closesocket(sock);
    WSACleanup();

    return 0;
}