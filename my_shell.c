#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include<inttypes.h>
#define DELIM " \t\n\a\r"


typedef long long int ll;
typedef long double ld;

#define lp(var,start,end) for (ll var = start; var <end ; ++var)
#define rlp(var,start,end) for(ll var = start; var>=end ; var--)
#define pb push_back
#define mp make_pair
#define pf push_front
#define F first
#define S second
#define vll vector<ll>
#define pll pair<ll,ll> 
#define endl "\n"

struct dirent *dir;
struct stat st;
struct passwd *password;
struct group *grp;
struct tm *tm;
char datestring[1050];
const ll N=1e3+50;
ll curr_pid,clockflag,processflag;
char* root;

void clockexit(int a)
{
    printf("\nKeyboard interupt ^C\n");
    clockflag=1;
    fflush(stdout);
}

ll CLOCK(char ** args)
{
    char * f1,*f2,*r1,*r2;
    f1 = (char *) malloc(1234*sizeof(char));
    f2 = (char *) malloc(1234*sizeof(char));

    strcpy(f1,"/sys/class/rtc/rtc0/date");    
    strcpy(f2,"/sys/class/rtc/rtc0/time");    
    size_t a=0, b=0;    
    clockflag=0;
    while(1)
    {  
        FILE * F1 = fopen(f1,"r");
        FILE *F2 = fopen(f2,"r");
        signal(SIGINT,clockexit);
        if(clockflag==1)
        {
            break;
        }
        getline(&r1,&a,F1);
        getline(&r2,&b,F2);
        ll x=strlen(r1);
        r1[x-1]='\0';
        printf("%s, %s",r1,r2 );  
        ll t=atoi(args[2]);
        sleep(t);
    }
    // fclose(F1);
    // fclose(F2);
    return 1;
}

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
        exit(EXIT_SUCCESS);
    }
    return 1;
}

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



char const * sperm(__mode_t mode) {
    static char local_buff[16] = {0};
    int i = 0;
    // is directory ?
    if (S_ISDIR(mode)) {
        local_buff[i] = 'd';
    }
    else {
        local_buff[i] = '-';
    }
    i++;
    // user permissions
    if ((mode & S_IRUSR) == S_IRUSR) {
        local_buff[i] = 'r';
    }
    else {
        local_buff[i] = '-';
    }
    i++;
    if ((mode & S_IWUSR) == S_IWUSR) {
        local_buff[i] = 'w';
    }
    else {
        local_buff[i] = '-';
    }
    i++;
    if ((mode & S_IXUSR) == S_IXUSR) {
        local_buff[i] = 'x';
    }
    else {
        local_buff[i] = '-';
    }
    i++;
    // group permissions
    if ((mode & S_IRGRP) == S_IRGRP) {
        local_buff[i] = 'r';
    }
    else {
        local_buff[i] = '-';
    }
    i++;
    if ((mode & S_IWGRP) == S_IWGRP) {
        local_buff[i] = 'w';
    }
    else {
        local_buff[i] = '-';
    }
    i++;
    if ((mode & S_IXGRP) == S_IXGRP) {
        local_buff[i] = 'x';
    }
    else {
        local_buff[i] = '-';
    }
    i++;
    // other permissions
    if ((mode & S_IROTH) == S_IROTH) {
        local_buff[i] = 'r';
    }
    else {
        local_buff[i] = '-';
    }
    i++;
    if ((mode & S_IWOTH) == S_IWOTH) {
        local_buff[i] = 'w';
    }
    else {
        local_buff[i] = '-';
    }
    i++;
    if ((mode & S_IXOTH) == S_IXOTH) {
        local_buff[i] = 'x';
    }
    else {
        local_buff[i] = '-';
    }
    return local_buff;
}

