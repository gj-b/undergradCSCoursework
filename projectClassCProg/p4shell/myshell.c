#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void error()
{
  char error_message[30] = "An error has occurred\n";
  write(STDOUT_FILENO, error_message, strlen(error_message));
}

void myPrint(char *msg)
{
    write(STDOUT_FILENO, msg, strlen(msg));
}

int sizeofCMD(char* input)
{
  char* ptr_mov;
  int strlength = strlen(input);
  char* strdup = malloc((strlength + 1)*sizeof(char));
  strcpy(strdup,input);
  int count = 0;
  int last = 0;
  ptr_mov = strdup;
  while(*ptr_mov != '\0')
  {
    if((*ptr_mov == ' ') || (*ptr_mov == '\t') || (*ptr_mov == '\n')) 
    {
      last = 0;
    }
    else if(last == 0)
    {
      last = 1;
      count++;
    }
    *ptr_mov++;
  }
  free(strdup);
  return count;
}

int num_comm_input(char* input)
{
  int strlength = strlen(input);
  int i;
  int count = 1;
  for(i=0; i<strlength; i++)
  {
    if(input[i] == ';')
    {
      count++;
    }
  }
  return count;
}

/*void parse_and_colons(char *input, char** all_comm[], int num_comm)
{

}*/ //args and multiplecommand
void read_cmd(char *input, char* sorted[], int size)
{
  int i=0; 
  char *token[514];
  char delmit[] = "\t\n ";
  token[i] = strtok(input, delmit);
  while (token[i] != NULL)
  {
    sorted[i] = token[i];
    i++;
    token[i] = strtok(NULL, delmit);
  }
  sorted[i] = NULL;
}

void change_dir(char **input)
{
  char cwd[514];
  char* curr = getcwd(cwd,sizeof(cwd));
  char postwd[514];
  char* post;

  if(input[1] == NULL)
  {
    chdir(getenv("HOME")); 
    return;
  }
  if(input[2] != NULL)
  {
    error();
  }
  else
  {
  int val = chdir(input[1]);
  if(val != 0)
    error(); 
 // char* post = getcwd(postwd,sizeof(postwd));
  //if(strcmp(curr,post) == 0)
   // error();
  }
}

void print_working(char **input)
{
  char cwd[514];
  getcwd(cwd, sizeof(cwd));
  myPrint(strcat(cwd,"\n")); 
}

int redir(char **input)
{
  
  int place = 0;
  int i = 0;
  while(input[i] != NULL)
  {
    if(strstr(input[i],">") != NULL)
    {
      place = i;
      break;
    }
    else
    {
      i++;
    }
  }
    return place;
} //dad

int redir_symb_present(char *input, char value)
{
  char* ptr_mov;
  int num_words = strlen(input);
  int i,j;

  for(i=0; i<num_words; i++)
  {
      if(input[i] == value)
        return 1;
  }
  return 0;
}

int larger_redir_symb_present(char *input[], int size, char value)
{
  int i = 0;
  int val = 0;
  int count = 0;
  while(input[i] != NULL)
  {
    val = redir_symb_present(input[i], value);
    if(val == 1)
       count++;
    i++;
  }
  return count;
}


int cd_symb_present(char *input)
{
  char* ptr_mov;
  int strlength = strlen(input);
  char* strdup = malloc((strlength + 1)*sizeof(char));
  strcpy(strdup,input);
  int present = 0;
  ptr_mov = strdup;
  while(*ptr_mov != '\0')
  {
    if((*ptr_mov == 'c') && (*ptr_mov++ == 'd')) 
      {
        present = 1;
        return present;
      }  
    *ptr_mov++;
  }
  free(strdup);
  return 0;
}
void run_redir(char **input, int size)
{
  //File will always be in the last spot
  int status;
  pid_t child;
  char *name = input[size - 1];
   input[size - 1] = NULL;
  // printf("%d\n",size);
  if(name == NULL)
  {
    error();
    return;
  }


  if(access(name, F_OK) != -1) //Making sure file doesn't already exist 
  {
    error();
    return;
  }
  else
  {
    if(fopen(name, "w") == NULL)
      {
        error();
        return;
      }

      child = getpid();
          switch (child = fork())
          {
            case -1:
              myPrint("Problem with forking");
            case 0:
              freopen(name, "w", stdout);
              execvp(input[0],input);
              myPrint("Problem with execvp");
                
            default:
              waitpid(child, &status, WUNTRACED);  
          }
    }
}
//asdf
int adv_redir(char **input)
{
  
  int place = 0;
  int i = 0;
  while(input[i] != NULL)
  {
    if((strcmp(input[i],">") == 0) && (strcmp(input[i+1], "+") == 0))
    {
      place = i;
      return place;
    }
    else
    {
      i++;
    }
  }
  return 0;
}

