#include"header.h"


ll execute(char ** args)
{
    pid_t pid,wpid;
    ll bg=0;
    int st;
    ll i=0;
    ll pip=0,red=0;
    while(args[i]!=NULL)
    {
        if(strcmp(args[i],">")==0||strcmp(args[i],"<")==0)   
        {   
            red=1;
            break;
        }
        i++;
    }   

    i=0;
    while(args[i]!=NULL)
    {
        if(strcmp(args[i],"|")==0)   
        {   
            pip=1;
            break;
        }
        i++;
    }   
    i=0;
    while(args[i]!=NULL)
    {
        if(strcmp(args[i],"&")==0&&args[i+1]==NULL)   
        {   
        	args[i]=NULL;
            bg=1;
            break;
        }
        i++;
    }   
    if(pip)
    {
        piping(args);
        return 1;
    }
    if(red)
    {
        redirect(args,1);
        return 1;
    }

    pid=fork();
    

    if (pid < 0) 
    {
        perror("ERROR:");
        return 1;
    }
    if(pid==0)
    {
    	if(bg==1&&strcmp(args[0],"vi")==0)exit(EXIT_SUCCESS);
        if ( execvp(args[0], args) == -1)
        {
            fprintf(stderr,"command: %s, not found\n",args[0] );
            exit(EXIT_FAILURE);
        }
    	return 0;
    }
    
    if(bg==0) 
    {
    	curr_pid=pid;
     	bg_arr[pid]=args[0];
    	signal(SIGTSTP,zhandler);
        wpid = waitpid (pid, &st, WUNTRACED);
        // for (i = 0;; i++) 
        // {
        //     if (!WIFEXITED(st) && !WIFSIGNALED(st)) 
        //     {
        //         wpid = waitpid (pid, &st, WUNTRACED);
        //         continue;
        //     }
        //     break;
        // }
    }
    else
    {
    	if(strcmp(args[0],"vi")==0)	status[pid]=2;
    	else 	status[pid]=1;
    	bg_arr[pid]=args[0];
    }
    return 1;
}

ll checkandrun(char ** args)
{
	ll cnt=0;
	ll pip=0,red=0;
	ll i=0;
    while(args[i]!=NULL)
    {
        if(strcmp(args[i],">")==0||strcmp(args[i],"<")==0)   
        {   
            red=1;
            break;
        }
        i++;
    }   

    i=0;
    while(args[i]!=NULL)
    {
        if(strcmp(args[i],"|")==0)   
        {   
            pip=1;
            break;
        }
        i++;
    }   
    if(pip)
    {
        piping(args);
        return 1;
    }
    if(red)
    {
        redirect(args,1);
        return 1;
    }

    i=0;
	if(args[0]==NULL)
	{
		return EXIT_FAILURE;
	}
    if(pip==1|| red==1)
    {
    	return execute(args);	
    }
	else if(strcmp(args[0],"cd")==0)
	{
		return CD(args);
	}
	else if(strcmp(args[0],"pwd")==0)
	{ 
		return PWD(args);
	}
	else if(strcmp(args[0],"echo")==0)
	{
		return ECHO(args);
	} 
	else if(strcmp(args[0],"ls")==0)
	{
        return LS(args);
	}
    else if(strcmp(args[0],"pinfo")==0)
    {
        return PINFO(args);
    }
    else if(strcmp(args[0],"clock")==0)
    {
        return CLOCK(args);
    }
    else if(strcmp(args[0],"remindme")==0)
    {
        return REMINDME(args);
    }
    else if(strcmp(args[0],"setenv")==0)
    {
        return mysetenv(args);
    }
    else if(strcmp(args[0],"unsetenv")==0)
    {
        return myunsetenv(args);
    }
    else if(strcmp(args[0],"jobs")==0)
    {
        return myjobs(args);
    }
    else if(strcmp(args[0],"kjob")==0)
    {
        return mykjobs(args);
    } 	
    else if(strcmp(args[0],"overkill")==0)
   	{
   		return myoverkill(args);
   	}	
    else if(strcmp(args[0],"fg")==0)
    {
        return myfg(args);
    } 	
    else if(strcmp(args[0],"bg")==0)
    {
        return mybg(args);
    } 	
    else if(strcmp(args[0],"quit")==0)
    {
    	return quit(args);
    }
    else 
    {
        return execute(args);
    }
}

void ctrlC(int signum)
{
    fprintf(stdout,"\nKeyboard interupt ^C, press enter to continue" );
    fflush(stdout);
}
void zhandler2(int signum)
{
	return 	;
}


void mainloop(void) 
{
	ll state;
    while(1) 
    {
        printPrompt();

        processflag=0;
        char **commands;

    	signal(SIGTSTP,zhandler2);
        signal(SIGINT,ctrlC);
        commands=Psemicolon();    
        ll i;
        for (i=0;commands[i]!=NULL;i++)
        {   
        	int st;
        	pid_t p = waitpid(-1,&st,WNOHANG);
        	if(p > 0 && WIFEXITED(st)>0)
        	{
        		fprintf(stderr, "Process %s with pid: %d exited normally\n",bg_arr[p],p);
        		status[p]=0;
        		bg_arr[p]=NULL;
        	}
        	else if(p > 0 && WIFSIGNALED(st) == 1)
        	{
        		fprintf(stderr, "Process %s with pid: %d exited abnormally\n",bg_arr[p],p);
        	}

            char **argsi;
            argsi = readandparse(commands[i]);
            state=checkandrun(argsi);
        }
    }
    
}
