#pragma once

// api::CMTFormBuilderBase and api::CMTFormBuilder: the builders of the forms of the IScreenMT screen. No record, symbol
// or RTTI names either class; the names are chosen, CMTFormBuilder after api::CPaperFormBuilder, the name the records
// give the IPaper one, CMTFormBuilderBase after it as its base (TSE names a base so: comum::CGeradorBUBase), and the
// file is CMTFormBuilder's in lower case, beside cformbuilder.h. What is read from the bytes: the object is 12 bytes,
// destroyed in line as one vector, fns 180, 941, 728, 435 and 1072 push to a vector at this + 0, and they build
// IFormField<IScreenMT> fields, which api::CFormBuilder's vector cannot hold. So there are other vectors' classes than
// api::CFormBuilder's, and binaryen keeps one body, fn 203, for CMTFormBuilder's constructor and api::CFormBuilder's.
// That these classes share no base with api::CFormBuilder is a choice.
//
// Two classes, by how the callers build the object (ledger/callgraph.tsv and the bodies). Of the target callers of
// GetForm (fn 1694) and GetInteractiveForm (fn 301), the 49 of 301 and one of 1694's seven, fn 10204, call fn 203; the
// other six of 1694's, fns 1150, 4633, 5341, 5343, 10214 and 10676, clear the builder's 12 bytes in their own frame (an
// i32 store of 0 at +8 and an i64 store of 0 at +0) and call no constructor. They call adders the others call too
// (AddTextField, fns 180, 619, 651 and 5409, AddLed 435, AddBuzz 941, AddClock 728) on that frame address, so, a
// reading, the adders and GetForm are members of a class whose constructor is inline, CMTFormBuilderBase, and the
// builder the others build is of a class over it whose constructor is out of line, CMTFormBuilder, whose `= default`
// constructor in cmtformbuilder.cpp is fn 203's body. Over CMTFormBuilderBase, 10214, 5341, 5343 and 10676 match (1150
// and 4633 are not measured over it). Measured with pnpm wasm score in the whole link, over CMTFormBuilderBase and then
// with only the four screens' builders made CMTFormBuilders: 10214 21 over 299 rows and 128 over 307, 5341 36 over 450
// and 86 over 458, 5343 66 over 950 and 145 over 962, 10676 51 over 507 and 96 over 510; units 104's, 165's and 161's
// fragments say what the rows are. Chosen: two classes rather than one CMTFormBuilder with a second, inline constructor
// beside the out-of-line one (`explicit CMTFormBuilder(int) {}`, the four screens building `builder(0)`), which gives
// the same objects function by function (cfinalizaoperador.cpp's, caguardainicio.cpp's, caguardainspecao.cpp's,
// csincronismooperador.cpp's and cmtformbuilder.cpp's at the link's compile lines, the class names masked); deriving
// rather than holding the base; GetInteractiveForm, AddInputControl and AddTextFieldUpdate being the derived class's
// (in the target only the builders fn 203 builds use them: 301's 49 callers, 395's 39, 5410 and 652, which hold the
// other two inlined) and AddField the base's (its three callers, 395, 1151 and 5410, take the derived class); m_campos
// being protected; the base declaring no constructor. The other naming, CMTFormBuilder as the base and a new name for
// the derived class (as api::CInteractiveFormBuilder derives from api::CFormBuilder), renames the class of every
// builder fn 203 builds; this one renames the members of the six callers' class.
//
// Each adder's name, and which overloads share a name, are chosen from the field it builds. CTextSource goes by value: the
// adders release its reference at their end, and a class holding a libc++ shared_ptr is trivial-ABI here, so the callee
// destroys it. std::function goes by value by choice: a const reference gives the same rows, since the caller destroys
// either. The alignments of the two overloads that default it are read from fns 5409 and 5419, which store 0 as a constant
// and have no parameter for it. The field's std::shared_ptr is the result of the text adders (each takes the address of
// its result) and they push it through the out-of-line push_back, fn 1400; the four other adders return nothing and clang
// inlines push_back, whose reference argument is then a local (src/units/31-uenux2-cformbuilder.mk).
//
// GetForm (fn 1694) and GetInteractiveForm (fn 301) build the form of the fields added with a api::CPreShowClearMT,
// name it and clear the vector. Each public one calls a private overload that takes the pre-show: binaryen inlines
// that overload into its one caller, which the second stack frame in the middle of fns 1694 and 301 shows, and clang
// leaves it out of line in the object. The names, the overloads and their parameters are chosen.
//
// AddField (fn 3674) moves a field into the vector at this + 0: its body is vector::emplace_back with the slow path, and
// its target callers are AddInputControl (fn 395), fn 1151 and fn 5410. 1151 is another object's code: its control
// block's vtable (@1588176) lies in app/vota/operador/outrasopcoes/cescolheopcao.cpp's data, where it is written
// (vota::AdicionaCampoNumerico, unit 121). AddField takes the field by rvalue reference: 395 and 1151 release the temporary SharedField after
// the call, which a by-value shared_ptr, trivial-ABI here, would leave to the callee. AddInputControl builds an
// api::CInputFieldControl<IScreenMT> with `new` (its block is a __shared_ptr_pointer, @1580708) and returns nothing:
// 395's wasm type has no result pointer. Their names, the SharedInput alias, emplace_back rather than push_back, and
// AddInputControl's being a member are chosen. For the membership: api::CInteractiveFormBuilder::AddLabeledInputControl
// (fn 653), a member by its record (1579136), reaches its fields only through CFormBuilder::AddField (fn 426), as
// AddInputControl reaches the vector only through AddField. src/units/31-uenux2-cformbuilder.mk has what was measured.

