#include "app/vota/eleitor/cestadoaudio.h"

#include "api/util/csynchronizer.h"
#include "api/util/csystem.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/crdv.h"
#include "app/comum/dados/crdvvota.h"
#include "app/vota/comum/csincronizavota.h"

namespace vota {

CEstadoAudio& CEstadoAudio::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CEstadoAudio());
    }
    return *s_inst;
}

std::unique_ptr<CEstadoAudio> CEstadoAudio::s_inst;
std::mutex CEstadoAudio::s_mutex;

CEstadoAudio::CEstadoAudio()
    : m_dadosCarregados(false)
    , m_eleitoresCarregados(false)
    , m_modo(MODO_DESATIVADO)
    , m_bancoCarregado(false)
    , m_teclaEsperada(0)
    , m_teclaPressionada(0)
{
}

void CEstadoAudio::SelecionaModo0()
{
    m_modo = MODO_0;
}

void CEstadoAudio::SelecionaModo1()
{
    m_modo = MODO_1;
}

void CEstadoAudio::GeraDadosDinamicos()
{
    CSincronizaVota::VerificaUrnaDesligando();
    if (comum::CAppInfo::EhTreinamentoEleitor()) {
        api::CSystem::RemoveFile(comum::GetArquivoRdvInterno());
        api::CSystem::RemoveFile(comum::GetArquivoRdvExterno());
        const comum::CRdvVota& rdv = comum::CRdvVota::GetInst();
        rdv.SalvaInterno();
        CSincronizaVota::AssinaRDVEBancoDados();
        rdv.SalvaExterno();
    } else {
        const comum::CEleitores& eleitores = comum::CEleitores::GetInst();
        const comum::CRdvVota& rdv = comum::CRdvVota::GetInst();
        CSincronizaVota::CriaBancoDadosMI(eleitores);
        rdv.SalvaInterno();
        CSincronizaVota::AssinaRDVEBancoDados();
        CSincronizaVota::CriaBancoDadosMV(eleitores);
        rdv.SalvaExterno();
    }
    CSincronizaVota::SincronizaAssinaturaDadosDinamicos();
    api::CSynchronizer::GetInst().Sync();
}

void CEstadoAudio::Desativa()
{
    m_modo = MODO_DESATIVADO;
}

bool CEstadoAudio::Modo0Selecionado() const
{
    return m_modo == MODO_0;
}

bool CEstadoAudio::Modo1Selecionado() const
{
    return m_modo == MODO_1;
}

void CEstadoAudio::SetTeclasTesteTeclado(char esperada, char pressionada)
{
    m_teclaEsperada = esperada;
    m_teclaPressionada = pressionada;
}

std::pair<char, char> CEstadoAudio::GetTeclasTesteTeclado() const
{
    return {m_teclaEsperada, m_teclaPressionada};
}

} // namespace vota
