// comum (/home/rubio/tse/uenux2/src/app/comum/comparecimentomesario/ccontroladorreconhecimetomesario.cpp): the list of
// the files of the WSQ directory "nao-registrado/" in reverse name order, target fn 5374, and with it the libc++ code
// of its std::sort the target keeps: __introsort (fn 5373), __insertion_sort_incomplete (fn 5370), __sort4 (fn 2726)
// and the comparator (fn 310). No record names fn 5374: its name, its being a free function and its line are chosen,
// and its file is its band's. comum::CControladorReconhecimentoMesario's GetInst (fn 1149), its constructor and its
// statics follow, their lines a choice. The records of CControladorReconhecimentoMesario::ComparaDigitais (fn 5372,
// lines 65 and 76) are not written. src/units/214-uenux2-app-comum-comparecimentomesario.mk says what each part rests
// on.
#include "app/comum/comparecimentomesario/ccontroladorreconhecimetomesario.h"

#include <algorithm>
#include <filesystem>
#include <string>
#include <vector>

#include "app/comum/gravadores/pathwsq.h"

namespace comum {

std::vector<std::filesystem::path> ListaArquivosNaoRegistrados()
{
    const std::filesystem::path diretorio = GetPathWsqNaoRegistrado();
    std::vector<std::filesystem::path> arquivos;
    std::ranges::for_each(std::filesystem::directory_iterator(diretorio),
                          [&arquivos](const std::filesystem::directory_entry& entrada) {
                              if (!entrada.is_directory()) {
                                  arquivos.push_back(entrada.path().filename());
                              }
                          });
    std::sort(arquivos.begin(), arquivos.end(),
              [](const std::filesystem::path& a, const std::filesystem::path& b) { return a.string() > b.string(); });
    return arquivos;
}

std::unique_ptr<CControladorReconhecimentoMesario> CControladorReconhecimentoMesario::s_inst;
std::mutex CControladorReconhecimentoMesario::s_mutex;

CControladorReconhecimentoMesario::CControladorReconhecimentoMesario()
    : m_dedo(static_cast<md::CDedo::TipoDedo>(0))
    , m_limiar(20)
    , m_estadoBiometria(static_cast<md::CComparecimentoMesario::EstadoReconhecimentoBiometrico>(1))
    , m_idArquivo()
    , m_quantidadeNaoRegistrados(ListaArquivosNaoRegistrados().size())
{
}

CControladorReconhecimentoMesario& CControladorReconhecimentoMesario::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CControladorReconhecimentoMesario());
    }
    return *s_inst;
}

} // namespace comum

// <stubs>
// f5372 · 720 B · unmatched · name unknown
// ? f5372(i32) { ... }
// </stubs>
