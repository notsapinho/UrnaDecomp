#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <vector>

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
    bool EhExterior() const;
    const md::CLocal& GetLocalData() const;
    TZonaID GetZonaID() const;
    TSecaoID GetSecaoID() const;
    bool UrnaBiometrica() const;
    TLocalID GetLocalID() const;
    // GetQtdAgregadas (fn 2816) and GetAgregadas (fn 3752) check the data through VerificaLido with those literals and
    // read the section's aggregated sections (CSecaoEleitoral's vector at +24, 8-byte elements): their count as a byte
    // (the target masks it with 255) and their numbers (the 16-bit word at +4 of each). GetTipoLocalVotacao is the
    // section's type behind VerificaEhSecao("GetTipoLocalVotacao"): comum::CRelatorioTesteImpressora::GetDadosLocal (fn
    // 11188) holds it in a stack frame of its own (binaryen's inlining of its one caller), so it has no target index.
    // The three names are chosen from the literals, as the members above are; the vector's element type is chosen.
    uebyte GetQtdAgregadas() const;
    std::vector<ueword> GetAgregadas() const;
    ETipoLocalVotacao GetTipoLocalVotacao() const;

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

// The aggregated sections' numbers, each as 4 digits after "" for the first and " " for the next ones, put into the
// format it is given at its one "{}" (fn 5738; callers comum::CRelUtil's 1543 and GetDadosLocal, 11188). It holds
// CLocal::GetInst and GetQtdAgregadas inlined, which clang does only in their own TU, so it is clocal.cpp's code. Its
// name, its parameter and its being a free function of comum are chosen.
std::string FormataAgregadas(const std::string& formato);

} // namespace comum
