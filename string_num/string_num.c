#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int alphabet[128];
int transtable[100][128];
char *word;
char *file_contents;
int wordcount = 0;

int GetLength(char *str) { return (strlen(word)); }

void RunDFA() {
  int current_state = 0;
  int char_index = 0;
  for (int i = 0; i < GetLength(file_contents); i++) {
    char_index = file_contents[i];
    if (char_index >= 65 && char_index <= 90) {
      char_index += 32;
    }
    current_state = transtable[current_state][char_index];
    if (current_state == GetLength(word) + 3) {
      wordcount++;
      current_state = 2;
    }
  }
}

void ConstructTransTable() {
  for (int i = 0; i < 128; i++) {
    for (int j = 0; j < GetLength(word) + 4; j++) {
      if (i == ' ' || i == '.' || i == ',') {
        if (j == GetLength(word) + 2) {
          transtable[j][i] = GetLength(word) + 3;
        } else {
          transtable[j][i] = 2;
        }
      } else {
        transtable[j][i] = 1;
      }
    }
  }
  int current_state = 2;
  int current_char = 0;
  int char_index = word[current_char];
  transtable[0][char_index] = 3;
  while (current_char < GetLength(word)) {
    char_index = word[current_char];
    transtable[current_state][char_index] = current_state + 1;
    current_state++;
    current_char++;
  }
  current_state++;
  for (int i = 0; i < 128; i++) {
    transtable[current_state][i] = 2;
  }
}

void DisplayTransTable() {
  char *line = " |";
  for (int i = 0; i < 128; i++) {
    if (alphabet[i] != 0) {
      line[GetLength(line) + 1] = ' ';
      line[GetLength(line) + 1] = i;
    }
  }
  printf("%s\n", line);
  line = "--------------------";
  printf("%s\n", line);
  for (int i = 0; i < GetLength(word) + 4; i++) {
    line = "";
    for (int j = 0; j < 128; j++) {
      if (alphabet[j] != 0) {
        line[GetLength(line) + 1] = ' ';
        line[GetLength(line) + 1] = transtable[i][j];
      }
    }
    printf("%i|%s\n", i, line);
  }
}

int main(int argc, char *argv[]) {
  long int input_file_size;
  FILE *input_file = fopen(argv[1], "rb");
  fseek(input_file, 0, SEEK_END);
  input_file_size = ftell(input_file);
  rewind(input_file);
  file_contents = malloc(input_file_size * (sizeof(char)));
  fread(file_contents, sizeof(char), input_file_size, input_file);
  fclose(input_file);
  file_contents[input_file_size] = '\0';
  word = argv[2];

  for (int i = 0; i < 128; i++) {
    alphabet[i] = 0;
  }
  alphabet[' '] = -1;
  alphabet['.'] = -1;
  alphabet[','] = -1;
  for (int i = 0; i < GetLength(word); i++) {
    if (word[i] >= 65 && word[i] <= 90) {
      alphabet[word[i] + 32]++;
    } else {
      alphabet[word[i] + 0]++;
    }
  }
  int flag = 0;
  printf("\"");
  for (int k = 0; k < input_file_size; k++) {
    if (file_contents[k] == '\n') {
      printf("\"");
      flag = 1;
    }
    printf("%c", file_contents[k]);
  }
  if (flag == 0) {
    printf("\"");
  }
  printf("\n");

  ConstructTransTable();
  DisplayTransTable();
  RunDFA();

  printf("\n\n");

  int count = 0;
  printf("The special word \"%s\" appaears %i times.\n", word, count);
  return 0;
}