#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "api/gui/cdatatext.h"
#include "api/gui/cdatatextfmt.h"
#include "api/gui/cinteractiveform.h"
#include "api/gui/cledfieldmt.h"
#include "api/gui/ctextfieldmt.h"
#include "api/gui/ctextsource.h"
#include "api/gui/iform.h"
#include "api/gui/iformfield.h"
#include "api/gui/iinputfield.h"
#include "api/gui/itext.h"
#include "api/gui/ipreshow.h"
#include "api/gui/primitives.h"
#include "api/hwil/iinput.h"

namespace api {

class CMTFormBuilderBase {
public:
    using SharedField = std::shared_ptr<IFormField<IScreenMT>>;

    void AddField(SharedField&& campo);

    SharedField AddTextField(const std::string& texto, const SPoint& posicao, ETextAlignment alinhamento);

    SharedField AddTextField(std::string (*fonte)(), const SPoint& posicao, ETextAlignment alinhamento);

    SharedField AddTextField(std::string (*fonte)(const std::string&), const SPoint& posicao, const std::string& formato,
                             ETextAlignment alinhamento);

    SharedField AddTextField(CTextSource fonte, const SPoint& posicao, const std::string& formato,
                             ETextAlignment alinhamento);

    SharedField AddTextField(CTextSource fonte, const SPoint& posicao, ETextAlignment alinhamento = ALINHAMENTO_ESQUERDA);

    SharedField AddTextField(std::function<std::string()> fonte, const SPoint& posicao,
                             ETextAlignment alinhamento = ALINHAMENTO_ESQUERDA);

    void AddLed(ELedOperacao operacao);

    void AddBeep(int vezes);

    void AddBuzz(int primeiro, int segundo);

    void AddClock(const SPoint& posicao);

    std::shared_ptr<IForm<IScreenMT>> GetForm(const std::string& nome);

    template <typename FONTE>
    SharedField AddTextField(FONTE fonte, const SPoint& posicao);

