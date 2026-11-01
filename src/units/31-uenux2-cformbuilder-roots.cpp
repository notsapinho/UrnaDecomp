// Roots: keep the unit's members in the skeleton link the way the target reaches them. Compiled with APP_CXXFLAGS, like the
// other stand-ins, and it emits none of them: each stand-in calls members its unit's objects define.
//
// api::CFormBuilder::GetLabeledKeyPos (target fn 5544): the target calls it from one function, 3678 (not reconstructed
// yet), at two call sites (ledger/callgraph.tsv lists 3678 twice), and never through the table (no elem slot holds it); two
// call sites keep binaryen from inlining it. PosicoesTecla reproduces 3678's two calls: the same area and alignment in
// both, passed through so that binaryen's dead-argument elimination folds neither, and the vertical offsets 0 and 21 that
// 3678 passes. It is address-taken from a static constructor. Declared through an asm label with the wasm-level signature
// (the SPoint result through its address first).
//
// The adders: the target calls each directly from the screens that build a form, and those are not reconstructed. Each pair
// of stand-ins stands for them, and each stand-in builds its form on the stack as they do, so the constructor (fn 203) gets
// its calls and the vector's destructor stays in line. Each adder has two call sites, or binaryen would inline it, and what
// the target's callers vary varies here, or binaryen would fold it:
//   TelaMTA, TelaMTB  652, 1150, 1901, 1905, 2734, 2735, 2740, 2743, 2747, 3610 and the other callers of 180, 619, 651, 1152, 5409
//                     (1150, 2734), 5419 (1905), 435, 1072, 941, 728. 5409's and 5419's alignment stays the default: their
//                     target callers all pass it, and they have no parameter for it
//   TelaA, TelaB      1255, 2291, 3064, 6569, 7787 and the other callers of 202, 1191, 3068, 5547, 2244, 2245, 3680 and 426,
//                     and 1190, 3064, 6602, 6603, 6605, 6608, 6624, 6641, 6646 and 7787, the callers of 1265
//   RelatorioA        5579, 5580, 5591 and the other callers of 193, 604, 198, 1264, and of 2775 (5591 and 12110). Its
//                     form is a parameter: their callers zero the vector in line, and it takes no constructor of ours. The
//                     EStyle and alignments vary as theirs do
// The bodies differ from each other and from every target function's: each is a list of calls no screen makes.
// The getters' stand-ins (FormMTA to FormPapelB, below) are listed beside them.
#include <functional>
#include <string>

#include "api/gui/cformbuilder.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/cpaperformbuilder.h"

extern "C" {
void w5544_root_0(void*, const void*, int, int) __asm__("_ZN3api12CFormBuilder16GetLabeledKeyPosERKNS_5SRectENS_14ETextAlignmentEs");
}

