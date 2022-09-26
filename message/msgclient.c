#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// A buffer large enough to contain the longest allowed string 
#define BUFSIZE 256

#define USAGE                                                          \
  "usage:\n"                                                           \
  "  echoclient [options]\n"                                           \
  "options:\n"                                                         \
  "  -s                  Server (Default: localhost)\n"                \
  "  -p                  Port (Default: 7169)\n"                      \
  "  -m                  Message to send to server (Default: \"Welcome " \
  "Back!.\")\n"                                                       \
  "  -h                  Show this help message\n"

/* OPTIONS DESCRIPTOR ====================================================== */
static struct option gLongOptions[] = {
    {"server", required_argument, NULL, 's'},
    {"port", required_argument, NULL, 'p'},
    {"message", required_argument, NULL, 'm'},
    {"help", no_argument, NULL, 'h'},
    {NULL, 0, NULL, 0}};

/* Main ========================================================= */
int main(int argc, char **argv) {
  unsigned short portno = 10823;
  int option_char = 0;
  char *message = "Welcome Back!";
  char *hostname = "localhost";

  // Parse and set command line arguments
  while ((option_char =
              getopt_long(argc, argv, "p:s:m:hx", gLongOptions, NULL)) != -1) {
    switch (option_char) {
      default:
        fprintf(stderr, "%s", USAGE);
        exit(1);
      case 's':  // server
        hostname = optarg;
        break;
      case 'p':  // listen-port
        portno = atoi(optarg);
        break;
      case 'h':  // help
        fprintf(stdout, "%s", USAGE);
        exit(0);
        break;
      case 'm':  // message
        message = optarg;
        break;
    }
  }

  setbuf(stdout, NULL);  // disable buffering

  if ((portno < 1025) || (portno > 65535)) {
    fprintf(stderr, "%s @ %d: invalid port number (%d)\n", __FILE__, __LINE__,
            portno);
    exit(1);
  }

  if (NULL == message) {
    fprintf(stderr, "%s @ %d: invalid message\n", __FILE__, __LINE__);
    exit(1);
  }

  if (NULL == hostname) {
    fprintf(stderr, "%s @ %d: invalid host name\n", __FILE__, __LINE__);
    exit(1);
  }

  /* Socket Code Here */
  
  int socketDesc;
  struct sockaddr_in serverAddr;
  char serverMessage[256], clientMessage[256];

  memset(serverMessage, '\0', sizeof(serverMessage)); //fills char arrays with null
  memset(clientMessage, '\0', sizeof(clientMessage));

  strcpy(clientMessage, message);

  socketDesc = socket(AF_INET, SOCK_STREAM, 0);
   printf("socket: ");
  if(socketDesc < 0){
    printf("error creating socket\n");
    return -1;
  }
  printf(" good\n");

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(portno);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  int connInt = connect(socketDesc, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
  printf("connect: ");
  if(connInt < 0){
    printf("unable to connect\n");
    return -1;
  }
  printf(" good\n");
  printf("connected to server\n");

  

  int sendInt = send(socketDesc, clientMessage, strlen(clientMessage), 0);
  printf("send: ");
  if(sendInt < 0){
    printf("unable to send message\n");
    return -1;
  }
  printf(" good\n");  
  
  int recvInt = recv(socketDesc, serverMessage, sizeof(serverMessage), 0);
  printf("recieve: ");
  if(recvInt < 0){
    printf("cant recieve from server\n");
    return -1;
  }
  printf(" good\n");
  printf("serverMessage: %s\n", serverMessage);

  close(socketDesc);
  return 0;
}
