#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace ecourna::api::security {
class ISymmetricCipher;
using TSharedSymmetricCipher = std::shared_ptr<ISymmetricCipher>;
} // namespace ecourna::api::security

namespace api {

// Reconstruction: a file whose content is held in memory and written encrypted. The layout is what the members' bodies
// read (target fns 2767, 2766, 3652, 3653): the cipher at +0, whose slots 2 and 3 Save and Load call (Encrypt and
// Decrypt of ecourna::api::security::ISymmetricCipher), the plain content at +8 and the read/write position at +20.
// The constructor (fn 1692) copies a shared_ptr into +0 and +4, adding to its count, and zeroes +8 to +20; the destructor
// (fn 1691) frees the content and releases that shared_ptr. The member names, the data members' types past their
// widths and the path of this header are chosen; so are the names Write and Read (fns 2766, 3652: no record, slot or
// RTTI names them; each holds MemWrite's or MemRead's records), and their parameter types past what the bodies read.
// Their uedword results are a reading of MemWrite's and MemRead's record types (int gives the same bytes). The
// constructor's parameter, its type and its name are chosen. The constructor and Load (fn 3653, declared from its
// records) are not written: fragment 128 says why.
class CEncryptedFile {
public:
    CEncryptedFile(const ecourna::api::security::TSharedSymmetricCipher& cifrador);
    ~CEncryptedFile();

    void Load(const std::string& nome);
    void Save(const std::string& nome) const;

    uedword Write(const std::vector<uebyte>& dados);
    uedword Read(std::vector<uebyte>& dados);

    uedword MemWrite(const void* buffer, uedword tamanho);
    uedword MemRead(void* buffer, uedword tamanho);

private:
    ecourna::api::security::TSharedSymmetricCipher m_cifrador;
    std::vector<uebyte> m_dados;
    uedword m_posicao;
};

} // namespace api
