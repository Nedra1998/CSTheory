#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int alphabet[128];

/*
 * int get_word_length()
 * int get_num_sym()
 * void print_trans_table()
 * void construct_trans_table()
 * */


int main(int argc, char *argv[]){
  char *file_contents;
  long int input_file_size;
  FILE *input_file = fopen(argv[1], "rb");
  fseek(input_file, 0, SEEK_END);
  input_file_size = ftell(input_file);
  rewind(input_file);
  file_contents = malloc(input_file_size * (sizeof(char)));
  fread(file_contents, sizeof(char), input_file_size, input_file);
  fclose(input_file);
  file_contents[input_file_size]='\0';
  char *word = argv[2];
  char trans_table[100][128];
  for(int i = 0; i < 128;i++){
    alphabet[i] = 0;
  }

  int flag = 0;
  int k;
  printf("\"");
  for(k = 0;k<input_file_size;k++){
    if(file_contents[k] == '\n'){
      printf("\"");
      flag = 1;
    }
    printf("%c", file_contents[k]);
  }
  if(flag == 0){
    printf("\"");
  }
  printf("\n");

  //DO STUFF HERE
  
  int count = 0;
  printf("The special word \"%s\" appaears %i times.\n", word, count);
}