    // A text a source of the caller's type gives through a format, CDataTextFmt<FONTE> with CDataTextFmt's default
    // alignment: its instances over the anonymous CComparecimentoMesariosDS of cpedetitulomesarioinicial.cpp,
    // cpedetitulomesariofinal.cpp and cpedetitulomesariovotacao.cpp are inlined into the constructors fn 10388 holds,
    // each in the constructor's frame (the format "{:02}" stored into the new CDataTextFmt, a CTextFieldMT over it,
    // fn 1262, and vector::push_back in place). Its name, and its being a member template beside the one above, are
    // chosen.
    template <typename FONTE>
    SharedField AddTextField(FONTE fonte, const SPoint& posicao, const std::string& formato);

protected:
    std::vector<SharedField> m_campos;

private:
    std::shared_ptr<IForm<IScreenMT>> GetForm(const std::shared_ptr<IPreShow<IScreenMT>>& preShow, const std::string& nome);

    SharedField AddTextField(const SharedIText& texto, const SPoint& posicao);
};

/**
 * Monta os formulários da tela MT.
 */
class CMTFormBuilder : public CMTFormBuilderBase {
public:
    using SharedInput = std::shared_ptr<IInputField<IScreenMT>>;

    CMTFormBuilder();

    void AddInputControl();

    // The control field built with std::make_shared (its block's vtable, @1580748, beside AddInputControl()'s
    // __shared_ptr_pointer one, @1580708, in this file's data): fn 5410 holds it inlined by binaryen, behind a 16-byte
    // frame of its own that keeps the SharedField passed to AddField. Its name, the overload and its parameter are
    // chosen after api::CInteractiveFormBuilder::AddInputControl(int).
    void AddInputControl(int teclas);

    std::shared_ptr<CInteractiveForm<IScreenMT, IInputMT>> GetInteractiveForm(const std::string& nome, bool limpaTeclado);

    // A text a source gives through a CDataTextFmt, in an api::CTextFieldUpdateMT that redraws it as it changes: its
    // instance over api::CTextSource is held inlined by binaryen in fn 652, behind a 16-byte frame of its own. It pushes a
    // copy of the field into m_campos with vector::emplace_back in place and releases the field before it returns, so it
    // is a member and returns nothing. Defined in app/vota/operador/comum/telasoperador.cpp, where CTextFieldUpdateMT is
    // complete; src/units/51-uenux2-ctextfieldupdatemt.mk says why a template there. Its name (after
    // api::CFormBuilder::AddTextFieldUpdate) and its parameters' order are chosen.
    template <typename FONTE>
    void AddTextFieldUpdate(FONTE fonte, const SPoint& posicao, const std::chrono::milliseconds& intervalo,
                            const std::string& formato);

private:
    std::shared_ptr<CInteractiveForm<IScreenMT, IInputMT>> GetInteractiveForm(const std::shared_ptr<IPreShow<IScreenMT>>& preShow,
                                                                          const std::string& nome, bool limpaTeclado);
};

// The adder of a text a source of the caller's type gives, CDataText<FONTE> with CDataText's default alignment: its
// instance over vota::CEscolheOpcao::COpcaoDS is held inlined by binaryen in fn 2753, behind a 48-byte frame of its own
// (the source's copy at +8, the text at +40), where clang leaves it out of line, linkonce; it builds the CDataText, a
// CTextFieldMT over it (fn 1262) and pushes the field through push_back (fn 1400), the private AddTextField's statements,
// which are written in place because that one is defined in cmtformbuilder.cpp. Its name and its being a member
// template with two parameters (an overload with an alignment would take the calls with a string literal from the
// non-template overloads) are chosen.
template <typename FONTE>
CMTFormBuilderBase::SharedField CMTFormBuilderBase::AddTextField(FONTE fonte, const SPoint& posicao)
{
    const SharedIText text(new CDataText<FONTE>(fonte));
    SharedField campo(new CTextFieldMT(posicao, text));
    m_campos.push_back(campo);
    return campo;
}

template <typename FONTE>
CMTFormBuilderBase::SharedField CMTFormBuilderBase::AddTextField(FONTE fonte, const SPoint& posicao, const std::string& formato)
{
    const SharedIText text(new CDataTextFmt<FONTE>(fonte, formato));
    SharedField campo(new CTextFieldMT(posicao, text));
    m_campos.push_back(campo);
    return campo;
}

} // namespace api
