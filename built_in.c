#include"header.h"

char *actual_address(char ** args,ll st)
{
    ll len=0;
    char *path;
    path = (char *) malloc(1234*sizeof(char));
    if(args[st][0]=='~')
    {
        strcpy(path,root);
        len=strlen(root);
        lp(j,1,strlen(args[st]))
        {
            path[len++]=args[st][j]; 
        }
    }
    else
    {
        strcpy(path,args[st]);
        len=strlen(args[st]);
        len;
    }
    path[len]='\0';
    return path;
}


ll CD(char **args)
{
	char *path=(char *) malloc(1234*sizeof(char));
	ll len=0;
    path=actual_address(args,1);
	if(chdir(path)!=0)
	{
		perror("Couldn't run cd command");
	}
	return 1;
}

ll ECHO(char **args)
{
    char a[1000];
    ll x= strlen(args[1]);
    // printf("%c\n",args[1][1] );
    if(args[1][0]=='$')
    {
        lp(i,1,x)
        {
            a[i-1]=args[1][i];
        }
        a[x]='\0';
        if(getenv(a)==NULL)
        {
            perror("not a env:");
            return 0;
        }
        printf("%s\n",getenv(a));
        return 1;
    }
    ll i=1;
    while(args[i]!=NULL)
    {
        printf("%s ",args[i] );
        i++;
    }
    printf("\n");
    return 1;
}

ll PWD(char **args)
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n",cwd );
    return 1;
}

int mysetenv(char **args)
{
    if(args[1]==NULL)
    {
        perror("Inappropriate No of Args");
        return 0;
    }
    if(args[2]!=NULL&&args[3]!=NULL)
    {
        perror("Inappropriate No of Args");
        return 0;
    }
    else if(args[2]==NULL)
    {
        args[2]="";
    }

    if(setenv(args[1],args[2],1)==-1)    printf("setenv failed \n");

    return 1;
}

int myunsetenv(char **args)
{
    if(args[1]==NULL)
    {   
        perror("Inappropriate No of Args");
        return 0;
    }
    if(unsetenv(args[1])==-1) printf("setenv failed \n");
    return 1;
}

void zhandler(int signum)
{

	status[curr_pid]=1;
	kill(curr_pid,SIGTSTP);
	printf("\nStopped : [%lld] \n",curr_pid);
	fflush(stdout);
	return 	;

}

ll myjobs(char **args)
{
	ll j=0;
	char * s = "stopped";
	char * r = "running";
	int i=0;
	while(i<100005)
	{
        if(status[i]==0)
        {
            //chill
        }
        else
        {
                // printf("[");
                // printf("%lld",j++);
                // printf("]");
                if(bg_arr[i]!=NULL)
                {
                    printf("%d\n",i);
                    char * var2=(malloc(sizeof(char)*1005));
                    sprintf(var2,"/proc/%d/stat",i);
                    //pinfo wala same
                    FILE *f =fopen(var2,"r");
                    if(f==NULL) 
                    {
                        perror("unable to open file \n");
                        return 0;
                    }
                    //first args
                    ll z=0;
                    int p;
                    char r[300];
                    char s;
                    char * str;
                    for(z=0;z<3;z++)
                    {
                        if(z==0)   fscanf(f,"%d",&p);
                        if(z==1)   fscanf(f,"%s",r);
                        if(z==2)   fscanf(f," %c",&s);
                    }
                    if(s=='R') status[i]=2;
                    if(s=='S') status[i]=2;
                    if(s!='S'&&s!='R') status[i]=1;
                    if(status[i]==1)   str="stopped";
                    else     str="running";
                    j++;
                    printf("[%lld]%s\t%s[%d]\n",j,str,bg_arr[i],i);
            }
			// if(status[i]!=1) printf("%s\t%s[%lld]\n",s,bg_arr[i],i);
			// else	printf("%s\t%s[%lld]\n",r,bg_arr[i],i);
		}
		i++;
	}
	return 1;
}
ll mykjobs(char **args)
{

    ll f=0;
    ll j=0,i=0,pid;
    ll x1= atoi(args[1]);
    while(i<1000005)
    {
        if(status[i]==0)
        {
            //chill
        }
        else
        {
            j++; //running jobs ++   
            if(x1==j)
            {
                pid = i,f=1;
                break;
            }   
        }
        i++;
    }   
    ll x=atoi(args[2]);
    // printf("%lld%lld\n",x,pid );
    kill(pid,x);
    if(x==9) status[pid],bg_arr[pid]= NULL;
}

ll myfg(char ** args)
{
    ll j=1;
    ll i=0;
    ll x=atoi(args[1]);

    while(i<100005)
    {
        if(status[i]==0)
        {
            //chill
        }
        else
        {
            int s;
            if(j==x)
            {
                kill(i,SIGCONT);
                waitpid(i,&s,WUNTRACED);
                if(WIFEXITED(s))
                {
                    bg_arr[i]=NULL;
                    status[i] =0;
                }
                if(WIFSIGNALED(s))
                {
                    bg_arr[i]=NULL;
                    status[i] =0;
                }
                break;
            }
            else
            {
                j++;
            }

        }
        i++;
    }
}

ll mybg(char ** args)
{
    ll j=1;
    ll i=0;
    ll x=atoi(args[1]);

    while(i<100005)
    {
        if(status[i]==0)
        {
            //chill
        }
        else
        {
            int s;
            if(j==x)
            {
                kill(i,SIGCONT);
                status[i]=2;
                break;
            }
            else
            {
                j++;
            }

        }
        i++;
    }
}

ll myoverkill(char ** args)
{
    ll i=0,j=0;
    while(i<100005)    
    {
        if(status[i]==0)
        {
            //chill
        }
        else j++,status[i]=0,bg_arr[i]=NULL,kill(i,9);
        i++;
    }
}

ll quit(char ** args)
{
    exit(EXIT_SUCCESS);
    return 0;
}