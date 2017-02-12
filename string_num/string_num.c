#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Table used to determin which charecters are present in the word
int alphabet[128];
// Transition table to runninging the dfa
int transtable[100][128];
// String containing special word
char *word;
// String containing contents of specified file to search
char *file_contents;
int input_file_size;
// Counter of number of times the special word appear
int wordcount = 0;

// Used to get the length of the special word
int GetLength(char *str) { return (strlen(word)); }

// Runs the dfa
void RunDFA() {
  // Sets the current state as 0
  int current_state = 0;
  int char_index = 0;
  // Loop through the length of the file
  for (int i = 0; i < input_file_size; i++) {
    // Gets the alphabet index for the current character from intput file
    char_index = file_contents[i];
    // If the current character is capital, convert it to lowercase
    if (char_index >= 65 && char_index <= 90) {
      char_index += 32;
    }
    // Sets the new current state to the the transition table says at the
    // current state, and the given letter from alphabet
    current_state = transtable[current_state][char_index];
    // If the new current state is the final state add one to the word counter
    // and transition imidiatly
    if (current_state == GetLength(word) + 3) {
      wordcount += 1;
      current_state = transtable[current_state][char_index];
    }
  }
}

// Constructs the transition table to the dfa to run from
void ConstructTransTable() {
  // For loop that runs through all characters
  for (int i = 0; i < 128; i++) {
    // For loop that runs through the number of states
    for (int j = 0; j < GetLength(word) + 4; j++) {
      // If the current character is PCS automaticaly sets state othersize
      // transition to state 1
      if (i == ' ' || i == '.' || i == ',') {
        // If the current state is seconed to last, then transition to the final
        // state otherwise transition back to state 2
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
  // Loop to conect each letter state to the next letter state
  while (current_char < GetLength(word)) {
    // Gets the alphabet position of the current char
    char_index = word[current_char];
    // Sets the transition from the current state given the current letter from
    // the word to be the next state
    transtable[current_state][char_index] = current_state + 1;
    // Moves up to the next state and next letter in the word
    current_state++;
    current_char++;
  }
  current_state++;
  // Sets all transitions from the final state to be back to state 2
  for (int i = 0; i < 128; i++) {
    transtable[current_state][i] = 2;
  }
}

// Displays the transition table
void DisplayTransTable() {
  // Prints the row of the alphabet characters that have intrest to the program
  printf(" |");
  for (int i = 0; i < 128; i++) {
    if (alphabet[i] != 0) {
      printf(" %c", i);
    }
  }
  printf("\n--------------------\n");
  // Prints the grid of transition table from alphabet characters that have
  // intrest
  for (int i = 0; i < GetLength(word) + 4; i++) {
    printf("%i|", i);
    for (int j = 0; j < 128; j++) {
      if (alphabet[j] != 0) {
        printf(" %i", transtable[i][j]);
      }
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  // Loading input file contents, and special word
  FILE *input_file = fopen(argv[1], "rb");
  fseek(input_file, 0, SEEK_END);
  input_file_size = ftell(input_file);
  rewind(input_file);
  file_contents = malloc(input_file_size * (sizeof(char)));
  fread(file_contents, sizeof(char), input_file_size, input_file);
  fclose(input_file);
  file_contents[input_file_size] = '\0';
  word = argv[2];

  // Setting the alphabet to all zeroes
  for (int i = 0; i < 128; i++) {
    alphabet[i] = 0;
  }
  // Manualy setting important characters in the alphabet
  alphabet[' '] = -1;
  alphabet['.'] = -1;
  alphabet[','] = -1;
  // Addind the occurances of characters from the special word to the alphabet
  // table
  for (int i = 0; i < GetLength(word); i++) {
    // If the letter in word is upper case save the lower case vale instead into
    // alphabet
    if (word[i] >= 65 && word[i] <= 90) {
      word[i] += 32;
    }
    alphabet[word[i] + 0]++;
  }
  // Prints file contents with quotation marks around it
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

  printf("The special word \"%s\" appaears %i times.\n", word, wordcount);
  return 0;
}
