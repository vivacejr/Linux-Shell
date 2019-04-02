#ifndef HEADER_H
#define HEADER_H

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
#include <inttypes.h>
#include <errno.h>
#include <unistd.h>
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

char **bg_arr;

ll curr_pid,clockflag,processflag;
ll status[1000005];
char* root;
ll pos;

ll execute(char ** args);
ll checkandrun(char ** args);
void ctrlC(int signum);
void mainloop(void); 
char* returnPath (char* cwd);
void printPrompt () ;
char ** readandparse(char *inp);
char ** Psemicolon();
char ** breakem(char * a);
char *actual_address(char ** args,ll st);
char *actual_address2(char ** args,ll st);
ll CD(char **args);
ll ECHO(char **args);
ll PWD(char **args);
char *actual_address(char ** args,ll st);
char const * sperm(__mode_t mode) ;
ll LS(char **args);
ll REMINDME(char ** args);
void clockexit(int a);
ll CLOCK(char ** args);
ll PINFO(char **args) ;
void piping(char **args);
int redirect(char **args, int num);
int myunsetenv(char **args);
int mysetenv(char **args);
ll myjobs(char **args);	
ll mykjobs(char **args);	
void zhandler(int signum);
ll myoverkill(char ** args);
ll mybg(char ** args);
ll myfg(char ** args);
void zhandler2(int signum);
ll quit(char ** args);

int main(int a,char **b);



#endif