// The reconstruction's note, not TSE's text. Target functions: the constructor (3768), the destructors (1704, 3767, one
// body each with the other two DAOs'), Inserir (5776, slot 3), ExcluirID (11543, slot 5, record at line 130), Atualizar
// (5775, slot 6), Clone (11541, slot 2, a thunk into 3894). Their order is what the bands give and the lines but 130's
// are chosen: src/units/91-uenux2-app-comum-dados-eleitor.mk says so. Slots 7 and 8, RecuperarID (11542) and RecuperarTodos
// (3766), are written and wait for a literal (the fragment says which).
#include "app/comum/dados/dao/celeitordinamicodao.h"

#include <format>

#include "app/comum/dados/euecomumdadoserror.h"
#include "ecourna/api/sql/sqlite/csqlconnection.hpp"
#include "ecourna/api/util/cstringutils.hpp"

namespace comum::dao {

namespace {

const std::string NOME_TABELA = "eleitor_dinamico";

} // namespace

CEleitorDinamicoDAO::CEleitorDinamicoDAO(const std::string& caminho)
    : m_conexao(new ecourna::api::sql::sqlite::CSqlConnection(caminho))
{
    const std::string sql = "CREATE TABLE IF NOT EXISTS " + NOME_TABELA + "( titulo BIGINT PRIMARY KEY UNIQUE NOT NULL, tipo_identificador INTEGER CHECK(tipo_identificador IN (1,2,3) ) NOT NULL, identidade_habilitacao BIGINT NOT NULL, tipo_identidade_habilitacao INTEGER CHECK(tipo_identidade_habilitacao IN (1,2,3) ) NOT NULL, estado_comparecimento INTEGER NOT NULL, tipo_habilitacao INTEGER NOT NULL, dedo_habilitacao INTEGER NOT NULL, score_habilitacao INTEGER NOT NULL, tipo_ativacao_audio INTEGER CHECK(tipo_ativacao_audio IN (0,1,2) ) NOT NULL, numero_tentativa INTEGER CHECK(numero_tentativa IN (0,1,2,3,4) ) NOT NULL, erro_decifrar_biometria INTEGER NOT NULL, estado_apresentacao_foto INTEGER CHECK(estado_apresentacao_foto IN (0,1,2) ) NOT NULL, resultado_decifracao_foto INTEGER CHECK(estado_apresentacao_foto IN (0,1,2,3,4,5,6,7,8) ) NOT NULL, titulo_mesario BIGINT, tipo_identificador_mesario INTEGER CHECK(tipo_identificador IN (1,2,3) ) ) \n";

    const ecourna::api::sql::TSharedSqlStatement stmt = m_conexao->Prepare(sql);
    stmt->Execute();
    stmt->Close();
}

CEleitorDinamicoDAO::~CEleitorDinamicoDAO() = default;

void CEleitorDinamicoDAO::Inserir(const TDado& dado) const
{
    using ecourna::api::util::CStringUtils;

    const std::string sql = "INSERT INTO " + NOME_TABELA + " (titulo, tipo_identificador, identidade_habilitacao, tipo_identidade_habilitacao, estado_comparecimento, tipo_habilitacao, dedo_habilitacao, score_habilitacao, tipo_ativacao_audio, numero_tentativa, erro_decifrar_biometria, estado_apresentacao_foto, resultado_decifracao_foto, titulo_mesario, tipo_identificador_mesario ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)\n";

    const ecourna::api::sql::TSharedSqlStatement stmt = m_conexao->Prepare(sql);
    stmt->SetInt64(1, CStringUtils::ToQWord(dado.GetEleitor().GetIdentificador()));
    stmt->SetInt(2, dado.GetEleitor().GetTipo());
    stmt->SetInt64(3, CStringUtils::ToQWord(dado.GetIdentidadeHabilitacao().GetIdentificador()));
    stmt->SetInt(4, dado.GetIdentidadeHabilitacao().GetTipo());
    stmt->SetInt(5, dado.GetEstadoComparecimento());
    stmt->SetInt(6, dado.GetTipoHabilitacao());
    stmt->SetInt(7, dado.GetDedoHabilitacao());
    stmt->SetInt(8, dado.GetScoreHabilitacao());
    stmt->SetInt(9, dado.GetTipoAtivacaoAudio());
    stmt->SetInt(10, dado.GetNumeroTentativa());
    stmt->SetInt(11, dado.GetErroDecifrarBiometria());
    stmt->SetInt(12, dado.GetApresentacaoFoto().GetEstado());
    stmt->SetInt(13, dado.GetApresentacaoFoto().GetResultado());
    if (dado.TemTituloMesarioHabilitacao()) {
        stmt->SetInt64(14, CStringUtils::ToQWord(dado.GetTituloMesarioHabilitacao().GetIdentificador()));
        stmt->SetInt(15, dado.GetTituloMesarioHabilitacao().GetTipo());
    } else {
        stmt->SetNull(14);
        stmt->SetNull(15);
    }
    stmt->Execute();
    stmt->Close();
}

std::vector<CEleitorDinamicoDAO::TDado> CEleitorDinamicoDAO::RecuperarTodos() const
{
    using ecourna::app::dados::CApresentacaoFotoEleitor;
    using ecourna::app::dados::ETipoIdentificadorEleitor;

    const std::string sql = "SELECT titulo, tipo_identificador, identidade_habilitacao, tipo_identidade_habilitacao, estado_comparecimento, tipo_habilitacao, dedo_habilitacao, score_habilitacao, numero_tentativa, erro_decifrar_biometria, tipo_ativacao_audio, estado_apresentacao_foto, resultado_decifracao_foto, titulo_mesario, tipo_identificador_mesario from " + NOME_TABELA + "\n";

    const ecourna::api::sql::TSharedSqlStatement stmt = m_conexao->Prepare(sql);
    const ecourna::api::sql::TSharedSqlResultSet rs = stmt->Execute();
    std::vector<TDado> dados;
    while (rs->Next()) {
        const std::string titulo = std::format("{}", rs->GetInt64(0));
        const ETipoIdentificadorEleitor tipo = static_cast<ETipoIdentificadorEleitor>(rs->GetInt(1));
        const std::string identidadeHabilitacao = std::format("{}", rs->GetInt64(2));
        const ETipoIdentificadorEleitor tipoIdentidadeHabilitacao = static_cast<ETipoIdentificadorEleitor>(rs->GetInt(3));
        const int estadoComparecimento = rs->GetInt(4);
        const int tipoHabilitacao = rs->GetInt(5);
        const md::CDedo::TipoDedo dedoHabilitacao = static_cast<md::CDedo::TipoDedo>(rs->GetInt(6));
        const int scoreHabilitacao = rs->GetInt(7);
        const int numeroTentativa = rs->GetInt(8);
        const int erroDecifrarBiometria = rs->GetInt(9);
        const int tipoAtivacaoAudio = rs->GetInt(10);
        const CApresentacaoFotoEleitor::EEstado estadoFoto = static_cast<CApresentacaoFotoEleitor::EEstado>(rs->GetInt(11));
        const CApresentacaoFotoEleitor::EResultado resultadoFoto =
            static_cast<CApresentacaoFotoEleitor::EResultado>(rs->GetInt(12));
        if (!rs->IsNull(13)) {
            const std::string tituloMesario = std::format("{}", rs->GetInt64(13));
            const ETipoIdentificadorEleitor tipoMesario = static_cast<ETipoIdentificadorEleitor>(rs->GetInt(14));
            const TDado dado(md::CEleitorIdentidade(titulo, tipo), md::CEleitorIdentidade(identidadeHabilitacao, tipoIdentidadeHabilitacao),
                             estadoComparecimento, tipoHabilitacao, dedoHabilitacao, scoreHabilitacao, numeroTentativa, tipoAtivacaoAudio,
                             erroDecifrarBiometria, md::CEleitorIdentidade(tituloMesario, tipoMesario),
                             CApresentacaoFotoEleitor(estadoFoto, resultadoFoto));
            dados.push_back(dado);
        } else {
            const TDado dado(md::CEleitorIdentidade(titulo, tipo), md::CEleitorIdentidade(identidadeHabilitacao, tipoIdentidadeHabilitacao),
                             estadoComparecimento, tipoHabilitacao, dedoHabilitacao, scoreHabilitacao, numeroTentativa, tipoAtivacaoAudio,
                             erroDecifrarBiometria, CApresentacaoFotoEleitor(estadoFoto, resultadoFoto));
            dados.push_back(dado);
        }
    }
    stmt->Close();
    return dados;
}

// (original lines 109-127: content not recovered)
#line 128
void CEleitorDinamicoDAO::ExcluirID(const TDadoID&) const
{
    throw CUeComumDadosError(EUE_COMUM_DADOS_7983, "Exclusão de eleitor dinâmico");
}

void CEleitorDinamicoDAO::Atualizar(const TDado& dado) const
{
    using ecourna::api::util::CStringUtils;

    const std::string sql = "UPDATE " + NOME_TABELA + " SET identidade_habilitacao = ?, tipo_identidade_habilitacao = ?, estado_comparecimento = ?, tipo_ativacao_audio = ?, tipo_habilitacao = ?,  dedo_habilitacao = ?, score_habilitacao = ?, numero_tentativa = ?, erro_decifrar_biometria = ?, estado_apresentacao_foto = ?, resultado_decifracao_foto = ?, titulo_mesario = ?, tipo_identificador_mesario = ? WHERE titulo = ?";

    const ecourna::api::sql::TSharedSqlStatement stmt = m_conexao->Prepare(sql);
    stmt->SetInt64(1, CStringUtils::ToQWord(dado.GetIdentidadeHabilitacao().GetIdentificador()));
    stmt->SetInt(2, dado.GetIdentidadeHabilitacao().GetTipo());
    stmt->SetInt(3, dado.GetEstadoComparecimento());
    stmt->SetInt(4, dado.GetTipoAtivacaoAudio());
    stmt->SetInt(5, dado.GetTipoHabilitacao());
    stmt->SetInt(6, dado.GetDedoHabilitacao());
    stmt->SetInt(7, dado.GetScoreHabilitacao());
    stmt->SetInt(8, dado.GetNumeroTentativa());
    stmt->SetInt(9, dado.GetErroDecifrarBiometria());
    stmt->SetInt(10, dado.GetApresentacaoFoto().GetEstado());
    stmt->SetInt(11, dado.GetApresentacaoFoto().GetResultado());
    if (dado.TemTituloMesarioHabilitacao()) {
        stmt->SetInt64(12, CStringUtils::ToQWord(dado.GetTituloMesarioHabilitacao().GetIdentificador()));
        stmt->SetInt(13, dado.GetTituloMesarioHabilitacao().GetTipo());
    } else {
        stmt->SetNull(12);
        stmt->SetNull(13);
    }
    stmt->SetInt64(14, CStringUtils::ToQWord(dado.GetEleitor().GetIdentificador()));
    stmt->Execute();
    stmt->Close();
}

std::shared_ptr<CEleitorDinamicoDAO::TDado> CEleitorDinamicoDAO::RecuperarID(const TDadoID& id) const
{
    using ecourna::api::util::CStringUtils;
    using ecourna::app::dados::CApresentacaoFotoEleitor;
    using ecourna::app::dados::ETipoIdentificadorEleitor;

    const std::string sql = "SELECT titulo, tipo_identificador, identidade_habilitacao, tipo_identidade_habilitacao, estado_comparecimento, tipo_habilitacao, dedo_habilitacao, score_habilitacao, numero_tentativa, erro_decifrar_biometria, tipo_ativacao_audio, estado_apresentacao_foto, resultado_decifracao_foto, titulo_mesario, tipo_identificador_mesario from " + NOME_TABELA + " WHERE titulo = ?\n";

    const ecourna::api::sql::TSharedSqlStatement stmt = m_conexao->Prepare(sql);
    stmt->SetInt64(1, CStringUtils::ToQWord(id));
    const ecourna::api::sql::TSharedSqlResultSet rs = stmt->Execute();
    std::shared_ptr<TDado> dado;
    if (rs->Next()) {
        const std::string titulo = std::format("{}", rs->GetInt64(0));
        const ETipoIdentificadorEleitor tipo = static_cast<ETipoIdentificadorEleitor>(rs->GetInt(1));
        const std::string identidadeHabilitacao = std::format("{}", rs->GetInt64(2));
        const ETipoIdentificadorEleitor tipoIdentidadeHabilitacao = static_cast<ETipoIdentificadorEleitor>(rs->GetInt(3));
        const int estadoComparecimento = rs->GetInt(4);
        const int tipoHabilitacao = rs->GetInt(5);
        const md::CDedo::TipoDedo dedoHabilitacao = static_cast<md::CDedo::TipoDedo>(rs->GetInt(6));
        const int scoreHabilitacao = rs->GetInt(7);
        const int numeroTentativa = rs->GetInt(8);
        const int erroDecifrarBiometria = rs->GetInt(9);
        const int tipoAtivacaoAudio = rs->GetInt(10);
        const CApresentacaoFotoEleitor::EEstado estadoFoto = static_cast<CApresentacaoFotoEleitor::EEstado>(rs->GetInt(11));
        const CApresentacaoFotoEleitor::EResultado resultadoFoto =
            static_cast<CApresentacaoFotoEleitor::EResultado>(rs->GetInt(12));
        if (!rs->IsNull(13)) {
            const std::string tituloMesario = std::format("{}", rs->GetInt64(13));
            const ETipoIdentificadorEleitor tipoMesario = static_cast<ETipoIdentificadorEleitor>(rs->GetInt(14));
            dado.reset(new TDado(md::CEleitorIdentidade(titulo, tipo), md::CEleitorIdentidade(identidadeHabilitacao, tipoIdentidadeHabilitacao),
                                 estadoComparecimento, tipoHabilitacao, dedoHabilitacao, scoreHabilitacao, numeroTentativa, tipoAtivacaoAudio,
                                 erroDecifrarBiometria, md::CEleitorIdentidade(tituloMesario, tipoMesario),
                                 CApresentacaoFotoEleitor(estadoFoto, resultadoFoto)));
        } else {
            dado.reset(new TDado(md::CEleitorIdentidade(id, tipo), md::CEleitorIdentidade(identidadeHabilitacao, tipoIdentidadeHabilitacao),
                                 estadoComparecimento, tipoHabilitacao, dedoHabilitacao, scoreHabilitacao, numeroTentativa, tipoAtivacaoAudio,
                                 erroDecifrarBiometria, CApresentacaoFotoEleitor(estadoFoto, resultadoFoto)));
        }
    }
    stmt->Close();
    return dado;
}

api::persistencia::IDAO* CEleitorDinamicoDAO::Clone() const
{
    return new CEleitorDinamicoDAO(*this);
}

} // namespace comum::dao
