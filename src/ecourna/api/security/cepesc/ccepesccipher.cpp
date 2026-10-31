#include "ecourna/api/security/cepesc/ccepesccipher.hpp"

namespace ecourna::api::cepesc {

namespace {

const size_t TAMANHO_CHAVE = 32;

} // namespace

CCipheredOut CCepescCipher::Encrypt(const CPlainText& texto) const
{
    const std::vector<uebyte> chave(TAMANHO_CHAVE);
    if (texto.GetInfoSalt()) {
        return CCipheredOut(chave, texto.GetConteudo(), *texto.GetInfoSalt());
    }
    return CCipheredOut(chave, texto.GetConteudo());
}

std::vector<uebyte> CCepescCipher::Decrypt(const CCipheredIn& entrada) const
{
    return entrada.GetConteudo();
}

} // namespace ecourna::api::cepesc
