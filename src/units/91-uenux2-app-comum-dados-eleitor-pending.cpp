// Pending members: the virtual members two vtables need and no source holds yet. These bodies are NOT the target's, they
// trap. Target functions, by slot, and what each waits for:
// comum::dao::CEleitorDinamicoDAO (@1558896), emitted by celeitordinamicodao.cpp with the destructor:
//   7  11542  RecuperarID (a chosen name): SELECT by the key; waits for fns 566, 5663 and 5664, no-candidate
//   8   3766  RecuperarTodos (a chosen name): SELECT of every row; the same three and fn 5759, no-candidate
// comum::dao::CComparecimentoMesarioDAO (@1593352), emitted by ccomparecimentomesariodao.cpp with the destructor:
//   3  10403  Inserir (a chosen name), the INSERT into comparecimento_mesario: waits for fn 1381, no-candidate, the
//             function that turns data_hora_registro (a CDate and a CTime) into a time_t through mktime (fn 2961), which
//             no source holds and no record names. Its source, as the bytes read: the literal into a local std::string,
//             stmt = m_conexao->Prepare(sql); SetInt64(1, CStringUtils::ToQWord(identificador at +0)); SetInt of 2 to 6
//             with +12, +16, the byte at +20, +24 and +28; SetDateTime(7, ptime from fn 1381's result, in microseconds);
//             SetInt(8, id_arquivo at +44) when the flag at +48 is set, else SetNull(8); Execute(); Close();
//   7  10402  RecuperarID (a chosen name): waits for fns 566, 1000, 2730, 2731, 5390 and 5391, no-candidate
//   8  10401  RecuperarTodos (a chosen name): the same six
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

void CComparecimentoMesarioDAO::Inserir(const TDado&) const
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
