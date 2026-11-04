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

    // Target fn 5740: reads the location file anew into the data, the md::CLocal allocated before the read and built in
    // place by the converter (`new` over CarregaArquivo<asn::CConversorLocal>, carregaarquivo.cpp, whose 64-byte frame
    // 5740 holds), then stored, the old one deleted (a std::unique_ptr reset). The file's path comes first
    // (GetPathArquivoLocal, below). It writes the private data, so it is a member; its name is chosen (VerificaLido's
    // text says "o arquivo de locais ainda não foi carregado"): no record, slot or RTTI names it. Its callers, fns
    // 4161 (vota::AdicionaLocal, ctelasvota.cpp) and 7787, call it on CLocal::GetInst's result. Use band 2 puts it
    // between GetTodasSecoes (5741) and TemSecao (5739), its place in clocal.cpp.
    void Carrega();

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
    // Target fn 5741: behind EhSecao("GetTodasSecoes"), the section itself (its number, +16 of the identification, and
    // its type, through CIdentificacaoAgregada's constructor, fn 5672) and then its aggregated sections, a range insert.
    // The body reads the section's two scalars, copies its vector, and copies that copy again for the insert, freeing
    // the second copy and then the first: a local md::CSecaoEleitoral and a local vector, a form chosen for those two
    // copies. The name is the literal's, as for the members above. Its callers, fns 12105 and 7787, are not written
    // (unit 309's roots stand in for both).
    md::TVectorIdentificacaoAgregada GetTodasSecoes() const;
    ETipoLocalVotacao GetTipoLocalVotacao() const;
    // Whether the data hold a section, the byte at +120 of md::CLocal (its section optional's flag), read with no
    // VerificaLido first (target fn 5739, 10 bytes: `i32.load8_u[i32.load[p0]+120]`). Its callers, fn 2725
    // (comum::CControlaArmazenamentoDeImagens' function, which builds the envelope's optional local id from GetLocalID
    // when it is set) and fn 4161 (whose text holds the section's number only when it is set), call it on
    // CLocal::GetInst's result. Out of line in clocal.cpp, between VerificaEhSecao and FormataAgregadas, by its place in
    // use band 2 of ledger/ordinals.tsv (5742 before it, 5738 after). The name, from md::CLocal's member it returns,
    // is chosen: no record, slot or RTTI names it.
    bool TemSecao() const;
    // Whether the data hold a contingency urn: md::CLocal's flag at +136, read with no VerificaLido. Fn 4161
    // (vota::AdicionaLocal, ctelasvota.cpp) reads that byte through the data's pointer when TemSecao is false, so the
    // read is a member's (the data are private), and 4161 has no call there. Out of line here beside TemSecao, binaryen
    // inlines it into its one caller; that is a choice (an inline accessor in this header would give 4161 the same load,
    // not measured). Its name, after md::CLocal::TemContingencia, is chosen; it has no target index.
    bool TemContingencia() const;

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

// The location file's name and path, which fn 5740 holds behind stack frames of their own (208 and 64 bytes, binaryen's
// inlining of a function with one caller): the name is CNomeArquivo::NomeArquivoLocal's "<municipio><zona><secao>-lo.dat"
// (cnomearquivo.cpp, behind a third frame, 112 bytes) of the general state's section (CAppInfo::GetGeralInterno), and
// the path is the internal flash's static directory (CPath::GetPathEstatico, fn 762) joined with that name. They read
// no class's state, so they are free functions of comum; their names and their file (clocal.cpp, that of their one
// caller) are chosen, and their place after Carrega is measured (src/units/89-uenux2-clocal.mk).
std::string GetNomeArquivoLocal();
std::string GetPathArquivoLocal();

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
