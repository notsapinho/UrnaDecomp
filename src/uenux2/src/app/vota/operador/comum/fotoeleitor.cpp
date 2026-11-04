// vota::ApresentaFotoEleitor (target fn 3616) and vota::MostraFotoIndisponivel (fn 3617), with the three functions
// 3616 holds behind frames of their own. This comment is the reconstruction's: no record names this file or any of its
// functions, so its path, its layout and every name in it are chosen
// (src/units/319-uenux2-app-vota-operador-comum.mk says why each is where it is).
#include "app/vota/operador/comum/fotoeleitor.h"

#include <string>
#include <vector>

#include "api/gui/cfixedimage.h"
#include "app/comum/cinfomtlcd.h"
#include "app/comum/dados/celeitores.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "app/vota/log/clogvota.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/comum/infofoto.h"
#include "ecourna/app/dados/cfoto.hpp"
#include "ecourna/app/dados/resultadournacadastro/capresentacaofotoeleitor.hpp"

namespace vota {

void MostraFotoIndisponivel()
{
    comum::CInfoMTLCD::GetInst().MostraImagem(api::CFixedImage(":/resource/images/biometria/fotoIndisponivel.jpg"),
        api::SPoint{0, 0});
}

void MostraEleitorSemBiometria()
{
    comum::CInfoMTLCD::GetInst().MostraImagem(api::CFixedImage(":/resource/images/biometria/semBiometria.jpg"),
        api::SPoint{0, 0});
}

bool ValidaFotoEleitor(const ecourna::app::dados::CFoto& foto)
{
    const SInfoFoto info = LeInfoFoto(foto.GetImagem());
    if (info.largura == -1 || info.altura == -1 || info.bitsPorPixel == -1) {
        SetFotoNaoApresentada(ecourna::app::dados::CApresentacaoFotoEleitor::ErroFormato);
        CLogVota::GetInst().LogaErroCarregarFotoEleitor();
        return false;
    }
    if (info.largura < 120 || info.largura > 240) {
        SetFotoNaoApresentada(ecourna::app::dados::CApresentacaoFotoEleitor::ErroResolucao);
        CLogVota::GetInst().LogaLarguraFotoInvalida(info.largura);
        return false;
    }
    if (info.altura < 160 || info.altura > 320) {
        SetFotoNaoApresentada(ecourna::app::dados::CApresentacaoFotoEleitor::ErroResolucao);
        CLogVota::GetInst().LogaAlturaFotoInvalida(info.altura);
        return false;
    }
    if (info.bitsPorPixel != 8) {
        SetFotoNaoApresentada(ecourna::app::dados::CApresentacaoFotoEleitor::ErroProfundidadeCores);
        CLogVota::GetInst().LogaQuantidadeCoresFoto(info.bitsPorPixel);
        return false;
    }
    return true;
}

void ApresentaFotoEleitor()
{
    const comum::md::CEleitorIdentidade identidade = GetIdentidadeEleitor();
    const comum::CEleitorDetalhe* eleitor = comum::CEleitores::GetInst().LocalizaEleitor(
        comum::md::FormataIdentidade(identidade.GetIdentificador(), identidade.GetTipo()), identidade.GetTipo());
    if (eleitor == nullptr) {
        return;
    }
    if (!eleitor->GetEleitor().TemBiometria()) {
        SetEleitorSemFoto();
        MostraEleitorSemBiometria();
        return;
    }
    const comum::md::CBiometriaEleitor biometria = eleitor->GetBiometria();
    if (biometria.GetErroDecifracao() > 0) {
        MostraFotoIndisponivel();
        if (biometria.GetErroDecifracao() == 9) {
            SetFotoNaoApresentada(ecourna::app::dados::CApresentacaoFotoEleitor::ErroDecifrandoBuffer);
        } else {
            SetFotoNaoApresentada(ecourna::app::dados::CApresentacaoFotoEleitor::ErroDesconhecidoDeCriptografia);
        }
    } else if (!biometria.TemFoto()) {
        SetEleitorSemFoto();
        MostraFotoIndisponivel();
    } else {
        const std::vector<uebyte> imagem = biometria.GetFoto().GetImagem();
        const ecourna::app::dados::CFoto foto(ecourna::app::dados::CFoto::EFI_JPEG, imagem);
        if (ValidaFotoEleitor(foto)) {
            comum::CInfoMTLCD::GetInst().MostraImagem(imagem, api::SPoint{0, 0});
            impl::IInformacaoThreadOperador::GetInst().SetFotoApresentada();
            CLogVota::GetInst().LogaFotoEleitorApresentada();
        } else {
            MostraFotoIndisponivel();
        }
    }
}

} // namespace vota
