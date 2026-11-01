// Pending members: the virtual members two vtables need and no source holds yet. These bodies are NOT the target's, they
// trap. Target functions, by slot, and what each waits for:
// comum::dao::CEleitorDinamicoDAO (@1558896), emitted by celeitordinamicodao.cpp with the destructor:
//   7  11542  RecuperarID (a chosen name): SELECT by the key; waits for fn 566, no-candidate
//   8   3766  RecuperarTodos (a chosen name): SELECT of every row; fns 566 and 5759, no-candidate
// comum::dao::CComparecimentoMesarioDAO (@1593352), emitted by ccomparecimentomesariodao.cpp with the destructor:
//   7  10402  RecuperarID (a chosen name): waits for fns 566, 2730 and 2731, no-candidate (its converters 5390 and 5391
//             are written and match)
//   8  10401  RecuperarTodos (a chosen name): the same three
// Move each member into its class's .cpp when it is written; delete this file with the last one.
#include "app/comum/comparecimentomesario/dao/ccomparecimentomesariodao.h"
#include "app/comum/dados/dao/celeitordinamicodao.h"

namespace comum::dao {

std::shared_ptr<CEleitorDinamicoDAO::TDado> CEleitorDinamicoDAO::RecuperarID(const TDadoID&) const
{
    __builtin_trap();
}

std::vector<CEleitorDinamicoDAO::TDado> CEleitorDinamicoDAO::RecuperarTodos() const
{
    __builtin_trap();
}

std::shared_ptr<CComparecimentoMesarioDAO::TDado> CComparecimentoMesarioDAO::RecuperarID(const TDadoID&) const
{
    __builtin_trap();
}

std::vector<CComparecimentoMesarioDAO::TDado> CComparecimentoMesarioDAO::RecuperarTodos() const
{
    __builtin_trap();
}

} // namespace comum::dao
