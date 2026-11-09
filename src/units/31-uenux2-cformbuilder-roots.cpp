// Roots: keep the unit's members in the skeleton link the way the target reaches them. Compiled with APP_CXXFLAGS, like the
// other stand-ins, and it emits none of them: each stand-in calls members its unit's objects define.
//
// The adders: the target calls each directly from the screens that build a form. The stand-ins stand for those not in
// the link, and each builds its form on the stack as they do, so the constructor (fn 203) gets its calls and the
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
//   TelaB             12098, the last target caller not in the link of 202 (AddTextField over a text, with colours) and
//                     of 502 (AddStatusHeader): one call of each, passing what 12098 passes (the alignment 2 and the
//                     colours 2 and 1; the fields 5). TelaA went, and with it TelaB's calls of 3068, 1191, 426, 2245,
//                     1265, 3058 and 2243: every target caller of those adders is in the link, 7787's calls made by
//                     unit 443's constructor (through unit 441's roots), and the link without them moved no row.
//                     Its call of 2244 (AddLine) stays though 2244's target callers (653, 3054, 7787, 12055 and 12065)
//                     are all in the link: each passes the colour 3, and without this call binaryen folds it into 2244,
//                     which the target keeps as a parameter, and 2244, 653, 3054 and 12065 leave `match` (a link without
//                     it). It stands for no caller the target shows, so the 11157 rule ("Finding the idle ones") would
//                     take it out at that cost; it stays until that is decided.
//                     Their calls of 3680 (AddRect: 1102, 1190 and 3064, unit 378's) and 5547 (AddImage: 12040, unit
//                     387's, and 12055, unit 37's) went before, for the same reason
//   RotuloTecla and TextoMultiLinha, for 7787's calls of 3678 (AddLabeledKey over the key's name) and 2782
//                     (AddTextFieldMultiLine), went: unit 443's constructor makes them, and the link without the two
//                     moved no row
//   RelatorioA        the caller of 193, 604, 198 and 1264 not in the link, 12110, one call of each, and 12110 for
//                     2775, two (5591, unit 296's, 5579, 5580 and 11946, fragment 325's, 2248, unit 220's, and 12105,
//                     fragment 372's, which call them too, are in the link: the calls that stood for 12105 went). Its
//                     form is a parameter: their callers zero the vector in line, and it takes no constructor of ours.
//                     The EStyle and alignment are parameters, as 12110's vary
// The bodies differ from each other and from every target function's: each is a list of calls no screen makes.
// The getters' stand-ins (FormMTA to FormPapelC, below) are listed beside them.
#include <string>

#include "api/gui/cformbuilder.h"
#include "api/gui/cmtformbuilder.h"
#include "api/gui/cpaperformbuilder.h"
#include "api/util/cdatetime.h"
#include "app/vota/eleitor/comum/ctelasvota.h"

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

__attribute__((noinline)) int TelaB(const std::string& texto, const api::SPoint& posicao, const api::SFont& fonte)
{
    api::CFormBuilder form;
    form.AddLine(posicao, api::SPoint{posicao.y, posicao.x}, static_cast<api::TColor>(2));
    form.AddTextField(texto, posicao, fonte, api::ALINHAMENTO_CENTRO, static_cast<api::TColor>(2), static_cast<api::TColor>(1));
    form.AddStatusHeader(5);
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
    form.AddCut();
    form.AddQRCode(qrcode);
    return static_cast<int>(linhas);
}

// The adders over a font every target caller passes, which binaryen's dead-argument elimination folded into the
// target's bodies: 5546 (AddTextRectField) loads the SFont {35, 0} at @475016, and 5545 (AddProgressBar) the size of
// the SFont {0, 0} at @475024, both among the fonts of vota/eleitor/comum/ctelasvota.cpp's data (unit 110's fragment).
// The stand-in passes one font in each of its calls, so the fold happens here too, and varies what the target's callers
// vary. BarraProgresso's is vota::FONTE_BARRA_PROGRESSO, the object ctelasvota.cpp's progress screen passes, external
// by a chosen linkage (the user's decision; ctelasvota.h), so that the fold still happens beside the screen's call
// (src/units/31-uenux2-cformbuilder.mk). TextoRetangulo, which stood for 7787's two calls of 5546 with a {35, 0} of its
// own, went: unit 443's constructor makes those calls (CriaTelaNumeroCopiasErrado's FONTE_TEXTO_CONFIRMA_CORRIGE),
// and beside them its second constant kept the font a parameter.
//   BarraProgresso    12098's call of 5545 (30, "%p"), its other target caller beside 7787, whose call (the limit 4,
//                     an empty text) unit 443's constructor makes: the stand-in's call for 7787 went, the link without
//                     it moving no row
__attribute__((noinline)) int BarraProgresso(api::CFormBuilder& form, const std::string& texto, const api::SPoint& canto,
                                             const api::SPoint& oposto, uedword limite)
{
    return form.AddProgressBar(limite + 26, oposto, canto, vota::FONTE_BARRA_PROGRESSO, texto).use_count();
}

// The forms: each of these stands for screens that end a form with the builder's getter, and each getter has two call
// sites here, or binaryen would inline it; what the target's callers vary varies here (the name).
//   FormMTA, FormMTB      callers of 1694 (4633; 1150, 5341, 5343, 10204, 10214 and 10676 are in the link); their
//                         calls of 301 (GetInteractiveForm) went: the last of its 49 target callers not in the link,
//                         10451 (unit 221's), is now
//   FormA, FormB          went: 5550's two target callers, 6117 (binaryen's body of GetForm overloads that build their
//                         pre-show) and 11891 (unit 104's, holding GetFormSemLimpar inlined), are in the link
//   FormPapelC   the caller of 357 (Build) not reconstructed, 12110 (11256, 2890, 12005, 11908, 11946, 3872, 3873,
//                5579, 5977, 3699, 5580, 5970, 5971, 11253 and fragment 372's 12105 are in the link): one call, the
//                one that stood for 12105 having gone with it
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

__attribute__((noinline)) int FormPapelC(api::CPaperFormBuilder& form)
{
    return form.Build().use_count() + 3;
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
        w5544_sink = reinterpret_cast<void*>(&TelaB);
        w5544_sink = reinterpret_cast<void*>(&RelatorioA);
        w5544_sink = reinterpret_cast<void*>(&FormMTA);
        w5544_sink = reinterpret_cast<void*>(&FormMTB);
        w5544_sink = reinterpret_cast<void*>(&FormPapelC);
        w5544_sink = reinterpret_cast<void*>(&BarraProgresso);
    }
} w5544_roots;

} // namespace