void adv_run_redir(char **input, int place)
{
  int status;
  pid_t child;
  char *name = input[place + 1];
 // FILE *fp = popen(name, "w");
  //Have to set ">" marker as null.
  input[place] = NULL;
  child = getpid();
          switch (child = fork())
          {
            case -1:
              myPrint("Problem with forking");
            case 0:
              freopen(name, "w", stdout);
             // int fd = open(file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
              execvp(input[0],input);
              //pclose(fp);
              myPrint("Problem with execvp");
            default:
              waitpid(child, &status, WUNTRACED);  
          }
}

int num_args(char* sorted[])
{
  int i=0;
  int size=0;
  while(sorted[i] != NULL)
  {
    size++;
    i++;
  }
  return size;
}

void break_up_redir(char* input, int size, char* new[])
{
  char* brkup_redir[size+2];
  int i=0;
  char *token[514];
  int size_arg;
  char delmit[] = "> \t \n";
 // printf("%s\n",input);
  token[i] = strtok(input,delmit);
  //char* cmd_list[size+1];
  while(token[i] != NULL)
  {
    new[i] = token[i];
    i++;
    token[i] = strtok(NULL,delmit);
  }
  new[i] = NULL;
  //return brkup_redir;
}


int adv_redir_symb_present(char *input)
{
  char* ptr_mov;
  int num_words = strlen(input);
  int i,j;

  for(i=0; i<num_words; i++)
  {
      if(strstr(input[i],">+" != NULL))
        return 1;
  }
  return 0;
}

int adv_larger_redir_symb_present(char *input[])
{
  int i = 0;
  int val = 0;
  int count = 0;
  while(input[i] != NULL)
  {
    if(strstr(input[i],">+"))
      count++;
    i++;
  }
  return count;
}

void break_up_adv_redir(char* input, int size, char* new[])
{
  char* brkup_redir[size+2];
  int i=0;
  char *token[514];
  int size_arg;
  char delmit[] = ">+ \t \n";
 // printf("%s\n",input);
  token[i] = strtok(input,delmit);
  //char* cmd_list[size+1];
  while(token[i] != NULL)
  {
    new[i] = token[i];
    i++;
    token[i] = strtok(NULL,delmit);
  }
  new[i] = NULL;
  //return brkup_redir;
}

void merge_files(char *given, char *temp)
{
  char* tmp_fin = "temp_final.txt";
  FILE *temp_final = fopen(tmp_fin,"w");
  FILE *temp_made = fopen(temp,"r");
  FILE *given_file = fopen(given,"r");

  char cont;
  if(temp_final == NULL || temp_made == NULL || given_file == NULL)
  {
    printf("error at one of files is NULL\n");
    error();
    exit(0);
  }

  while((cont = fgetc(temp_made)) != EOF)
    fputc(cont, temp_final);

  while((cont = fgetc(given_file)) != EOF)
    fputc(cont,temp_final);

  fclose(temp_final);
  fclose(given_file);

  FILE *tmp_final = fopen(tmp_fin,"r");
  FILE *final = fopen(given,"w");

  while((cont = fgetc(tmp_final)) != EOF)
    fputc(cont,final);

  fclose(final);
  fclose(tmp_final);
  fclose(temp_made);

  //remove(temp_final);
  //remove(temp_made);
}

void run_adv_redir(char **input, int size)
{
  //File will always be in the last spot
  int status;
  int errnum;
  pid_t child;
  

  char* temp_input[size];

  int i=0;

  while(input[i] != NULL)
  {
    temp_input[i] = input[i];
    i++;
  }

  char *name = input[size - 1];


   i = 0;
  for(i=0; i< strlen(name); i++)
  {
    name[i];
  }
  char *temp = "temp.txt";

  input[size - 1] = NULL;
  if(name == NULL)
  {
    error();
    return;
  }


  if(access(name, F_OK) == -1) //Making sure file doesn't already exist 
  {
    run_redir(temp_input,size);
    //printf("error at run_redir\n");
    return;
  }
  else
  {
    FILE *file = fopen(name,"r");
    if(file == NULL)
      {

        error();
        return;
      }

    child = getpid();
          switch (child = fork())
          {
            case -1:
              myPrint("Problem with forking");
            case 0:
              freopen(temp, "w", stdout);
              execvp(input[0],input);
              myPrint("Problem with execvp");
                
            default:
              waitpid(child, &status, WUNTRACED);  
          }
    }
    merge_files(name, temp);
}

