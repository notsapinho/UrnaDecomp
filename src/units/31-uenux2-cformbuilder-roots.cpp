// Roots: keep the unit's members in the skeleton link the way the target reaches them. Compiled with APP_CXXFLAGS, like the
// other stand-ins, and it emits none of them: each stand-in calls members its unit's objects define.
//
// The adders: the target calls each directly from the screens that build a form. Each pair of stand-ins stands for
// those not in the link (TelaA's and TelaB's lists still name 1255, comum::TelaRegistroMesarios, unit 247, 2376,
// vota::TelaTextoConfirmaCorrige, ctelasvota.cpp, 2291, vota::CRetirarMR::GetInst, unit 156, 12055,
// CMostraQRCodeBU::StartState, unit 37, and 12065, CImprimirBUOutrasObrigatorias::StartState, unit 104, which are),
// and each stand-in builds its form on the stack as they do, so the constructor (fn 203) gets its calls and the
// vector's destructor stays in line. Each adder has two call sites, or binaryen would inline it, and what the target's
// callers vary varies here, or binaryen would fold it. A call goes when every target caller of its adder is in the
// link (src/units/README.md "Companion files"):
//   TelaMTA, TelaMTB  the callers of 180 (AddTextField) and 435 (AddLed) not in the link: 4633 (5341, 10316, 10443,
//                     10451, 10465, 10474, 10489, 10500 and 10590 are in the link; 4633 builds an
//                     api::CMTFormBuilderBase in its frame, and 10451, as these stand-ins do, an api::CMTFormBuilder
//                     over fn 203). Their calls of 1072 (AddBeep) went: its last target caller not in the link, 10451
//                     (unit 221's), is now. Their calls of 651 (AddTextField over a function, with a format) went: its
//                     last target caller not in the link, 10316 (unit 135's), is now. Their calls of 1152 (AddTextField
//                     over a CTextSource, with a text) went: its seven target callers (1901, 2734, 2747, 5397, 10440,
//                     10465 and 10740) are in the link. Their calls of 619 (AddTextField over a function, with no
//                     format) went: 10500, its last target caller not in the link, is. Their calls of 5409 and 5419
//                     (AddTextField over a CTextSource and over a std::function, with no text), 941 (AddBuzz) and 728
//                     (AddClock) went: every target caller of the four is in the link (5409's 1150 and 2734, 5419's
//                     1905, 941's 13 and 728's 16), and the link without those calls moved no row (steps 6 to 10)
//   TelaA, TelaB      1255, 2291, 3064, 6569, 7787 and the other callers of 202, 1191, 3068, 5547, 2244, 2245, 3680 and 426,
//                     and 1190, 3064, 6602, 6603, 6605, 6608, 6624, 6641, 6646 and 7787, the callers of 1265; 1255,
//                     2291, 2376, 3059, 6599, 6601, 7787, 11812, 11881, 11884, 11888, 11892, 12040,
//                     12055, 12065 and 12098, the callers of 502 (AddStatusHeader), whose fields vary (2380, 3059 and
//                     6599, unit 110's, 11812, unit 217's, and 11881, unit 104's, are in the link); TelaB for 7787,
//                     the caller of 3058 (AddTextFieldUpdate, the instance over a function pointer) beside 502, with
//                     another callback, alignment and font; and 6569, 7787 and 12055, the callers of 2243 (AddLabeledKey
//                     over a key), which pass the keys '4' and '6', 'B' and 'D', and 'B', with the alignments 0 and 2
//                     (6569, unit 110's, and 12055 are in the link); 6569 is in the link for the other adders too
//   RotuloTecla       7787, the other caller of 3678 (AddLabeledKey over the key's name) beside 2243 and 653 (in the link,
//                     unit 120, which holds AddKeyLabel's code inlined): its third call site. It leaves the colours at
//                     their defaults
//   TextoMultiLinha   3074, 7787 and 12040, the callers of 2782 (AddTextFieldMultiLine) not in the link (1588, unit
//                     110's, is): it calls it twice, with another rectangle and alignment the second time
//   RelatorioA        the callers of 193, 604, 198 and 1264 not in the link (12105, 12110), and 12110 for 2775
//                     (5591, unit 296's, 5579, 5580 and 11946, fragment 325's, and 2248, unit 220's, which call them
//                     too, are in the link). Its form is a parameter: their callers zero the vector in line, and it takes no
//                     constructor of ours. The EStyle and alignments vary as theirs do
// The bodies differ from each other and from every target function's: each is a list of calls no screen makes.
// The getters' stand-ins (FormMTA to FormPapelC, below) are listed beside them.
#include <string>

#include "api/gui/cformbuilder.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/cpaperformbuilder.h"
#include "api/util/cdatetime.h"