ll LS(char **args)
{
    ll i,j,k,flaga=0,flagl=0,flag=0;
    DIR *directory;
    char buf[N],dir_name[N];
    for(i=0;args[i]!=NULL;i++)
    {
        if(strcmp(args[i],"ls")==0)  continue;
        else if(strcmp(args[i],"-a")==0) flaga=1;
        else if(strcmp(args[i],"-l")==0) flagl=1;
        else if(strcmp(args[i],"-la")==0||strcmp(args[i],"-al")==0) flaga=1,flagl=1;
        else
        {
            char *path=(char *) malloc(1234*sizeof(char));
            flag =1,k=0;
            path=actual_address(args,i);
            directory=opendir(path);
            if(directory==NULL)
            {
                fprintf(stderr,"cannot open directory%s\n",path );
                return 1;
            }   
            strcpy(dir_name,path);
        }
    }
    // printf("%lld %lld\n",flaga,flagl );
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    if(!flag)
    {
        directory=opendir(cwd);
        if(directory==NULL)
        {
            fprintf(stderr,"cannot open directory%s\n",cwd );
            return 1;
        } 
        strcpy(dir_name,cwd);
    }

    if(flagl&&flaga)
    {   
        while((dir = readdir(directory))!= NULL)
        {
            //stores on a string buffer instead of printing on console
            
            sprintf(buf, "%s/%s" , dir_name,dir->d_name);
            //we pass the file to read and read all its info using struct stat(here st)
            stat(buf,&st);
            //hidden files
            //file type and mode
            printf("%10.10s ",sperm(st.st_mode) );

            printf("%4lu",st.st_nlink );
            if ((password = getpwuid(st.st_uid)) != NULL){
                printf(" %s", password->pw_name);
            }
            else {
                printf(" %d", st.st_uid);
            }
            if ((grp = getgrgid(st.st_gid)) != NULL) {
                printf(" %s", grp->gr_name);
            }
            else {
                printf(" %d", st.st_gid);
            }
            printf(" %9jd", (intmax_t)st.st_size);
            tm = localtime(&st.st_mtime);
            strftime(datestring, sizeof(datestring), "%b %d %H:%M", tm);
            printf(" %s %s\n", datestring, dir->d_name);
        }
    }
    else if(flagl)
    {
        //ek ek krke dirent struct ko pointer deta rehta(read more later)
        while((dir = readdir(directory))!= NULL)
        {
            //stores on a string buffer instead of printing on console
            
            sprintf(buf, "%s/%s" , dir_name,dir->d_name);
            //we pass the file to read and read all its info using struct stat(here st)
            stat(buf,&st);
            //hidden files
            if(dir->d_name[0] == '.') continue;
            //file type and mode
            printf("%10.10s ",sperm(st.st_mode) );

            printf("%4lu",st.st_nlink );
            if ((password = getpwuid(st.st_uid)) != NULL){
                printf(" %s", password->pw_name);
            }
            else {
                printf(" %d", st.st_uid);
            }
            if ((grp = getgrgid(st.st_gid)) != NULL) {
                printf(" %s", grp->gr_name);
            }
            else {
                printf(" %d", st.st_gid);
            }
            printf(" %9jd", (intmax_t)st.st_size);
            tm = localtime(&st.st_mtime);
            strftime(datestring, sizeof(datestring), "%b %d %H:%M", tm);
            printf(" %s %s\n", datestring, dir->d_name);
        }
    }
    else if(flaga)
    {
        while(  (dir=readdir(directory))   != NULL)
        {
            printf(">> %s\n",dir->d_name );
        }
        closedir(directory);
    }
    else
    {
        //if no more items to read returns null
        while(  (dir=readdir(directory))   != NULL)
        {
            if(dir->d_name[0]=='.') continue;
            printf(">> %s\n",dir->d_name );

        }
        closedir(directory);
    }
}

