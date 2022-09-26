#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <getopt.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFSIZE 512

#define USAGE                                                \
  "usage:\n"                                                 \
  "  transferclient [options]\n"                             \
  "options:\n"                                               \
  "  -h                  Show this help message\n"           \
  "  -p                  Port (Default: 10823)\n"            \
  "  -s                  Server (Default: localhost)\n"      \
  "  -o                  Output file (Default cs6200.txt)\n" 

/* OPTIONS DESCRIPTOR ====================================================== */
static struct option gLongOptions[] = {{"server", required_argument, NULL, 's'},
                                       {"output", required_argument, NULL, 'o'},
                                       {"port", required_argument, NULL, 'p'},
                                       {"help", no_argument, NULL, 'h'},
                                       {NULL, 0, NULL, 0}};

/* Main ========================================================= */
int main(int argc, char **argv) {
  unsigned short portno = 10823;
  int option_char = 0;
  char *hostname = "localhost";
  char *filename = "./outputShouldGoHere";

  setbuf(stdout, NULL);

  /* Parse and set command line arguments */ 
  while ((option_char =
              getopt_long(argc, argv, "xp:s:h:o:", gLongOptions, NULL)) != -1) {
    switch (option_char) {
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
      default:
        fprintf(stderr, "%s", USAGE);
        exit(1);
      case 'o':  // filename
        filename = optarg;
        break;
    }
  }

  if (NULL == hostname) {
    fprintf(stderr, "%s @ %d: invalid host name\n", __FILE__, __LINE__);
    exit(1);
  }

  if (NULL == filename) {
    fprintf(stderr, "%s @ %d: invalid filename\n", __FILE__, __LINE__);
    exit(1);
  }

  if ((portno < 1025) || (portno > 65535)) {
    fprintf(stderr, "%s @ %d: invalid port number (%d)\n", __FILE__, __LINE__,
            portno);
    exit(1);
  }

  // Socket Code Here 

  
  int socketDesc;
  struct sockaddr_in serverAddr;

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

  
  //recieve file here
  FILE *BILL;
  char philString[BUFSIZE];
  int rec;

  BILL = fopen(filename, "w");

  while(1 == 1){
  int rec = recv(socketDesc, philString, BUFSIZE, 0);
  if(rec <= 0){
    fclose(BILL);
    break;
  }
  fwrite(philString, rec, 1, BILL);
  }

  close(socketDesc);
  return 0;
}

