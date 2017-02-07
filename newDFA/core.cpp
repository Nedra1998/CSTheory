#include "dfa_core.hpp"
#include <appareo.h>
#include <math.h>
#include <ncurses.h>
#include <pessum.h>
#include <vector>

using namespace appareo::curse;

int main(int argc, char const *argv[]) {
  appareo::InitializeAppareo();
  fa::Init();
  fa::Loop();
  appareo::TerminateAppareo();
  return 0;
}
