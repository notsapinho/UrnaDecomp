#pragma once

#include <string>

#include "api/util/cdatetime.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "ecourna/app/dados/resultadournacadastro/capresentacaofotoeleitor.hpp"
#include "ecourna/app/dados/tiposbasicos.hpp"

namespace vota::impl {

// Recovered: the virtual destructor and the 29 members of slots 2 to 30, from the vtable of
// vota::impl::CInformacaoThreadOperador (vtable @1590108), the one class that implements it, and GetInst (record
// cinformacaothreadoperador.cpp:554, target fn 599). The target has this class's typeinfo and no vtable: every member
// is inline or pure. Four members are named by their records (slots 23 to 26, cinformacaothreadoperador.cpp:474 to
// :504), with the return types and const those records spell. No record, symbol or string names the other 25: their
// names (SlotN, after the vtable slot), their const (on the ones whose target body only reads) and their parameter and
// return types (from the wasm signatures and what the bodies store or return) are choices, as is the EEstado type and
// its enumerators. No record names this header's file: the interface goes beside its implementation's file.
class IInformacaoThreadOperador {
public:
    // the three values slots 9 to 15 test, set and return (fns 10576 ... 2587); not in the target
    enum EEstado {
        Estado0,
        Estado1,
        Estado2,
    };

    virtual ~IInformacaoThreadOperador() = default;

    virtual void Slot2() = 0;
    virtual bool Slot3() const = 0;
    virtual bool Slot4() const = 0;
    virtual bool Slot5() const = 0;
    virtual bool Slot6() const = 0;
    virtual void Slot7(bool valor) = 0;
    virtual std::string Slot8() const = 0;
    virtual bool Slot9() const = 0;
    virtual bool Slot10() const = 0;
    virtual bool Slot11() const = 0;
    virtual void Slot12() = 0;
    virtual void Slot13() = 0;
    virtual void Slot14() = 0;
    virtual EEstado Slot15() const = 0;
    virtual std::string Slot16() const = 0;
    virtual void Slot17() = 0;
    virtual api::CDateTime Slot18() const = 0;
    virtual bool Slot19() const = 0;
    virtual void Slot20() = 0;
    virtual void Slot21(const std::string& identidade) = 0;
    virtual void Slot22(ecourna::app::dados::ETipoIdentificadorEleitor tipo) = 0;
    virtual std::string GetIdentidadeDigitada() const = 0;
    virtual ecourna::app::dados::ETipoIdentificadorEleitor GetTipoIdentidadeDigitada() const = 0;
    virtual comum::md::CEleitorIdentidade GetIdentidadeEleitor() const = 0;
    virtual comum::md::CEleitorIdentidade GetIdentidadePrincipalEleitor() const = 0;
    virtual void Slot27() = 0;
    virtual void Slot28() = 0;
    virtual void Slot29(ecourna::app::dados::CApresentacaoFotoEleitor::EResultado resultado) = 0;
    virtual ecourna::app::dados::CApresentacaoFotoEleitor Slot30() const = 0;

    static IInformacaoThreadOperador& GetInst();
};

} // namespace vota::impl
