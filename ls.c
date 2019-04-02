#include"header.h"


char *actual_address2(char ** args,ll st)
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
    char buf[1050],dir_name[1050];
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
            path=actual_address2(args,i);
            directory=opendir(path);
            if(directory==NULL)
            {
                fprintf(stderr,"cannot open directory%s\n",path );
                return 1;
            }   
            strcpy(dir_name,path);
        }
    }

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
            printf(" %d", st.st_uid);
            printf(" %d", st.st_gid);

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