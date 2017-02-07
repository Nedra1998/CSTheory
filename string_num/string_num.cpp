#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
int alphabet[128];

/*
 * int get_word_length()
 * int get_num_sym()
 * void print_trans_table()
 * void construct_trans_table()
 * */

int main(int argc, char *argv[]) {
  std::string file_contents;
  std::ifstream file(argv[1]);
  if (file.is_open()) {
    getline(file, file_contents);
    file.close();
  }
  long int input_file_size = file_contents.size();
  std::string word = argv[2];
  for (int i = 0; i < 128; i++) {
    alphabet[i] = 0;
  }
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

  int count = 0;
  // std::string str = "The special word \"" + word + "\" appears %i times.\n";
  printf("The special word \"%s\" appears %i times.\n", word.c_str(), count);
  // printf(str.c_str(), count);
}
