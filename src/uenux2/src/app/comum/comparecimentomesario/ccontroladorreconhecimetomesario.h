#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

#include "app/comum/comparecimentomesario/md/ccomparecimentomesario.h"
#include "app/comum/dados/md/eleitor/cdedo.h"

namespace comum {

// The list of the files of the WSQ directory "nao-registrado/", in reverse name order: target fn 5374, whose name, its
// being a free function and its line in ccontroladorreconhecimetomesario.cpp are chosen
// (src/units/214-uenux2-app-comum-comparecimentomesario.mk). Declared here, beside the class whose constructor calls it,
// a choice.
std::vector<std::filesystem::path> ListaArquivosNaoRegistrados();

// The poll worker's WSQ stored through comum::CControlaArmazenamentoDeImagens::ArmazenaImagem (fn 2725), held by fn 5382
// behind a frame of its own: its name, its being a free function and its file (ccontroladorreconhecimetomesario.cpp)
// are chosen (src/units/214-uenux2-app-comum-comparecimentomesario.mk).
uint32_t ArmazenaImagemMesario(const std::vector<uebyte>& wsq, const std::string& titulo);

// comum::CControladorReconhecimentoMesario: the records of ComparaDigitais (ccontroladorreconhecimetomesario.cpp:65 and
// :76, fn 5372, written and matched) name the class and the file; no vtable or typeinfo of it is in the target. GetInst
// is fn 1149: its result is the `this` both target callers of ComparaDigitais pass it (fn 3614 and fn 10451 call fn
// 1149 and hand its result to fn 5372). It is the project's singleton: the test of s_inst (@1909960), new of 24 bytes,
// the old object freed with no destructor call (the class is trivially destructible), the unlock of s_mutex (@1909936)
// through fn 150; the exit destructors are fns 10306 and 10305. Both statics lie in .bss right after
// CRegistradorMesario's (@1909908 and @1909932), and this file's records follow cregistradormesario.cpp's in the data:
// the next object.
//
// The layout is what the constructor stores, a function of its own that binaryen inlined into fn 1149 (its 16-byte
// frame opens after the new): 0 at +0, 20 at +4, 1 at +8, the bytes +12 and +16 cleared, then at +20 the size of
// ListaArquivosNaoRegistrados()'s vector. The readers fix the types: fn 10337 passes +0 as the CDedo::TipoDedo and +8
// as the EstadoReconhecimentoBiometrico of md::CComparecimentoMesario's constructors, and the word at +12 as the
// id_arquivo of fn 2730 when the byte at +16 is set, fn 2731 otherwise: a std::optional<int>, whose empty construction
// clears its two bytes. Fns 3614 and 10316 pass +4 to api::IFingerMatcher's slot 2 as its last argument; fns 10316 and
// 5382 store +0, and fn 10316 stores 2 and 3 at +8. Chosen: the members' names, +4's int and +20's std::size_t (the
// vector's size: the division by 12 is signed, a pointer difference), the accessors and their names, the private
// constructor, and this header's path and name, the .cpp's in lower case. SalvarBiometriaMesarioRegistrado's name and
// signature are its lambda's typeinfo's (fn 5382 holds it); GravaWsq (fn 5371, a chosen name) is public, a choice (its
// callers, SalvarBiometriaMesarioRegistrado and SalvarBiometriaMesarioNaoRegistrado, are members), and its last
// parameter, the free space it requires, is a reading of its test (its name and type chosen;
// src/units/214-uenux2-app-comum-comparecimentomesario.mk).
class CControladorReconhecimentoMesario {
public:
    static CControladorReconhecimentoMesario& GetInst();

    md::CDedo::TipoDedo GetDedo() const { return m_dedo; }
    md::CComparecimentoMesario::EstadoReconhecimentoBiometrico GetEstadoBiometria() const { return m_estadoBiometria; }
    const std::optional<int>& GetIdArquivo() const { return m_idArquivo; }
    int GetLimiar() const { return m_limiar; }
    void SetDedo(md::CDedo::TipoDedo dedo) { m_dedo = dedo; }
    void SetEstadoBiometria(md::CComparecimentoMesario::EstadoReconhecimentoBiometrico estado)
    {
        m_estadoBiometria = estado;
    }

    // Fn 5372: the record's member. Its wasm type is `(i32)->(i32)`: dead-argument elimination dropped the two vectors,
    // which only reach vota::CParametrosImagemDigital's two extractions (fn 2224's one body) after their own
    // parameters went the same way; it keeps `this`, whose +4 it passes the matcher. The parameters' names are chosen.
    bool ComparaDigitais(const std::vector<uebyte>& digital, const std::vector<uebyte>& outraDigital);
    // What 3614 and 10451 hold behind frames of their own (binaryen's inlining of members clang kept out of line in
    // this TU): BiometriaPresenteNosRegistrados's 16-byte frame, the GetPathWsqRegistrado() it passes
    // BiometriaPresenteNoArquivo, whose 384-byte frame formats "me{:06}.wsq"; and BiometriaPresenteNosNaoRegistrados,
    // over the first six of ListaArquivosNaoRegistrados() (fn 5374). Each calls ComparaDigitais on `this` (fn 1149's
    // result in both callers). Their names, their being members and the parameters' names are chosen.
    bool BiometriaPresenteNosRegistrados(const std::vector<uebyte>& digital, int idArquivo);
    bool BiometriaPresenteNosNaoRegistrados(const std::vector<uebyte>& digital);
    void SalvarBiometriaMesarioRegistrado(const std::vector<uebyte>& wsq, const std::string& titulo);
    // The name and signature are its lambda's typeinfo's (`ZN5comum33CControladorReconhecimentoMesario35Salvar...`,
    // @543297): fn 10451 holds it inlined. The lambda returns ++m_quantidadeNaoRegistrados (fn 10296's body), so it
    // captures `this`.
    void SalvarBiometriaMesarioNaoRegistrado(const std::vector<uebyte>& wsq);
    void GravaWsq(const std::vector<uebyte>& wsq, const std::filesystem::path& diretorio,
        const std::filesystem::path& diretorioExterno, const std::function<uint32_t()>& geraId, double espacoMinimo);

private:
    CControladorReconhecimentoMesario();

    bool BiometriaPresenteNoArquivo(const std::vector<uebyte>& digital, const std::filesystem::path& diretorio,
        int idArquivo);

    md::CDedo::TipoDedo m_dedo;
    int m_limiar;
    md::CComparecimentoMesario::EstadoReconhecimentoBiometrico m_estadoBiometria;
    std::optional<int> m_idArquivo;
    std::size_t m_quantidadeNaoRegistrados;

    static std::unique_ptr<CControladorReconhecimentoMesario> s_inst;
    static std::mutex s_mutex;
};

} // namespace comum
