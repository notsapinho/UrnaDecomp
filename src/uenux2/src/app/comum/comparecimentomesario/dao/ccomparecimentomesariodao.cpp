// The reconstruction's note, not TSE's text: the destructors (1704, 3767, one body each with the other two DAOs'),
// Inserir (10403, slot 3, a chosen name), Clone (10399, slot 2, a thunk into 3894) and the records' two converters,
// ConverteEstadoBiometria (line 200, fn 5391) and ConverteDedoHabilitacao (line 232, fn 5390). Evidence: Inserir comes
// first of the file's slot members in band uses 1 (ledger/ordinals.tsv: 10403, 10402, 10401, then 10399, downwards).
// Chosen: every line but the two throws', and the converters' place after Clone (they are in band uses 2). Slots 7 and 8,
// RecuperarID (10402) and RecuperarTodos (10401), names chosen, follow Inserir in the band's order;
// src/units/91-uenux2-app-comum-dados-eleitor.mk says what they rest on.
#include "app/comum/comparecimentomesario/dao/ccomparecimentomesariodao.h"

#include <format>

#include <boost/date_time/posix_time/conversion.hpp>

#include "app/comum/comparecimentomesario/euecomumcomparecimentomesarioerror.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum::dao {

CComparecimentoMesarioDAO::~CComparecimentoMesarioDAO() = default;

void CComparecimentoMesarioDAO::Inserir(const TDado& dado) const
{
    const std::string sql = " INSERT INTO comparecimento_mesario (numero_titulo, tipo_identificador, periodo_presente, pertence_secao, estado_biometria, dedo_habilitacao, data_hora_registro, id_arquivo) VALUES (?, ?, ?, ?, ?, ?, ?, ?) \n";

    const ecourna::api::sql::TSharedSqlStatement stmt = m_conexao->Prepare(sql);
    stmt->SetInt64(1, ecourna::api::util::CStringUtils::ToQWord(dado.GetMesario().GetIdentificador()));
    stmt->SetInt(2, dado.GetMesario().GetTipo());
    stmt->SetInt(3, dado.GetPeriodoPresente());
    stmt->SetInt(4, dado.PertenceSecao());
    stmt->SetInt(5, dado.GetEstadoBiometria());
    stmt->SetInt(6, dado.GetDedoHabilitacao());
    stmt->SetDateTime(7, boost::posix_time::from_time_t(dado.GetDataHoraRegistro().ConvertToLocalTime()));
    ecourna::api::sql::ISqlStatement& comando = *stmt;
    if (dado.GetIdArquivo().has_value()) {
        comando.SetInt(8, dado.GetIdArquivo().value());
    } else {
        comando.SetNull(8);
    }
    stmt->Execute();
    stmt->Close();
}

std::shared_ptr<CComparecimentoMesarioDAO::TDado> CComparecimentoMesarioDAO::RecuperarID(const TDadoID& id) const
{
    using ecourna::app::dados::ETipoIdentificadorEleitor;

    const std::string sql = " SELECT numero_titulo, tipo_identificador, periodo_presente, pertence_secao, estado_biometria, dedo_habilitacao, data_hora_registro, id_arquivo FROM comparecimento_mesario WHERE numero_titulo = ? and periodo_presente = ? \n";

    const ecourna::api::sql::TSharedSqlStatement stmt = m_conexao->Prepare(sql);
    stmt->SetInt64(1, ecourna::api::util::CStringUtils::ToQWord(id.GetMesario().GetIdentificador()));
    stmt->SetInt(2, id.GetPeriodoPresente());
    const ecourna::api::sql::TSharedSqlResultSet rs = stmt->Execute();
    std::shared_ptr<TDado> dado;
    if (rs->Next()) {
        const std::string titulo = std::format("{}", rs->GetInt64("numero_titulo"));
        const ETipoIdentificadorEleitor tipo = static_cast<ETipoIdentificadorEleitor>(rs->GetInt("tipo_identificador"));
        const int periodoPresente = rs->GetInt("periodo_presente");
        const bool pertenceSecao = rs->GetBool("pertence_secao");
        const TDado::EstadoReconhecimentoBiometrico estadoBiometria =
            ConverteEstadoBiometria(rs->GetInt("estado_biometria"));
        const md::CDedo::TipoDedo dedoHabilitacao = ConverteDedoHabilitacao(rs->GetInt("dedo_habilitacao"));
        const api::CDateTime dataHoraRegistro(boost::posix_time::to_time_t(rs->GetDateTime("data_hora_registro")));
        if (!rs->IsNull("id_arquivo")) {
            const int idArquivo = rs->GetInt("id_arquivo");
            dado.reset(new TDado(md::CEleitorIdentidade(titulo, tipo), periodoPresente, pertenceSecao, estadoBiometria,
                                 dedoHabilitacao, dataHoraRegistro, idArquivo));
        } else {
            dado.reset(new TDado(md::CEleitorIdentidade(titulo, tipo), periodoPresente, pertenceSecao, estadoBiometria,
                                 dedoHabilitacao, dataHoraRegistro));
        }
    }
    stmt->Close();
    return dado;
}

