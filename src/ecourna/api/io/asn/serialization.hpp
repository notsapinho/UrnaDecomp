#pragma once
#include <string>
#include <vector>

#include "asn1/asn1.h"
#include "ecourna/api/io/cfile.hpp"
#include "ecourna/api/io/cioerror.hpp"

namespace ecourna::api::io {

// (original lines 11-36: content not recovered)
#line 37
// BER-decodes buffer into entidade and insists on a valid result.
template <typename ClasseASN1>
void DeserializeFromBuffer(ClasseASN1& entidade, const std::vector<char>& buffer)
{
    ASN1::CoderEnv env;
    env.set_encodingRule(ASN1::CoderEnv::ber);
    if (!env.decode(buffer.begin(), buffer.end(), entidade, false)) {
        throw CIoError(EIO_DECODE_BER, EFileOperation::None, "Falha ao fazer decode BER.");
    }
    if (!entidade.isValid() || !entidade.isStrictlyValid()) {
        throw CIoError(EIO_CONTEUDO_INVALIDO, EFileOperation::None, "Foi lido conteúdo inválido.");
    }
}

// Reads the whole file through CFile into the buffer the caller gets back. The reconstruction's: DeserializeFromFile's
// one instance in the target (fn 2280) destroys the CFile before the decode and builds the buffer in the stack slot
// of the mode string, which died before it; that the read is a function of its own that clang inlines is a reading.
// Its name and linkage are chosen (internal, though DeserializeFromFile is a template: an ODR hazard once two TUs
// instantiate it); `static inline` or a namespace { } give the same object, `inline` not (unit 293's fragment).
static std::vector<char> ReadWholeFile(const std::string& nome)
{
    CFile arquivo(nome, "rb");
    arquivo.Seek(0, SEEK_END);
    long tamanho = arquivo.Position();
    std::vector<char> buffer(tamanho);
    arquivo.Seek(0, SEEK_SET);
    uedword lidos = arquivo.RawRead(buffer.data(), buffer.size());
    arquivo.Close();
    buffer.resize(lidos);
    return buffer;
}

// Reads the whole file and decodes it.
template <typename ClasseASN1>
void DeserializeFromFile(ClasseASN1& entidade, const std::string& nome)
{
    DeserializeFromBuffer(entidade, ReadWholeFile(nome));
}

} // namespace ecourna::api::io
