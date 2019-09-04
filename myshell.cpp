#include<stdio.h> 
#include <iostream>
#include<string>
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<vector>
#include <dirent.h>
#include <sys/stat.h>
#include <signal.h>
#include<vector>
#include<readline/readline.h> 
#include<readline/history.h> 
  
#define MAXCOM 1000 // max number of letters to be supported 
#define MAXLIST 100 // max number of commands to be supported 
#define clear() printf("\033[H\033[J") 

using namespace std;
string USER;
string HOME;
string PATH;
string PS1;
string HOSTNAME;
int readInput();
void printprompt() 
{ 
    char cwd[1024]; 
    getcwd(cwd, 1024); 
    printf("\n%s", cwd);
    cout<<" $ ";
    
} 

void init_prompt()
{
    vector<string> v;
    //char* v[5];
    FILE* fptr;
    char * line = NULL;
    size_t len = 0;
    ssize_t read1;

    fptr = fopen("mybashrc.txt", "r");
    if (fptr == NULL)
        exit(EXIT_FAILURE);
    while ((read1 = getline(&line, &len, fptr)) != -1) {
        v.push_back(line);
       // i++;
        //printf("%s", line);
    }

    fclose(fptr);
    if (line)
    free(line);

USER = v[2];
HOME = v[3];
PATH = v[4];
PS1 = v[0];
HOSTNAME = v[1];

}
int change_dir(char* s[])
{ int chdir_rtrn1;
  char path[500];
if (strcmp(s[1],"~")==0) {
    chdir_rtrn1 = chdir("/home/nausheen");
        }
      else {
  chdir(s[1]);
  }
  return chdir_rtrn1;
}

void execArgs(char** my_token) 
{   
     pid_t pid = fork();  
     int chdir_rtrn; 
    if (pid <0) { 
        printf("\nFailed forking child.."); 
        return; 
    } 
    else if (pid == 0) 
    {
        if(strcmp(my_token[0],"cd")==0)
      {
         chdir_rtrn = change_dir(my_token);
        if(chdir_rtrn<0)
        printf("Error while changing the directory, error is : %s",strerror(errno));

      } 

      else
       execvp(my_token[0], my_token);
       // cout<<"Cannot execute command";
    } 
    else { 
        wait(NULL); 
    } 
}

 

void init_shell() 
{ 
    clear();
   // sleep(1); 
} 
void process_string(char str[]) 
{ 
  char** token_arr = new char*[50];
    char* token = strtok(str, " "); 
    int i=0;
    while (token != NULL) 
    { 
       token_arr[i]= token;
       //cout<<temp[i]<<endl;
       token = strtok(NULL, " "); 
       i++;
    }   token_arr[i] = NULL;
     
    execArgs(token_arr);

 /* vector<char*> token_arr;
  char* token = strtok(str," ");
  while(token != NULL)
  {
    token_arr.push_back(token);
    token = strtok(NULL," ");
  }

  char** temp_token = new char*[token_arr.size()+1];
  for(int i=0;i<token_arr.size();i++)
  {
    temp_token[i] = token_arr[i];
  }
  temp_token[token_arr.size()] = NULL;
  execArgs(temp_token);
*/

} 

void sig_handler(int signo)
{
  //signal(SIGINT, sig_handler);
  fflush(stdout);
}

int main() 
{ 
  cout<<"I am shell"<<endl;
  int exitshell =0;
  init_shell(); 
 // signal(SIGINT, sig_handler);
  
   while (exitshell != 1)
   {  
    //init_prompt();
    printprompt();
    char str[256];
    scanf("%[^\n]%*c", str);
    if(strcmp(str,"exit")==0)
  {
    exitshell =1;
    continue;
  } 
    if(strlen(str) != 0){
    process_string(str); 
  } 
    // else
      // continue;
  }
    return 0; 
} 