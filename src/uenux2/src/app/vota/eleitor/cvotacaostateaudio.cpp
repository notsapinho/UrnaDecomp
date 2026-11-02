#include "app/vota/eleitor/cvotacaostateaudio.h"

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <format>
#include <regex>

#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargods.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/cpartidos.h"
#include "app/comum/dados/crespostas.h"
#include "app/vota/eleitor/cestadoaudio.h"
#include "app/vota/eleitor/comum/cinformacaoeleitor.h"
#include "app/vota/eleitor/cthreadeleitor.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/log/clogvota.h"

namespace vota {

CVotacaoStateAudio::CVotacaoStateAudio(int eventos)
    : comum::CAppState(eventos), m_bAudioHabilitado(false)
{
    m_tickEco = CThreadEleitor::GetInst().AddStoppedTick(2000);
    m_tickMensagem = CThreadEleitor::GetInst().AddStoppedTick(1500);
}

CVotacaoStateAudio::~CVotacaoStateAudio()
{
    CancelaEsperaFimAudio();
}

// (original lines 35-79: content not recovered)
#line 80
void CVotacaoStateAudio::StartState()
{
    m_bAudioHabilitado = CEstadoAudio::GetInst().Ativo();
    StartStateAudio();
    if (m_bAudioHabilitado) {
        const uebyte tick = m_tickMensagem;
        CThreadEleitor::GetInst().StartTick(tick);
    }
}

void CVotacaoStateAudio::FinishState()
{
    CancelaEsperaFimAudio();
    if (m_bAudioHabilitado) {
        CThreadEleitor::GetInst().StopTick(m_tickEco);
        CThreadEleitor::GetInst().StopTick(m_tickMensagem);
    }
    FinishStateAudio();
}

// (original lines 100-132: content not recovered)
#line 133
// <stubs>
// f1455 · 496 B · unmatched · name unknown
// void f1455(i32, i32) { ... }
// </stubs>

// (original lines 138-227: content not recovered)
#line 228
namespace {

std::string SoletraNumero(std::string numero)
{
    static const std::regex digito("\\B\\d");
    return std::regex_replace(numero, digito, ", $&");
}

const std::string& TextoConsulta(const comum::md::CDetalheConsulta& detalhe)
{
    return !detalhe.GetTextoFonetico().empty() ? detalhe.GetTextoFonetico() : detalhe.GetPergunta();
}

} // namespace

std::string GetNomeCargoAtual()
{
    const comum::md::CCargo& cargo = comum::CCargos::GetInst().GetCurrent();
    const std::string nome = cargo.IsConsulta() ? TextoConsulta(cargo.GetDetalheConsulta()) : cargo.GetNomeNeutro();
    std::string complemento;
    if (cargo.GetQtdeEscolhas() > 1) {
        complemento = std::format(" {}ª {}", static_cast<unsigned>(g_escolhaAtual), cargo.IsConsulta() ? "escolha" : "vaga");
    }
    return nome + complemento;
}

std::string GetCandidatoComSuplentes()
{
    const comum::md::CCandidatura& candidatura = *comum::CCandidaturas::GetInst().GetCurrent();
    const comum::md::CDadosCandidato& titular = candidatura.GetTitular();
    std::string texto = titular.GetNomeFonetico().value_or(titular.GetNomeUrna());
    uebyte suplente = 0;
    for (const comum::md::CDadosCandidato& dados : candidatura.GetSuplentes()) {
        texto += ", " + comum::CCargoDSNomeSexoCandidato(++suplente, true)() + " " +
            dados.GetNomeFonetico().value_or(dados.GetNomeUrna());
    }
    return texto;
}

std::string GetQuantidadeDigitos()
{
    const uebyte digitos = comum::CCargos::GetInst().GetCurrent().GetNumeroDigitos();
    return std::format("{} {}", digitos, digitos > 1 ? "dígitos" : "dígito");
}

std::string FormataProgresso(size_t atual, uebyte total)
{
    return std::format("{} de {}", atual, total);
}

std::string GetProgresso(size_t atual)
{
    uebyte total = 0;
    for (const comum::CCargos::TCargoEleicao& cargo : comum::CCargos::GetInst().GetCargos()) {
        total += comum::CConfiguracaoEleicao::GetInst().GetCargo(cargo.second).GetQtdeEscolhas();
    }
    return FormataProgresso(atual, total);
}

// (original lines 287-290: content not recovered)
#line 291
std::string CVotacaoStateAudio::FormatPartyName(const std::string& numero)
{
    const ueword numeroPartido = static_cast<ueword>(std::atoi(numero.c_str()));
    const comum::md::CPartido* partido = comum::CPartidos::GetInst().Find(numeroPartido);
    if (partido == nullptr) {
        CLogVota::GetInst().LogaErroPartidoNaoEncontrado();
        throw CUeVotaError(EUE_VOTA_PARTIDO_NAO_ENCONTRADO, "Nao foi encontrado o partido");
    }
    return partido->GetNome();
}

std::string CVotacaoStateAudio::SubstituiMarcador(const std::string& marcador)
{
    if (marcador == "{cargo-atual}") {
        return GetNomeCargoAtual();
    }
    if (marcador == "{voto}") {
        return SoletraNumero(g_numeroDigitado);
    }
    if (marcador == "{legenda}") {
        return SoletraNumero(g_numeroDigitado.substr(0, 2));
    }
    if (marcador == "{nome-partido}") {
        return FormatPartyName(g_numeroDigitado.substr(0, 2));
    }
    if (marcador == "{escolha-referendo}") {
        const comum::md::CRespostaConsulta& resposta = *comum::CRespostas::GetInst().GetCurrent();
        return !resposta.GetTextoFonetico().empty() ? resposta.GetTextoFonetico() : resposta.GetResposta();
    }
    if (marcador == "{o/a}") {
        return std::string(1, ArtigoCandidato());
    }
    if (marcador == "{candidato}") {
        const comum::md::CDadosCandidato& titular = comum::CCandidaturas::GetInst().GetCurrent()->GetTitular();
        return titular.GetNomeFonetico().value_or(titular.GetNomeUrna());
    }
    if (marcador == "{candidato-com-suplentes}") {
        return GetCandidatoComSuplentes();
    }
    if (marcador == "{quantidade-digitos}") {
        return GetQuantidadeDigitos();
    }
    if (marcador == "{progresso}") {
        return GetProgresso(g_votosEleitor.GetVotos().size() + 1);
    }
    return marcador;
}

std::string CVotacaoStateAudio::FormataMensagem(const std::string& mensagem)
{
    if (mensagem.empty()) {
        return "";
    }
    std::string resultado;
    const std::regex marcadores("\\{.+?\\}");
    std::sregex_token_iterator it(mensagem.begin(), mensagem.end(), marcadores, {-1, 0});
    std::sregex_token_iterator fim;
    std::for_each(it, fim, [this, &resultado](const std::string& parte) {
        resultado += SubstituiMarcador(parte);
    });
    return resultado;
}

} // namespace vota
