#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <getopt.h>
#include <netdb.h>
#include <arpa/inet.h>

#define BUFSIZE 256
#define SA struct sockaddr

#define USAGE                                                        \
  "usage:\n"                                                         \
  "  echoserver [options]\n"                                         \
  "options:\n"                                                       \
  "  -p                  Port (Default: 10823)\n"                    \
  "  -m                  Maximum pending connections (default: 5)\n" \
  "  -h                  Show this help message\n"

/* OPTIONS DESCRIPTOR ====================================================== */
static struct option gLongOptions[] = {
    {"help", no_argument, NULL, 'h'},
    {"port", required_argument, NULL, 'p'},
    {"maxnpending", required_argument, NULL, 'm'},
    {NULL, 0, NULL, 0}};

int main(int argc, char **argv) {
  int maxnpending = 5;
  int option_char;
  int portno = 10823; /* port to listen on */

  // Parse and set command line arguments
  while ((option_char =
              getopt_long(argc, argv, "hx:m:p:", gLongOptions, NULL)) != -1) {
    switch (option_char) {
      case 'm':  // server
        maxnpending = atoi(optarg);
        break;
      case 'p':  // listen-port
        portno = atoi(optarg);
        break;
      case 'h':  // help
        fprintf(stdout, "%s ", USAGE);
        exit(0);
        break;
      default:
        fprintf(stderr, "%s ", USAGE);
        exit(1);
    }
  }

  setbuf(stdout, NULL);  // disable buffering

  if ((portno < 1025) || (portno > 65535)) {
    fprintf(stderr, "%s @ %d: invalid port number (%d)\n", __FILE__, __LINE__,
            portno);
    exit(1);
  }
  if (maxnpending < 1) {
    fprintf(stderr, "%s @ %d: invalid pending count (%d)\n", __FILE__, __LINE__,
            maxnpending);
    exit(1);
  }

  // Socket Code Here
  //hi
  
    int socketDesc, clientSocket, clientSize;
    struct sockaddr_in serverAddr, clientAddr;
    char serverMessage[BUFSIZE], clientMessage[BUFSIZE];

  memset(serverMessage, '\0', sizeof(serverMessage)); //fills char arrays with null
  memset(clientMessage, '\0', sizeof(clientMessage));

  socketDesc = socket(AF_INET, SOCK_STREAM, 0);

  printf("socket:");
  if(socketDesc < 0){
    printf("error creating socket\n");
    return -1;
  }
  printf(" good\n");
  bzero(&serverAddr, sizeof(serverAddr));

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(portno);
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  int bentInt = bind(socketDesc, (SA*)&serverAddr, sizeof(serverAddr));
  printf("bind: ");
  if(bentInt < 0){
    printf("error binding\n");
    return -1;
  }
  printf(" good\n");

  while(1 == 1){
  int listInt = listen(socketDesc, 3);
  printf("listen: ");
  if(listInt < 0){
    printf("error listening\n");
    return -1;
  }
  printf(" good\n");

  printf("Listening now\n---\n");

  clientSize = sizeof(clientAddr);
  clientSocket = accept(socketDesc, (SA*)&clientAddr, &clientSize);
  printf("accept: ");
  if(clientSocket < 0){
    printf("cant accept\n");
    return -1;
  }
  printf(" good\n");

  printf("Client connected at IP: %s and port: %i\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

  int recvInt = recv(clientSocket, clientMessage, sizeof(clientMessage), 0);
  printf("recieve: ");
  if(recvInt < 0){
    printf("cant recieve\n");
    return -1;
  }
  printf(" good\n");

  strcpy(serverMessage, clientMessage);

  int sendInt = send(clientSocket, serverMessage, strlen(serverMessage), 0);
  printf("send: ");
  if(sendInt < 0){
    printf("cant send\n");
    return -1;
  }
  printf(" good\n");  

  close(clientSocket);
  }
  close(socketDesc);

  return 0;
}
