#ifndef DFA_CORE_HPP
#define DFA_CORE_HPP
namespace fa {
extern int titlewin, outputwin, actionwin, scriptwin, deltawindfa, deltawinndfa;
extern bool outputwinb, scriptwinb, deltawindfab, deltawinndfab;
void Init();
void Loop();
void New();
}
#endif
