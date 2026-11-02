// comum::CArquivosSavd (/home/rubio/tse/uenux2/src/app/comum/carquivossavd.cpp). Its two throws are records of the target:
//   275  operator[](ESavdPacote) const     record at line 49, column 15
//   680  operator[](ESavdArquivoUE) const  record at line 73, column 15
// The functions with no record (GetInst, fn 1164, with the constructor and its three loaders inlined; the destructor,
// fn 5907; DescricaoArquivo, fn 5905) and their lines are chosen (src/units/95-uenux2-app-comum.mk).

#include "app/comum/carquivossavd.h"

#include <format>

#include "app/comum/carquivosresultado.h"
#include "app/comum/cpath.h"
#include "app/comum/euecomumerror.h"

namespace comum {

CArquivosSavd& CArquivosSavd::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_instancia) {
        s_instancia.reset(new CArquivosSavd);
    }
    return *s_instancia;
}

std::unique_ptr<CArquivosSavd> CArquivosSavd::s_instancia;
std::mutex CArquivosSavd::s_mutex;

CArquivosSavd::CArquivosSavd()
{
    CarregaAssinaturas();
    CarregaAssinados();
    CarregaNomesPacotes();
}

CArquivosSavd::~CArquivosSavd() = default;

// (original lines 38-44: content not recovered)
#line 45
std::string CArquivosSavd::operator[](ESavdPacote pacote) const
{
    const auto it = m_assinaturas.find(pacote);
    if (it == m_assinaturas.end()) {
        throw CUeComumError(EUE_COMUM_ARQUIVO_ASSINATURA_NAO_ENCONTRADO, std::format("Arquivo de assinatura associado ao identificador {} não encontrado", pacote));
    }
    return it->second;
}

// (original lines 54-68: content not recovered)
#line 69
std::string CArquivosSavd::operator[](ESavdArquivoUE arquivo) const
{
    const auto it = m_assinados.find(arquivo);
    if (it == m_assinados.end()) {
        throw CUeComumError(EUE_COMUM_ARQUIVO_ASSINADO_NAO_ENCONTRADO, std::format("Arquivo assinado associado ao identificador {} não encontrado", arquivo));
    }
    return it->second;
}

