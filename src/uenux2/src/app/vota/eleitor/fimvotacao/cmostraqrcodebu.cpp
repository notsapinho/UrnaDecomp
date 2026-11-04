// vota::CMostraQRCodeBU and vota::IQRCodeBUDS. Reconstruction notes, not TSE's text: GetQRDSInst (fn 1956, record 31),
// IQRCodeBUDS's constructor (record 38; inlined into 1956), GeraPartes and CreateInst (inlined into 1956), StartState
// (fn 12055, record 70) with its three texts (fns 12054, 12053, 12052), ProcessInput (fn 12051, record 85), AjustaTela
// (fn 5982, record 195) and CMostraQRCodeBU's GetInst, constructor and destructor. The lines of the functions with no
// record, and every name the records do not give, are chosen (unit 37's fragment).
#include "app/vota/eleitor/fimvotacao/cmostraqrcodebu.h"

#include "api/gui/cinteractiveform.h"
#include "api/gui/ctextfield.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/dados/crdvvota.h"
#include "app/comum/iinterfaceinit.h"
#include "app/comum/relatorios/cgeradorbuqrcodevota.h"
#include "app/vota/eleitor/comum/ctelasvota.h"
#include "app/vota/eleitor/cvotacaostateaudio.h"
#include "app/vota/eleitor/fimvotacao/caplicacaoencerrada.h"
#include "app/vota/eleitor/fimvotacao/cmostraqrcodecertificado.h"
#include "app/vota/euevotaerror.h"

namespace vota {

namespace {


IQRCodeBUDS& GetQRDSInst()
{
    if (!api::CPolySingletonList::has<IQRCodeBUDS>()) {
        IQRCodeBUDS::CreateInst(IQRCodeBUDS::GeraPartes());
    }
    return api::CPolySingleton<IQRCodeBUDS>::instance();
}

} // namespace
IQRCodeBUDS::IQRCodeBUDS(std::vector<std::string> partes) : m_partes(std::move(partes))
{
    if (m_partes.empty()) {
        throw CUeVotaError(EUE_VOTA_VETOR_PARTES_VAZIO, "Vetor de partes vazio");
    }
}

CMostraQRCodeBU::CMostraQRCodeBU()
    : CEstadoComDesligamentoAutomatico(EVENTO_ENTRADA)
{
}

CMostraQRCodeBU::~CMostraQRCodeBU() = default;

CMostraQRCodeBU& CMostraQRCodeBU::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CMostraQRCodeBU());
    }
    return *s_inst;
}

std::unique_ptr<CMostraQRCodeBU> CMostraQRCodeBU::s_inst;
std::mutex CMostraQRCodeBU::s_mutex;

namespace {

std::string TextoAjuda();
std::string ConteudoQRCode();
std::string TextoPagina();

} // namespace
void CMostraQRCodeBU::StartState()
{
    bool ehDemo = api::CPolySingleton<comum::IInterfaceInit>::instance().GetDemoMode();
    if (ehDemo) {
        m_pNextState = &CAplicacaoEncerrada::GetInst();
        return;
    }
    GetQRDSInst().Reinicia();
    m_form = CTelasVota::GetInst().CriaTelaQRCodeBU(TextoAjuda, ConteudoQRCode, TextoPagina);
    AjustaTela(m_form);
    m_pNextState = this;
}

