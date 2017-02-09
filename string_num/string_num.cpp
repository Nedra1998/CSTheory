#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
// Time: 1:08
int alphabet[128];
int transtable[100][128];
std::string word;
std::string file_contents;
int wordcount = 0;

void RunDFA() {
  int currentstate = 0;
  int charindex = -1;
  for (int i = 0; i < file_contents.size(); i++) {
    charindex = int(file_contents[i]);
    if (charindex >= 65 && charindex <= 90) {
      charindex += 32;
    }
    currentstate = transtable[currentstate][charindex];
    if (currentstate == word.size() + 3) {
      wordcount++;
      currentstate = 2;
    }
  }
}

void ConstructTransTable() {
  for (int i = 0; i < 128; i++) {
    for (int j = 0; j < word.size() + 4; j++) {
      if (i == int(' ') || i == int('.') || i == int(',')) {
        if (j == word.size() + 2) {
          transtable[j][i] = word.size() + 3;
        } else {
          transtable[j][i] = 2;
        }
      } else {
        transtable[j][i] = 1;
      }
    }
  }
  int currentstate = 2;
  int currentchar = 0;
  transtable[0][int(word[currentchar])] = 3;
  while (currentchar < word.size()) {
    transtable[currentstate][int(word[currentchar])] = currentstate + 1;
    currentstate++;
    currentchar++;
  }
  currentstate++;
  for (int i = 0; i < 128; i++) {
    transtable[currentstate][i] = 2;
  }
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
  for (int i = 0; i < word.size() + 4; i++) {
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
    if (int(word[i]) >= 65 && int(word[i]) <= 90) {
      alphabet[int(word[i]) + 32]++;
    } else {
      alphabet[int(word[i])]++;
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
  printf("\n\n");

  ConstructTransTable();
  DisplayTransTable();
  RunDFA();
  printf("\n\n");

  printf("The special word \"%s\" appears %i times.\n", word.c_str(),
         wordcount);
}