namespace {

struct SPosicao {
    short x;
    short y;
};

__attribute__((noinline)) int PosicoesTecla(const void* area, int alinhamento)
{
    SPosicao rotulo;
    SPosicao legenda;
    w5544_root_0(&rotulo, area, alinhamento, 0);
    w5544_root_0(&legenda, area, alinhamento, 21);
    return rotulo.x + legenda.y;
}

__attribute__((noinline)) int TelaMTA(const std::string& texto, const api::SPoint& posicao, api::ETextAlignment alinhamento,
                                      std::string (*fonte)(), std::string (*fonteFmt)(const std::string&),
                                      const api::CTextSource& origem, const std::function<std::string()>& funcao, int vezes)
{
    api::CMTFormBuilder form;
    form.AddLed(static_cast<api::ELedOperacao>(vezes));
    form.AddTextField(texto, posicao, alinhamento);
    form.AddTextField(fonte, posicao, alinhamento);
    form.AddTextField(fonteFmt, posicao, texto, alinhamento);
    form.AddTextField(origem, posicao, texto, alinhamento);
    form.AddTextField(origem, posicao);
    form.AddTextField(funcao, posicao);
    form.AddBeep(vezes);
    form.AddBuzz(vezes, vezes + 1);
    form.AddClock(posicao);
    return vezes;
}

__attribute__((noinline)) int TelaMTB(const std::string& texto, const api::SPoint& posicao, std::string (*fonte)(),
                                      std::string (*fonteFmt)(const std::string&), const api::CTextSource& origem,
                                      const std::function<std::string()>& funcao, int vezes)
{
    api::CMTFormBuilder form;
    form.AddClock(posicao);
    form.AddBuzz(vezes + 2, 5);
    form.AddBeep(vezes + 3);
    form.AddTextField(funcao, posicao);
    form.AddTextField(origem, posicao);
    form.AddTextField(origem, posicao, texto, api::ALINHAMENTO_DIREITA);
    form.AddTextField(fonteFmt, posicao, texto, api::ALINHAMENTO_CENTRO);
    form.AddTextField(fonte, posicao, api::ALINHAMENTO_DIREITA);
    form.AddTextField(texto, posicao, api::ALINHAMENTO_CENTRO);
    form.AddLed(api::LED_OPERACAO_1);
    return vezes + 1;
}

__attribute__((noinline)) int TelaA(const std::string& texto, const api::SPoint& posicao, const api::SFont& fonte,
                                    api::ETextAlignment alinhamento, api::TColor corTexto, api::TColor corFundo,
                                    std::string (*origem)(), const api::SharedIImage& imagem)
{
    api::CFormBuilder form;
    form.AddImage(imagem, posicao);
    form.AddDoubleLineField(origem, posicao, posicao, posicao.x, fonte, corFundo);
    form.AddTextField(origem, posicao, fonte, alinhamento);
    api::CFormBuilder::SharedField campo = form.AddTextField(texto, posicao, fonte, alinhamento, corTexto, corFundo);
    form.AddField(campo);
    form.AddLine(posicao, posicao, corTexto);
    form.AddFill(posicao, posicao, corTexto);
    form.AddRect(posicao, posicao);
    form.AddBlinkingTextField(texto, posicao, fonte, alinhamento);
    return posicao.x;
}

__attribute__((noinline)) int TelaB(const std::string& texto, const api::SPoint& posicao, const api::SFont& fonte,
                                    const api::CFormBuilder::SharedField& campo, std::string (*origem)(),
                                    const api::SharedIImage& imagem)
{
    api::CFormBuilder form;
    form.AddField(campo);
    form.AddTextField(origem, posicao, fonte, api::ALINHAMENTO_CENTRO);
    form.AddDoubleLineField(origem, posicao, api::SPoint{posicao.y, posicao.x}, posicao.y, fonte, static_cast<api::TColor>(1));
    form.AddImage(imagem, api::SPoint{posicao.y, posicao.x});
    form.AddRect(posicao, api::SPoint{posicao.y, posicao.x});
    form.AddFill(posicao, api::SPoint{posicao.y, posicao.x}, static_cast<api::TColor>(1));
    form.AddLine(posicao, api::SPoint{posicao.y, posicao.x}, static_cast<api::TColor>(2));
    form.AddBlinkingTextField(texto, api::SPoint{posicao.y, posicao.x}, fonte, api::ALINHAMENTO_DIREITA);
    form.AddTextField(texto, posicao, fonte, api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    return posicao.y;
}

__attribute__((noinline)) int RelatorioA(api::CPaperFormBuilder& form, const std::string& texto, std::string (*fonte)(), size_t linhas,
                                         api::IPaper::EStyle estilo, api::ETextAlignment alinhamento,
                                         const api::CQRCodeImagePaper::QrcodeData& qrcode)
{
    form.AddQRCode(qrcode);
    form.AddTextField(texto, estilo, alinhamento);
    form.AddTextField(fonte, alinhamento);
    form.AddNewLine(linhas);
    form.AddNewLine(1);
    form.AddCut();
    form.AddTextField(texto, static_cast<api::IPaper::EStyle>(2), api::ALINHAMENTO_CENTRO);
    form.AddTextField(fonte, api::ALINHAMENTO_DIREITA);
    form.AddCut();
    form.AddQRCode(qrcode);
    return static_cast<int>(linhas);
}

// The forms: each of these stands for screens that end a form with the builder's getter, and each getter has two call
// sites here, or binaryen would inline it; what the target's callers vary varies here (the name, 301's bool).
//   FormMTA, FormMTB      callers of 1694 (1150, 4633, 5341, 5343, 10204, 10214, 10676) and of 301 (652, 1901, 1905, 2734,
//                         2735 and the other 44)
//   FormA, FormB          callers of 5550: 6117 (binaryen's body of GetForm overloads that build their pre-show) and 11891
//   FormPapelA, FormPapelB  callers of 5515: 357 and 10997
__attribute__((noinline)) int FormMTA(api::CMTFormBuilder& form, const std::string& nome, bool limpa)
{
    const auto simples = form.GetForm(nome);
    const auto interativo = form.GetInteractiveForm(nome, limpa);
    return simples.use_count() + interativo.use_count();
}

__attribute__((noinline)) int FormMTB(api::CMTFormBuilder& form, const std::string& nome, int vezes)
{
    const auto interativo = form.GetInteractiveForm(nome, true);
    form.AddBeep(vezes);
    const auto simples = form.GetForm(std::string());
    return vezes - simples.use_count();
}

__attribute__((noinline)) int FormA(api::CFormBuilder& form, const std::shared_ptr<api::IPreShow<api::IScreen>>& preShow,
                                    const std::string& nome)
{
    return form.GetForm(preShow, nome).use_count();
}

__attribute__((noinline)) int FormB(api::CFormBuilder& form, const std::shared_ptr<api::IPreShow<api::IScreen>>& preShow,
                                    const api::SPoint& posicao, api::TColor cor)
{
    form.AddLine(posicao, posicao, cor);
    return form.GetForm(preShow, std::string()).use_count() + posicao.x;
}

__attribute__((noinline)) int FormPapelA(api::CPaperFormBuilder& form)
{
    return form.GetForm().use_count();
}

__attribute__((noinline)) int FormPapelB(api::CPaperFormBuilder& form, size_t linhas)
{
    form.AddNewLine(linhas);
    return form.GetForm().use_count() + 2;
}

void* volatile w5544_sink;

struct SW5544Roots {
    SW5544Roots()
    {
        w5544_sink = reinterpret_cast<void*>(&PosicoesTecla);
        w5544_sink = reinterpret_cast<void*>(&TelaMTA);
        w5544_sink = reinterpret_cast<void*>(&TelaMTB);
        w5544_sink = reinterpret_cast<void*>(&TelaA);
        w5544_sink = reinterpret_cast<void*>(&TelaB);
        w5544_sink = reinterpret_cast<void*>(&RelatorioA);
        w5544_sink = reinterpret_cast<void*>(&FormMTA);
        w5544_sink = reinterpret_cast<void*>(&FormMTB);
        w5544_sink = reinterpret_cast<void*>(&FormA);
        w5544_sink = reinterpret_cast<void*>(&FormB);
        w5544_sink = reinterpret_cast<void*>(&FormPapelA);
        w5544_sink = reinterpret_cast<void*>(&FormPapelB);
    }
} w5544_roots;

} // namespace
