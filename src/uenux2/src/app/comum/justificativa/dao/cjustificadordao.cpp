// The reconstruction's note, not TSE's text: fns 1704 and 3767 (the destructors), 11473 (slot 3, Inserir, a chosen
// name), 11472 and 11471 (ExcluirID and Atualizar, records at lines 56 and 63) and 11468 (slot 2, Clone, a chosen name, a
// thunk into 3894). Evidence: Inserir stands before line 56 and Clone after line 63, as band uses 1 runs 11473, 11472,
// 11471, 11470, 11469, 11468 downwards. Chosen: the exact lines of Inserir and Clone, and the destructors' place
// (1704, 3767: other bands). Other members: src/units/66-uenux2-cjustificadordao-pending.cpp.
#include "app/comum/justificativa/dao/cjustificadordao.h"

#include "app/comum/justificativa/euecomumjustificativaerror.h"
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

// (original lines 27-53: content not recovered)
#line 54
void CJustificadorDAO::ExcluirID(const TDadoID&) const
{
    throw CUeComumJustificativaError(EUE_COMUM_JUSTIFICATIVA_DAO_EXCLUSAO_NAO_ESPERADA, "Nao é esperado que o CJustificadorDAO exclua registros do banco");
}

// (original lines 59-60: content not recovered)
#line 61
void CJustificadorDAO::Atualizar(const TDado&) const
{
    throw CUeComumJustificativaError(EUE_COMUM_JUSTIFICATIVA_DAO_ATUALIZACAO_NAO_ESPERADA, "Nao é esperado que o CJustificadorDAO atualize registros do banco");
}

api::persistencia::IDAO* CJustificadorDAO::Clone() const
{
    return new CJustificadorDAO(*this);
}

} // namespace comum::dao
