

#include <stdio.h>
#include <string.h>
#include "msg.h" 

int * msg_1_svc(char **msg, struct svc_req *req)
{
    static int result; 
    FILE *fp;
    
    fp = fopen("secret.txt", "a");
    
    if (fp == (FILE *)NULL)
    {
        result = 0;
        return (&result);
    }
    
    fprintf(fp, "%ld, %s", strlen(*msg) - 1, *msg);
    fclose(fp);
    result = 1;
    return (&result);
}