std::string DescricaoArquivo(ESavdArquivoUE arquivo)
{
    switch (arquivo) {
    case 25:
        return "EG Geral MI";
    case 26:
        return "EG Geral ME";
    case 27:
        return "EG GAP 1 MI";
    case 28:
        return "EG GAP 2 MI";
    case 29:
        return "EG GAP 1 ME";
    case 30:
        return "EG GAP 2 ME";
    case 31:
        return "EG VOTA MI";
    case 32:
        return "EG VOTA ME";
    case 33:
        return "EG SA MI";
    case 34:
        return "Tabela de correspondência";
    case 35:
        return "BU do VOTA MI (res)";
    case 36:
        return "BU do SA MI (res)";
    case 37:
        return "RDV MI (res)";
    case 38:
        return "Res. RDV SA";
    case 39:
        return "Justif. de Seção MI (res)";
    case 40:
        return "Justif. SA (res)";
    case 41:
        return "Justif. de MRJ MI (res)";
    case 42:
        return "Justif. de MRJ ME (res)";
    case 43:
        return "BU imp. do VOTA MI (res)";
    case 44:
        return "ZE imp. do VOTA MI (res)";
    case 45:
        return "BU imp. do SA MI (res)";
    case 46:
        return "Hashes MI (res)";
    case 47:
        return "Hashes do SA MI (res)";
    case 48:
        return "Habilitados MI (res)";
    case 49:
        return "Não Habilitados MI (res)";
    case 50:
        return "Mesario MI (res)";
    case 51:
        return "Habilitados ME (res)";
    case 52:
        return "Não Habilitados ME (res)";
    case 53:
        return "Mesario ME (res)";
    case 54:
        return "Habilitados MI (res)";
    case 55:
        return "Não Habilitados MI (res)";
    case 56:
        return "Mesario MI (res)";
    case 57:
        return "Habilitados ME (res)";
    case 58:
        return "Não Habilitados ME (res)";
    case 59:
        return "Mesario ME (res)";
    case 60:
        return "Log MI (res)";
    case 61:
        return "Log do SA MI (res)";
    case 62:
        return "Log da MR do SA MI (res)";
    case 63:
        return "BU do VOTA ME (res)";
    case 64:
        return "Justif. de Seção ME (res)";
    case 65:
        return "RDV ME (res)";
    case 66:
        return "BU imp. do VOTA ME (res)";
    case 67:
        return "ZE imp. do VOTA ME (res)";
    case 68:
        return "Hashes ME (res)";
    case 69:
        return "Log ME (res)";
    case 70:
        return "Arquivo de versões na MI";
    case 71:
        return "Arquivo de versões na ME";
    case 72:
        return "Arquivo de versões do SA";
    case 73:
        return "Justif. de Seção MI (rec. Para SA)";
    case 74:
        return "RDV MI (rec. Para SA)";
    case 75:
        return "BU imp. MI (rec. Para SA)";
    case 76:
        return "ZE imp. MI (rec. Para SA)";
    case 77:
        return "Log MI (rec. Para SA)";
    case 78:
        return "Justif. de Seção ME (rec. Para SA)";
    case 79:
        return "RDV ME (rec. Para SA)";
    case 80:
        return "BU imp. ME (rec. Para SA)";
    case 81:
        return "ZE imp. ME (rec. Para SA)";
    case 82:
        return "Log ME (rec. Para SA)";
    case 83:
        return "RDV MI";
    case 84:
        return "BU imp. de Justif. Seção MI";
    case 85:
        return "BU imp. de Justif. Seção ME";
    case 86:
        return "BU imp. do VOTA MI";
    case 87:
        return "BU imp. do VOTA ME";
    case 88:
        return "Zerésima MI";
    case 89:
        return "Resumo da Zerésima MI";
    case 90:
        return "BU imp. do RED. MI";
    case 91:
        return "BUJ imp. do RED MI";
    case 92:
        return "BIM imp. do RED MI";
    case 93:
        return "BEHB imp. do RED MI";
    case 94:
        return "BU imp. do RED ME";
    case 95:
        return "BUJ imp. do RED. ME";
    case 96:
        return "BIM imp. do RED. ME";
    case 97:
        return "BEHB imp. do RED. ME";
    case 98:
        return "RDV SA INT";
    case 99:
        return "ZE SA INT";
    case 100:
        return "BU SEÇÃO SA INT";
    case 101:
        return "SARAIZ SA INT";
    case 102:
        return "SASECAO SA INT";
    case 103:
        return "BU DIGITADO SA INT";
    case 104:
        return "REG CERTIFICAÇÕES SIECO";
    case 105:
        return "REG AUTENTICAÇÕES SIECO";
    case 106:
        return "BIM da MI";
    case 107:
        return "BIM da ME";
    case 108:
        return "BEHB da MI";
    case 109:
        return "BEHB da ME";
    case 110:
        return "UENUXDB INT";
    case 111:
        return "UENUXDB EXT";
    case 112:
        return "Arquivo de local";
    case 113:
        return "Dados disp. carga";
    case 114:
        return "UENUX CFG";
    case 115:
        return "EG RED MI";
    case 116:
        return "ZE imp. SA (res)";
    case 117:
        return "Habilitados da MR do SA MI (res)";
    case 118:
        return "Não habilitados da MR do SA MI (res)";
    case 119:
        return "Mesário da MR do SA MI (res)";
    case 120:
        return "";
    default:
        return "Arquivo não identificado";
    }
}

