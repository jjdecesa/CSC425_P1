For part 1 I found a website to teach me the different parts of connecting a server and
client. I found using htonl(INADDR_ANY) binds the server to all interfaces and not just 
the local host which is generally what you want to do. for each step, such as binding the
socket and listening he set the result to an int and checked it to see if it errored out,
returned -1, to help with troubleshooting. I looped the listening and below to allow it
to search for another connection once disconnected from client. I also set the listen to 
allow for up 3 pending connections before droping them. The client side was similar with the
main differences being that it only connects to the socket, sends, and recieves. Also for
serverAddr.sin_addr.s_addr I used just the local hosthost.

For part 2 I was able to set up the server and client similar to the message part. My first 
road block was using fgets instead of freads which from my understanding only read text since
I was having issues reading binary files. I ran into a lot of segmentation and broken pipe 
errors. It took a second to figure out how to use fread and fwrite to not cause errors with
the type of information I was sending over the socket. Currently the code create a FILE var
and char to hold the contents. I then open the file with fopen and using a while loop read it
all to the char and send it. Then close connection with the file and client once it is 
completly sent. I was not able to find a way to distinguish the type of file send but the
client can rename their output file as needed with -o. The server can change what file to 
send with -f './location' It is current set to './outputShouldGoHere' and 
'./server_files'girrafes.jpg'


https://www.educative.io/answers/how-to-implement-tcp-sockets-in-c
https://www.geeksforgeeks.org/memset-c-example/
https://www.gta.ufrj.br/ensino/eel878/sockets/sockaddr_inman.html
https://linux.die.net/man/3/htons
https://www.geeksforgeeks.org/difference-strlen-sizeof-string-c-reviewed/
https://www.programiz.com/c-programming/library-function/string.h/strcpy
https://stackoverflow.com/questions/16508685/understanding-inaddr-any-for-socket-programming
https://www.linuxquestions.org/questions/linux-networking-3/inet_addr-compile-problem-658104/
https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
https://www.programiz.com/c-programming/c-pointers
