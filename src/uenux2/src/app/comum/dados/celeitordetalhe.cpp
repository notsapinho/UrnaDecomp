// comum::CEleitorDetalhe: ConfereDadosDinamicos, the record at line 224 col 15, and GetImpedimento, GetDinamico,
// MarcaHabilitado and MarcaVotou below it, which have no record (their lines are a choice). The reconstruction's own note; the blank lines stand for text not
// recovered.
#include "app/comum/dados/celeitordetalhe.h"

#include <format>

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/celeitordadoshabilitacao.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum {

// (original lines 14-90: content not recovered)
#line 91
// <stubs>
// f1937 · 5175 B · unmatched · name unknown
// void f1937(i32, i32) { ... }
// </stubs>

// (original lines 96-220: content not recovered)
#line 221
void CEleitorDetalhe::ConfereDadosDinamicos(const std::string& funcao) const
{
    if (!m_dinamico.has_value()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7832, std::format("{}: Dados dinâmicos não carregados", funcao));
    }
}

md::ETipoImpedimento CEleitorDetalhe::GetImpedimento() const
{
    const CAppInfo& appInfo = CAppInfo::GetInst();
    return appInfo.GetGeral().GetDadoCarga().GetTurno() == TURNO_2 ? m_impedimentoP2 : m_impedimentoP1;
}

const md::CEleitorDinamico& CEleitorDetalhe::GetDinamico() const
{
    ConfereDadosDinamicos("GetDinamico");
    return *m_dinamico;
}

void CEleitorDetalhe::MarcaHabilitado(const CEleitorDadosHabilitacao& dados)
{
    ConfereDadosDinamicos("MarcaHabilitado");
    const md::CEleitorDadosHabilitacaoBiometrica& biometria = dados.GetBiometria();
    switch (dados.GetTipo()) {
    case CEleitorDadosHabilitacao::HABILITACAO_SEM_BIOMETRIA:
        m_dinamico->HabilitaSemBiometria();
        break;
    case CEleitorDadosHabilitacao::HABILITACAO_BIOMETRICA:
        m_dinamico->HabilitaPorBiometria(biometria.GetDedo(), biometria.GetScore(), biometria.GetNumeroTentativa());
        break;
    case CEleitorDadosHabilitacao::HABILITACAO_MESARIO:
        if (biometria.TemTituloMesario()) {
            m_dinamico->HabilitaPorMesario(biometria.GetNumeroTentativa(), biometria.GetErroDecifrarBiometria(),
                                           biometria.GetTituloMesario());
        } else {
            m_dinamico->HabilitaPorMesario(biometria.GetNumeroTentativa(), biometria.GetErroDecifrarBiometria());
        }
        break;
    }
    m_dinamico->SetTipoAtivacaoAudio(dados.GetTipoAtivacaoAudio());
    m_dinamico->SetIdentidadeHabilitacao(dados.GetIdentidade());
    m_dinamico->SetApresentacaoFoto(dados.GetApresentacaoFoto());
}

void CEleitorDetalhe::MarcaVotou()
{
    ConfereDadosDinamicos("MarcaVotou");
    m_dinamico->SetEstadoComparecimento(3);
}

} // namespace comum
