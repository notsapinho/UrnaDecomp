// Pending members: the virtual members a vtable needs and no source holds yet. These bodies are NOT the target's, they
// trap. Target functions, by slot, and what each waits for:
// comum::dao::CComparecimentoMesarioDAO (@1593352), emitted by ccomparecimentomesariodao.cpp with the destructor:
//   7  10402  RecuperarID (a chosen name): waits for fns 2730 and 2731, no-candidate (its converters 5390 and 5391 and
//             CEleitorIdentidade's constructor 566 are written and match)
//   8  10401  RecuperarTodos (a chosen name): the same two
// Move each member into its class's .cpp when it is written; delete this file with the last one.
#include "app/comum/comparecimentomesario/dao/ccomparecimentomesariodao.h"

namespace comum::dao {

std::shared_ptr<CComparecimentoMesarioDAO::TDado> CComparecimentoMesarioDAO::RecuperarID(const TDadoID&) const
{
    __builtin_trap();
}

std::vector<CComparecimentoMesarioDAO::TDado> CComparecimentoMesarioDAO::RecuperarTodos() const
{
    __builtin_trap();
}

} // namespace comum::dao
