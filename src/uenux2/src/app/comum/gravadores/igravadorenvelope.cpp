// comum::IGravadorEnvelope's constructor, GravaResultado (target fn 11626) and the envelope's builder, MontaEnvelope
// (this file's name and path are the reconstruction's choice: no record names the class's file;
// app/comum/gravadores/igravadorenvelope.h says what is recovered). The constructor has no target index of its own:
// binaryen inlines it into its one caller, CGravadorEnvelopeArquivo's constructor (target fn 5856). MontaEnvelope has
// none either: binaryen inlines it into its one caller, GravaResultado, where fn 11626 holds it behind a 400-byte
// frame of its own. Fn 11626 has no record: what it does is read from its calls. MontaEnvelope reads the urna's type
// from the load (CAppInfo's state, CDadoCarga::GetTipoUrna inlined), the media's serial from the external flash's
// "infomidia.dat" when it exists (fn 3735, comum::CarregaArquivoEcourna, then CStringUtils::BytesToHexString over the
// serial's bytes, else "00000000"), the content from slot 8, and builds the header (fn 1945), the load (fn 2802) and the
// correspondence (fn 2801) from the correspondence the constructor copied, the urna (fns 2855 and 2854, with and
// without the apuracao type) and the envelope (fn 5860). GravaResultado writes it with comum::asn::GravaArquivo (fn
// 2724). Chosen: the locals' names, the order of the statements no call fixes, and the locality as a named copy (the
// target reads it as one i64 before the header's constructor; reading its three fields in place was not tried).

#include "app/comum/gravadores/igravadorenvelope.h"

#include <filesystem>
#include <string>
#include <vector>

#include "api/util/csystem.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/carregaarquivo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/md/correspondencia/ccarga.h"
#include "app/comum/dados/md/correspondencia/ccorrespondenciaresultado.h"
#include "app/comum/gravadores/asn/cconversorenvelopegenerico.h"
#include "app/comum/gravadores/cgravadorutil.h"
#include "app/comum/md/ccabecalhoentidade.h"
#include "ecourna/api/util/cstringutils.hpp"
#include "ecourna/app/dados/asn/midias/cconversorinformacaomidia.hpp"

namespace comum {

IGravadorEnvelope::IGravadorEnvelope(const api::CDateTime& dataHora, TMunicipioID municipio, TZonaID zona,
    TLocalID local, TSecaoID secao, char fase, EExtensaoArquivoResultado extensao, ESavdArquivoUE arquivoSavd,
    md::CEnvelopeGenerico::Tipo tipoEnvelope, const md::estadoaplicacao::CDadoCorrespondencia& correspondencia)
    : IGravador(municipio, zona, local, secao, fase, extensao, arquivoSavd),
      m_dataHora(dataHora),
      m_faseUrna(CGravadorUtil::ConverteFase(fase)),
      m_tipoArquivo(TIPO_ARQUIVO_VOTACAO_UE),
      m_tipoEnvelope(tipoEnvelope),
      m_correspondencia(correspondencia)
{
}

void IGravadorEnvelope::GravaResultado(api::CFile& arquivo) const
{
    const md::CEnvelopeGenerico envelope = MontaEnvelope();
    asn::GravaArquivo(arquivo, envelope);
}

md::CEnvelopeGenerico IGravadorEnvelope::MontaEnvelope() const
{
    const md::estadoaplicacao::CEstadoGeral& geral = CAppInfo::GetInst().GetGeral();
    const std::filesystem::path arquivoInfoMidia = CPath::GetPathEstatico(FLASH_EXTERNA) / "infomidia.dat";
    const EUrnaTipo tipoUrna = geral.GetDadoCarga().GetTipoUrna();

    std::string numeroSerieFV("00000000");
    if (api::CSystem::ExistFile(arquivoInfoMidia)) {
        const ecourna::app::dados::CInformacaoMidia informacaoMidia =
            CarregaArquivoEcourna<ecourna::app::dados::asn::CConversorInformacaoMidia>(arquivoInfoMidia);
        numeroSerieFV = ecourna::api::util::CStringUtils::BytesToHexString(
            informacaoMidia.GetDadosGeracaoMidia().GetSerialMidia().GetSerial());
    }

    const std::vector<uebyte> conteudo = LeConteudo();
    const md::estadoaplicacao::CLocalidadeEleitoral secaoCarga = m_correspondencia.GetSecaoCarga();
    const md::CCabecalhoEntidade cabecalho(m_dataHora, CConfiguracaoEleicao::GetInst().GetPleito().GetID(),
        md::TIPO_CABECALHO_PLEITO);
    const md::CCarga carga(m_correspondencia.GetNumeroInternoUrna(), m_correspondencia.GetNumeroSerieFC(),
        m_correspondencia.GetDataHoraCarga(), m_correspondencia.GetCodigoCarga(),
        m_correspondencia.GetIdentificadorGeradorMidia());
    const md::CCorrespondenciaResultado correspondencia(secaoCarga.GetMunicipio(), secaoCarga.GetZona(),
        secaoCarga.GetSecao(), carga, tipoUrna);
    const md::CUrna urna = m_tipoApuracao
        ? md::CUrna(tipoUrna, "10.23.0.1 - DESENVOLVIMENTO", correspondencia, m_tipoArquivo, numeroSerieFV,
              *m_tipoApuracao)
        : md::CUrna(tipoUrna, "10.23.0.1 - DESENVOLVIMENTO", correspondencia, m_tipoArquivo, numeroSerieFV);

    return md::CEnvelopeGenerico(cabecalho, m_faseUrna, urna, m_municipio, m_zona, m_local, m_secao, m_tipoEnvelope,
        conteudo);
}

} // namespace comum
