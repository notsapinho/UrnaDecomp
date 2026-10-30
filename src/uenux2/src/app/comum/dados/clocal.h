#pragma once

#include <memory>
#include <string>

#include "app/comum/dados/md/clocal.h"

namespace comum {

// Recovered: one std::unique_ptr, 4 bytes (fn 5738 allocates 4, and 2261 resets it and frees a md::CLocal), the data a
// loader fills; every member below checks it through VerificaLido, which takes the member's name as a literal, so
// those literals name the members with no record. The member name is not in the target.
class CLocal {
public:
    CLocal();
    ~CLocal();

    uedword GetMunicipio() const;
    const std::string& GetNomeMunicipio() const;
    const std::string& GetUF() const;
    std::string GetUFMinuscula() const;
    const md::CLocal& GetLocalData() const;
    TZonaID GetZonaID() const;
    TSecaoID GetSecaoID() const;
    bool UrnaBiometrica() const;

    void VerificaEhSecao(const std::string& funcao) const;

private:
    void VerificaLido(const std::string& funcao) const;
    bool EhSecao(const std::string& funcao) const
    {
        VerificaLido(funcao);
        return m_local->TemSecao();
    }

    std::unique_ptr<md::CLocal> m_local;
};

} // namespace comum
