// Reconstruction: comum::asn::CConversorTipoApuracaoSA (target fns 10283 and 10282), with the four ConverteMotivo*
// members, which binaryen inlines into DoConverte. The throws are records of the target (lines 54 to 165, columns 15 and
// 19); the lines of the code around them are a choice.

#include "app/comum/gravadores/asn/cconversortipoapuracaosa.h"

#include <format>

#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum::asn {

using ModuloTiposResultadosEcoUrna::ApuracaoEletronica;
using ModuloTiposResultadosEcoUrna::ApuracaoMistaBUAE;
using ModuloTiposResultadosEcoUrna::ApuracaoMistaMR;
using ModuloTiposResultadosEcoUrna::ApuracaoTotalmenteManualDigitacaoAE;
using ModuloTiposResultadosEcoUrna::TipoApuracao;


CConversorTipoApuracaoSA::TEntidade CConversorTipoApuracaoSA::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    const md::CTipoApuracaoSA::ETipoApuracao tipo = dado.GetTipoApuracao();
    switch (tipo) {
        case md::CTipoApuracaoSA::TIPO_TOTALMENTE_MANUAL: {
            ApuracaoTotalmenteManualDigitacaoAE apuracao;
            apuracao.set_tipoapuracao(TipoApuracao::totalmenteManual);
            apuracao.set_motivoApuracao(ConverteMotivoApuracaoManual(dado.GetMotivoApuracao()));
            entidade.select_apuracaoTotalmenteManual() = apuracao;
            break;
        }
        case md::CTipoApuracaoSA::TIPO_TOTALMENTE_ELETRONICA: {
            ApuracaoEletronica apuracao;
            apuracao.set_tipoapuracao(TipoApuracao::totalmenteEletronica);
            apuracao.set_motivoApuracao(ConverteMotivoApuracaoEletronica(dado.GetMotivoApuracao()));
            entidade.select_apuracaoEletronica() = apuracao;
            break;
        }
        case md::CTipoApuracaoSA::TIPO_MISTA_BU: {
            ApuracaoMistaBUAE apuracao;
            apuracao.set_tipoapuracao(TipoApuracao::mistaBU);
            apuracao.set_motivoApuracao(ConverteMotivoApuracaoBU(dado.GetMotivoApuracao()));
            entidade.select_apuracaoMistaBUAE() = apuracao;
            break;
        }
        case md::CTipoApuracaoSA::TIPO_MISTA_MR: {
            ApuracaoMistaMR apuracao;
            apuracao.set_tipoApuracao(TipoApuracao::mistaMR);
            apuracao.set_motivoApuracao(ConverteMotivoApuracaoMR(dado.GetMotivoApuracao()));
            entidade.select_apuracaoMistaMR() = apuracao;
            break;
        }
        default:
            throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8621, std::format("Tipo de apuração inválido: {}", tipo));
    }
    return entidade;
}

// (original lines 59-66: content not recovered)
#line 67
md::CTipoApuracaoSA CConversorTipoApuracaoSA::DoDesconverte(const TEntidade& entidade) const
{
    if (entidade.apuracaoMistaMR_isSelected()) {
        return TDado(md::CTipoApuracaoSA::TIPO_MISTA_MR, entidade.get_apuracaoMistaMR().get_motivoApuracao());
    } else if (entidade.apuracaoMistaBUAE_isSelected()) {
        return TDado(md::CTipoApuracaoSA::TIPO_MISTA_BU, entidade.get_apuracaoMistaBUAE().get_motivoApuracao());
    } else if (entidade.apuracaoTotalmenteManual_isSelected()) {
        return TDado(md::CTipoApuracaoSA::TIPO_TOTALMENTE_MANUAL, entidade.get_apuracaoTotalmenteManual().get_motivoApuracao());
    } else if (entidade.apuracaoEletronica_isSelected()) {
        return TDado(md::CTipoApuracaoSA::TIPO_TOTALMENTE_ELETRONICA, entidade.get_apuracaoEletronica().get_motivoApuracao());
    } else {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8622, "Tipo de apuração inválido");
    }
}

// (original lines 82-85: content not recovered)
#line 86
ModuloTiposResultadosEcoUrna::MotivoApuracaoManual CConversorTipoApuracaoSA::ConverteMotivoApuracaoManual(const uebyte motivo) const
{
    switch (motivo) {
        case 1:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoManual::urnaComDefeito;
        case 2:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoManual::urnaIndisponivelInicio;
        case 3:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoManual::urnaOutraSecao;
        case 99:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoManual::outros;
        default:
            throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8623, std::format("Motivo inválido: {}", motivo));
    }
}

// (original lines 102-104: content not recovered)
#line 105
ModuloTiposResultadosEcoUrna::MotivoApuracaoEletronica CConversorTipoApuracaoSA::ConverteMotivoApuracaoEletronica(const uebyte motivo) const
{
    switch (motivo) {
        case 1:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoEletronica::naoFoiPossivelReuperarResultado;
        case 2:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoEletronica::urnaNaoChegouMidiaDefeituosa;
        case 3:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoEletronica::urnaNaoChegouMidiaExtraviada;
        case 99:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoEletronica::outros;
        default:
            throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8624, std::format("Motivo inválido: {}", motivo));
    }
}

// (original lines 121-123: content not recovered)
#line 124
ModuloTiposResultadosEcoUrna::MotivoApuracaoMistaComBU CConversorTipoApuracaoSA::ConverteMotivoApuracaoBU(const uebyte motivo) const
{
    switch (motivo) {
        case 1:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoMistaComBU::urnaDataHoraIncorreta;
        case 2:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoMistaComBU::urnaComDefeito;
        case 3:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoMistaComBU::urnaOutrasecao;
        case 4:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoMistaComBU::urnaPreparadaIncorretamente;
        case 5:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoMistaComBU::urnaEncerradaComEleitoresNaFila;
        case 99:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoMistaComBU::outros;
        default:
            throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8625, std::format("Motivo inválido: {}", motivo));
    }
}

// (original lines 144-146: content not recovered)
#line 147
ModuloTiposResultadosEcoUrna::MotivoApuracaoMistaComMR CConversorTipoApuracaoSA::ConverteMotivoApuracaoMR(const uebyte motivo) const
{
    switch (motivo) {
        case 1:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoMistaComMR::naoObteveExitoContingencia;
        case 2:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoMistaComMR::indisponibilidadeUrnaContingencia;
        case 3:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoMistaComMR::indisponibilidadeFlashContingencia;
        case 4:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoMistaComMR::problemaEnergiaEletrica;
        case 5:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoMistaComMR::naoFoiPossivelTrocarUrna;
        case 6:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoMistaComMR::naoFoiSolicitadaTrocaUrna;
        case 99:
            return ModuloTiposResultadosEcoUrna::MotivoApuracaoMistaComMR::outros;
        default:
            throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8626, std::format("Motivo inválido: {}", motivo));
    }
}

} // namespace comum::asn