namespace {

__attribute__((noinline)) int TelaMTA(const std::string& texto, const api::SPoint& posicao, api::ETextAlignment alinhamento,
                                      std::string (*fonte)(), std::string (*fonteFmt)(const std::string&),
                                      const api::CTextSource& origem, int vezes)
{
    api::CMTFormBuilder form;
    form.AddLed(static_cast<api::ELedOperacao>(vezes));
    form.AddTextField(texto, posicao, alinhamento);
    return vezes;
}

__attribute__((noinline)) int TelaMTB(const std::string& texto, const api::SPoint& posicao, std::string (*fonte)(),
                                      std::string (*fonteFmt)(const std::string&), const api::CTextSource& origem,
                                      int vezes)
{
    api::CMTFormBuilder form;
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
    form.AddStatusHeader(static_cast<api::CFormBuilder::StatusHeaderFields>(posicao.y));
    form.AddLabeledKey('B', texto, alinhamento);
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
    form.AddTextFieldUpdate(&api::CDateTime::FormatCurrentDate, api::SPoint{posicao.y, posicao.x},
                            std::chrono::milliseconds(1000), fonte, texto, api::ALINHAMENTO_CENTRO);
    form.AddStatusHeader(5);
    form.AddLabeledKey('D', texto, api::ALINHAMENTO_CENTRO);
    return posicao.y;
}

__attribute__((noinline)) int RotuloTecla(api::CFormBuilder& form, const std::string& nome, const std::string& rotulo,
                                          api::ETextAlignment alinhamento)
{
    form.AddLabeledKey(nome, rotulo, alinhamento);
    return static_cast<int>(alinhamento) + 1;
}

__attribute__((noinline)) int TextoMultiLinha(api::CFormBuilder& form, const std::string& texto, const api::SRect& rect,
                                              const api::SFont& fonte, api::ETextAlignment alinhamento)
{
    form.AddTextFieldMultiLine(texto, rect, fonte, alinhamento);
    return form.AddTextFieldMultiLine(texto, api::SRect{rect.top, rect.left, rect.bottom, rect.right}, fonte, api::ALINHAMENTO_CENTRO).use_count();
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
// sites here, or binaryen would inline it; what the target's callers vary varies here (the name).
//   FormMTA, FormMTB      callers of 1694 (4633; 1150, 5341, 5343, 10204, 10214 and 10676 are in the link); their
//                         calls of 301 (GetInteractiveForm) went: the last of its 49 target callers not in the link,
//                         10451 (unit 221's), is now
//   FormA, FormB          callers of 5550: 6117 (binaryen's body of GetForm overloads that build their pre-show) and 11891
//   FormPapelC   the callers of 357 (Build): 12105 and 12110, not reconstructed (11256, 2890, 12005, 11908, 11946,
//                3872, 3873, 5579, 5977, 3699, 5580, 5970, 5971 and 11253 are in the link); it calls Build twice
__attribute__((noinline)) int FormMTA(api::CMTFormBuilder& form, const std::string& nome, bool limpa)
{
    const auto simples = form.GetForm(nome);
    return simples.use_count() + (limpa ? 1 : 0);
}

__attribute__((noinline)) int FormMTB(api::CMTFormBuilder& form, const std::string& nome, int vezes)
{
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

__attribute__((noinline)) int FormPapelC(api::CPaperFormBuilder& form, api::CPaperFormBuilder& outro)
{
    return form.Build().use_count() + outro.Build().use_count() + 3;
}

// The MT builder's input fields: ControleMT, the stand-in for the callers of 395 (CMTFormBuilder::AddInputControl),
// went: the last of its 39 target callers not in the link, 10451 (unit 221's), is now.
// The stand-in for 5410, the third caller of 3674 (CMTFormBuilderBase::AddField) and of 3673 (IInputField<IScreenMT>'s
// constructor), went: 5410 is in the link (vota::MontaTelaEleitorPodeVotar, unit 161, over AddInputControl(int)), with
// 395 and 1151 (unit 121), the other two.

void* volatile w5544_sink;

struct SW5544Roots {
    SW5544Roots()
    {
        w5544_sink = reinterpret_cast<void*>(&TelaMTA);
        w5544_sink = reinterpret_cast<void*>(&TelaMTB);
        w5544_sink = reinterpret_cast<void*>(&TelaA);
        w5544_sink = reinterpret_cast<void*>(&TelaB);
        w5544_sink = reinterpret_cast<void*>(&RotuloTecla);
        w5544_sink = reinterpret_cast<void*>(&TextoMultiLinha);
        w5544_sink = reinterpret_cast<void*>(&RelatorioA);
        w5544_sink = reinterpret_cast<void*>(&FormMTA);
        w5544_sink = reinterpret_cast<void*>(&FormMTB);
        w5544_sink = reinterpret_cast<void*>(&FormA);
        w5544_sink = reinterpret_cast<void*>(&FormB);
        w5544_sink = reinterpret_cast<void*>(&FormPapelC);
    }
} w5544_roots;

} // namespace