void CMostraQRCodeBU::ProcessInput()
{
    IQRCodeBUDS& ds = GetQRDSInst();
    if (m_form->GetEntradas().size() != 1) {
        throw CUeVotaError(EUE_VOTA_QRCODE_BU_NUMERO_INPUTS_INVALIDO, "Número de inputs inválido");
    }
    const api::IInputField<api::IScreen>* entrada = m_form->GetEntradas().front();
    switch (m_form->Read()) {
    case api::INPUT_CONFIRMA:
        if (ds.GetAtual() + 1 == ds.GetPartes().size()) {
            m_pNextState = &CAplicacaoEncerrada::GetInst();
        }
        break;
    case api::INPUT_BRANCO:
        m_pNextState = &CMostraQRCodeCertificado::GetInst();
        break;
    case api::INPUT_SEM_TECLA:
        switch (entrada->GetUltimaTecla()) {
        case '3':
            if (ds.Anterior()) {
                AjustaTela(m_form);
            }
            break;
        case '9':
            if (ds.Proxima()) {
                AjustaTela(m_form);
            }
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

namespace {

std::string TextoAjuda()
{
    if (GetQRDSInst().GetPartes().size() == 1) {
        return "O QR code ao lado contém o resultado da votação para esta urna.";
    }
    return "O QR code ao lado contém o resultado da votação para esta urna. Use as teclas 3 e 9 para navegar pelas "
           "partes do BU.";
}

std::string ConteudoQRCode()
{
    const IQRCodeBUDS& ds = GetQRDSInst();
    return ds.GetPartes().at(ds.GetAtual());
}

std::string TextoPagina()
{
    const IQRCodeBUDS& ds = GetQRDSInst();
    return std::to_string(ds.GetAtual() + 1) + "/" + std::to_string(ds.GetPartes().size());
}

} // namespace

// (original lines 143-180: content not recovered)
#line 181
void CMostraQRCodeBU::AjustaTela(CFormInterativoTelaVota& tela)
{
    if (tela->IsVisible()) {
        tela->Hide();
    }
    const IQRCodeBUDS& ds = GetQRDSInst();
    const auto confirma = tela->FindFieldAs<api::CTextField>("Confirma");
    const auto acaoConfirma = tela->FindFieldAs<api::CTextField>("AcaoConfirma");
    const auto acao3 = tela->FindFieldAs<api::CTextField>("Acao3");
    const auto tecla3 = tela->FindFieldAs<api::CTextField>("3");
    const auto acao9 = tela->FindFieldAs<api::CTextField>("Acao9");
    const auto tecla9 = tela->FindFieldAs<api::CTextField>("9");
    const auto pagina = tela->FindFieldAs<api::CTextField>("Pagina");
    if (!confirma || !acaoConfirma || !acao3 || !tecla3 || !acao9 || !tecla9 || !pagina) {
        throw CUeVotaError(EUE_VOTA_QRCODE_BU_CAMPO_NAO_ENCONTRADO, "Campo não encontrado no formulário");
    }
    if (ds.GetPartes().size() == 1) {
        confirma->SetCorTexto(api::TColor{2});
        acaoConfirma->SetCorTexto(api::TColor{2});
        tecla3->SetCorTexto(api::TColor{1});
        acao3->SetCorTexto(api::TColor{1});
        tecla9->SetCorTexto(api::TColor{1});
        acao9->SetCorTexto(api::TColor{1});
        pagina->SetCorTexto(api::TColor{1});
    } else {
        pagina->SetCorTexto(api::TColor{2});
        if (ds.GetAtual() == 0) {
            confirma->SetCorTexto(api::TColor{3});
            acaoConfirma->SetCorTexto(api::TColor{3});
            tecla3->SetCorTexto(api::TColor{3});
            acao3->SetCorTexto(api::TColor{3});
            tecla9->SetCorTexto(api::TColor{2});
            acao9->SetCorTexto(api::TColor{2});
        } else if (ds.GetAtual() + 1 == ds.GetPartes().size()) {
            confirma->SetCorTexto(api::TColor{2});
            acaoConfirma->SetCorTexto(api::TColor{2});
            tecla3->SetCorTexto(api::TColor{2});
            acao3->SetCorTexto(api::TColor{2});
            tecla9->SetCorTexto(api::TColor{3});
            acao9->SetCorTexto(api::TColor{3});
        } else {
            confirma->SetCorTexto(api::TColor{3});
            acaoConfirma->SetCorTexto(api::TColor{3});
            tecla3->SetCorTexto(api::TColor{2});
            acao3->SetCorTexto(api::TColor{2});
            tecla9->SetCorTexto(api::TColor{2});
            acao9->SetCorTexto(api::TColor{2});
        }
    }
    tela->Slot2();
}

std::vector<std::string> IQRCodeBUDS::GeraPartes()
{
    const comum::md::estadoaplicacao::CEstadoGeral& geral = comum::CAppInfo::GetInst().GetGeral();
    const comum::md::estadoaplicacao::CEstadoGeralGap& gap = comum::CAppInfo::GetInst().GetGap(comum::TURNO_ATUAL);
    const ueword zona = geral.GetDadoLocal().GetSecaoCarga().GetZona();
    const ueword secao = geral.GetDadoLocal().GetSecaoCarga().GetSecao();
    const ueword comparecimento = comum::CRdvVota::GetInst().Comparecimento();
    const api::CDateTime dataHoraEmissao = comum::CAppInfo::GetInst().GetVota(comum::TURNO_ATUAL).GetDtHrEmissaoBU();
    comum::CCabecalhoQRCodeBuilder cabecalho;
    cabecalho.DefineZona(zona);
    cabecalho.DefineSecao(secao);
    cabecalho.DefineIdUrna(geral.GetCorrespondencia().GetNumeroInternoUrna());
    cabecalho.DefineCodigoCarga(geral.GetCorrespondencia().GetCodigoCarga());
    std::vector<std::string> cargas;
    cargas.reserve(gap.GetCorrespondencias().size() + 1);
    for (const comum::md::estadoaplicacao::CDadoCorrespondencia& correspondencia : gap.GetCorrespondencias()) {
        cargas.push_back(std::string(correspondencia.GetCodigoCarga()));
    }
    cabecalho.DefineHistoricoCarga(cargas);
    const comum::CGeradorBUQRCodeVota gerador(cabecalho, comparecimento, false, false, dataHoraEmissao);
    return gerador.Gera(2500).first;
}

void IQRCodeBUDS::CreateInst(std::vector<std::string> partes)
{
    api::TPolySingletonsInfo& info = api::g_polySingletonsInfo();
    api::CPolySingletonList::set(std::make_unique<IQRCodeBUDS>(std::move(partes)), info);
}

} // namespace vota
