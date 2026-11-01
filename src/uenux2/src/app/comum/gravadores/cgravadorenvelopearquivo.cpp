// comum::CGravadorEnvelopeArquivo (this file's name and path are the reconstruction's choice: no record names the
// class's file; app/comum/gravadores/cgravadorenvelopearquivo.h says what is recovered). It holds the key function,
// LeConteudo (target fn 11623, slot 8, a chosen name), which has no record: its line is a choice. The class's vtable
// and implicit destructors (fns 11622, 11621) are emitted here with it.

#include "app/comum/gravadores/cgravadorenvelopearquivo.h"

#include "api/util/csystem.h"
#include "ecourna/api/io/cfile.hpp"

namespace comum {

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

// <stubs>
// f5856 · 176 B · unmatched · placement: link order · name unknown
// ? f5856(i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32) { ... }
// </stubs>
