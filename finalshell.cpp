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
//int pipe_count =0;
bool outr =false;
bool append = false;
vector<string> v1;
vector<string>v2;
int prid;
void init_prompt();
bool flag1 =false;
void process_string(char str[]) ;
//int readInput();
unordered_map<char*,string> m1;
unordered_map<char*,string> :: iterator it1,it2;
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
    //cout<<ctr1[m]<<endl;
    //i++;
    m++;
    temp=strtok(NULL,":");
  }
  ctr1[m] = NULL;
  return ctr1;
}

char** splitsstr(char s[])
{
  char** ctr2 = new char*[20];

  char* temp2=strtok(s, " ");
  int m2=0;
  while(temp2!=NULL)
  {
    //cout<<temp<<endl;
    ctr2[m2] = temp2;
    //cout<<v[i]<<endl;
    //i++;
    m2++;
    temp2=strtok(NULL,":");
  }
  ctr2[m2] = NULL;
  return ctr2;
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

//////////////////////////////////////////////////////////////////
       FILE* file = fopen("/etc/passwd", "r");
    char line5[256];
    string s;
    int p = 0;

    while (fgets(line5, sizeof(line5), file)) {
        p++;
        if(p == 41 )
        {
            //printf("%s", line);  
            s = line5; 
            //cout<<s;
        }
    }
 
    fclose(file);
    char st[2000];
    int l;
    int len3 = s.size();
    for(l=0;l<len3;l++)
    {
      st[l]= s[l];
      //cout<<st[l];
    }
    st[l]='\0';
    char** chr = new char*[20];
    chr = splits1(st);
    //cout<<chr[0]<<endl;
    //cout<<chr[5]<<endl;
    fclose(file);
    //////////////////////////////////////////////////////////////////////
    char chara ='$';
    FILE* ofp;
    ofp = fopen("mybashrc4.txt","w");
    fprintf(ofp ,"%c\n" ,chara);
    fprintf(ofp,"%s",c1 );
    fprintf(ofp, "%s",c3 );
    fprintf(ofp, "%s\n",chr[0]);
    fprintf(ofp, "%s\n",chr[5]);
    fclose(ofp);
    //////////////////////////////////////////////////////////////////////

   string line2;
    int i1=0;
    ifstream ifp("mybashrc4.txt");
    if(ifp.is_open())
    {
      while(getline(ifp,line2))
  {
      v1.push_back(line2);
    }

  ifp.close();}
  ////////////////////////////////////////////////////////////////////
   /* FILE* fpr;
    string line2;
    int lengg = line2.size();
    ssize_t read;
    fpr = fopen("mybashrc4.txt","r");
    if(fpr == NULL)
    {
      cout<<"error while opening file"<<endl;
    }
    while((read = getline(line2 , lengg, fpr)) != -1)
    {
      v1.push_back(line2);
    }*/
  ////////////////////////////////////////////////////////////////////
  /*cout<<v1[0]<<endl;
  cout<<v1[1]<<endl;
  cout<<v1[2]<<endl;
  cout<<v1[3]<<endl;
  cout<<v1[4]<<endl;*/
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
   // cout<<"execlnsvln k andar hun mai.."<<endl;
     pid_t pid = fork(); 
     int chdir_rtrn; 
      if (pid <0) 
        { 
          printf("\nFailed forking child.."); 
          return; 
        } 
    else if (pid == 0) 
    {  //cout<<"baccha ban gya"<<endl;
        
        

        if(strcmp(my_token[0],"cd")==0)
      {  //cout<<"inside pid"<<endl;
         chdir_rtrn = change_dir(my_token);
        if(chdir_rtrn<0)
        {printf("Error while changing the directory, error is : %s",strerror(errno));}
        //execvp(my_token[0], my_token);

      } 
      else if(strcmp(my_token[0],"$$")==0)
      {
        //cout<<"inside $$"<<endl;
        cout<<prid<<endl;
      }

      else if(outr)// || append == true)
      { 
       // cout<<"redirection k andar"<<endl;
        my_token[k]=NULL;
        //cout<<my_token[k+1]<<endl;
        int fd;
        fd = open(my_token[k+1],O_WRONLY | O_CREAT ,0644);
          if(fd < 0)
          {
          cout<<"Cannot open file"<<endl;
          }
          else{
          dup2(fd,1);
          close(fd);
          outr = false;
          cout<<outr;}
          cout<<"toke" <<my_token[0]<<my_token[1]<<endl;
          if(execvp(my_token[0], my_token)<0)
          {
          cout<<"command not found"<<endl;
          }
        }
      else if(append)
      { 
          my_token[k]=NULL;
        //cout<<my_token[k+1]<<endl;
        int fd;
        //cout<<"append k andar"<<endl;
         fd = open(my_token[k+1],O_WRONLY|O_CREAT | O_APPEND,0644);
        if(fd < 0)
        {
          cout<<"Cannot open file"<<endl;
        }
        else{
        dup2(fd,1);
        close(fd);
        append = false;}
        if(execvp(my_token[0], my_token)<0)
        {
          cout<<"command not found"<<endl;
        }
      }
        
        
      
       else if(strcmp(my_token[0],"echo")==0)
      {  //cout<<v1[1]<<v1[2];
        //cout<<"echo wale k andar"<<endl;
        if(strcmp(my_token[1],"$HOME")==0)
        { //cout<<"home k anadr"<<endl;
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
          else if(strcmp(my_token[1],"$PS1")==0)
          {
          cout<<v1[0]<<endl;
          }
          else 
            {
              if(execvp(my_token[0], my_token)<0)
              {
                cout<<"command not found"<<endl;
              }  
            }  
      }
      else if(strcmp(my_token[0],"history")==0)
      {// cout<<"history k andar"<<endl;
        vector<string>::iterator it;
        it = v2.begin();
        while(it != v2.end())
        {
          cout<<*it<<endl;
          ++it;
        }
        
      }

      else if(strcmp(my_token[0],"alias")==0)
      { //cout<<"inside alias";
        //cout<<"ddd"<<my_token[3];
        int n=0;
        while(true)
        {if(strcmp(my_token[n],"=")!=0)
           {  n++;
            //cout<<"n=="<<n<<endl;
           }
          else
            break;
        }
        /*while(strcmp(my_token[3],"=")!=0)
        {
          n++;
        }
        cout<<"n="<<n;*/
        string ss(my_token[n+1]);

        ss = ss.substr(1);
        if(my_token[n+2] != NULL)
        {
        int m =0;
        while(my_token[m] != NULL)
        {
          m++;
        }
        string ss1(my_token[m-1]);
        int k = ss1.size();
        ss1 = ss1.substr(0,k-1);
         ss = ss + " " + ss1;
        }
        else 
          ss = ss.substr(0,ss.size()-1);
         m1.insert(pair<char*, string>(my_token[1], ss));
        // it1 = m1.find(my_token[1]);
          //if(it1 != m1.end())
         // {
            //cout<<it1->second<<" "<<it1->first<<endl;
         // } 
         // m1[my_token[1]] = ss;*/
      }
        
      else if(flag1)
      {
        //cout<<"alias1 ka dusra part"<<endl;
        string s = it2->second;
        //cout<<s<<endl;
        int length1 = s.size();
        //cout<<length1<<endl;
        char newchar[20];
        int i;
        for(i=0;i<length1;i++)
        {
          newchar[i] = s[i];
        }newchar[i] ='\0';
        /*for(int k =0;k<i;k++)
        {
          cout<<newchar[k];
        }*/
        char** new_token;
        new_token = splitsstr(newchar);
        if(execvp(new_token[0],new_token)<0)
        {
          cout<<"command not found"<<endl;
        }
      }
      else 
       { //cout<<"main command wale pagal k andar hun"<<endl;
        if(execvp(my_token[0], my_token)<0)
        {
          cout<<"command not found"<<endl;
        }
      }
       }

    else 
        { 
        wait(NULL); 
        } 
}
//////////////////////////////////////////////////////////////////////////////////////
char** process_string_inside_pipe(char* command)
{
    char** token_arr_cmd = new char*[20];
    char* token_cmd = strtok(command, " "); 
    int i=0;
    while (token_cmd != NULL) 
    { 
       token_arr_cmd[i]= token_cmd;
       //cout<<token_arr_cmd[i]<<endl;
       token_cmd = strtok(NULL, " "); 
       i++;
    }   token_arr_cmd[i] = NULL;
    return token_arr_cmd;
}
//////////////////////////////////////////////////////////////////////////////////////
 void my_fork_with_pipe(char** token_arr11,int pipe_count1)
 {  
  int file_des =0;
  int first_cmd =0;
    int pipe_file_des[2];
    int command_count = pipe_count1 + 1;
    int j=0;
    while(j<pipe_count1)
    {
      pipe(pipe_file_des);
      pid_t processid = fork();
    if(processid < 0)
    {
      cout<<"process creation failed"<<endl;
    }

    else if(processid ==0)
          {    
            
            dup2(file_des,STDIN_FILENO);
            //close(file_des);
            dup2(pipe_file_des[1],STDOUT_FILENO);
            close (pipe_file_des[1]);
            close(pipe_file_des[0]);
            //first_cmd =1;
            char** token_pipe = process_string_inside_pipe(token_arr11[j]);
            execvp(token_pipe[0],token_pipe);
   } 
   else 
      wait(NULL);
        close(pipe_file_des[1]);
       file_des = pipe_file_des[0];
       j++;
    }
    pipe(pipe_file_des);
    pid_t prcsid = fork();
    if(prcsid ==0 ){
    dup2(file_des,0);
     close(file_des);
      char** token_pipe = process_string_inside_pipe(token_arr11[j]);
      execvp(token_pipe[0],token_pipe);
    }
    else {
      wait(NULL);
      close(pipe_file_des[1]);
    }
 }
//////////////////////////////////////////////////////////////////////////////////////
int search_for_redirection(char** temp,int i)
{ int j;
  for(j=0;j<i;j++)
   {
      
    if(strcmp(temp[j],">>")==0)
    {
      append = true;
      temp[j]=NULL;
      break;
    }

    else if(strcmp(temp[j],">")==0)
    { //cout<<"hello";
      outr = true;
      temp[j]=NULL;
      break;
    }
   }
   return j;
}
/////////////////////////////////////////////////////////////////
void process_string_with_pipe(char str[],int pipe_count) 
{ //cout<<"str="<<str;

  char** token_arr1 = new char*[20];
    char* token1 = strtok(str, "|"); 
    int i=0;
    while (token1 != NULL) 
    { 
       token_arr1[i]= token1;
      // cout<<token_arr1[i]<<endl;
       token1 = strtok(NULL, "|"); 
       i++;
    }   token_arr1[i] = NULL;
    
    my_fork_with_pipe(token_arr1,pipe_count);
} 


////////////////////////////////////////////////////////////////////

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
  // cout<<"exerccc k andar jaa raha"<<endl;
   for(it2 = m1.begin();it2 != m1.end();it2++)
        {
          if(strcmp(it2->first,token_arr[0])==0)
          { //cout<<"map ka interator"<<endl;
            flag1 = true;
            break;
          }
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
  string s3;
  //signal(SIGINT, sigint_handler);
    signal(SIGINT, sig_handler);
  init_prompt();
   while (exitshell != 1)
   {  
    printprompt();
    int pipe_count =0;
    int i=0;
    char c;
    char* c1 = (char*)malloc((sizeof(char))*1024);
    string s;
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
        //continue;
        //break;
        //return;

      }
      c1[i++]=c;
      if(c =='|')
      {
        pipe_count++;
      }
    }c1[i]='\0';

    
   /* for(int k=0;k<=i;k++)
    {
      if(s[k] == "|")
      {

      }
    }*/

    v2.push_back(c1);
    if(strcmp(c1,"exit")==0)
    {
      exitshell =1;
    }
    //char** pr_st = new char*[50];
    //pr_st
    if(pipe_count != 0)
    {
      
      process_string_with_pipe(c1,pipe_count);
      
    } 
    else 
      {
        process_string(c1);
      }
    
    
  }

    return 0; 
} 