#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 5000

int main() {
    WSADATA wsa;
    SOCKET server_fd, new_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_len = sizeof(client_addr);
    int num;

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Error en WSAStartup. Código: %d\n", WSAGetLastError());
        return 1;
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("No se pudo crear el socket: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Error en bind: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    if (listen(server_fd, 3) == SOCKET_ERROR) {
        printf("Error en listen: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    new_socket = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (new_socket == INVALID_SOCKET) {
        printf("Error: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    while (1) {
        int recibido;
        int bytesRecibidos = recv(new_socket, (char*)&recibido, sizeof(recibido), 0);

        if (bytesRecibidos <= 0) {
            printf("Cliente desconectado.\n");
            break;
        }

        recibido = ntohl(recibido);
        printf("Cliente: %d\n", recibido);

        if (recibido == 0) {
            printf("Cliente envio 0. Cerrando servidor.\n");
            break;
        }

        int respuesta = recibido + 1;
        printf("Servidor responde: %d\n", respuesta);

        respuesta = htonl(respuesta); 
        send(new_socket, (char*)&respuesta, sizeof(respuesta), 0);
    }

    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();

    return 0;
}
