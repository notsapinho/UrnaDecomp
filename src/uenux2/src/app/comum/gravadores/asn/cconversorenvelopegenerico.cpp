// Reconstruction: comum::asn::CConversorEnvelopeGenerico's DoConverte and DoDesconverte (target fns 10271 and 10270),
// with the two static members binaryen inlines into them. Their throws are records of the target (lines 72, 126, 139,
// 168 and 191); the lines of the code around them are a choice.

#include "app/comum/gravadores/asn/cconversorenvelopegenerico.h"

#include <format>
#include <memory>
#include <optional>
#include <vector>

#include "app/comum/asn/cconversorcabecalhoentidade.h"
#include "app/comum/asn/cconversorseguranca.h"
#include "app/comum/asn/util.h"
#include "app/comum/gravadores/asn/cconversorurna.h"
#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum::asn {

// (original lines 20-32: content not recovered)
#line 33
CConversorEnvelopeGenerico::TEntidade CConversorEnvelopeGenerico::DoConverte(const TDado& dado) const
{
    TEntidade entidade;
    const CConversorCabecalhoEntidade conversorCabecalho;
    const ModuloTiposEleitorais::CabecalhoEntidade cabecalho = conversorCabecalho.Converte(dado.GetCabecalho());
    entidade.set_cabecalho() = cabecalho;
    entidade.set_fase() = Utils::ConverteFase(dado.GetFase());
    if (dado.TemUrna()) {
        const CConversorUrna conversorUrna;
        entidade.set_urna() = conversorUrna.Converte(dado.GetUrna());
    } else {
        entidade.omit_urna();
    }
    if (dado.GetSecao() == 0) {
        ModuloTiposEleitorais::IdentificacaoContingencia contingencia;
        contingencia.set_municipioZona().set_municipio(dado.GetMunicipio());
        contingencia.set_municipioZona().set_zona(dado.GetZona());
        entidade.set_identificacao().select_identificacaoContingencia() = contingencia;
    } else {
        switch (dado.GetTipoUrna()) {
            case eUrnaVota:
            case eUrnaContingenciaVota:
            case eUrnaContingenciaVotaRecupera: {
                ModuloTiposEleitorais::IdentificacaoSecaoEleitoral secao;
                secao.set_municipioZona().set_municipio(dado.GetMunicipio());
                secao.set_municipioZona().set_zona(dado.GetZona());
                secao.set_local(dado.GetLocal());
                secao.set_secao(dado.GetSecao());
                entidade.set_identificacao().select_identificacaoSecaoEleitoral() = secao;
                break;
            }
            case eUrnaContingencia: {
                ModuloTiposEleitorais::IdentificacaoContingencia contingencia;
                contingencia.set_municipioZona().set_municipio(dado.GetMunicipio());
                contingencia.set_municipioZona().set_zona(dado.GetZona());
                entidade.set_identificacao().select_identificacaoContingencia() = contingencia;
                break;
            }
            case eUrnaSemTipo:
                throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8611, std::format("Tipo inválido de urna: {}", static_cast<int>(dado.GetTipoUrna())));
        }
    }
    entidade.set_tipoEnvelope(ConverteTipoEnvelope(dado.GetTipo()));
    if (dado.TemSeguranca()) {
        const CConversorSeguranca conversorSeguranca;
        entidade.set_seguranca() = conversorSeguranca.Converte(dado.GetSeguranca());
    } else {
        entidade.omit_seguranca();
    }
    entidade.set_conteudo() = std::vector<char>(dado.GetConteudo().begin(), dado.GetConteudo().end());
    return entidade;
}

