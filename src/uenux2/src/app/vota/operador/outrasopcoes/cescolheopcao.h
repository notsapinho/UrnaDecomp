#pragma once

#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "app/comum/cappstate.h"

namespace api {
class IScreenMT;
class IInputMT;
class CMTFormBuilder;
struct SPoint;
template <typename MEDIA>
class IInputField;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// RTTI: vota::CEscolheOpcao, an si_class of comum::CAppState (stub file cescolheopcao.cpp), and the name of its nested
// data source, which only the RTTI of api::CDataText<vota::CEscolheOpcao::COpcaoDS> gives (fn 2753 builds that text).
//
// CEscolheOpcao (vtable @1587996 [2752, 10691, 10690, 7480, 1661, 218, 425, 10689, 425]): it overrides the destructors
// (slots 0 and 1, fns 2752 and 10691), StartState (slot 2, fn 10690, records cescolheopcao.cpp:150 to 152) and
// ProcessInput (slot 7, fn 10689; src/units/121-uenux2-datasources.mk has what its match rests on).
// A singleton: GetInst (fn 2753) creates the object under a static std::mutex (@1905284, destroyed at exit by fn
// 10696) and keeps it in a static std::unique_ptr (@1905308, by fn 10697). The constructor, which binaryen inlines into
// GetInst behind a 272-byte frame of its own, passes comum::CAppState::EVENTO_ENTRADA (2) to the base's, fills the map
// and builds the form. The destructor is out of line: the deleting one (fn 10691) calls it, drops its result and frees
// `this`. It releases the std::shared_ptr at +24, then destroys the std::map at +12 (fn 3630, the tree's recursive
// destroy), and stores no vptr first: a final class.
//
// The layout: +12 a std::map whose nodes fn 2753 builds 64 bytes long, an int key at +16 (its search compares it signed
// with 1, 2 and 3), and at +24 a SOpcao, 40 bytes (fn 2750 builds it from an int and a COpcaoDS: the int at +24, the
// COpcaoDS at +32, its int and its std::function, which fn 3630 destroys at +40, the only member of the node it
// destroys); +24 the form from api::CMTFormBuilder::GetInteractiveForm (fn 301). The key is the option's number on the
// screen and SOpcao's int a code fn 2753 passes as a constant (1 to 4) where the number can be 3 or 4. The member names,
// SOpcao's name and its being a class of its own (fn 2750 takes the int by value, which std::pair's constructors, all
// templates over forwarding references, do not) and the form's type beyond what its destruction shows are chosen.
//
// COpcaoDS: the layout is what the bodies give, 32 bytes. fn 2753 allocates its CDataText as 40 bytes and stores the
// source's int at +8 and a std::function at +16 (the copy of a std::function's buffer and target pointer); fn 10685,
// CDataText<COpcaoDS>::GetText, formats "{}-{}" with that int, as an int (argument type 3), and the std::string the
// std::function returns (type 13, called through slot 6 of its target, a bad_function_call when it is empty); the
// CDataText's D2 and D0 (fns 10688, 10686) destroy the std::function at +16. fn 2751 is its constructor: it stores the
// int and moves the std::function in. The members' names and their being public are chosen. The call operator is
// defined in cescolheopcao.cpp, a choice: src/units/121-uenux2-datasources.mk has the other form that gives the same
// GetText.
class CEscolheOpcao final : public comum::CAppState {
public:
    class COpcaoDS {
    public:
        COpcaoDS(int numero, std::function<std::string()> texto);

        std::string operator()() const;

        int m_numero;
        std::function<std::string()> m_texto;
    };

    class SOpcao {
    public:
        SOpcao(int codigo, COpcaoDS ds);

        int m_codigo;
        COpcaoDS m_ds;
    };

    virtual ~CEscolheOpcao() override;

    static CEscolheOpcao& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CEscolheOpcao();

    // The CONFIRMA branch of ProcessInput: a function of its own that binaryen inlines into fn 10689, its one caller (a
    // 32-byte frame of its own there). It reads m_form and m_opcoes; its being a member, its name, its being private
    // and its result type (the next state, or null to stay) are chosen.
    comum::CAppState* ConfirmaOpcao();

    static std::unique_ptr<CEscolheOpcao> s_inst;
    static std::mutex s_mutex;

    std::map<int, SOpcao> m_opcoes;
    std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> m_form;
};

// fn 1151: builds an api::CInputFieldMT over a new api::CNumberValidation, adds it to the builder through AddField
// (fn 3674) and returns it. Its copy is cescolheopcao.cpp's object: the control block it alone instantiates
// (__shared_ptr_pointer<CInputFieldMT*, ...>, @1588176) lies in that object's data. Its name, its being a free function
// declared here, and its parameters' names are chosen: no record, slot or RTTI names it.
std::shared_ptr<api::IInputField<api::IScreenMT>> AdicionaCampoNumerico(api::CMTFormBuilder& builder, size_t tamanho,
                                                                       bool confirmaAoCompletar, const api::SPoint& posicao);

} // namespace vota
