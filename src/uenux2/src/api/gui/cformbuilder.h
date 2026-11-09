#pragma once

// api::CFormBuilder (/home/rubio/tse/uenux2/src/api/gui/cformbuilder.cpp, the file of the records of AddStatusHeader and
// GetLabeledKeyPos). The records name the class, those two members and, in app/vota/eleitor/comum/ctelasvota.cpp, its
// passing by reference; the header's path follows the .cpp. The layout is a reading: fn 203, the constructor, zeroes 12
// bytes, and fn 426 walks a vector of two-word elements at this + 0, so the class holds the fields it has built in one
// std::vector. Its destructor is implicit: the callers destroy the vector in line. Fn 203 stays out of line in the target,
// with 88 callers and 18 bytes, which clang would inline from a header, so the constructor is defined in the .cpp. No
// record names an adder: every adder's name, and which overloads share a name, are chosen from the field each builds.
//
// GetForm (fn 5550) builds the api::IForm<IScreen> of the fields added, names it, and clears the vector: its name and
// its parameters are chosen. The overload of a name alone (fn 11140) passes it an api::CPreShowClearScreen, whose
// vtable and typeinfo lie in cformbuilder.cpp's data (cpreshowclearscreen.h); its being an overload, its name and its
// place after the first in the .cpp are chosen. m_campos is protected because api::CInteractiveFormBuilder
// (cinteractiveformbuilder.h) builds its forms from it, a choice that goes with deriving that class.
//
// AddStatusHeader (fn 502, records cformbuilder.cpp 292:30 and 305:24) adds up to four fields, one per bit of its
// argument: 1 the date and time, 8 the battery's charge, 4 the battery's icon, 2 the mode's text. RTTI types the
// argument unsigned int (CDataText<api::CFormBuilder::AddStatusHeader(unsigned int)::$_0>) and the record spells it
// StatusHeaderFields. The alias's being a member, and the enumerators and their names, are chosen; the values are the
// bits the body tests.
//
// The two AddTextFieldUpdate templates: fn 3058 is the first's instance over std::string (*)(const std::string &),
// called by 502 and 7787 (which holds vota::CTelasVota's constructor); the second's instance over 502's lambda is
// inlined into 502. That 3058 is linkonce, an inline or template definition, is evidence of two kinds. Its vtables
// (CDataTextFmt over that pointer, @1539160, and the control blocks of it and of CTextFieldUpdate, @1539120 and
// @1539196) lie among the data of app/vota/eleitor/comum/ctelasvota.cpp, not of cformbuilder.cpp: the kept copy is the
// first object's to emit them. And 502 tests the format string's long flag before freeing it after its call of 3058,
// where 502 with 3058 a plain member of cformbuilder.cpp frees it with no test (measured in the link); that clang drops
// the test because it infers the callee's attributes, and infers none for a linkonce one, is a reading. Templates
// rather than plain inline members, the names and the parameters' order beyond the wasm's are chosen.

#include <chrono>
#include <memory>
#include <string>
#include <vector>

#include "api/gui/cdatatext.h"
#include "api/gui/cdatatextfmt.h"
#include "api/gui/ctextfieldupdate.h"
#include "api/gui/iform.h"
#include "api/gui/iformfield.h"
#include "api/gui/iimage.h"
#include "api/gui/ipreshow.h"
#include "api/gui/itext.h"
#include "api/gui/primitives.h"
#include "ecourna/api/uetypes.hpp"

namespace api {

class CDSImageField;
class CProgressBar;

/**
 * Monta os formulários da interface.
 */
class CFormBuilder {
public:
    using SharedField = std::shared_ptr<IFormField<IScreen>>;

    using StatusHeaderFields = unsigned int;

    enum : StatusHeaderFields {
        STATUS_DATA_HORA = 1,
        STATUS_MODO = 2,
        STATUS_ICONE_BATERIA = 4,
        STATUS_CARGA_BATERIA = 8,
    };

    CFormBuilder();

    void AddField(SharedField campo);

    SharedField AddTextField(const std::string& texto, const SPoint& posicao, const SFont& fonte,
                             ETextAlignment alinhamento, TColor corTexto, TColor corFundo);

    SharedField AddTextField(std::string (*fonte)(), const SPoint& posicao, const SFont& font, ETextAlignment alinhamento);

    // a CTextFieldBlinking over a CFixedText of texto, in the colours 2 and 3 over 1: target fn 1265. The name is chosen,
    // and so is having the colours in the body rather than as parameters every caller passes the same
    SharedField AddBlinkingTextField(const std::string& texto, const SPoint& posicao, const SFont& fonte,
                                     ETextAlignment alinhamento);