void execute(char* orig, char* sorted[], int size)
{
  int redir_place = redir(sorted);
  char temp[strlen(orig)];
  strcpy(temp,orig);
  int length = strlen(temp);
  int last_char_pos = 0;
  int i = 0;
  
  
  
  //printf("%c\n",last_char );
  int status;
  pid_t child;
  int adv_redir_present = adv_larger_redir_symb_present(sorted);
  int red_present = larger_redir_symb_present(sorted,size,'>');
  int size_str = 0;
  int size_str_new_line = 0;
  
    while(temp[i] != '\n') 
    {
      size_str_new_line++;
      i++;
    }

  i = 0;
  int size_str_end_string = 0;
  while(temp[i] != '\0') 
    {
      size_str_end_string++;
      i++;
    }

    if(size_str_end_string >= size_str_new_line)
      size_str = size_str_new_line;

    if(size_str_new_line>size_str_end_string)
      size_str = size_str_end_string;

  char last_char = temp[size_str - 1];


    if(sorted[0] == NULL)
      return;

    if(strstr(sorted[0],"cd") != NULL)
    {
      //if(sorted[1] != NULL)
      //{
        if(larger_redir_symb_present(sorted,size,'>'))//if(strcmp(sorted[1],">") == 0)
        {
          error();
          return;
        }
     // }
      if(strcmp(sorted[0],"cd") == 0)
      {
        change_dir(sorted);
      }
      else
      {

        error();
        return;
      }
    }

    //else if(strcmp(sorted[0],"exit") == 0)
    else if(strstr(sorted[0],"exit") != NULL)
    {
      if(sorted[1] != NULL)
      {
        error();
        return;
      }
      if(strcmp(sorted[0],"exit") == 0)
      {
        exit(0);
      }
      else
      {
        error();
        return;
      } 
    }

    //else if(strcmp(sorted[0],"pwd") == 0)
    else if(strstr(sorted[0],"pwd") != NULL)
    {
      if(sorted[1] != NULL)
      {
        error();
        return;
      }
      if(strcmp(sorted[0],"pwd") == 0)
      {
        print_working(sorted);
      }
      else
      {
        error();
        return;
      }
    }
     
  else if(adv_redir_present)
  {
    char *new_sorted[size+2];
    break_up_adv_redir(orig,size,new_sorted);
    int size = num_args(new_sorted);

    if(size == 0)
      {
        error();
        return;
      }
    if(larger_redir_symb_present(sorted,size,'>') > 1)
    {
      error();
      return;
    }

    if((last_char == '>') || (last_char == '+'))
    {
      error();
      return;
    }
    run_adv_redir(new_sorted,size);
  } 

  else if(red_present)
  {
    char* new_sorted[size+2];
    break_up_redir(orig,size,new_sorted);
    int size = num_args(new_sorted);
    //printf("%s\n",orig);

    if(size == 0)
      {
        error();
        return;
      }
    if(larger_redir_symb_present(sorted,size,'>') > 1)
    {
      error();
      return;
    }

    if(last_char == '>')
    {
      error();
      return;
    }
    run_redir(new_sorted,size);
  }
 
  else
  {
    child = getpid();
    switch (child = fork())
    {
      case -1:
        myPrint("Problem with forking");
      case 0:
        execvp(sorted[0],sorted);
        child = getpid();
        //printf("error at execv\n");
        error();
        kill(child,SIGTERM);
      default:
        waitpid(child, &status, WUNTRACED);
    } 
  }
}

void sep_cmd(char *input, char* input2, char* cmd_list[], int num_com, char* sorted[], int num_arg)
{
  int i=0;
  char *token[514];
  int size_arg;
  char delmit[] = ";";
  token[i] = strtok(input,delmit);
  //char* cmd_list[size+1];
  while(token[i] != NULL)
  {
    cmd_list[i] = token[i];
    i++;
    token[i] = strtok(NULL,delmit);
  }
  cmd_list[i] = NULL;
 // printf("%s\n",cmd_list[0]);
  //printf("%d\n",strlen(cmd_list[0]));
  i=0;
  while(cmd_list[i] != NULL)
  {
    //printf("%d\n",sizeof(cmd_list[i])); 
    char temp[strlen(cmd_list[i])];
    strcpy(temp,cmd_list[i]);
    //printf("%s\n",cmd_list[i]);

    read_cmd(cmd_list[i],sorted,num_arg);
    //printf("%s\n",temp);
    execute(temp,sorted,num_arg);
    i++;
  }
}

int main(int argc, char *argv[]) 
{
    char cmd_buff[1024];
    char *pinput;
    char *used;
    pid_t child, parent;
    int t, i = 0;
    int num_arg;
    int status;
    int redir_place;
    int adv_redir_place;
    int num_com;
    FILE* fp = fopen(argv[1], "r");
    if(fp == NULL)
    {
      error();
    //  exit(1);
    }
    //chdir(getenv("HOME"));
    //  while(1)
   

      while(!feof(fp)) //while(!feof(fp))
      {
        fgets(cmd_buff, 1024, fp);


        if(sizeofCMD(cmd_buff) == 0)
          continue;
        if(feof(fp))
          continue;

        write(STDOUT_FILENO, cmd_buff, strlen(cmd_buff));
       // printf("%d \n",strlen(cmd_buff));
        //myPrint("myshell> "); 
        if(sizeofCMD(cmd_buff) &&  (strlen(cmd_buff) < 515))
        {
          num_arg = sizeofCMD(cmd_buff);
          num_com = num_comm_input(cmd_buff);
          char *cmd_list[num_com+1];
          char* sorted[num_arg+1];
          sep_cmd(cmd_buff, cmd_buff,cmd_list,num_com,sorted,num_arg);
        }
        else if(strlen(cmd_buff) > 514)
        {
          error();
        }
      
      }
}