#pragma once

#include <memory>
#include <string>

#include "api/gui/ipreshow.h"
#include "api/gui/primitives.h"

namespace api {
class IScreen;
class IInputKbd;
class CFormBuilder;
class CInteractiveFormBuilder;
template <typename MEDIA>
class IForm;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// RTTI: CPreShowFormVota is an si_class of api::IPreShow<api::IScreen>, vtable @1532600 [174, 144, 7707], and
// CPreShowProgressBar an si_class of it, vtable @1536544 [174, 144, 13550]. Slot 2 of the first, PreShow (fn 7707), is
// written in cpreshowformvota.cpp, where it is the key function; the second's, PreShow (fn 13550), is its key function
// in app/vota/eleitor/comum/cpreshowprogressbar.cpp (src/units/391-uenux2-cpreshowprogressbar.mk).
// Its constructor is implicit: the CriaTela* screens of ctelasvota.cpp store its vptr inside their std::make_shared (no
// call), which an implicit or inline constructor gives (the declared, undefined one this head had did not link).
// Neither class is final: their blocks' __on_zero_shared go through the vtable (fns 172 and 411). The path is chosen,
// under app/vota/comum: no record names either class, and the header holds both because the second derives from the
// first; it is not beside cpreshowprogressbar.cpp, whose place the second's vtable gives (after
// vota::impl::CPoliticaExecucaoEleitor's typeinfo @1536388, not beside CPreShowFormVota's).
class CPreShowFormVota : public api::IPreShow<api::IScreen> {
public:
    void PreShow(api::IScreen& tela) override;

protected:
    // Fn 4620 (229 B, 2 callers): the text api::CApplication::GetDescricaoModo (fn 5564) gives, when it is not empty,
    // drawn at a point as an api::CFixedText with alignment 2, in the font {20, 1}, colour 3 over 0 (api::IScreen's
    // slot 19). Its callers are CPreShowFormVota::PreShow (fn 7707, at {340, 5}) and CPreShowProgressBar's slot 2 (fn
    // 13550, at {320, 30}), each after the screen's slot 4 with 1. The point is taken by value: each caller stores it
    // twice (read as the temporary and the byval copy whose address it passes; 7707 at +12 and +8, 13550 at +156 and
    // +8), which a `const api::SPoint&` parameter does not give (one store; measured, cpreshowformvota.cpp's object).
    // Placement: no record names it. CFixedText, a class with no key function, has its vtable (@1532640) right after
    // the typeinfos of CPreShowFormVota and api::IPreShow<api::IScreen> and before the vtable of the block fn 576
    // builds, so this object is CFixedText's first user (docs/how-to-decompile.md step 3, rule 2), and 4620 is the
    // function here that builds one (a reading). It is external, its caller 13550 being in another object (the reading
    // above). A member of CPreShowFormVota that reads no state, so each caller passes `this`, which binaryen's
    // dead-argument elimination drops (the target's type is (i32 i32)->()). That it takes `this` is measured: in the
    // target 13550's vector end holds the local of 13550's own `this`, which clang's register coloring gives a later
    // value only once `this` has a live range (a reading), and with this function free 13550 scores 297 over 1028 rows,
    // as this member, the rest unchanged, 49 over 1008 (src/units/391-uenux2-cpreshowprogressbar.mk has both links). A
    // free function that takes the object passes it too, with the same code, 4620's symbol aside (the two objects'
    // disassembly compared): the member form, its access, its name and its parameters' names are chosen.
    void DesenhaDescricaoModo(api::IScreen& tela, api::SPoint posicao);
};

class CPreShowProgressBar : public CPreShowFormVota {
public:
    void PreShow(api::IScreen& tela) override;
};

// Fn 576 (144 B, 16 callers): the interactive form of the builder's fields, named, with a new CPreShowFormVota as its
// pre-show (api::CInteractiveFormBuilder::GetInteractiveForm, fn 554, with true as its last argument). It builds the
// std::shared_ptr<api::IPreShow<api::IScreen>> from the pointer (the __shared_ptr_pointer block, vptr @1532684), and
// that block's vtable lies right after CPreShowFormVota's typeinfo. A reading: the object that first builds the block
// emits its vtable, so the function is in the class's file (fn 886, the other builder, could be too). No record names
// it: a free function of vota, its name and its parameters' are chosen.
std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> GetFormularioInterativo(
    api::CInteractiveFormBuilder& builder, const std::string& nome);

// Fn 886 (21 B, 11 callers): the same over api::CFormBuilder, the form (api::IForm<api::IScreen>, fn 5550's) of the
// builder's fields, named, with a new CPreShowFormVota as its pre-show. It builds the block fn 576 builds, whose vtable
// lies after CPreShowFormVota's typeinfo, which places it in this file as fn 576 is placed (a reading). Its target body
// is a thunk of binaryen's fn 6117, which binaryen forms from it and fn 11140 (the same with an
// api::CPreShowClearScreen: they pass fn 6117 the control block's and the object's vptrs, @1532684 and @1532608 here),
// in our link too since fn 11140 keeps its body there (src/units/165-uenux2-app-vota-execucao.mk). No record names it:
// a free function of vota beside fn 576, its name and its parameters' are chosen.
std::shared_ptr<api::IForm<api::IScreen>> GetFormulario(api::CFormBuilder& builder, const std::string& nome);

} // namespace vota
