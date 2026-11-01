#pragma once

#include <memory>
#include <string>

#include "api/gui/ipreshow.h"

namespace api {
class IScreen;
class IInputKbd;
class CInteractiveFormBuilder;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// RTTI: CPreShowFormVota is an si_class of api::IPreShow<api::IScreen>, vtable @1532600 [174, 144, 7707], and
// CPreShowProgressBar an si_class of it, vtable [174, 144, 13550]. Recovered: the heads only. Slot 2 is fn 7707 and fn
// 13550, not reconstructed. Neither class is final: their blocks' __on_zero_shared go through the vtable (fns 172 and
// 411). The path is chosen, under app/vota/comum: no record names either class, and the file holds both because the
// second derives from the first.
class CPreShowFormVota : public api::IPreShow<api::IScreen> {
public:
    void PreShow(api::IScreen& tela) override;
};

class CPreShowProgressBar : public CPreShowFormVota {
public:
    CPreShowProgressBar();

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

} // namespace vota
