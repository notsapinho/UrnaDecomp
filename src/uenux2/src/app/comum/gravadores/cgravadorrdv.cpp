// comum::CGravadorRDV's constructor, which fn 12098 holds inlined (no index; unrooted: src/units/305-uenux2-cgravadorrdv.mk
// says what it rests on), and GravaResultado (target fn 11587, slot 7; this file's name and path are the
// reconstruction's choice: no record names the class's file, app/comum/gravadores/cgravadorrdv.h says what is
// recovered). Fn 11587 has
// no record of its own: its records are those of the api::CFileASN templates it holds (cfileasn.h:161 and :171,
// CodeObjectFunction for ModuloRegistroDigitalVoto::EntidadeResultadoRDV, behind the frames of CodeObject and
// CodeObjectFunction, which binaryen inlined), and what it does is read from its calls. It decodes the RDV's bytes
// (CRdv's slot 11, copied into a std::vector<char>) as a ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto with
// CFileASN::DecodeObject (fn 5825, this object's instance: its records lie in this object's data, after this class's
// vtable), reads the urna's type from the load, the media's serial from the external flash's "infomidia.dat" when it
// exists (fn 3735, then CStringUtils::BytesToHexString over the serial's bytes, else "00000000"), builds the load (fn
// 2802), the correspondence (fn 2801; the urna's type eUrnaVota for a section, else eUrnaContingencia), the header (fn
// 1945) and the urna (fns 2855 and 2854), converts the header and the urna into a ModuloRegistroDigitalVoto::
// EntidadeResultadoRDV beside the RDV (fns 2275 and 3799, the converters' vptrs stored before the entity is built),
// codes it with CFileASN::CodeObject and writes the coded bytes, copied into a std::vector<uebyte>, with CFile::Write
// (fn 5180; ecourna/api/io/cfile.hpp says what shows the copy's element type). Chosen: the locals' names, the order of
// the statements no call fixes, and the copy as a temporary of the call (the target frees it right after the write,
// before the coded vector).

#include "app/comum/gravadores/cgravadorrdv.h"

#include <filesystem>
#include <string>
#include <vector>

#include "api/io/asn/cfileasn.h"
#include "api/util/csystem.h"
#include "app/comum/appinfo/cappinfo.h"
#include "app/comum/asn/cconversorcabecalhoentidade.h"
#include "app/comum/carquivosresultado.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/carregaarquivo.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/dados/crdv.h"
#include "app/comum/dados/md/correspondencia/ccarga.h"
#include "app/comum/dados/md/correspondencia/ccorrespondenciaresultado.h"
#include "app/comum/gravadores/asn/cconversorurna.h"
#include "app/comum/md/ccabecalhoentidade.h"
#include "asn1/modules/ModuloRegistroDigitalVoto.h"
#include "ecourna/api/util/cstringutils.hpp"
#include "ecourna/app/dados/asn/midias/cconversorinformacaomidia.hpp"

namespace comum {

CGravadorRDV::CGravadorRDV(const api::CDateTime& dataHora, TMunicipioID municipio, TZonaID zona, TLocalID local,
    TSecaoID secao, char fase, const md::estadoaplicacao::CDadoCorrespondencia& correspondencia, const CRdv* rdv)
    : IGravador(municipio, zona, local, secao, fase, EXTENSAO_RDV_DAT, static_cast<ESavdArquivoUE>(37)),
      m_dataHora(dataHora), m_tipoArquivo(TIPO_ARQUIVO_VOTACAO_UE), m_correspondencia(correspondencia), m_rdv(rdv)
{
}

void CGravadorRDV::GravaResultado(api::CFile& arquivo) const
{
    const std::vector<uebyte> dados = m_rdv->Converte();
    const ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto rdv =
        api::CFileASN::DecodeObject<ModuloRegistroDigitalVoto::EntidadeRegistroDigitalVoto>(
            std::vector<char>(dados.begin(), dados.end()));

    const CConfiguracaoEleicao& configuracao = CConfiguracaoEleicao::GetInst();
    const md::estadoaplicacao::CEstadoGeral& geral = CAppInfo::GetInst().GetGeral();
    const EUrnaTipo tipoUrna = geral.GetDadoCarga().GetTipoUrna();

    std::string numeroSerieFV("00000000");
    const std::filesystem::path arquivoInfoMidia = CPath::GetPathEstatico(FLASH_EXTERNA) / "infomidia.dat";
    if (api::CSystem::ExistFile(arquivoInfoMidia)) {
        const ecourna::app::dados::CInformacaoMidia informacaoMidia =
            CarregaArquivoEcourna<ecourna::app::dados::asn::CConversorInformacaoMidia>(arquivoInfoMidia);
        numeroSerieFV = ecourna::api::util::CStringUtils::BytesToHexString(
            informacaoMidia.GetDadosGeracaoMidia().GetSerialMidia().GetSerial());
    }

    const md::CCarga carga(m_correspondencia.GetNumeroInternoUrna(), m_correspondencia.GetNumeroSerieFC(),
        m_correspondencia.GetDataHoraCarga(), m_correspondencia.GetCodigoCarga(),
        m_correspondencia.GetIdentificadorGeradorMidia());
    const md::CCorrespondenciaResultado correspondencia(m_municipio, m_zona, m_secao, carga,
        m_secao != 0 ? eUrnaVota : eUrnaContingencia);
    const md::CCabecalhoEntidade cabecalho(m_dataHora, configuracao.GetPleito().GetID(), md::TIPO_CABECALHO_PLEITO);
    const md::CUrna urna = m_tipoApuracao
        ? md::CUrna(tipoUrna, "10.23.0.1 - DESENVOLVIMENTO", correspondencia, m_tipoArquivo, numeroSerieFV,
              *m_tipoApuracao)
        : md::CUrna(tipoUrna, "10.23.0.1 - DESENVOLVIMENTO", correspondencia, m_tipoArquivo, numeroSerieFV);

    const asn::CConversorCabecalhoEntidade conversorCabecalho;
    const asn::CConversorUrna conversorUrna;
    ModuloRegistroDigitalVoto::EntidadeResultadoRDV entidade;
    entidade.set_cabecalho() = conversorCabecalho.Converte(cabecalho);
    entidade.set_urna() = conversorUrna.Converte(urna);
    entidade.set_rdv() = rdv;

    const std::vector<char> codificado = api::CFileASN::CodeObject(entidade);
    arquivo.Write(std::vector<uebyte>(codificado.begin(), codificado.end()));
}

} // namespace comum
