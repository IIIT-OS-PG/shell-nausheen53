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
#include <fstream>
#include<termios.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<readline/readline.h> 
#include<unordered_map>
#include<readline/history.h>
  
#define MAXCOM 1000 // max number of letters to be supported 
#define MAXLIST 100 // max number of commands to be supported 
#define clear() printf("\033[H\033[J") 

using namespace std;
bool outr =false;
bool append = false;
vector<string> v1;
vector<string>v2;
int prid;
void init_prompt();
//int readInput();
unordered_map<char*,string> m1;
void inputmode()
{
  struct termios tattr;
  tcgetattr (STDIN_FILENO, &tattr);
  tattr.c_lflag &= ~(ICANON); 
  tcsetattr(STDIN_FILENO,TCSAFLUSH,&tattr);
}
void init_shell() 
{ 
    clear();
    prid = getpid();
    //cout<<prid; 
}

void printprompt() 
{ 
    char dirt[1024]; 
    getcwd(dirt, 1024); 
    printf("\n%s", dirt);
    cout<<" "<<v1[0];
    
} 

 char** splits1(char s[])
{
  char** ctr1 = new char*[20];

  char* temp=strtok(s, ":");
  int m=0;
  while(temp!=NULL)
  {
    //cout<<temp<<endl;
    ctr1[m] = temp;
    //cout<<v[i]<<endl;
    //i++;
    m++;
    temp=strtok(NULL,":");
  }
  ctr1[m] = NULL;
  return ctr1;
}

