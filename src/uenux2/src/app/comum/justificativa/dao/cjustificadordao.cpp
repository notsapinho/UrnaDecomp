// The reconstruction's note, not TSE's text: fns 1704 and 3767 (the destructors), 11473 (slot 3, Inserir, a chosen
// name), 11472 and 11471 (ExcluirID and Atualizar, records at lines 56 and 63), 11470 and 11469 (slots 7 and 8,
// RecuperarID and RecuperarTodos, chosen names) and 11468 (slot 2, Clone, a chosen name, a thunk into 3894). Evidence:
// Inserir stands before line 56, and the two SELECTs and Clone after line 63 in that order, as band uses 1 runs 11473,
// 11472, 11471, 11470, 11469, 11468 downwards. Chosen: the exact lines of those four, and the destructors' place (1704,
// 3767: other bands).
#include "app/comum/justificativa/dao/cjustificadordao.h"

#include <format>

#include "app/comum/justificativa/euecomumjustificativaerror.h"
#include "ecourna/api/util/cstringutils.hpp"
#include "ecourna/app/dados/cnumeroinscricaoeleitoral.hpp"

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

// (original lines 31-53: content not recovered)
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

std::shared_ptr<CJustificadorDAO::TDado> CJustificadorDAO::RecuperarID(const TDadoID& id) const
{
    const std::string sql = " SELECT numero_titulo, ano_nascimento FROM registro_justificativa WHERE numero_titulo = ? \n";

    const ecourna::api::sql::TSharedSqlStatement stmt = m_conexao->Prepare(sql);
    stmt->SetInt64(1, ecourna::api::util::CStringUtils::ToQWord(id));
    const ecourna::api::sql::TSharedSqlResultSet rs = stmt->Execute();

    std::shared_ptr<TDado> justificativa;
    if (rs->Next()) {
        const std::string numero = std::format("{}", rs->GetInt64(0));
        const int ano = rs->GetInt(1);
        const ecourna::app::dados::CNumeroInscricaoEleitoral titulo(numero);
        const TDado dado(ecourna::app::dados::CRegistroIdentificacaoEleitor(
                             std::make_shared<ecourna::app::dados::CNumeroInscricaoEleitoral>(titulo)),
                         ano);
        justificativa.reset(new TDado(dado));
    }
    stmt->Close();
    return justificativa;
}

std::vector<CJustificadorDAO::TDado> CJustificadorDAO::RecuperarTodos() const
{
    const std::string sql = " SELECT numero_titulo, ano_nascimento FROM registro_justificativa \n";

    const ecourna::api::sql::TSharedSqlStatement stmt = m_conexao->Prepare(sql);
    const ecourna::api::sql::TSharedSqlResultSet rs = stmt->Execute();

    std::vector<TDado> justificativas;
    while (rs->Next()) {
        const std::string numero = std::format("{}", rs->GetInt64(0));
        const int ano = rs->GetInt(1);
        const ecourna::app::dados::CNumeroInscricaoEleitoral titulo(numero);
        const TDado dado(ecourna::app::dados::CRegistroIdentificacaoEleitor(
                             std::make_shared<ecourna::app::dados::CNumeroInscricaoEleitoral>(titulo)),
                         ano);
        justificativas.push_back(dado);
    }
    stmt->Close();
    return justificativas;
}

api::persistencia::IDAO* CJustificadorDAO::Clone() const
{
    return new CJustificadorDAO(*this);
}

} // namespace comum::dao
