// Pending members: the virtual members comum::dao::CJustificadorDAO's vtable (@1560760) needs and no source holds yet.
// cjustificadordao.cpp emits the vtable with the destructor, the key function here. These bodies are NOT the target's,
// they trap. Target functions, by slot of the vtable, and what each waits for:
//   2  11468  Clone (a chosen name, api/persistencia/idao.h), `return new CJustificadorDAO(*this);`. A merge thunk,
//             f3894(this, vptr): fn 3894 is binaryen's merge of the three DAOs' Clone (10399, 11468, 11541), so it
//             matches once comum::dao::CEleitorDinamicoDAO and CComparecimentoMesarioDAO have theirs
//   4  11467  the base's default, IUenuxGenericDAO<CIdentificacaoJustificativa, std::string>::Excluir, record
//             api/persistencia/iuenuxgenericdao.h:41:15, code 6804. A merge thunk into fn 2297 with four other defaults.
//             iuenuxgenericdao.h does not define it yet, and every DAO compiles that header, so this file defines this one
//             instantiation as an explicit specialization, with the symbol the vtable references. Delete it when the
//             header defines the default: a strong symbol with that name would keep this trap in the vtable with no word
//   5  11472  ExcluirID, record cjustificadordao.cpp:56:11, code 8804 of a CBaseError<comum::EUeComumJustificativaError,
//             {8800, 8850}>, whose header and constructor (fn 2260, no-candidate) are not in this tree
//   6  11471  Atualizar, record cjustificadordao.cpp:63:11, code 8805, the same
//   7  11470  RecuperarID (a chosen name): SELECT by the key; fn 1875, no-candidate, builds the row's data
//   8  11469  RecuperarTodos (a chosen name): SELECT of every row, fns 1875 and 5831, no-candidate
// Move each member into cjustificadordao.cpp when it is written; delete this file with the last one.
#include "app/comum/justificativa/dao/cjustificadordao.h"

namespace api::persistencia {

template <>
void IUenuxGenericDAO<ecourna::app::dados::CIdentificacaoJustificativa, std::string>::Excluir(const TDado&) const
{
    __builtin_trap();
}

} // namespace api::persistencia

namespace comum::dao {

api::persistencia::IDAO* CJustificadorDAO::Clone() const
{
    __builtin_trap();
}

void CJustificadorDAO::ExcluirID(const TDadoID&) const
{
    __builtin_trap();
}

void CJustificadorDAO::Atualizar(const TDado&) const
{
    __builtin_trap();
}

std::shared_ptr<CJustificadorDAO::TDado> CJustificadorDAO::RecuperarID(const TDadoID&) const
{
    __builtin_trap();
}

std::vector<CJustificadorDAO::TDado> CJustificadorDAO::RecuperarTodos() const
{
    __builtin_trap();
}

} // namespace comum::dao
