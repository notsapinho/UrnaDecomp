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
// The member names, the shared_ptr (its second word, +4, is read by none of those bodies; comum::CRdv's header takes the
// cipher so) and the path of this header are chosen. Only Save is written; Load, MemWrite and MemRead are not.
class CEncryptedFile {
public:
    void Save(const std::string& nome) const;

private:
    ecourna::api::security::TSharedSymmetricCipher m_cifrador;
    std::vector<uebyte> m_dados;
    uedword m_posicao;
};

} // namespace api
