#include"header.h"



char* returnPath (char* cwd)
{
    int i,cwd_size = strlen(cwd), root_size = strlen(root);
    if (root_size > cwd_size) 
    {
        return cwd;
    }
    else if (root_size == cwd_size)
    {
        return "~";
    }
    else 
    {
        char *new = (char*)malloc(100);
        new[0] = '~';
        new[1] = '/';
        for (i = 0 ; i < cwd_size-root_size-1; i++)
        {
            new[i+2] = cwd[root_size+i+1];
        }
        return new;
    }
} 


void printPrompt () 
{
    char hostname[1024];
    char cwd[1024];
    hostname[1023] = '\0';
    gethostname(hostname, 1023);
    char *username = getenv("USER");
    getcwd(cwd, sizeof(cwd));
    char *path = returnPath(cwd);
    printf("<%s@%s:%s/> ",username,hostname,path);
}
