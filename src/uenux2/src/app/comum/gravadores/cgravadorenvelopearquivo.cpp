// comum::CGravadorEnvelopeArquivo (this file's name and path are the reconstruction's choice: no record names the
// class's file; app/comum/gravadores/cgravadorenvelopearquivo.h says what is recovered). It holds the constructor
// (target fn 5856) and the key function, LeConteudo (target fn 11623, slot 8, a chosen name); neither has a record, so
// their lines and their order are a choice. The class's vtable and implicit destructors (fns 11622, 11621) are emitted
// here with LeConteudo.

#include "app/comum/gravadores/cgravadorenvelopearquivo.h"

#include "api/util/csystem.h"
#include "ecourna/api/io/cfile.hpp"

namespace comum {

CGravadorEnvelopeArquivo::CGravadorEnvelopeArquivo(const api::CDateTime& dataHora, TMunicipioID municipio, TZonaID zona,
    TLocalID local, TSecaoID secao, char fase, EExtensaoArquivoResultado extensao, ESavdArquivoUE arquivoSavd,
    md::CEnvelopeGenerico::Tipo tipoEnvelope, const md::estadoaplicacao::CDadoCorrespondencia& correspondencia,
    const std::string& nomeArquivoEnvelope)
    : IGravadorEnvelope(dataHora, municipio, zona, local, secao, fase, extensao, arquivoSavd, tipoEnvelope,
          correspondencia),
      m_nomeArquivoEnvelope(nomeArquivoEnvelope)
{
}

std::vector<uebyte> CGravadorEnvelopeArquivo::LeConteudo() const
{
    const uedword tamanho = api::CSystem::GetFileSize(m_nomeArquivoEnvelope);
    std::vector<uebyte> conteudo(tamanho);
    if (tamanho > 0) {
        ecourna::api::io::CFile arquivo(m_nomeArquivoEnvelope, "rb");
        arquivo.RawRead(conteudo.data(), tamanho);
    }
    return conteudo;
}

} // namespace comum
