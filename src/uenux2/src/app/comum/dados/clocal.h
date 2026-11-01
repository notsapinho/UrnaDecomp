#pragma once

#include <memory>
#include <mutex>
#include <string>

#include "app/comum/dados/md/clocal.h"

namespace comum {

// Recovered: one std::unique_ptr, 4 bytes (fn 5738 allocates 4, and 2261 resets it and frees a md::CLocal), the data a
// loader fills. Every member below checks it through VerificaLido with a literal. Reading that literal as the member's
// name is a choice, for the members with no record: it is shorter than the record's name in GetZonaID, and in
// GetUFMinuscula it is GetUF's (the fragment lists them). The data member's name is not in the target.
class CLocal {
public:
    static CLocal& GetInst();

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
    TLocalID GetLocalID() const;

    void VerificaEhSecao(const std::string& funcao) const;

private:
    static std::unique_ptr<CLocal> s_inst;
    static std::mutex s_mutex;

    void VerificaLido(const std::string& funcao) const;
    bool EhSecao(const std::string& funcao) const
    {
        VerificaLido(funcao);
        return m_local->TemSecao();
    }

    std::unique_ptr<md::CLocal> m_local;
};

} // namespace comum
