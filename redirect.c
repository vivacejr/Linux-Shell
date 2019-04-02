#include"header.h"

int redirect(char **args, int num)
{
	ll f1=0,f2=0,f3=0;
	ll prein,preout;
	ll fd[2];
	char *cur_com[1000];
	ll i=0;
	while(args[i]!=NULL)	if(strcmp(args[i++],"<")==0)   f1=1;
	i=0;
	while(args[i]!=NULL)	if(strcmp(args[i++],">")==0)   f2=1;
	i=0;
	while(args[i]!=NULL)    if(strcmp(args[i++],">>")==0)   f3=1;
	i=0;
	char in[1000],out[1000];
	ll x=100000000000;

	if(f1==1)
	{
		i=0;
		while(args[i]!=NULL)
		{
			if(strcmp(args[i],"<")==0)
			{
				if(i-1<x)x=i-1;
				strcpy(in,args[i+1]);
			}
			i++;
		}
	}
	if(f2==1||f3==1)
	{
		i=0;
		while(args[i]!=NULL)	
		{		
			if(strcmp(args[i],">")==0||strcmp(args[i],">>")==0)
			{
				if(i-1<x)x=i-1;
				strcpy(out,args[i+1]);
			}
			i++;
		}
	}
	// printf("%lld %lld %lld \n",f1,f2,f3 );
	args[x+1]=NULL;
	if(f1==1)
	{
		struct stat chk;
		if(stat(in,&chk)==-1)
		{
			perror("file does not exist\n");
		}
		prein=dup(0);
   		fd[0] = open(in,O_RDONLY, 0644);
		dup2(fd[0],0);
	}
	if(f2==1||f3==1)
	{
		preout=dup(1);
		if(f2==1)
	    	fd[1] = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
	    	fd[1] = open(out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if(dup2(fd[1],1)==-1)
		{
			perror("dup2 failed");
			return 0;
		}
	}
	pid_t pid;
	pid=fork();
	if(pid==-1)
	{
		close(fd[1]);
		perror("fork error : ");
		return 0;
	}
	else if(!pid)
	{
		if(execvp(args[0],args)==-1)
		{
			perror("command not found");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
		dup2(prein,0);
		dup2(preout,1);
		// exit(EXIT_FAILURE);
	}

}

