#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <errno.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define BUFSIZE 512
#define SA struct sockaddr

#define USAGE                                            \
  "usage:\n"                                             \
  "  transferserver [options]\n"                         \
  "options:\n"                                           \
  "  -h                  Show this help message\n"       \
  "  -f                  Filename (Default: 6200.txt)\n" \
  "  -p                  Port (Default: 10823)\n"

/* OPTIONS DESCRIPTOR ====================================================== */
static struct option gLongOptions[] = {
    {"help", no_argument, NULL, 'h'},
    {"port", required_argument, NULL, 'p'},
    {"filename", required_argument, NULL, 'f'},
    {NULL, 0, NULL, 0}};


int main(int argc, char **argv) {
  char *filename = "./server_files/giraffes.jpg"; // file to transfer 
  int portno = 10823;          // port to listen on 
  int option_char;

  setbuf(stdout, NULL);  // disable buffering

  // Parse and set command line arguments
  while ((option_char =
              getopt_long(argc, argv, "hf:xp:", gLongOptions, NULL)) != -1) {
    switch (option_char) {
      case 'p':  // listen-port
        portno = atoi(optarg);
        break;
      case 'h':  // help
        fprintf(stdout, "%s", USAGE);
        exit(0);
        break;
      default:
        fprintf(stderr, "%s", USAGE);
        exit(1);
      case 'f':  // file to transfer
        filename = optarg;
        break;
    }
  }

  if ((portno < 1025) || (portno > 65535)) {
    fprintf(stderr, "%s @ %d: invalid port number (%d)\n", __FILE__, __LINE__,
            portno);
    exit(1);
  }

  if (NULL == filename) {
    fprintf(stderr, "%s @ %d: invalid filename\n", __FILE__, __LINE__);
    exit(1);
  }

  /* Socket Code Here */

  
  int socketDesc, clientSocket, clientSize;
  struct sockaddr_in serverAddr, clientAddr;

  socketDesc = socket(AF_INET, SOCK_STREAM, 0);

  printf("socket:");
  if(socketDesc < 0){
    printf("error creating socket\n");
    return -1;
  }
  printf(" good\n");

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

  //send file
  
  FILE *phil;
  char philString[BUFSIZE];

  phil = fopen(filename, "r");
  int fr;
  while((fr = fread(philString, 1, BUFSIZE, phil))){
    send(clientSocket, philString, fr, 0);
  }

  fclose(phil);
  close(clientSocket);
  }
  close(socketDesc);

  return 0;
}