ll PINFO(char **args) {
    ll pid;
    if (args[1] == NULL) 
    {
        pid = getpid();
    } 
    else 
    {
        //converts string to int
        pid = atoi(args[1]);
    }

    printf("pid -- %lld\n", pid);
    //initializes
    char * name2 = (char * ) calloc(10024, sizeof(char));

    if (name2) 
    {
        sprintf(name2, "/proc/%lld/status", pid);
        FILE * f = fopen(name2, "r");
        if (f) 
        {
            size_t size;
            //1024 is min mem of name2,f is file name
            size = fread(name2, sizeof(char), 1024, f);
            if (size > 0) 
            {
                if ('\n' == name2[size - 1]) 
                {
                    name2[size - 1] = '\0';
                }
            }
        }
        else 
        {
            fprintf(stderr, "Failed to open file \"%s\"\n", name2);
            exit(1);
        }
 
        fclose(f);
    }
    ll i=0;
    // printf("%s\n",name2 );
    int pos = 0;
    char * token;
    char ** tokens = malloc(200 * sizeof(char * ));
    char s[3] = " \n\t";

    if (!tokens) 
    {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(name2,s);

    while (token != NULL)
    {
        tokens[pos] = token;
        pos++;
        token = strtok(NULL," \n\t");
        // printf("%s\n",tokens[pos-1] );
    }

    lp(i,0,pos)
    {
        // printf("%lld %s\n",i,tokens[i] );
        if (strcmp(tokens[i], "VmSize:") == 0) 
        {
            printf("Memory -- %s {Virtual Memory}\n", tokens[i + 1]);
        }
        if (strcmp(tokens[i], "Status:") == 0)
        {
            printf("Status -- %s\n", tokens[i + 1]);
        }
    }
    printf("Executable Path -- ");

    char path[PATH_MAX];
    char dest[PATH_MAX];
    memset(dest, 0, sizeof(dest));
    // readlink does not null terminate!
    struct stat info;

    sprintf(path, "/proc/%lld/exe", pid);

    if (readlink(path, dest, PATH_MAX) == -1)
    {
        perror("readlink");
    }
    else 
    {
        printf("%s\n", dest);
    }
    free(name2);
    return 1;
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


char ** read_parse(char *inp)
{
    ll pos=0;
    char *token;
    ssize_t bufsize = 100005;
    char ** tokens = malloc(bufsize*sizeof(char *));
    if(!tokens)
    {
        fprintf(stderr, "malloc error\n" );
        exit(EXIT_FAILURE);
    }
    token =strtok(inp,DELIM);
    while(token!=NULL)
    {
        tokens[pos]=token;
        pos++;
        token =strtok(NULL,DELIM);
    }    
    tokens[pos]=NULL;
    return tokens;

}

char ** semicolon_parse()
{
    ll pos = 0;
    char *inp_string = NULL,*token;
    ssize_t bufsize = 0;
    getline(&inp_string,&bufsize,stdin);
    char ** tokens = malloc(bufsize*sizeof(char*));
    
    if(!tokens)
    {
        fprintf(stderr, "malloc error\n" );
        exit(EXIT_FAILURE);
    }
    token =strtok(inp_string,";");
    while(token!=NULL)
    {
        tokens[pos]=token;
        pos++;
        token =strtok(NULL,";");
    }    
    tokens[pos]=NULL;
    return tokens;
}

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

ll execute(char ** args)
{
    pid_t pid,wpid;
    ll bg=0;
    int status;
    ll i=0;
    while(args[i]!=NULL)
    {
        if(strcmp(args[i],"&")==0&&args[i+1]==NULL)   
        {   
            bg=1;
            break;
        }
        i++;
    }   
    pid=fork();
    printf("%d\n",pid);
    if (pid < 0) 
    {
        perror("ERROR:");
        return 1;
    }
    if(pid==0)
    {
        if ( execvp(args[0], args) == -1)
        {
            fprintf(stderr,"command: %s, not found\n",args[0] );
            exit(EXIT_FAILURE);
        }
    }
    
    if(bg==0) 
    {
        wpid = waitpid (pid, &status, WUNTRACED);
        for (i = 0;; i++) 
        {
            if (!WIFEXITED(status) && !WIFSIGNALED(status)) 
            {
                wpid = waitpid (pid, &status, WUNTRACED);
                continue;
            }
            break;
        }
    }
    return 1;
}

ll checkCommand(char ** args)
{
	ll cnt=0;
	if(args[0]==NULL)
	{
		return EXIT_FAILURE;
	}
	if(strcmp(args[0],"cd")==0)
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

void interpretCommand(void) 
{
	ll state;
    while(1) 
    {
        printPrompt();

        processflag=0;
        char **commands;
        signal(SIGINT,ctrlC);
        commands=semicolon_parse();    
        ll i;
        for (i=0;commands[i]!=NULL;i++)
        {   
            char **argsi;
            argsi = read_parse(commands[i]);
            state=checkCommand(argsi);
        }
    }
    
}

int main(int arg1, char **arg2) 
{
    root = getenv("PWD");
    interpretCommand();
    return EXIT_SUCCESS;
}	