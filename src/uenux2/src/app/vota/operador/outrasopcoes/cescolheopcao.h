#pragma once

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// RTTI: vota::CEscolheOpcao, an si_class of comum::CAppState (stub file cescolheopcao.cpp), and the name of its nested
// data source, which only the RTTI of api::CDataText<vota::CEscolheOpcao::COpcaoDS> gives (fn 2753 builds that text).
//
// CEscolheOpcao (vtable @1587996 [2752, 10691, 10690, 7480, 1661, 218, 425, 10689, 425]): it overrides the destructors
// (slots 0 and 1, fns 2752 and 10691), StartState (slot 2, fn 10690, records cescolheopcao.cpp:150 to 152) and
// ProcessInput (slot 7, fn 10689); the last two are pending (src/units/121-uenux2-datasources-pending.cpp says what each
// waits for). A singleton: fn 2753 holds GetInst and the constructor inlined, allocates 32 bytes, passes
// comum::CAppState::EVENTO_ENTRADA (2) to the base's constructor and keeps the object in a static std::unique_ptr
// (@1905308); it calls fn 1151, which no form has matched, so GetInst and the constructor are not written. The destructor
// is out of line: the deleting one (fn 10691) calls it, drops its result and frees `this`. It releases the
// std::shared_ptr at +24, then destroys the std::map at +12 (fn 3630, the tree's recursive destroy), and stores no vptr
// first: a final class.
//
// The layout: +12 a std::map whose nodes fn 2753 builds 64 bytes long, an int key at +16 (its search compares it signed
// with 1, 2 and 3), and at +24 a copy of a 40-byte value fn 2750 builds from an int and a COpcaoDS (an int at +24, the
// COpcaoDS at +32: its int and its std::function, which fn 3630 destroys at +40, the only member of the node it
// destroys); +24 the form from api::CMTFormBuilder::GetInteractiveForm (fn 301). std::pair<int, COpcaoDS> as the mapped
// type, the member names and the form's type beyond what its destruction shows are chosen.
//
// COpcaoDS: the layout is what the bodies give, 32 bytes. fn 2753 allocates its CDataText as 40 bytes and stores the
// source's int at +8 and a std::function at +16 (the copy of a std::function's buffer and target pointer); fn 10685,
// CDataText<COpcaoDS>::GetText, formats "{}-{}" with that int, as an int (argument type 3), and the std::string the
// std::function returns (type 13, called through slot 6 of its target, a bad_function_call when it is empty); the
// CDataText's D2 and D0 (fns 10688, 10686) destroy the std::function at +16. The members' names, their being public and
// the class's having no constructor of its own are chosen: no body shows a constructor. The call operator is defined in
// cescolheopcao.cpp, a choice: src/units/121-uenux2-datasources.mk has the other form that gives the same GetText.
class CEscolheOpcao final : public comum::CAppState {
public:
    class COpcaoDS {
    public:
        std::string operator()() const;

        int m_numero;
        std::function<std::string()> m_texto;
    };

    virtual ~CEscolheOpcao() override;

    static CEscolheOpcao& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CEscolheOpcao();

    std::map<int, std::pair<int, COpcaoDS>> m_opcoes;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

} // namespace vota
