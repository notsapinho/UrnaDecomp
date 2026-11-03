// vota's operator screens of vota::CPedeIdentidade. This comment is the reconstruction's: no record names this file, so
// its path, its name and every line are chosen; src/units/51-uenux2-ctextfieldupdatemt.mk gives the evidence that the
// code is in a file of its own, linked after ctextfieldupdatemt.cpp, and what was measured. Written here:
// api::CMTFormBuilder::AddTextFieldUpdate (the instance over api::CTextSource, defined here because it builds an
// api::CTextFieldUpdateMT), the constant TITULO_TREINAMENTO, MontaTelaPedeIdentidade and the functions it builds the
// form with. Binaryen inlines each into its one caller, so none has a target index: the chain ends in fn 652,
// vota::CPedeIdentidade::GetInst, whose constructor calls MontaTelaPedeIdentidade. Of the order of the definitions,
// only MontaTelaPedeIdentidade's place ahead of both builders is measured (the fragment says how); the rest is free.
#include "app/vota/operador/comum/telasoperador.h"

#include <chrono>
#include <format>
#include <string>
#include <vector>

#include "api/gui/capplication.h"
#include "api/gui/cdatatextfmt.h"
#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/ctextsource.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/celeitores.h"
#include "app/vota/operador/comum/ctextfieldupdatemt.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

namespace api {

template <typename FONTE>
void CMTFormBuilder::AddTextFieldUpdate(FONTE fonte, const SPoint& posicao, const std::chrono::milliseconds& intervalo,
                                        const std::string& formato)
{
    const SharedIText text(new CDataTextFmt<FONTE>(fonte, formato));
    SharedField campo(new CTextFieldUpdateMT(posicao, text, intervalo));
    m_campos.push_back(campo);
}

} // namespace api

namespace vota {

const char TITULO_TREINAMENTO[] = "TREINAMENTO DE ELEITORES";

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTelaTreinamento();
std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTelaVotacao(std::shared_ptr<std::string> aviso);

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTelaPedeIdentidade(std::shared_ptr<std::string> aviso)
{
    if (comum::CAppInfo::EhTreinamentoEleitor()) {
        return MontaTelaTreinamento();
    }
    return MontaTelaVotacao(aviso);
}

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTelaTreinamento()
{
    api::CMTFormBuilder builder;
    builder.AddBuzz(51, 10);
    builder.AddClock(api::SPoint{33, 1});
    builder.AddTextField(TITULO_TREINAMENTO, api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("Votos:", api::SPoint{30, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&GetTextoComparecimento, api::SPoint{37, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&GetTextoAudio, api::SPoint{40, 3}, api::ALINHAMENTO_DIREITA);
    builder.AddTextField("CORRIGE: outras opções", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField("CONFIRMA: votar", api::SPoint{1, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddLed(api::LED_OPERACAO_0);
    builder.AddInputControl();
    return builder.GetInteractiveForm("", true);
}

std::string DescricaoTipoIdentificador(ecourna::app::dados::ETipoIdentificadorEleitor tipo)
{
    switch (tipo) {
    case ecourna::app::dados::TipoIDInscricaoEleitoral:
        return "o Título";
    case ecourna::app::dados::TipoIDCPF:
        return "o CPF";
    case ecourna::app::dados::TipoIDNumeroLivre:
        return "o Identificador";
    default:
        return "a Identidade";
    }
}

std::string TextoDigiteIdentificador()
{
    const std::vector<ecourna::app::dados::ETipoIdentificadorEleitor>& tiposEleicao =
        comum::CConfiguracaoEleicao::GetInst().GetTiposIdentificador();
    std::vector<std::string> tipos;
    for (const auto tipo : tiposEleicao) {
        tipos.push_back(DescricaoTipoIdentificador(tipo));
    }
    const std::string identificadores = api::Join(tipos, " ou ");
    return std::format("Digite {}", identificadores);
}

namespace {

std::string TextoQuantidadeAptos()
{
    const comum::CEleitores::SQuantidadeAptos aptos = comum::CEleitores::GetInst().QuantidadeAptos();
    return std::format("/{:04}", static_cast<ueword>(aptos.m_semTransferencia + aptos.m_comTransferencia));
}

} // namespace

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTelaVotacao(std::shared_ptr<std::string> aviso)
{
    const std::string textoAptos = TextoQuantidadeAptos();
    api::CMTFormBuilder builder;
    builder.AddBuzz(51, 10);
    builder.AddClock(api::SPoint{33, 1});
    builder.AddTextField(TextoDigiteIdentificador(), api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&GetTextoComparecimento, api::SPoint{32, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(textoAptos, api::SPoint{36, 2}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(&GetTextoAudio, api::SPoint{40, 4}, api::ALINHAMENTO_DIREITA);
    builder.AddTextFieldUpdate(api::CTextSource(aviso), api::SPoint{1, 4}, std::chrono::milliseconds(300), "%s");
    builder.AddLed(api::LED_OPERACAO_0);
    AdicionaCampoNumerico(builder, 12, true, api::SPoint{1, 2});
    return builder.GetInteractiveForm("", true);
}

} // namespace vota