    // a CTextRectField over a CFixedText of texto, centred, the text in the colour 2 over 20: target fn 5546, which
    // holds the field's constructor inlined (ctextrectfield.cpp). Its one target caller, fn 7787 (vota::CTelasVota's
    // constructor), passes one SFont at both its calls, {35, 0} @475016 among ctelasvota.cpp's fonts, which 5546 loads
    // at that address: a parameter binaryen's dead-argument elimination folded, a reading. The name, the font's place
    // among the parameters, and the colours and the alignment as constants of the body rather than parameters every
    // caller passes the same are chosen
    SharedField AddTextRectField(const std::string& texto, const SRect& rect, const SFont& fonte);

    // a CProgressBar from 0 to limite over the rectangle of two corners, the bar in the colour 13 over 1, the text
    // over the bar in 1 and off it in 2, a border 2 pixels wide in 2, with the text texto and the size of fonte: target
    // fn 5545, which holds the bar's constructor inlined (cprogressbar.cpp). Its two target callers, 7787 and 12098,
    // pass one SFont, {0, 0} @475024 amid ctelasvota.cpp's fonts, which binaryen folded: 5545 reads its size there.
    // Chosen: the name, the font's place among the parameters, the fixed values as constants of the body, limite's
    // being the upper limit (the callers pass 0 for the other two, cprogressbar.h) and the return type, read from 7787,
    // which keeps the result in vota::CTelasVota's std::shared_ptr<api::CProgressBar> (ctelasvota.h)
    std::shared_ptr<CProgressBar> AddProgressBar(uedword limite, const SPoint& canto, const SPoint& oposto,
                                                 const SFont& fonte, const std::string& texto);

    // a CMaskedTextField<CFramedText> over a CFixedText of texto (alignment 0), its frames as many as tamanho, the
    // alignment read from the text (CMaskedTextField's constructor for it): the code fn 2384 (vota::
    // AdicionaCamposInputVazio, ctelasvota.cpp) holds behind a second stack-pointer prologue of 16 bytes (the field's
    // copy for AddField), with "" and the font @474880 (FONTE_NUMERO, ctelasvota.cpp's), a parameter dead-argument
    // elimination folds, a reading as for AddTextRectField. Evidence for another TU than its caller's: 2384 keeps the
    // "" temporary's destruction after the call (its long-mode byte tested and the buffer freed), which our clang drops
    // when the helper is in ctelasvota.cpp and only reads its parameter; with the helper there 2384 scored 134 over
    // 363 rows, and 17 over 353, operand-only, with it in this TU (pnpm wasm score, whole link). That it is a member
    // of CFormBuilder, as the file's other CFixedText adders are, its name and its parameters' order are chosen.
    SharedField AddMaskedTextField(const std::string& texto, size_t tamanho, const SPoint& posicao, const SFont& fonte);

    SharedField AddDoubleLineField(std::string (*fonte)(), const SPoint& linha1, const SPoint& linha2, TPosition maxX,
                                   const SFont& font, TColor corFundo);

    template <typename FONTE>
    SharedField AddTextFieldUpdate(FONTE fonte, const SPoint& posicao, const std::chrono::milliseconds& intervalo,
                                   const SFont& font, const std::string& formato, ETextAlignment alinhamento)
    {
        const auto text = std::make_shared<CDataTextFmt<FONTE>>(fonte, formato, alinhamento);
        SharedField campo = std::make_shared<CTextFieldUpdate>(posicao, text, intervalo, font, static_cast<TColor>(2),
                                                               static_cast<TColor>(1));
        AddField(campo);
        return campo;
    }

    template <typename FONTE>
    SharedField AddTextFieldUpdate(FONTE fonte, const SPoint& posicao, const std::chrono::milliseconds& intervalo,
                                   const SFont& font, ETextAlignment alinhamento)
    {
        const auto text = std::make_shared<CDataText<FONTE>>(fonte, alinhamento);
        SharedField campo = std::make_shared<CTextFieldUpdate>(posicao, text, intervalo, font, static_cast<TColor>(2),
                                                               static_cast<TColor>(1));
        AddField(campo);
        return campo;
    }

    SharedField AddImage(SharedIImage imagem, const SPoint& posicao);

    // a CMovieField of movie at posicao, anchored by its bottom right corner (the constant 7): target fn 5543, which
    // holds the field's constructor inlined (cmoviefield.cpp); its callers are the gif screens of
    // app/vota/eleitor/comum/ctelasvota.cpp (fns 1593 and 3076). The name, the anchor's being a constant of the body
    // and the parameters' order beyond the wasm's are chosen
    SharedField AddMovie(const SPoint& posicao, const std::shared_ptr<CMovie>& movie);

