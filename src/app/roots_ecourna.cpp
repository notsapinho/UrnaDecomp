// Root callers for the reconstructed ecourna units (src/ecourna, docs/reference/app-flags.md): the same call-site counts as
// the target so binaryen inlines and merges them the same way. Compiled as uenux2 code (UENUX2_CXXFLAGS).
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "ecourna/api/security/base64.hpp"
#include "ecourna/api/util/cstringutils.hpp"
#include "ecourna/app/dados/cfabricaidentificadoreleitor.hpp"
#include "ecourna/app/dados/cnumerocpf.hpp"
#include "ecourna/app/dados/cnumeroidentificacaolivre.hpp"
#include "ecourna/app/dados/cnumeroinscricaoeleitoral.hpp"

namespace {

using ecourna::api::util::CStringUtils;

struct SComResumo {
    char preenchimento[168];
    std::vector<uebyte> dados;
};

__attribute__((noinline)) std::string ResumoBase64(const SComResumo& obj)
{
    return ecourna::api::security::EncodeBase64(obj.dados).substr(0, 8);
}

std::shared_ptr<ecourna::app::dados::IIdentificadorEleitor> CriaIdentificador(int tipo, const std::string& numero)
{
    switch (tipo) {
    case 1:
        return std::make_shared<ecourna::app::dados::CNumeroInscricaoEleitoral>(numero);
    case 2:
        return std::make_shared<ecourna::app::dados::CNumeroCPF>(numero);
    default:
        return std::make_shared<ecourna::app::dados::CNumeroIdentificacaoLivre>(numero);
    }
}

__attribute__((noinline)) unsigned long long UsaConversoes1(const std::string& s)
{
    return CStringUtils::ToByte(s) + CStringUtils::ToInt16(s) + CStringUtils::ToWord(s) + CStringUtils::ToInt32(s) +
           CStringUtils::ToQWord(s) + CStringUtils::ToDWord(s) + CStringUtils::HexToInt(s) +
           CStringUtils::HexStringToBytes(s).size();
}

__attribute__((noinline)) unsigned long long UsaConversoes2(const std::string& s)
{
    return CStringUtils::ToByte(s) * 3 + CStringUtils::ToInt16(s) * 5 + CStringUtils::ToWord(s) * 7 +
           CStringUtils::ToInt32(s) * 11 + CStringUtils::ToQWord(s) * 13 + CStringUtils::ToDWord(s) * 17 +
           CStringUtils::HexToInt(s) * 19 + CStringUtils::HexStringToBytes(s).size() * 23;
}

__attribute__((noinline)) unsigned long long UsaConversoes3(const std::string& s)
{
    return CStringUtils::ToQWord(s) ^ CStringUtils::HexToQWord(s) ^ CStringUtils::ToDWord(s);
}

__attribute__((noinline)) std::string UsaPreenche1(const std::string& s) { return CStringUtils::PreencheAEsquerda(s, '0', 11); }
__attribute__((noinline)) std::string UsaPreenche2(const std::string& s) { return CStringUtils::PreencheAEsquerda(s, ' ', 20) + "x"; }
__attribute__((noinline)) std::string UsaPreenche3(const std::string& s) { return "y" + CStringUtils::PreencheAEsquerda(s, '*', 5); }

// CStringUtils::PreencheADireita's copying form (target fn 1881) has five callers in the target: fn 1542 pads two strings
// to 28, fns 2248 and 11188 pad to 34, fns 11253 and 11478 to 26, all with ' '. 11478 is in the link; these stand for the
// other four.
__attribute__((noinline)) std::string UsaPreencheCopiaA(const std::string& s) { return CStringUtils::PreencheADireita(s, ' ', 28) + "|"; }
__attribute__((noinline)) std::string UsaPreencheCopiaB(const std::string& s) { return "|" + CStringUtils::PreencheADireita(s, ' ', 34); }

// The CStringUtils members src/units/00-ecourna-app-dados-identificadoreleitor.mk adds last. The target callers not in
// our link that these stand for: ToUpper in place (fn 3509), 5604 (654 is in the link); its copying form (5156), 6592, and table slot 29,
// which the executable TU's code takes; Split (1880), 2380, 3689, 5869, 11377 and 12065 (654 is in the link); FindRegex
// (2199), 5465 (654 and 1539 are in the link); the copying Replace (2677), 3651, 3689 and api::CProgressBar::Draw
// (10977). Split is called through its label, so that this object, ahead of src/app/roots_vector.o on the link line,
// instantiates none of std::vector<std::string>'s destruction.
extern "C" void urna_divide(void* partes, const std::string& valor, char separador) __asm__(
    "_ZN7ecourna3api4util12CStringUtils5SplitERKNSt3__212basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEEc");
__attribute__((noinline)) std::string UsaMaiusculasA(std::string s) { CStringUtils::ToUpper(s); return s + "a"; }
__attribute__((noinline)) std::string UsaMaiusculasB(const std::string& s) { return "b" + CStringUtils::ToUpper(s); }
__attribute__((noinline)) int UsaDivideA(const std::string& s)
{
    int partes[3];
    urna_divide(partes, s, '|');
    return partes[1] - partes[0];
}
__attribute__((noinline)) int UsaDivideB(const std::string& s)
{
    int partes[3];
    urna_divide(partes, s + "|", ';');
    return partes[2];
}
__attribute__((noinline)) int UsaBusca(const std::string& s)
{
    const auto [inicio, fim] = CStringUtils::FindRegex("^[0-9]+", s + "0");
    return static_cast<int>(fim - inicio);
}
__attribute__((noinline)) std::string UsaSubstituiA(const std::string& s) { return CStringUtils::Replace(s, "a", "b") + "c"; }
__attribute__((noinline)) std::string UsaSubstituiB(const std::string& s) { return "d" + CStringUtils::Replace(s, s, "e"); }
__attribute__((noinline)) std::string UsaBase64A(const SComResumo& v) { return ResumoBase64(v) + "A"; }
__attribute__((noinline)) std::string UsaBase64B(const SComResumo& v) { return "B" + ResumoBase64(v); }
__attribute__((noinline)) std::string UsaBase64C(const SComResumo& v) { return ResumoBase64(v); }

__attribute__((noinline)) std::string UsaIdentificador(int tipo, const std::string& numero)
{
    auto id = CriaIdentificador(tipo, numero);
    auto outro = ecourna::app::dados::CFabricaIdentificadorEleitor::Cria(tipo, numero + "1");
    return id->Formatado() + id->GetNumero() + outro->Formatado();
}

} // namespace

int urna_roots_ecourna(int a)
{
    std::string s(static_cast<size_t>(a), '1');
    SComResumo v{};
    v.dados.assign(s.begin(), s.end());
    unsigned long long acc = UsaConversoes1(s) + UsaConversoes2(s) + UsaConversoes3(s);
    std::string out = UsaBase64A(v) + UsaBase64B(v) + UsaBase64C(v);
    out += UsaPreenche1(s) + UsaPreenche2(s) + UsaPreenche3(s);
    out += UsaPreencheCopiaA(s) + UsaPreencheCopiaB(out);
    out += UsaIdentificador(a, s) + UsaIdentificador(a + 1, s) + UsaIdentificador(a + 2, s);
    out += UsaMaiusculasA(s) + UsaMaiusculasB(out) + UsaSubstituiA(s) + UsaSubstituiB(out);
    acc += UsaDivideA(s) + UsaDivideB(out) + UsaBusca(out);
    std::string (*maiusculas)(const std::string&) = &CStringUtils::ToUpper;
    acc += reinterpret_cast<uintptr_t>(maiusculas);
    return static_cast<int>(acc) + static_cast<int>(out.size());
}
