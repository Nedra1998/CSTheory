#include "dfa.hpp"
#include <appareo.h>

using namespace appareo::curse;

void fa::DFA::Init() {
  std::vector<Field> fields;
  Field newfield;
  newfield.name = "States";
  newfield.type = 4;
  newfield.sval = "0";
  fields.push_back(newfield);
  newfield.name = "Language";
  newfield.name = "Language";
  newfield.type = 4;
  newfield.sval = "0,1";
  fields.push_back(newfield);
  newfield.name = "Starting State";
  newfield.type = 4;
  newfield.sval = "0";
  fields.push_back(newfield);
  newfield.name = "Success States";
  newfield.type = 4;
  newfield.sval = "0";
  fields.push_back(newfield);
  fields = NewForm(fields, "New Automaton", scrwidth / 2, scrheight / 2);
  std::string str = "";
  for (int i = 0; i < fields[0].sval.size(); i++) {
    if (fields[0].sval[i] == ',') {
      states.push_back(str);
      str = "";
    } else {
      str += fields[0].sval[i];
    }
  }
  states.push_back(str);
  for (int i = 0; i < fields[1].sval.size(); i++) {
    if (fields[1].sval[i] != ',') {
      language.push_back(fields[1].sval[i]);
    }
  }
  str = "";
  startingstate = fields[2].sval;
  for (int i = 0; i < fields[3].sval.size(); i++) {
    if (fields[3].sval[i] == ',') {
      successstates.push_back(str);
      str = "";
    } else {
      str += fields[3].sval[i];
    }
  }
  successstates.push_back(str);
  for (int i = 0; i < states.size(); i++) {
    std::vector<std::string> changes;
    for (int j = 0; j < language.size(); j++) {
      changes.push_back(states[0]);
    }
    delta.push_back(changes);
  }
  GetDelta();
}

void fa::DFA::GetDelta() {
  int x = 0, y = 0;
  int xsize = (scrwidth - 10) / language.size();
  int ysize = (scrheight - 10) / states.size();
  int input = 0;
  InitializeWindow();
  windows[1].CreateWindow("Delta Table", scrwidth - 10, scrheight - 10, -1, -1,
                          true, true);
  while (input != 10) {
    windows[1].Clear();
    std::string str = "";
    for (int i = 0; i < language.size(); i++) {
      str += language[i];
      out::Print(str, 1, (i + 1) * xsize + 1 - (xsize / 2), 1);
      str = "";
    }
    for (int i = 0; i < states.size(); i++) {
      str = states[i];
      out::Print(str, (i + 1) * ysize + 1 - (ysize / 2), 1, 1);
    }
    for (int i = 0; i < delta.size(); i++) {
      for (int j = 0; j < delta[i].size(); j++) {
        str = delta[i][j];
        if (i == y && j == x) {
          out::SetAtt({out::STANDOUT}, 1);
        }
        out::Print(str, (i + 1) * ysize + 1 - (ysize / 2),
                   (j + 1) * xsize + 1 - (xsize / 2), 1);
        if (i == y && j == x) {
          out::SetAtt({out::NORMAL}, 1);
        }
      }
    }
    input = wgetch(windows[1].windowpointer);
    if (input == KEY_UP) {
      if (y > 0) {
        y--;
      }
    } else if (input == KEY_DOWN) {
      if (y < states.size() - 1) {
        y++;
      }
    } else if (input == KEY_LEFT) {
      if (x > 0) {
        x--;
      }
    } else if (input == KEY_RIGHT) {
      if (x < language.size() - 1) {
        x++;
      }
    } else if (input == KEY_BACKSPACE) {
      if (delta[y][x].size() > 0) {
        delta[y][x].pop_back();
      }
    } else if (input != 10) {
      delta[y][x] += char(input);
    }
  }
  TerminateWindow(1);
}
