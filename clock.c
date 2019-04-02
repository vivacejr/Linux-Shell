#include"header.h"

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