void CArquivosSavd::CarregaAssinaturas()
{
    m_assinaturas[ESavdPacote(120)] = (CPath::GetPathDinamico(FLASH_INTERNA) / "eg.vsu").string();
    m_assinaturas[ESavdPacote(121)] = (CPath::GetPathDinamico(FLASH_EXTERNA) / "eg.vsu").string();
    m_assinaturas[ESavdPacote(146)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_1) / "gap.vsu").string();
    m_assinaturas[ESavdPacote(147)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_2) / "gap.vsu").string();
    m_assinaturas[ESavdPacote(148)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_1) / "gap.vsu").string();
    m_assinaturas[ESavdPacote(149)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_2) / "gap.vsu").string();
    m_assinaturas[ESavdPacote(122)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_1) / "vota.vsu").string();
    m_assinaturas[ESavdPacote(123)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_2) / "vota.vsu").string();
    m_assinaturas[ESavdPacote(124)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_1) / "vota.vsu").string();
    m_assinaturas[ESavdPacote(125)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_2) / "vota.vsu").string();
    m_assinaturas[ESavdPacote(126)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_1) / "bu.vsu").string();
    m_assinaturas[ESavdPacote(127)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_2) / "bu.vsu").string();
    m_assinaturas[ESavdPacote(128)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_1) / "bu.vsu").string();
    m_assinaturas[ESavdPacote(129)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_2) / "bu.vsu").string();
    m_assinaturas[ESavdPacote(130)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_1) / "buj.vsu").string();
    m_assinaturas[ESavdPacote(131)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_2) / "buj.vsu").string();
    m_assinaturas[ESavdPacote(132)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_1) / "buj.vsu").string();
    m_assinaturas[ESavdPacote(133)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_2) / "buj.vsu").string();
    m_assinaturas[ESavdPacote(138)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_1) / "ze.vsu").string();
    m_assinaturas[ESavdPacote(139)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_2) / "ze.vsu").string();
    m_assinaturas[ESavdPacote(140)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_1) / "ze.vsu").string();
    m_assinaturas[ESavdPacote(141)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_2) / "ze.vsu").string();
    m_assinaturas[ESavdPacote(142)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_1) / "rze.vsu").string();
    m_assinaturas[ESavdPacote(143)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_2) / "rze.vsu").string();
    m_assinaturas[ESavdPacote(144)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_1) / "rze.vsu").string();
    m_assinaturas[ESavdPacote(145)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_2) / "rze.vsu").string();
    m_assinaturas[ESavdPacote(134)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_1) / "rdv.vsu").string();
    m_assinaturas[ESavdPacote(135)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_2) / "rdv.vsu").string();
    m_assinaturas[ESavdPacote(136)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_1) / "rdv.vsu").string();
    m_assinaturas[ESavdPacote(137)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_2) / "rdv.vsu").string();
    m_assinaturas[ESavdPacote(150)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_1) / "sa.vsu").string();
    m_assinaturas[ESavdPacote(151)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_2) / "sa.vsu").string();
    m_assinaturas[ESavdPacote(152)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_1) / "red.vsu").string();
    m_assinaturas[ESavdPacote(153)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_2) / "red.vsu").string();
    m_assinaturas[ESavdPacote(154)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_1) / "red.vsu").string();
    m_assinaturas[ESavdPacote(155)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_2) / "red.vsu").string();
    m_assinaturas[ESavdPacote(156)] = (CPath::GetPathTrabExterno() / "tabcorr.vsc").string();
    m_assinaturas[ESavdPacote(157)] = (CPath::GetPathEstatico(FLASH_EXTERNA) / "{:05}{:04}{:04}-lo.vsc").string();
    m_assinaturas[ESavdPacote(203)] = (CPath::GetPathEstatico(FLASH_EXTERNA) / "dadoscarga.vsu").string();
    m_assinaturas[ESavdPacote(158)] = (CPath::GetPathResult(FLASH_INTERNA, TURNO_1) / "{:c}{:05}{}{:05}{:04}{:04}-").string() + CArquivosResultado::GetInst()[EXTENSAO_VOTA_VSC];
    m_assinaturas[ESavdPacote(159)] = (CPath::GetPathResult(FLASH_INTERNA, TURNO_2) / "{:c}{:05}{}{:05}{:04}{:04}-").string() + CArquivosResultado::GetInst()[EXTENSAO_VOTA_VSC];
    m_assinaturas[ESavdPacote(160)] = (CPath::GetPathResult(FLASH_EXTERNA, TURNO_1) / "{:c}{:05}{}{:05}{:04}{:04}-").string() + CArquivosResultado::GetInst()[EXTENSAO_VOTA_VSC];
    m_assinaturas[ESavdPacote(161)] = (CPath::GetPathResult(FLASH_EXTERNA, TURNO_2) / "{:c}{:05}{}{:05}{:04}{:04}-").string() + CArquivosResultado::GetInst()[EXTENSAO_VOTA_VSC];
    m_assinaturas[ESavdPacote(162)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_SA_VSC];
    m_assinaturas[ESavdPacote(163)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_SA_VSC];
    m_assinaturas[ESavdPacote(164)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_SA_VSC];
    m_assinaturas[ESavdPacote(165)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_SA_VSC];
    m_assinaturas[ESavdPacote(166)] = (CPath::GetPathResult(FLASH_INTERNA, TURNO_1) / "{:c}{:05}{}{:05}{:04}{:04}-").string() + CArquivosResultado::GetInst()[EXTENSAO_RED_VSC];
    m_assinaturas[ESavdPacote(167)] = (CPath::GetPathResult(FLASH_INTERNA, TURNO_2) / "{:c}{:05}{}{:05}{:04}{:04}-").string() + CArquivosResultado::GetInst()[EXTENSAO_RED_VSC];
    m_assinaturas[ESavdPacote(168)] = (CPath::GetPathResult(FLASH_EXTERNA, TURNO_1) / "{:c}{:05}{}{:05}{:04}{:04}-").string() + CArquivosResultado::GetInst()[EXTENSAO_RED_VSC];
    m_assinaturas[ESavdPacote(169)] = (CPath::GetPathResult(FLASH_EXTERNA, TURNO_2) / "{:c}{:05}{}{:05}{:04}{:04}-").string() + CArquivosResultado::GetInst()[EXTENSAO_RED_VSC];
    m_assinaturas[ESavdPacote(170)] = (CPath::GetPathRootSemSA(FLASH_INTERNA) / "dinamico/sa/{}/trab1/").string() + "rdv.vsu";
    m_assinaturas[ESavdPacote(171)] = (CPath::GetPathRootSemSA(FLASH_INTERNA) / "dinamico/sa/{}/trab2/").string() + "rdv.vsu";
    m_assinaturas[ESavdPacote(172)] = (CPath::GetPathRootSemSA(FLASH_INTERNA) / "dinamico/sa/{}/trab1/").string() + "rdv.vsu";
    m_assinaturas[ESavdPacote(173)] = (CPath::GetPathRootSemSA(FLASH_INTERNA) / "dinamico/sa/{}/trab2/").string() + "rdv.vsu";
    m_assinaturas[ESavdPacote(174)] = (CPath::GetPathRootSemSA(FLASH_EXTERNA) / "dinamico/sa/{}/trab1/").string() + "rdv.vsu";
    m_assinaturas[ESavdPacote(175)] = (CPath::GetPathRootSemSA(FLASH_EXTERNA) / "dinamico/sa/{}/trab2/").string() + "rdv.vsu";
    m_assinaturas[ESavdPacote(176)] = (CPath::GetPathRootSemSA(FLASH_INTERNA) / "dinamico/sa/{}/trab1/").string() + "ze.vsu";
    m_assinaturas[ESavdPacote(177)] = (CPath::GetPathRootSemSA(FLASH_INTERNA) / "dinamico/sa/{}/trab2/").string() + "ze.vsu";
    m_assinaturas[ESavdPacote(178)] = (CPath::GetPathRootSemSA(FLASH_INTERNA) / "dinamico/sa/{}/trab1/").string() + "ze.vsu";
    m_assinaturas[ESavdPacote(179)] = (CPath::GetPathRootSemSA(FLASH_INTERNA) / "dinamico/sa/{}/trab2/").string() + "ze.vsu";
    m_assinaturas[ESavdPacote(180)] = (CPath::GetPathRootSemSA(FLASH_INTERNA) / "dinamico/sa/{}/trab1/").string() + "bu.vsu";
    m_assinaturas[ESavdPacote(181)] = (CPath::GetPathRootSemSA(FLASH_INTERNA) / "dinamico/sa/{}/trab2/").string() + "bu.vsu";
    m_assinaturas[ESavdPacote(182)] = (CPath::GetPathRootSemSA(FLASH_INTERNA) / "dinamico/sa/{}/trab1/").string() + "saraiz.vsu";
    m_assinaturas[ESavdPacote(183)] = (CPath::GetPathRootSemSA(FLASH_INTERNA) / "dinamico/sa/{}/trab2/").string() + "saraiz.vsu";
    m_assinaturas[ESavdPacote(184)] = (CPath::GetPathRootSemSA(FLASH_INTERNA) / "dinamico/sa/{}/trab1/").string() + "sasecao.vsu";
    m_assinaturas[ESavdPacote(185)] = (CPath::GetPathRootSemSA(FLASH_INTERNA) / "dinamico/sa/{}/trab2/").string() + "sasecao.vsu";
    m_assinaturas[ESavdPacote(186)] = (CPath::GetPathRootSemSA(FLASH_INTERNA) / "dinamico/sa/{}/trab1/").string() + "busa.vsu";
    m_assinaturas[ESavdPacote(187)] = (CPath::GetPathRootSemSA(FLASH_INTERNA) / "dinamico/sa/{}/trab2/").string() + "busa.vsu";
    m_assinaturas[ESavdPacote(188)] = (CPath::GetPathRootSemSA(FLASH_EXTERNA) / "dinamico/sa/{}/trab1/").string() + "busa.vsu";
    m_assinaturas[ESavdPacote(189)] = (CPath::GetPathRootSemSA(FLASH_EXTERNA) / "dinamico/sa/{}/trab2/").string() + "busa.vsu";
    m_assinaturas[ESavdPacote(190)] = (CPath::GetPathMR() / "sieco-dados/").string();
    m_assinaturas[ESavdPacote(191)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_1) / "bim.vsu").string();
    m_assinaturas[ESavdPacote(192)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_2) / "bim.vsu").string();
    m_assinaturas[ESavdPacote(193)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_1) / "bim.vsu").string();
    m_assinaturas[ESavdPacote(194)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_2) / "bim.vsu").string();
    m_assinaturas[ESavdPacote(195)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_1) / "behb.vsu").string();
    m_assinaturas[ESavdPacote(196)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_2) / "behb.vsu").string();
    m_assinaturas[ESavdPacote(197)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_1) / "behb.vsu").string();
    m_assinaturas[ESavdPacote(198)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_2) / "behb.vsu").string();
    m_assinaturas[ESavdPacote(199)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_1) / "uenux.vsu").string();
    m_assinaturas[ESavdPacote(200)] = (CPath::GetPathTrab(FLASH_INTERNA, TURNO_2) / "uenux.vsu").string();
    m_assinaturas[ESavdPacote(201)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_1) / "uenux.vsu").string();
    m_assinaturas[ESavdPacote(202)] = (CPath::GetPathTrab(FLASH_EXTERNA, TURNO_2) / "uenux.vsu").string();
}

