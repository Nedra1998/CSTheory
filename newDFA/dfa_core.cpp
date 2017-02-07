#include "dfa_core.hpp"
#include "fas/dfa.hpp"
#include <appareo.h>

using namespace appareo::curse;

namespace fa {
int titlewin, outputwin, actionwin, scriptwin, deltawindfa, deltawinndfa;
bool outputwinb = true, scriptwinb = true, deltawindfab = true,
     deltawinndfab = true;
}

void fa::Init() {
  titlewin = windows.size();
  InitializeWindow();
  windows[titlewin].CreateWindow("TITLE", -1, 3, -1, 0);
  out::PrintZ("Finite Automata", 5, titlewin);
  actionwin = windows.size();
  InitializeWindow();
  windows[actionwin].CreateWindow("ACTION", -1, 3, -1, scrheight - 3);
  out::PrintZ("New[n]   Quit[q]", 5, actionwin);
  std::vector<std::string> blocks = {};
  if (outputwinb == true) {
    blocks.push_back("Output");
  }
  if (deltawinndfab == true) {
    blocks.push_back("NDFA Delta");
  }
  if (deltawindfab == true) {
    blocks.push_back("DFA Delta");
  }
  if (scriptwinb == true) {
    blocks.push_back("Script");
  }
  if (blocks.size() != 0) {
    int blocksize = scrwidth / blocks.size();
    for (int i = 0; i < blocks.size(); i++) {
      if (blocks[i] == "Output") {
        outputwin = windows.size();
      } else if (blocks[i] == "NDFA Delta") {
        deltawinndfa = windows.size();
      } else if (blocks[i] == "DFA Delta") {
        deltawindfa = windows.size();
      } else if (blocks[i] == "Script") {
        scriptwin = windows.size();
      }
      InitializeWindow();
      win->CreateWindow(blocks[i], blocksize, scrheight - 6, blocksize * i, 3,
                        true, true);
    }
  }
}

void fa::Loop() {
  int in = 0;
  while (in != int('q')) {
    in = getch();
    if (in == int('n')) {
      New();
    }
  }
}

void fa::New() {
  Field newfield;
  newfield.name = "Deterministic";
  newfield.type = 3;
  newfield.bval = true;
  newfield = NewForm({newfield}, "New Automata", scrwidth / 2, 3)[0];
  if (newfield.bval == true) {
    DFA newdfa;
    newdfa.Init();
  } else if (newfield.bval == false) {
  }
}
