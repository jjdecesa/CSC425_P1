# P1 - Socket Communications
In this course, your clients and servers will communicate via sockets.  This first project will familiarize you with the standard C APIs for sockect communication. You will build client-server configurations to send messages and to send files.

## Part 1 - Message Client-Server

You will create a client and server that will send (client) and return (server) a text message entered on the command line.

### Assumptions and Rules:

-Messages will be up to BUSIZE in length (defined in the code)
-You may assume the full message is sent or received in a single call (no need to check message length against bytes sent.)
-The only output of the client shall be the message returned from
the server
-The server should handle multiple messages and not terminate after replying to a message. (You can run your client(s) multiple times without needing to restart the server.)
-You should never assume a message is null-terminated.
-Your code will support IPv4 and IPv6


## Part 2 - File Transfer Client-Server

In this part of the assignment, you will implement code to transfer files on a server to clients.

### System flow

-The server is started with the name of the file to transfer provided in the command line arguments
-The file to send will be one of the files in the server_file directory
-Server waits for a connection request
-Once connected, the server will send the file to the client
-The client will receive the file and save it to the server_files directory
-When the server is done sending the file, it closes the connection to the client.
-Your code will support IPv4 and IPv6

### Assumptions
-You cannot make any assumptions about the data being transferred from server to client.  You may ask to send 2048 bytes but only 987 get sent. You may have a 3 MB file but only a 1024 byte buffer. You will need to keep track of what was sent and what remains to be sent.
-You can (should) design your system to process and send data "chunks."
-When the file has been sent by the server, the server will close the connection to let the client know that all data has been sent.
-The server will continue to run and will accept new connection requests

## Deliveables
There are two deliverables for this assignment:
1. For this assignment you will upload your code to GitHub in a PRIVATE repository called CSC425_P1.  You will make me a collaborator for the repository so that I can access your code.
2. You will create a pdf file called CSC425_P1_Readme.pdf. It must be called this name.  The pdf will contain an explanation of what you did, why you did it and what were the results.
You will need to exaplain your design, alternatives considered, obstacles faced and how you overcame them.  In addition, you will need to include a references section that shows all outside resources used 
to complete the project.  You do not need to include the textbook, "Understanding and Using C Pointers" or "The Linux Programming Interface" as these are identified course materials.
If you use Stack Overflow (for example) you need to include the URL of the post that you used. The pdf will be uploaded ot e-Learning prior to the due date 
for the assignment. There is no requirement for the format but keep in mind that a picture can often be  worth a thousand words and can convey 
ideas more easily than lots of text.

## Academic Integrity
As previously stated, collaboration with students in general terms is permitted and encouraged. However, you must do your own work and must write your own code.
You may not cut/paste anything from any website or reference material. Obviously, you may consult outside resources to understand what needs to be done.  But, you 
should only use that for ideas and direction so that you know enough to go write the code for your project.
