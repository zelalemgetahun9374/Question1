#include <string.h>
#include <stdio.h>
#include <rpc/rpc.h>
#include "msg.h"  

char* receive(char *line, const char *code)
{
    if(strstr(line, code) != NULL)
    {
        return line;
    }
    else
    {
        return NULL;
    }
}

int main(int argc, char *argv[])
{
    CLIENT *cl;
    int *result;
    char *server;
    int flag;
    
    
    if (argc != 2)
    {
        printf("Usage: clinet hostname not appropriate!");
        exit(1);
    }
    
    
    cl = clnt_create(argv[1], SHARED_MEMORY_PROG,SHARED_MEMORY_VERS, "tcp");
    if (cl == NULL) {
        clnt_pcreateerror(argv[1]);
        exit(1);
    }
    
    
    server = argv[1];
    
    
    while(1)
    {
        
        char *line;
        size_t len = 0;
        sleep(2);
        
        printf("Please input your command:\n");
        if((flag = getline(&line, &len, stdin)) == -1)
        {
            clnt_destroy(cl);
            exit(0);
        }
        
        //printf("%s %d", line, len);
        if(strcmp(line, "exit\n") == 0)
        {
            clnt_destroy(cl);
            exit(0);
        }
        
        
        if(receive(line, "C00L")!= NULL)
        {
            result = msg_1(&line, cl);
            
            if (result == (int *)NULL
            {
                clnt_perror(cl, server);
                clnt_destroy(cl);
                exit(1);
            }
            printf("Back from shared_memory\n");
            
            
            if (*result != 1)
            {
                clnt_perror(cl,argv[1]);
                clnt_destroy(cl);
                exit(1);
            }
        }
    }
    
    clnt_destroy(cl);
    return 0;
}
