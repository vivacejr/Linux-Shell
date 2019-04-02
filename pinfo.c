#include"header.h"

char ** breakem(char * name)
{
	char * token;
    char ** tokens = malloc(200 * sizeof(char * ));
    char s[3] = " \n\t";
	token = strtok(name,s);
	pos=0;
    while (token != NULL)
    {
        tokens[pos] = token;
        pos++;
        token = strtok(NULL," \n\t");
        // printf("%s\n",tokens[pos-1] );
    }	
    return tokens;
}

ll PINFO(char **args) {
    ll pid;
    if (args[1] == NULL)        pid = getpid();
    else   pid = atoi(args[1]);

    printf("pid -- %lld\n", pid);
    //initializes also
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
                if ('\n' == name2[size - 1]) 
                    name2[size - 1] = '\0';
        }
        else 
        {
            fprintf(stderr, "Failed to open file \"%s\"\n", name2);
            exit(1);
        }
        fclose(f);
    }
    //break into tokens
    char ** tokens = breakem(name2);
    lp(i,0,pos)
    {
        // printf("%lld %s\n",i,tokens[i] );
        if (strcmp(tokens[i], "VmSize:") == 0) 	   printf("Memory -- %s {Virtual Memory}\n", tokens[i + 1]);
        if (strcmp(tokens[i], "Status:") == 0)     printf("Status -- %s\n", tokens[i + 1]);
    }
    printf("Executable Path -- ");

    char path[PATH_MAX];
    char dest[PATH_MAX];
    memset(dest, 0, sizeof(dest));
    // readlink does not null terminate!
    struct stat info;

    sprintf(path, "/proc/%lld/exe", pid);

    if (readlink(path, dest, PATH_MAX) == -1)     perror("readlink");
    if (readlink(path, dest, PATH_MAX) != -1)     printf("%s\n", dest);
    free(name2);
    return 1;
}