void init_prompt()
{  
    FILE* f1;
    char c;
    char* c1 = (char*)malloc((sizeof(char))*1024);
    f1 = fopen("/etc/environment", "r"); 
    int i=0;
   if (f1 == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
 
   while((c = fgetc(f1)) != EOF)
    {
      c1[i++]= c;
    }c1[i]= '\0';
 
   fclose(f1);

   FILE* f2;
    char c2;
    char* c3 = (char*)malloc((sizeof(char))*1024);
    f2 = fopen("/etc/hostname", "r"); 
    int j=0;
   if (f2 == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
 
   while((c2 = fgetc(f2)) != EOF)
    {
      c3[j++]= c2;
    }c3[j]= '\0';
 
   fclose(f2);

FILE* f3;
    char c4;
    char* c5 = (char*)malloc((sizeof(char))*1024);
    f3 = fopen("/etc/hostname", "r"); 
    int k=0;
   if (f3 == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
 
   while((c4 = fgetc(f3)) != EOF)
    {
      c5[k++]= c4;
    }c5[k]= '\0';
 
    fclose(f3);
    string myString(c5, k);
    char st[2000];
    int l;
    for(l=0;l<k;l++)
    {
      st[l]=myString[l];
    }
    st[l]='\0';
    char** chr = new char*[20];
    chr = splits1(st);
//////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////
      ofstream st1;
      st1.open("mybashrc1.txt",ios::out);
      if(!st1)
      {
        cout<<"Cannot initialize variables.";
      }
      else
      {
        st1<<"$"<<endl; //PS1
        st1<<c1<<endl; //PATH
        st1<<c3<<endl; //HOSTNAME
        st1<<chr[0]<<endl; //USER
        st1<<chr[5]<<endl; //HOME
      }
    st1.close();

    string line2;
    int i1=0;
    ifstream ifp("mybashrc1.txt");
    if(ifp.is_open())
    {
      while(getline(ifp,line2))
  {
      v1.push_back(line2);
    }

  ifp.close();}
 // cout<<v1[0]<<endl;
  //cout<<v1[1]<<endl;
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

void execArgs(char** my_token,int k) 
{   
    unordered_map<char*,string> :: iterator it1;
     pid_t pid = fork(); 
     int chdir_rtrn; 
    if (pid <0) 
    { 
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
        execvp(my_token[0], my_token);

      } 
      else if(strcmp(my_token[0],"$$")==0)
      {
        cout<<prid<<endl;
      }

      else if(outr == true || append == true)
      { 
        my_token[k]=NULL;
        //cout<<my_token[k+1]<<endl;
        int fd;
        if(outr == true)
        { fd = open(my_token[k+1],O_WRONLY | O_CREAT ,0644);}
      else if(append == true)
      {
         fd = open(my_token[k+1],O_WRONLY| O_CREAT | O_APPEND,0644);
      }
        if(fd < 0)
        {
          cout<<"Cannot open file"<<endl;
        }
        dup2(fd,1);
        close(fd);
        outr = false;
        append = false;
        execvp(my_token[0], my_token);
      }
       else if(strcmp(my_token[0],"echo")==0)
      {  //cout<<v1[1]<<v1[2];
        
        if(strcmp(my_token[1],"$HOME")==0)
        {
          cout<<v1[4]<<endl;
        }
        else if(strcmp(my_token[1],"$PATH")==0)
          {cout<<v1[1]<<endl;}
        else if(strcmp(my_token[1],"$HOST")==0)
          {
          cout<<v1[2]<<endl;
          }
        else if(strcmp(my_token[1],"$USER")==0)
          {
          cout<<v1[3]<<endl;
          }
          else execvp(my_token[0], my_token);
            
      }
      else if(strcmp(my_token[0],"history")==0)
      {
        vector<string>::iterator it;
        it = v2.begin();
        while(it != v2.end())
        {
          cout<<*it<<endl;
          ++it;
        }
        execvp(my_token[0], my_token);
      }

      else if(strcmp(my_token[0],"alias")==0)
      { 
        cout<<"inside alias";
          int i = 4;
          string s = my_token[i];
          while(my_token[i] != "'")
          {
            s = s + " " + my_token[++i];
          }
        m1.insert({my_token[1],s});
        cout<<s;
      }
        
      else if((it1 = m1.find(my_token[0])) != m1.end())
      {
        string s = m1[my_token[0]];
        char** temp = new char*[10];
        temp[0] = &s[0];
        temp[1] = NULL;
        execvp(temp[0],temp);
      }
      else 
       execvp(my_token[0], my_token);
       }
    else { 
        wait(NULL); 
        } 
}

int search_for_redirection(char** temp,int i)
{ int j;
  for(j=0;j<i;j++)
   {
      if(strcmp(temp[j],">")==0)
    { //cout<<"hello";
      outr = true;
      temp[j]=NULL;
      break;
    }
    else if(strcmp(temp[j],">>")==0)
    {
      append = true;
      temp[j]=NULL;
      break;
    }
   }
   return j;
}
void process_string(char str[]) 
{ //cout<<"str="<<str;

  char** token_arr = new char*[20];
    char* token = strtok(str, " "); 
    int i=0;
    while (token != NULL) 
    { 
       token_arr[i]= token;
       //cout<<token_arr[i]<<endl;
       token = strtok(NULL, " "); 
       i++;
    }   token_arr[i] = NULL;
    int j=0;
    int k;
    if(strcmp(token_arr[0],"echo")==0)
    {
      k=search_for_redirection(token_arr,i);
    }
    else {
      k=search_for_redirection(token_arr,i);
    }
   
    execArgs(token_arr,k);
    
} 

void sig_handler(int signo)
{
  signal(SIGINT, sig_handler);
  return ;
}

int main() 
{ 
  init_shell(); 
  inputmode();
  int exitshell=0;
  //signal(SIGINT, sigint_handler);
 signal(SIGINT, sig_handler);
  init_prompt();
   while (exitshell != 1)
   {  
    printprompt();
    int i=0;
    char c;
    char* c1 = (char*)malloc((sizeof(char))*2048);
    if(c1 == NULL)
    {
      cout<<"memory allo fail"<<endl;
      exit(EXIT_FAILURE);
    }
    while((c=getchar()) != '\n')
    {
      if(c == EOF)
      {
        free(c1);
        continue;
      }
      c1[i++]=c;
    }c1[i]='\0';
    v2.push_back(c1);
    if(strcmp(c1,"exit")==0)
    {
      exitshell =1;
    }
     process_string(c1); 
    
  }

    return 0; 
} 