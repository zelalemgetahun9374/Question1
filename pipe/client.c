#include<stdio.h> 
#include<fcntl.h>
#include<stdlib.h>
main()
{
 FILE *file1;
 int fifo_server,fifo_client;
 char str[256];
 char *buf;
 char *choice;
 printf("Welcome to chat\n\n");
if(fork() == 0)
    {   

    while(1)
    {
         choice = malloc(10*sizeof(char));
         scanf("%s",choice);

         fifo_server=open("fifo_server",O_RDWR);
         if(fifo_server < 1) {
          printf("Error in opening file");
          exit(-1);
          }

         write(fifo_server,choice,sizeof(choice));

         //sleep(10);   
    }    


    }
 else{
    while(1)
    {


        fifo_client = open("fifo_client",O_RDWR);
        if(fifo_client<1) {
         printf("Error opening file");
         exit(1);
         }

        read(fifo_client,choice,sizeof(choice));
        printf("%s\n",choice);

        /*      
        fifo_client=open("fifo_client",O_RDWR);

         if(fifo_client < 0) {
          printf("Error in opening file");
          exit(-1);
          }

         buf=malloc(10*sizeof(char));
         read (fifo_client,buf,sizeof(buf));
         printf("\n %s***\n",buf);
        */
    }

}

close(fifo_server); 
close(fifo_client);  
}