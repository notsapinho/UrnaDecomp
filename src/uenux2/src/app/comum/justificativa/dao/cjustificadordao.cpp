// The reconstruction's note, not TSE's text: fns 1704 and 3767 (the destructors) and 11473 (slot 3, Inserir, a chosen
// name), the only functions written here. Their lines are a choice: no record gives one. They stand before line 56,
// the first record of the file (ExcluirID): in their band the indices run 11473, 11472 (ExcluirID), 11471 (Atualizar)
// downwards, so Inserir comes first. The other members are in src/units/66-uenux2-cjustificadordao-pending.cpp.
#include "app/comum/justificativa/dao/cjustificadordao.h"

#include "ecourna/api/util/cstringutils.hpp"

namespace comum::dao {

CJustificadorDAO::~CJustificadorDAO() = default;

void CJustificadorDAO::Inserir(const TDado& dado) const
{
    const std::string sql = " INSERT INTO registro_justificativa (numero_titulo, ano_nascimento) VALUES (?, ?) \n";

    const ecourna::api::sql::TSharedSqlStatement stmt = m_conexao->Prepare(sql);
    stmt->SetInt64(1, ecourna::api::util::CStringUtils::ToQWord(
                          dado.GetIdentificacaoEleitor().GetIdentificadorHabilitacao()->GetNumero()));
    stmt->SetInt(2, dado.GetAnoNascimentoEleitor());
    stmt->Execute();
    stmt->Close();
}

} // namespace comum::dao
