// comum::CGravadorHashes (/home/rubio/tse/uenux2/src/app/comum/gravadores/cgravadorhashes.cpp, the file its record
// names): the two constructors fn 12098 holds inlined (no index; unrooted), GravaResultado (target fn 11620, slot 7,
// the key function), whose throw is a record of the target (line 112, column 15), and CalculaHashesArquivos, which
// binaryen inlines into it. The other lines are a choice (src/units/136-uenux2-app-comum-gravadores-md.mk says what
// each rests on).
#include "app/comum/gravadores/cgravadorhashes.h"

#include <filesystem>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "api/hash/chasharquivo.h"
#include "api/hash/cmontadorhash.h"
#include "app/comum/carquivosresultado.h"
#include "app/comum/cpath.h"
#include "app/comum/dados/cconfiguracaoeleicao.h"
#include "app/comum/gravadores/asn/cconversorentidadehashes.h"
#include "app/comum/gravadores/cgravadorutil.h"
#include "app/comum/gravadores/euecomumgravadoreserror.h"
#include "app/comum/gravadores/md/centidadehashes.h"
#include "app/comum/md/ccabecalhoentidade.h"
#include "app/comum/md/cidentificacaosecao.h"
#include "app/comum/md/cidentificacaournacontingencia.h"

namespace comum {

CGravadorHashes::CGravadorHashes(const api::CDateTime& dataHora, const md::CIdentificacaoSecao& identificacao,
    char fase, const std::string& siglaUF, const std::string& versao)
    : IGravador(identificacao.GetMunicipio(), identificacao.GetZona(), identificacao.GetLocal(),
          identificacao.GetSecao(), fase, EXTENSAO_HASH_DAT, static_cast<ESavdArquivoUE>(46)),
      m_dataHora(dataHora), m_faseUrna(CGravadorUtil::ConverteFase(fase)), m_siglaUF(siglaUF),
      m_identificacaoSecao(new md::CIdentificacaoSecao(identificacao)), m_versao(versao)
{
}

CGravadorHashes::CGravadorHashes(const api::CDateTime& dataHora,
    const md::CIdentificacaoUrnaContingencia& identificacao, char fase, const std::string& siglaUF,
    const std::string& versao)
    : IGravador(identificacao.GetMunicipio(), identificacao.GetZona(), 0, 0, fase, EXTENSAO_HASH_DAT,
          static_cast<ESavdArquivoUE>(46)),
      m_dataHora(dataHora), m_faseUrna(CGravadorUtil::ConverteFase(fase)), m_siglaUF(siglaUF),
      m_identificacaoContingencia(new md::CIdentificacaoUrnaContingencia(identificacao)), m_versao(versao)
{
}

// (original lines 48-87: content not recovered)
#line 88
std::vector<api::hash::CHashArquivo> CalculaHashesArquivos()
{
    const std::set<std::string> excluidos = CPath::GetDiretoriosSemHash();
    std::vector<api::hash::CHashArquivo> hashes = api::hash::ListaHashesDiretorio(CPath::GetPathRoot() / "", excluidos);
    std::vector<api::hash::CHashArquivo> hashesChave = api::hash::ListaHashesDiretorio(CPath::GetPathChave(), excluidos);
    hashes.insert(hashes.end(), hashesChave.begin(), hashesChave.end());
    return hashes;
}


void CGravadorHashes::GravaResultado(api::CFile& arquivo) const
{
    const md::CCabecalhoEntidade cabecalho(m_dataHora, CConfiguracaoEleicao::GetInst().GetPleito().GetID(),
        md::TIPO_CABECALHO_PLEITO);
    const std::vector<api::hash::CHashArquivo> hashes = CalculaHashesArquivos();

    if (m_identificacaoSecao) {
        const md::CEntidadeHashes entidade(cabecalho, m_faseUrna, m_siglaUF, *m_identificacaoSecao, m_versao, hashes);
        asn::GravaArquivo(arquivo, entidade);
    } else if (m_identificacaoContingencia) {
        const md::CEntidadeHashes entidade(cabecalho, m_faseUrna, m_siglaUF, *m_identificacaoContingencia, m_versao,
            hashes);
        asn::GravaArquivo(arquivo, entidade);
    } else {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8644, "Tipo de urna inválido");
    }
}

} // namespace comum
