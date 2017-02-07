#ifndef DFA_HPP
#define DFA_HPP
#include <string>
#include <vector>
namespace fa {
class DFA {
public:
  void Init();
  void GetDelta();

private:
  std::string startingstate;
  std::vector<std::string> states;
  std::vector<std::string> successstates;
  std::vector<char> language;
  std::vector<std::vector<std::string>> delta;
};
}
#endif
