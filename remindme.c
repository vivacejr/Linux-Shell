#include"header.h"

ll REMINDME(char ** args)
{
    ll t= atoi(args[1]);
    pid_t pid;
    pid=fork();
    if(pid==0)
    {
        sleep(t);
        ll i=2;
        fprintf(stdout, "\nReminder: " );
        while(args[i]!=NULL)
        {   
            fprintf(stdout,"%s ",args[i]);
            i++;
        }
        fprintf(stdout, "\n" );
        exit(EXIT_FAILURE);
    }
    return 1;
}