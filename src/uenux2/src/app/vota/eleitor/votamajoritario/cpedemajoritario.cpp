#include "app/vota/eleitor/votamajoritario/cpedemajoritario.h"

#include "api/gui/cinteractiveform.h"
#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/cpartidos.h"
#include "app/comum/dados/crespostas.h"
#include "app/vota/eleitor/cconferevotoemcargo.h"
#include "app/vota/eleitor/comum/cinformacaoeleitor.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/votamajoritario/cmajoritariobranco.h"
#include "app/vota/eleitor/votamajoritario/cmajoritarionulo.h"
#include "app/vota/eleitor/votamajoritario/cmajoritariorepetido.h"
#include "app/vota/eleitor/votamajoritario/cmajoritariovalido.h"
#include "app/vota/euevotaerror.h"
#include "app/vota/log/clogvota.h"
#include "ecourna/api/util/cstringutils.hpp"

namespace vota {

CPedeMajoritario::CPedeMajoritario()
    : CVotacaoStateAudio(EVENTO_ENTRADA)
{
}

CPedeMajoritario::~CPedeMajoritario() = default;

CPedeMajoritario& CPedeMajoritario::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPedeMajoritario());
    }
    return *s_inst;
}

std::unique_ptr<CPedeMajoritario> CPedeMajoritario::s_inst;
std::mutex CPedeMajoritario::s_mutex;

CFormInterativoTelaVota CPedeMajoritario::GetTelaCargoAtual()
{
    const auto& cargos = comum::CCargos::GetInst();
    if (cargos.IsFim()) {
        throw CUeVotaError(EUE_VOTA_PEDE_MAJORITARIO_CARGO_NAO_POSICIONADO, "O cargo atual nao esta posicionado");
    }
    const auto& cargo = cargos.GetCurrent();
    return CTelasVota::GetInst().GetTelaCargo(cargo.GetID(), ETelaVotacao::TELA_INICIAL);
}

void CPedeMajoritario::StartStateAudio()
{
    GetTelaCargoAtual()->Slot2();
    m_pNextState = this;
}

// (original lines 56-60: content not recovered)
#line 61
void CPedeMajoritario::ProcessInputAudio()
{
    if (comum::CCargos::GetInst().IsFim()) {
        throw CUeVotaError(EUE_VOTA_PEDE_MAJORITARIO_ENTRADA_CARGO_NAO_POSICIONADO, "O cargo atual nao esta posicionado");
    }
    const auto resultado = EmiteEcoComInputField(GetTelaCargoAtual());
    switch (resultado.first) {
    case api::INPUT_BRANCO:
        SetNumeroDigitado("");
        m_pNextState = &CConfereVotoEmCargo<CMajoritarioBranco, ETelaVotacao::TELA_CONFERENCIA_VOTO_BRANCO>::GetInst();
        break;
    case api::INPUT_CONFIRMA:
        SetNumeroDigitado(resultado.second);
        if (!ExisteCandidatoValidoResposta(resultado.second)) {
            m_pNextState = &CConfereVotoEmCargo<CMajoritarioNulo, ETelaVotacao::TELA_CONFERENCIA_VOTO_NULO>::GetInst();
        } else if (ExisteVotoRepetido(resultado.second)) {
            m_pNextState =
                &CConfereVotoEmCargo<CMajoritarioRepetido, ETelaVotacao::TELA_CONFERENCIA_CANDIDATO_REPETIDO>::GetInst();
        } else {
            m_pNextState = &CConfereVotoEmCargo<CMajoritarioValido, ETelaVotacao::TELA_CONFERENCIA_VOTO_NOMINAL>::GetInst();
        }
        break;
    default:
        break;
    }
}

bool CPedeMajoritario::ExisteVotoRepetido(const std::string& numero) const
{
    const auto& cargo = comum::CCargos::GetInst().GetCurrent();
    if (cargo.GetQtdeEscolhas() == 1 || cargo.PodeRepetir() || g_escolhaAtual == 1) {
        return false;
    }
    const auto& votos = g_votosEleitor.GetVotos();
    const size_t quantidade = votos.size();
    for (comum::md::TQtdEscolha escolha = 1; escolha < g_escolhaAtual; ++escolha) {
        const comum::md::SVotoCargo& anterior = votos.at(quantidade - escolha);
        if (anterior.cargo == cargo.GetID() && anterior.voto.GetTipo() == comum::md::CVoto::NOMINAL &&
            anterior.voto.GetNumero() == numero) {
            return true;
        }
    }
    return false;
}

// (original lines 106-110: content not recovered)
#line 111
bool CPedeMajoritario::ExisteCandidatoValidoResposta(const std::string& numero) const
{
    const auto& cargo = comum::CCargos::GetInst().GetCurrent();
    const comum::TCargoID idCargo = cargo.GetID();
    const comum::TCandidatoID valor = ecourna::api::util::CStringUtils::ToDWord(numero);
    if (cargo.IsConsulta()) {
        return comum::CRespostas::GetInst().Busca(idCargo, valor) != nullptr;
    }
    const auto* candidatura = comum::CCandidaturas::GetInst().Busca(idCargo, valor);
    if (candidatura == nullptr || candidatura->GetTitular().GetSituacao() != 0) {
        return false;
    }
    if (comum::CPartidos::GetInst().Find(candidatura->GetPartidoID()) == nullptr) {
        CLogVota::GetInst().LogaErroPartidoNaoEncontrado();
        throw CUeVotaError(EUE_VOTA_PEDE_MAJORITARIO_PARTIDO_NAO_ENCONTRADO, "Nao foi encontrado o partido do candidato");
    }
    return true;
}











std::string CPedeMajoritario::GetMensagem() const
{
    if (comum::CCargos::GetInst().GetCurrent().IsConsulta()) {
        return "{cargo-atual} {quantidade-digitos}. Voto {progresso}.";
    }
    return "Você está votando para {cargo-atual}. {quantidade-digitos}. Voto {progresso}.";
}

} // namespace vota
