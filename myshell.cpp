#include<stdio.h> 
#include <iostream>
#include<string>
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<vector>
#include <signal.h>
#include<readline/readline.h> 
#include<readline/history.h> 
  
#define MAXCOM 1000 // max number of letters to be supported 
#define MAXLIST 100 // max number of commands to be supported 
#define clear() printf("\033[H\033[J") 

using namespace std;
int readInput();
void printprompt() 
{ 
    char cwd[1024]; 
    getcwd(cwd, 1024); 
    printf("\n%s", cwd);
    printf(" $ ");
} 


void execArgs(char* temp[]) 
{   
     pid_t pid = fork();  
  
    if (pid <0) { 
        printf("\nFailed forking child.."); 
        return; 
    } else if (pid == 0) { 
        execvp(temp[0], temp);
    } else { 
        wait(NULL);  
        return; 
    } 
}

int change_dir(char* s[])
{ int chdir_rtrn1;
  char path[500];
  /* if(strncmp(s[1],"/",1)!=0) {
            getcwd(path, sizeof(path));
              strcpy(path, "/");
              strcpy(path,s[1]);
              chdir_rtrn1 = chdir(path);
                        }
  else */if (strncmp(s[1],"~",1)==0) {
            chdir_rtrn1 = chdir("/home/nausheen/");
                        }
                        else {
                                chdir(s[1]);
                        }
                        return chdir_rtrn1;
} 

void init_shell() 
{ 
    clear();
   // sleep(1); 
} 
char* process_string(char str[]) 
{ 

	char* temp[50];
	char** token_arr = new char*[50];
    char* token = strtok(str, " "); 
    int i=0;
    while (token != NULL) 
    { 
       temp[i]= token;
       //cout<<temp[i]<<endl;
       token = strtok(NULL, " "); 
       i++;
    }   
     int chdir_rtrn; 
      if(strcmp(temp[0],"cd")==0)
      {
         chdir_rtrn = change_dir(temp);
  if(chdir_rtrn<0)
  printf("Error while changing the directory, error is : %s",strerror(errno));
  }
   else execArgs(temp);
    //if(y<0)
      //cout<<"execution failed!!!"
} 

void sig_handler(int signo)
{
  //signal(SIGINT, sig_handler);
  fflush(stdout);
}

int main() 
{ 
  int exitshell =0;
  init_shell(); 
 // signal(SIGINT, sig_handler);
   while (exitshell != 1)
   {  
    printprompt();
    char str[256];
    scanf("%[^\n]%*c", str); 
    if(strlen(str) != 0){
    process_string(str); 
  } 
    if(strcmp(str,"exit")==0)
  {
    exitshell =1;
    continue;
  }
  }
    return 0; 
} 