    SharedField AddLine(const SPoint& inicio, const SPoint& fim, TColor cor);

    SharedField AddFill(const SPoint& canto, const SPoint& oposto, TColor cor);

    SharedField AddRect(const SPoint& canto, const SPoint& oposto);
    // the same over a rectangle, which the overload above calls: public, as vota::CTelasVota::CriaTelaZeresimaTardia
    // (ctelasvota.cpp) calls it, its body behind a 16-byte prologue of its own in fn 7787 (+0x174a1: the CRectField
    // of colour 2, binaryen's one caller folding the colour); it was private, a choice
    SharedField AddRect(const SRect& rect);

    // a CTextFieldMultiLine over a CFixedText of texto, in the colours 2 over 1: target fn 2782. The name is chosen, and
    // so is having the colours in the body rather than as parameters every caller passes the same (not measured)
    SharedField AddTextFieldMultiLine(const std::string& texto, const SRect& rect, const SFont& fonte, ETextAlignment alinhamento);

    void AddStatusHeader(StatusHeaderFields campos);

    static SPoint GetLabeledKeyPos(const SRect& area, ETextAlignment alinhamento, TPosition deslocamento);

    // a key's name and, under it, its action's label, at GetLabeledKeyPos's offsets 0 and 21 of the screen's area:
    // target fn 3678 over the name, fn 2243 over the key (KeyName, then 3678). The target's 3678 takes no colour, which
    // fits parameters every caller passes alike, folded by binaryen (a reading). With both colours constants of the
    // body 3678 differs; with the text colour a parameter it matches, the background a parameter or a constant alike
    // (src/units/31-uenux2-cformbuilder.mk has the measurements). The names, the overloading, the background's being a
    // parameter, the colours as default arguments (= 2, = 1: each call passing them gives the same code) and the
    // parameters' order beyond the wasm's are chosen
    void AddLabeledKey(const std::string& tecla, const std::string& rotulo, ETextAlignment alinhamento,
                       TColor corTexto = static_cast<TColor>(2), TColor corFundo = static_cast<TColor>(1));

    void AddLabeledKey(char tecla, const std::string& rotulo, ETextAlignment alinhamento);

    // the same, called by api::CInteractiveFormBuilder::AddLabeledInputControl (target fn 653) alone: 653 holds this code
    // behind a second prologue, the twin of fn 2243 above, so it was a function of its own with 653 as its one caller
    // when binaryen inlined it, and one that duplicate-function-elimination had not joined with 2243 before that
    // (docs/reference/facts/tool-traps.md X1): it differed in the object. That difference, the label first, the name,
    // and its being CFormBuilder's, in cformbuilder.cpp after 2243, are chosen (KeyName, fn 744, is api/hwil/iinput.h's
    // inline, so the code pins no TU but that it is not 653's); the colours as two more parameters 653 passes gives the
    // same 653 (src/units/120-uenux2-iform.mk)
    void AddKeyLabel(const std::string& rotulo, char tecla, ETextAlignment alinhamento);

    std::shared_ptr<IForm<IScreen>> GetForm(const std::shared_ptr<IPreShow<IScreen>>& preShow, const std::string& nome);

    std::shared_ptr<IForm<IScreen>> GetForm(const std::string& nome);

    // the same with an api::CPreShowNothing<IScreen>, so the form is drawn over the screen without clearing it: target
    // fn 11891 (vota::CMenuFiltrarCandidatosPorNumero::ProcessInput) holds it behind a second prologue of 16 bytes (the
    // pre-show's std::shared_ptr), inside the message screen it holds (api::MostraMensagemTemporaria, capplication.h),
    // with "" for the name. CPreShowNothing<IScreen>'s vtable and typeinfo (@1577920, @1577940) lie in this file's data
    // right after CPreShowClearScreen's, which GetForm(nome) builds, and before the two control blocks' vtables
    // (@1577952, then @1577992, whose address plus 8 11891 stores): a reading that puts it in cformbuilder.cpp after
    // GetForm(nome). Its name, its being a member and its line are chosen
    std::shared_ptr<IForm<IScreen>> GetFormSemLimpar(const std::string& nome);

protected:
    std::vector<SharedField> m_campos;

private:
    // The battery's icon of AddStatusHeader (fn 502) as a field with no generated name, pushed as it is. It has no
    // target function: binaryen inlined it into 502, whose push's throw paths come after the field's release, as the
    // end of a function of its own lays them out (src/units/31-uenux2-cformbuilder.mk has the evidence and the
    // measurements). Its name, its being a private member and its parameter's name are chosen
    void AddDSImageField(CDSImageField* campo);

    std::string GeraNome(const IFormField<IScreen>& campo) const;
};

} // namespace api