// (original lines 86-93: content not recovered)
#line 94
md::CEnvelopeGenerico CConversorEnvelopeGenerico::DoDesconverte(const TEntidade& entidade) const
{
    const CConversorCabecalhoEntidade conversorCabecalho;
    const CConversorUrna conversorUrna;
    const CConversorSeguranca conversorSeguranca;
    const md::CCabecalhoEntidade cabecalho = conversorCabecalho.Desconverte(entidade.get_cabecalho());
    const EUrnaFase fase = Utils::DesconverteFase(entidade.get_fase());
    std::unique_ptr<md::CUrna> urna;
    if (entidade.urna_isPresent()) {
        urna.reset(new md::CUrna(conversorUrna.Desconverte(entidade.get_urna())));
    }
    const ModuloTiposResultadosEcoUrna::Identificacao& identificacao = entidade.get_identificacao();
    TMunicipioID municipio;
    TZonaID zona;
    std::optional<TLocalID> local;
    EUrnaTipo tipoUrna;
    TSecaoID secao = 0;
    if (identificacao.identificacaoSecaoEleitoral_isSelected()) {
        const ModuloTiposEleitorais::IdentificacaoSecaoEleitoral& secaoEleitoral =
            identificacao.get_identificacaoSecaoEleitoral();
        municipio = secaoEleitoral.get_municipioZona().get_municipio().getValue();
        zona = secaoEleitoral.get_municipioZona().get_zona().getValue();
        local = secaoEleitoral.get_local().getValue();
        secao = secaoEleitoral.get_secao().getValue();
        tipoUrna = eUrnaVota;
    } else if (identificacao.identificacaoContingencia_isSelected()) {
        const ModuloTiposEleitorais::IdentificacaoContingencia& contingencia =
            identificacao.get_identificacaoContingencia();
        municipio = contingencia.get_municipioZona().get_municipio().getValue();
        zona = contingencia.get_municipioZona().get_zona().getValue();
        tipoUrna = eUrnaContingencia;
    } else {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8612, "Entidade inválida. Tipo de identificação incorreto");
    }
    const md::CEnvelopeGenerico::Tipo tipo = DesconverteTipoEnvelope(entidade.get_tipoEnvelope());
    std::unique_ptr<md::CSeguranca> seguranca;
    if (entidade.seguranca_isPresent()) {
        seguranca.reset(
            new md::CSeguranca(conversorSeguranca.Desconverte(entidade.get_seguranca())));
    }

    const std::vector<uebyte> conteudo(entidade.get_conteudo().begin(),
        entidade.get_conteudo().end());

    if (urna && seguranca) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8613, "Entidade inválida com informação de urna e criptografia");
    }
    if (urna) {
        return TDado(cabecalho, fase, *urna, municipio, zona, local, secao, tipo, conteudo);
    }
    if (seguranca) {
        return TDado(cabecalho, fase, municipio, zona, local, secao, tipo, *seguranca, conteudo, tipoUrna);
    }
    return TDado(cabecalho, fase, municipio, zona, local, secao, tipo, conteudo, tipoUrna);
}

// (original lines 150-153: content not recovered)
#line 154
ModuloEnvelopeGenerico::TipoEnvelope::NamedNumber CConversorEnvelopeGenerico::ConverteTipoEnvelope(TDado::Tipo tipo)
{
    switch (tipo) {
        case TDado::ENVELOPE_BOLETIM_URNA:
            return ModuloEnvelopeGenerico::TipoEnvelope::envelopeBoletimUrna;
        case TDado::ENVELOPE_REGISTRO_DIGITAL_VOTO:
            return ModuloEnvelopeGenerico::TipoEnvelope::envelopeRegistroDigitalVoto;
        case TDado::ENVELOPE_BOLETIM_URNA_IMPRESSO:
            return ModuloEnvelopeGenerico::TipoEnvelope::envelopeBoletimUrnaImpresso;
        case TDado::ENVELOPE_IMAGEM_BIOMETRIA:
            return ModuloEnvelopeGenerico::TipoEnvelope::envelopeImagemBiometria;
        case TDado::ENVELOPE_ZERESIMA_IMPRESSA:
            return ModuloEnvelopeGenerico::TipoEnvelope::envelopeZeresimaImpressa;
    }
    throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8614, std::format("Tipo de envelope inválido: {}", tipo));
}

// (original lines 171-174: content not recovered)
#line 175
md::CEnvelopeGenerico::Tipo CConversorEnvelopeGenerico::DesconverteTipoEnvelope(ModuloEnvelopeGenerico::TipoEnvelope::NamedNumber tipo)
{
    switch (tipo) {
        case ModuloEnvelopeGenerico::TipoEnvelope::envelopeBoletimUrna:
            return md::CEnvelopeGenerico::ENVELOPE_BOLETIM_URNA;
        case ModuloEnvelopeGenerico::TipoEnvelope::envelopeRegistroDigitalVoto:
            return md::CEnvelopeGenerico::ENVELOPE_REGISTRO_DIGITAL_VOTO;
        case ModuloEnvelopeGenerico::TipoEnvelope::envelopeBoletimUrnaImpresso:
            return md::CEnvelopeGenerico::ENVELOPE_BOLETIM_URNA_IMPRESSO;
        case ModuloEnvelopeGenerico::TipoEnvelope::envelopeImagemBiometria:
            return md::CEnvelopeGenerico::ENVELOPE_IMAGEM_BIOMETRIA;
        case ModuloEnvelopeGenerico::TipoEnvelope::envelopeZeresimaImpressa:
            return md::CEnvelopeGenerico::ENVELOPE_ZERESIMA_IMPRESSA;
        default:
            break;
    }
    throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8615, std::format("Tipo de envelope inválido: {}", tipo));
}

} // namespace comum::asn