void CArquivosSavd::CarregaAssinados()
{
    m_assinados[ESavdArquivoUE(25)] = "eg.bin";
    m_assinados[ESavdArquivoUE(26)] = "eg.bin";
    m_assinados[ESavdArquivoUE(27)] = "gap.bin";
    m_assinados[ESavdArquivoUE(28)] = "gap.bin";
    m_assinados[ESavdArquivoUE(29)] = "gap.bin";
    m_assinados[ESavdArquivoUE(30)] = "gap.bin";
    m_assinados[ESavdArquivoUE(31)] = "vota.bin";
    m_assinados[ESavdArquivoUE(32)] = "vota.bin";
    m_assinados[ESavdArquivoUE(33)] = "sa.bin";
    m_assinados[ESavdArquivoUE(115)] = "red.bin";
    m_assinados[ESavdArquivoUE(34)] = "tabcorr.dat";
    m_assinados[ESavdArquivoUE(112)] = "{:05}{:04}{:04}-lo.dat";
    m_assinados[ESavdArquivoUE(113)] = "dadoscarga.dat";
    m_assinados[ESavdArquivoUE(35)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_BU_DAT];
    m_assinados[ESavdArquivoUE(36)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_BUSA_DAT];
    m_assinados[ESavdArquivoUE(37)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_RDV_DAT];
    m_assinados[ESavdArquivoUE(39)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_JUFA_DAT];
    m_assinados[ESavdArquivoUE(41)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_JUFA_DAT];
    m_assinados[ESavdArquivoUE(42)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_JUFA_DAT];
    m_assinados[ESavdArquivoUE(43)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_IMGBU_DAT];
    m_assinados[ESavdArquivoUE(44)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_IMGZE_DAT];
    m_assinados[ESavdArquivoUE(45)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_IMGBUSA_DAT];
    m_assinados[ESavdArquivoUE(46)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_HASH_DAT];
    m_assinados[ESavdArquivoUE(47)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_HASH_DAT];
    m_assinados[ESavdArquivoUE(48)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_WSQBIO_JEZ];
    m_assinados[ESavdArquivoUE(49)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_WSQMAN_JEZ];
    m_assinados[ESavdArquivoUE(50)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_WSQMES_JEZ];
    m_assinados[ESavdArquivoUE(51)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_WSQBIO_JEZ];
    m_assinados[ESavdArquivoUE(52)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_WSQMAN_JEZ];
    m_assinados[ESavdArquivoUE(53)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_WSQMES_JEZ];
    m_assinados[ESavdArquivoUE(54)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_WSQBIO_JEZ];
    m_assinados[ESavdArquivoUE(55)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_WSQMAN_JEZ];
    m_assinados[ESavdArquivoUE(56)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_WSQMES_JEZ];
    m_assinados[ESavdArquivoUE(57)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_WSQBIO_JEZ];
    m_assinados[ESavdArquivoUE(58)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_WSQMAN_JEZ];
    m_assinados[ESavdArquivoUE(59)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_WSQMES_JEZ];
    m_assinados[ESavdArquivoUE(60)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_LOG_JEZ];
    m_assinados[ESavdArquivoUE(61)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_LOGSA_JEZ];
    m_assinados[ESavdArquivoUE(63)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_BU_DAT];
    m_assinados[ESavdArquivoUE(64)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_JUFA_DAT];
    m_assinados[ESavdArquivoUE(65)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_RDV_DAT];
    m_assinados[ESavdArquivoUE(66)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_IMGBU_DAT];
    m_assinados[ESavdArquivoUE(67)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_IMGZE_DAT];
    m_assinados[ESavdArquivoUE(68)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_HASH_DAT];
    m_assinados[ESavdArquivoUE(69)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_LOG_JEZ];
    m_assinados[ESavdArquivoUE(73)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_JUFA_DAT];
    m_assinados[ESavdArquivoUE(74)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_RDVRED_DAT];
    m_assinados[ESavdArquivoUE(75)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_IMGBU_DAT];
    m_assinados[ESavdArquivoUE(76)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_IMGZE_DAT];
    m_assinados[ESavdArquivoUE(77)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_LOG_JEZ];
    m_assinados[ESavdArquivoUE(78)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_JUFA_DAT];
    m_assinados[ESavdArquivoUE(79)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_RDVRED_DAT];
    m_assinados[ESavdArquivoUE(80)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_IMGBU_DAT];
    m_assinados[ESavdArquivoUE(81)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_IMGZE_DAT];
    m_assinados[ESavdArquivoUE(82)] = "{:c}{:05}{}{:05}{:04}{:04}-" + CArquivosResultado::GetInst()[EXTENSAO_LOG_JEZ];
    m_assinados[ESavdArquivoUE(83)] = "rdv.dat";
    m_assinados[ESavdArquivoUE(84)] = "buj.dat";
    m_assinados[ESavdArquivoUE(106)] = "bim.dat";
    m_assinados[ESavdArquivoUE(108)] = "behb.dat";
    m_assinados[ESavdArquivoUE(86)] = "bu.dat";
    m_assinados[ESavdArquivoUE(85)] = "buj.dat";
    m_assinados[ESavdArquivoUE(107)] = "bim.dat";
    m_assinados[ESavdArquivoUE(109)] = "behb.dat";
    m_assinados[ESavdArquivoUE(87)] = "bu.dat";
    m_assinados[ESavdArquivoUE(88)] = "ze.dat";
    m_assinados[ESavdArquivoUE(89)] = "rze.dat";
    m_assinados[ESavdArquivoUE(90)] = "bur.dat";
    m_assinados[ESavdArquivoUE(91)] = "bujr.dat";
    m_assinados[ESavdArquivoUE(92)] = "bimr.dat";
    m_assinados[ESavdArquivoUE(93)] = "behbr.dat";
    m_assinados[ESavdArquivoUE(94)] = "bur.dat";
    m_assinados[ESavdArquivoUE(95)] = "bujr.dat";
    m_assinados[ESavdArquivoUE(96)] = "bimr.dat";
    m_assinados[ESavdArquivoUE(97)] = "behbr.dat";
    m_assinados[ESavdArquivoUE(98)] = "rdv.dat";
    m_assinados[ESavdArquivoUE(99)] = "ze.dat";
    m_assinados[ESavdArquivoUE(100)] = "bu.dat";
    m_assinados[ESavdArquivoUE(101)] = "saraiz.bin";
    m_assinados[ESavdArquivoUE(102)] = "sasecao.bin";
    m_assinados[ESavdArquivoUE(103)] = "busa.dig";
    m_assinados[ESavdArquivoUE(110)] = "uenux.db";
    m_assinados[ESavdArquivoUE(111)] = "uenux.db";
    m_assinados[ESavdArquivoUE(104)] = "uesieco-20[0-9]{2}.[0-1][0-9].[0-3][0-9]-[0-2][0-9].[0-5][0-9].[0-5][0-9]-[0-9]{8}-cert.dat";
    m_assinados[ESavdArquivoUE(105)] = "uesieco-20[0-9]{2}.[0-1][0-9].[0-3][0-9]-[0-2][0-9].[0-5][0-9].[0-5][0-9]-[0-9]{8}-aut.dat";
}

