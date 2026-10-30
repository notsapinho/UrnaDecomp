// Pending members: the virtual members comum::dao::CJustificadorDAO's vtable (@1560760) needs and no source holds yet.
// cjustificadordao.cpp emits the vtable with the destructor, the key function here. These bodies are NOT the target's,
// they trap. Target functions, by slot of the vtable, and what each waits for:
//   7  11470  RecuperarID (a chosen name): SELECT by the key; fn 1875, no-candidate, builds the row's data
//   8  11469  RecuperarTodos (a chosen name): SELECT of every row, fns 1875 and 5831, no-candidate
// Move each member into cjustificadordao.cpp when it is written; delete this file with the last one.
#include "app/comum/justificativa/dao/cjustificadordao.h"

namespace comum::dao {

std::shared_ptr<CJustificadorDAO::TDado> CJustificadorDAO::RecuperarID(const TDadoID&) const
{
    __builtin_trap();
}

std::vector<CJustificadorDAO::TDado> CJustificadorDAO::RecuperarTodos() const
{
    __builtin_trap();
}

} // namespace comum::dao
