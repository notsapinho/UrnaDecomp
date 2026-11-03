// comum::CEleitorDetalhe: the two constructors (the record at line 49 col 15 is the second's; the first's lines are a choice),
// ConfereDadosDinamicos (line 224 col 15), and GetImpedimento, GetDinamico, MarcaHabilitado and MarcaVotou below it, which
// have no record (their lines are a choice). The reconstruction's own note; the blank lines stand for text not recovered.
#include "app/comum/dados/celeitordetalhe.h"

#include <format>

#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/celeitordadoshabilitacao.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum {

// (original lines 14-35: content not recovered)
#line 36
CEleitorDetalhe::CEleitorDetalhe(const md::CEleitorDecorator& eleitor, const md::ETipoImpedimento impedimentoP1,
    const md::ETipoImpedimento impedimentoP2)
    : m_eleitor(eleitor), m_impedimentoP1(impedimentoP1), m_impedimentoP2(impedimentoP2)
{
}

// (original lines 42-43: content not recovered)
#line 44
CEleitorDetalhe::CEleitorDetalhe(const md::CEleitorDecorator& eleitor, const md::CEleitorDinamico& dinamico,
    const md::ETipoImpedimento impedimentoP1, const md::ETipoImpedimento impedimentoP2)
    : m_eleitor(eleitor), m_dinamico(dinamico), m_impedimentoP1(impedimentoP1), m_impedimentoP2(impedimentoP2)
{
    if (eleitor.GetIdentidadePorTipo(eleitor.GetTipoIdentificador()) != dinamico.GetEleitor()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7829, "CEleitorDetalhe - identidades divergentes");
    }
}

// (original lines 53-90: content not recovered)
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

bool CEleitorDetalhe::SemImpedimento() const
{
    return GetImpedimento() == md::IMPEDIMENTO_SEM_IMPEDIMENTO;
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