void CArquivosSavd::CarregaNomesPacotes()
{
    m_nomesPacotes[ESavdNomePacote(19)] = "partido.pub";
    m_nomesPacotes[ESavdNomePacote(18)] = "partido.app";
    m_nomesPacotes[ESavdNomePacote(17)] = "partido";
    m_nomesPacotes[ESavdNomePacote(20)] = "partido.id";
    m_nomesPacotes[ESavdNomePacote(1)] = "vota.of";
    m_nomesPacotes[ESavdNomePacote(2)] = "vota.si";
    m_nomesPacotes[ESavdNomePacote(3)] = "vota.te";
    m_nomesPacotes[ESavdNomePacote(4)] = "vota.tm";
    m_nomesPacotes[ESavdNomePacote(5)] = "sa.of";
    m_nomesPacotes[ESavdNomePacote(6)] = "sa.si";
    m_nomesPacotes[ESavdNomePacote(7)] = "sa.tr";
    m_nomesPacotes[ESavdNomePacote(9)] = "red";
    m_nomesPacotes[ESavdNomePacote(10)] = "vpp";
    m_nomesPacotes[ESavdNomePacote(11)] = "adh";
    m_nomesPacotes[ESavdNomePacote(12)] = "atue";
    m_nomesPacotes[ESavdNomePacote(13)] = "ste";
    m_nomesPacotes[ESavdNomePacote(8)] = "gap";
    m_nomesPacotes[ESavdNomePacote(16)] = "savd";
    m_nomesPacotes[ESavdNomePacote(15)] = "turno2.jez";
    m_nomesPacotes[ESavdNomePacote(22)] = "infomidia.pwd";
}

} // namespace comum
