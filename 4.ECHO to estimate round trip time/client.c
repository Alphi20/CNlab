#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

int main() {

  char buffer[1024] = {0};
  char msg[1024];

  int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (clientSocket < 0) {
    printf("Socket failed\n");
    return 1;
  }

  struct sockaddr_in serverAddress;
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(9000);
  serverAddress.sin_addr.s_addr = INADDR_ANY;

  scanf("%[^\n]", msg);

  clock_t start = clock();

  sendto(clientSocket, msg, sizeof(msg), MSG_CONFIRM, (const struct sockaddr *)&serverAddress, sizeof(serverAddress));

  printf("Message sent\n");

  int len=sizeof(serverAddress);
  int n = recvfrom(clientSocket, buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr *)&serverAddress, &len);

  clock_t end = clock();

  buffer[n] = '\0';
  printf("Server: %s\n", buffer);

  printf("Round trip time: %f\n", (double)(end - start) / (double)CLOCKS_PER_SEC);

  close(clientSocket);
  return 0;
}
