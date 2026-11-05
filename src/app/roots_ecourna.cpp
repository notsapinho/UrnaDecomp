// Root callers for the reconstructed ecourna units (src/ecourna, docs/reference/app-flags.md): the same call-site counts as
// the target so binaryen inlines and merges them the same way. Compiled as uenux2 code (UENUX2_CXXFLAGS).
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "ecourna/api/util/cstringutils.hpp"
#include "ecourna/app/dados/cfabricaidentificadoreleitor.hpp"
#include "ecourna/app/dados/cnumerocpf.hpp"
#include "ecourna/app/dados/cnumeroidentificacaolivre.hpp"
#include "ecourna/app/dados/cnumeroinscricaoeleitoral.hpp"

namespace {

using ecourna::api::util::CStringUtils;

// ecourna::api::security::EncodeBase64's one caller in the target is comum::md::estadoaplicacao::CEstadoGeral::
// GetResumoHashVersoesPacotes (fn 3703, in unit 215's cestadogeral.cpp, its name chosen), which holds it inlined.
// 3703's target callers not in our link: 3059 and 7787 (11222, unit 287's, is in the link). UsaBase64A and UsaBase64B
// stand for them, through its label, on an object whose +168 is the hash vector, as CEstadoGeral's is, so that this TU
// needs no uenux2 header.
struct SComResumo {
    char preenchimento[168];
    std::vector<uebyte> dados;
};

extern "C" void urna_resumo_hash(void* resultado, const SComResumo& geral) __asm__(
    "_ZNK5comum2md15estadoaplicacao12CEstadoGeral27GetResumoHashVersoesPacotesEv");

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

// CStringUtils::HexToQWord has no call here: its one target caller, fn 3700 (comum::CCalculaCV::CalculaCodigo, unit
// 121), holds it inlined by binaryen and is in the link.
__attribute__((noinline)) unsigned long long UsaConversoes3(const std::string& s)
{
    return CStringUtils::ToQWord(s) ^ CStringUtils::ToDWord(s);
}

__attribute__((noinline)) std::string UsaPreenche1(const std::string& s) { return CStringUtils::PreencheAEsquerda(s, '0', 11); }
__attribute__((noinline)) std::string UsaPreenche2(const std::string& s) { return CStringUtils::PreencheAEsquerda(s, ' ', 20) + "x"; }
__attribute__((noinline)) std::string UsaPreenche3(const std::string& s) { return "y" + CStringUtils::PreencheAEsquerda(s, '*', 5); }

// CStringUtils::PreencheADireita's copying form (target fn 1881) has five callers in the target: fn 1542 pads two strings
// to 28, fns 2248 and 11188 pad to 34, fns 11253 and 11478 to 26, all with ' '. 1542, 11188, 11253 and 11478 are in
// the link; this stands for 2248.
__attribute__((noinline)) std::string UsaPreencheCopiaB(const std::string& s) { return "|" + CStringUtils::PreencheADireita(s, ' ', 34); }

// The CStringUtils members src/units/00-ecourna-app-dados-identificadoreleitor.mk adds last. The target callers not in
// our link that these stand for: ToUpper's copying form (5156), 6592, and table slot 29,
// which the executable TU's code takes; the copying Replace (2677), 3651 (3689 and api::CProgressBar::Draw, 10977, are
// in the link: Draw's stand-in went with it). Split's (1880) went: its callers 654, 2380, 3689, 5869, 11377 and 12065
// are in the link.
__attribute__((noinline)) std::string UsaMaiusculasB(const std::string& s) { return "b" + CStringUtils::ToUpper(s); }
__attribute__((noinline)) std::string UsaSubstituiA(const std::string& s) { return CStringUtils::Replace(s, "a", "b") + "c"; }
__attribute__((noinline)) int UsaBase64A(const SComResumo& v)
{
    int resumo[3];
    urna_resumo_hash(resumo, v);
    return resumo[0] + resumo[1];
}
__attribute__((noinline)) int UsaBase64B(const SComResumo& v)
{
    int resumo[3];
    urna_resumo_hash(resumo, v);
    return resumo[2];
}

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
    unsigned long long acc = UsaConversoes1(s) + UsaConversoes2(s) + UsaConversoes3(s) + UsaBase64A(v) + UsaBase64B(v);
    std::string out = UsaPreenche1(s) + UsaPreenche2(s) + UsaPreenche3(s);
    out += UsaPreencheCopiaB(out);
    out += UsaIdentificador(a, s) + UsaIdentificador(a + 1, s) + UsaIdentificador(a + 2, s);
    out += UsaMaiusculasB(out) + UsaSubstituiA(s);
    std::string (*maiusculas)(const std::string&) = &CStringUtils::ToUpper;
    acc += reinterpret_cast<uintptr_t>(maiusculas);
    return static_cast<int>(acc) + static_cast<int>(out.size());
}
