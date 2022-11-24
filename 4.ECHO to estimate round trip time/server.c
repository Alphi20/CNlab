#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {

  char buffer[1024] = {0};

  const int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (serverSocket < 0) {
    printf("Socket error\n");
    return 1;
  }

  struct sockaddr_in serverAddress;
  struct sockaddr_in clientAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(9000);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  const int b_val = bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
  if (b_val < 0) {
    printf("binding failed\n");
    return 1;
  }

  int len = sizeof(clientAddress);
  int n = recvfrom(serverSocket, buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr *)&clientAddress, &len);

  buffer[n] = '\0';

  printf("Client: %s\n", buffer);

  sendto(serverSocket, buffer, sizeof(buffer), MSG_CONFIRM, (const struct sockaddr *)&clientAddress, len);

  close(serverSocket);

  return 0;
}
