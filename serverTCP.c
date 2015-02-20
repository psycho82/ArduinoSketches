#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
/*function declaration*/
void doprocessing (int sock,int numclient,char *endtag);




int main( int argc, char *argv[] )
{
   int sockfd, newsockfd, portno, clilen,numclient;
   char buffer[256];
   char *endtag;
	
   struct sockaddr_in serv_addr, cli_addr;
   int  n;
   
 if (argc < 3) {
         fprintf(stderr," USAGE : server [port] [endtag] \n\n\t [port]: server port number listening\n\t [endtag]: tag server wait to close the connection\n\n");
         exit(1);
     }

   numclient=0; 	
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0)
      {
      perror("ERROR opening socket");
      exit(1);
      }
   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   /* Get port from first argument*/
   portno = atoi(argv[1]);
   /* Get port from first argument*/
   endtag= argv[2];
	
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
      {
      perror("ERROR on binding");
      exit(1);
      }
   
   /* Now start listening for the clients, here
   * process will go in sleep mode and will wait
   * for the incoming connection
   */
   
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   
   while (1)
   {
      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
      if (newsockfd < 0)
         {
         perror("ERROR on accept");
         exit(1);
         }
      
      /* Create child process */
      int pid = fork();
      numclient=numclient+1;
      if (pid < 0)
         {
	 numclient--;	
         perror("ERROR on fork");
         exit(1);
         }
      
      if (pid == 0)
         {
         /* This is the client process */
         close(sockfd);
         doprocessing(newsockfd,numclient,endtag);
         exit(0);
         }
      else
         {
         close(newsockfd);
         }
   } /* end of while */
}


/*function implementation*/
void doprocessing (int sock,int numclient,char *endtag)
{
   int n;
   char buffer[256];
   

while(strstr(buffer,endtag)==NULL){
   bzero(buffer,256);
   n = read(sock,buffer,255);
   
   if (n < 0)
      {
      perror("ERROR reading from socket");
      exit(1);
      }
   
   printf("[Process %i]msg: %s\n",numclient,buffer);
  
   
   if (n < 0)
      {
      perror("ERROR writing to socket");
      exit(1);
      }
}
 printf("[Thread %i] CloseConnection TAG detected: connection closed! \n",numclient);
 n = write(sock,"Connection close",18);
}
