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
    // Whether the data hold a section, the byte at +120 of md::CLocal (its section optional's flag), read with no
    // VerificaLido first (target fn 5739, 10 bytes: `i32.load8_u[i32.load[p0]+120]`). Its callers, fn 2725
    // (comum::CControlaArmazenamentoDeImagens' function, which builds the envelope's optional local id from GetLocalID
    // when it is set) and fn 4161 (whose text holds the section's number only when it is set), call it on
    // CLocal::GetInst's result. Out of line in clocal.cpp, between VerificaEhSecao and FormataAgregadas, by its place in
    // use band 2 of ledger/ordinals.tsv (5742 before it, 5738 after). The name, from md::CLocal's member it returns,
    // is chosen: no record, slot or RTTI names it.
    bool TemSecao() const;

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

// The count of the aggregated sections put into the format it is given at its one "{:04}" (std::vformat with one
// unsigned argument): comum::CRelUtil::IncluiCabecalhoEleicoesMZS (fn 1543) holds it behind a 384-byte stack frame of
// its own (binaryen's inlining of a function with one caller), with CLocal::GetInst and GetQtdAgregadas inlined, which
// clang does only in their own TU, so it is clocal.cpp's code, as FormataAgregadas is. It has no target index. Its name,
// its parameter and its being a free function of comum are chosen.
std::string FormataQtdAgregadas(const std::string& formato);

} // namespace comum
