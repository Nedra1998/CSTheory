#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
int alphabet[128];
int transtable[100][128];
std::string word;
int wordchars = 0;

/*
 * int get_word_length()
 * int get_num_sym()
 * void print_trans_table()
 * void construct_trans_table()
 * */

void ConstructTransTable() {
  for (int i = 0; i < 128; i++) {
    for (int j = 0; j < wordchars; j++) {
      if (i == int(' ') || i == int('.') || i == int(',')) {
        transtable[j][i] = 2;
      } else {
        transtable[j][i] = 1;
      }
    }
  }
}

void LoadWordChars() {
  for (int i = 0; i < 128; i++) {
    if (alphabet[i] != 0) {
      wordchars++;
    }
  }
  wordchars += 1;
}

void DisplayTransTable() {
  std::string line = " |";
  for (int i = 32; i < 128; i++) {
    if (alphabet[i] != 0) {
      line += " ";
      line += char(i);
    }
  }
  printf("%s\n", line.c_str());
  line = std::string(100, '-');
  printf("%s\n", line.c_str());
  for (int i = 0; i < wordchars; i++) {
    line = "";
    for (int j = 0; j < 128; j++) {
      if (alphabet[j] != 0) {
        line += " ";
        line += std::to_string(transtable[i][j]);
      }
    }
    printf("%i|%s\n", i, line.c_str());
  }
}

int main(int argc, char *argv[]) {
  std::string file_contents;
  std::ifstream file(argv[1]);
  if (file.is_open()) {
    getline(file, file_contents);
    file.close();
  }
  long int input_file_size = file_contents.size();
  word = argv[2];
  for (int i = 0; i < 128; i++) {
    alphabet[i] = 0;
  }
  alphabet[int(' ')] = -1;
  alphabet[int('.')] = -1;
  alphabet[int(',')] = -1;
  for (int i = 0; i < word.size(); i++) {
    alphabet[int(word[i])]++;
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
  printf("\n\n");

  // DO STUFF HERE
  LoadWordChars();
  ConstructTransTable();
  DisplayTransTable();

  int count = 0;
  // std::string str = "The special word \"" + word + "\" appears %i times.\n";
  printf("The special word \"%s\" appears %i times.\n", word.c_str(), count);
  // printf(str.c_str(), count);
}