std::vector<CComparecimentoMesarioDAO::TDado> CComparecimentoMesarioDAO::RecuperarTodos() const
{
    using ecourna::app::dados::ETipoIdentificadorEleitor;

    const std::string sql = " SELECT numero_titulo, tipo_identificador, periodo_presente, pertence_secao, estado_biometria,  dedo_habilitacao, data_hora_registro, id_arquivo FROM comparecimento_mesario  ORDER BY pertence_secao ASC, numero_titulo ASC, periodo_presente ASC, dedo_habilitacao ASC \n";

    const ecourna::api::sql::TSharedSqlStatement stmt = m_conexao->Prepare(sql);
    const ecourna::api::sql::TSharedSqlResultSet rs = stmt->Execute();
    std::vector<TDado> dados;
    while (rs->Next()) {
        const std::string titulo = std::format("{}", rs->GetInt64("numero_titulo"));
        const ETipoIdentificadorEleitor tipo = static_cast<ETipoIdentificadorEleitor>(rs->GetInt("tipo_identificador"));
        const int periodoPresente = rs->GetInt("periodo_presente");
        const bool pertenceSecao = rs->GetBool("pertence_secao");
        const TDado::EstadoReconhecimentoBiometrico estadoBiometria =
            ConverteEstadoBiometria(rs->GetInt("estado_biometria"));
        const md::CDedo::TipoDedo dedoHabilitacao = ConverteDedoHabilitacao(rs->GetInt("dedo_habilitacao"));
        const api::CDateTime dataHoraRegistro(boost::posix_time::to_time_t(rs->GetDateTime("data_hora_registro")));
        if (!rs->IsNull("id_arquivo")) {
            const int idArquivo = rs->GetInt("id_arquivo");
            dados.emplace_back(md::CEleitorIdentidade(titulo, tipo), periodoPresente, pertenceSecao, estadoBiometria,
                               dedoHabilitacao, dataHoraRegistro, idArquivo);
        } else {
            dados.emplace_back(md::CEleitorIdentidade(titulo, tipo), periodoPresente, pertenceSecao, estadoBiometria,
                               dedoHabilitacao, dataHoraRegistro);
        }
    }
    stmt->Close();
    return dados;
}

api::persistencia::IDAO* CComparecimentoMesarioDAO::Clone() const
{
    return new CComparecimentoMesarioDAO(*this);
}

// (original lines 112-189: content not recovered)
#line 190
comum::md::CComparecimentoMesario::EstadoReconhecimentoBiometrico CComparecimentoMesarioDAO::ConverteEstadoBiometria(ueint32 estado) const
{
    switch (estado) {
    case 1:
        return static_cast<comum::md::CComparecimentoMesario::EstadoReconhecimentoBiometrico>(1);
    case 2:
        return static_cast<comum::md::CComparecimentoMesario::EstadoReconhecimentoBiometrico>(2);
    case 3:
        return static_cast<comum::md::CComparecimentoMesario::EstadoReconhecimentoBiometrico>(3);
    }
    throw CUeComumComparecimentoMesarioError(EUE_COMUM_COMPARECIMENTO_MESARIO_ESTADO_BIOMETRIA_INVALIDO, std::format("Estado biometria inválido: {}", estado));
}

// (original lines 203-205: content not recovered)
#line 206
comum::md::CDedo::TipoDedo CComparecimentoMesarioDAO::ConverteDedoHabilitacao(const ueint32 dedo) const
{
    switch (dedo) {
    case 0:
        return static_cast<comum::md::CDedo::TipoDedo>(0);
    case 1:
        return static_cast<comum::md::CDedo::TipoDedo>(1);
    case 2:
        return static_cast<comum::md::CDedo::TipoDedo>(2);
    case 3:
        return static_cast<comum::md::CDedo::TipoDedo>(3);
    case 4:
        return static_cast<comum::md::CDedo::TipoDedo>(4);
    case 5:
        return static_cast<comum::md::CDedo::TipoDedo>(5);
    case 6:
        return static_cast<comum::md::CDedo::TipoDedo>(6);
    case 7:
        return static_cast<comum::md::CDedo::TipoDedo>(7);
    case 8:
        return static_cast<comum::md::CDedo::TipoDedo>(8);
    case 9:
        return static_cast<comum::md::CDedo::TipoDedo>(9);
    case 10:
        return static_cast<comum::md::CDedo::TipoDedo>(10);
    }
    throw CUeComumComparecimentoMesarioError(EUE_COMUM_COMPARECIMENTO_MESARIO_DEDO_HABILITACAO_INVALIDO, std::format("Dedo habilitação inválido: {}", dedo));
}

} // namespace comum::dao
