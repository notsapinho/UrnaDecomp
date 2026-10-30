#pragma once

// api::EUePrinterError, api::CUePrinterError and api::CUeCodedPrinterError. RTTI names the two classes: CUePrinterError
// is an si_class of CBaseError<api::EUePrinterError, SErrorLimits{4450, 4650}> (typeinfo 1530740), and
// CUeCodedPrinterError an si_class of it (typeinfo 1583832). No record names this file or a member: the header's name
// is chosen, after the tree's other error headers (eueioerror.h, eueguierror.h), beside iimpressora.h, whose throws use
// it.
//
// The layout is read from the constructors and the destructor. CUePrinterError is the 64 bytes fn 6133 allocates: past
// CError's 40 bytes, two strings at +40 and +52, which the destructor 8351 frees, +52 first. Fn 10257 stores "" in both
// (one byte each at +40, +51, +52 and +63, where a default-constructed std::string gives three i64 zeros), and the
// constructor inlined into fn 10881 moves its third argument into +40 and stores "" in +52. CUeCodedPrinterError is the
// 68 bytes fn 10881 allocates: one int more at +64, stored 2. Nothing in the target reads +40, +52 or +64, so the
// members' names, the type of +64 and what the strings hold are chosen, as are the arguments that carry the constants
// 4468 and 2: binaryen folds them, so a literal in the constructor gives the same bytes.
//
// The destructors are implicit: fn 4910, the D0, holds the D2's body. CUeCodedPrinterError adds a trivial member, so
// its vtable's slot 0 holds the same D2 and its slot 1 a D0 that binaryen merges with CUePrinterError's (4910 fills a
// table slot in each vtable). The class is not final: 8351 begins with its vptr store.
//
// Fn 10881 holds three stack prologues, so binaryen inlined two functions into it (docs/reference/facts/reading.md
// §R10), each with one caller: CUeCodedPrinterError's constructor and, inside it, CUePrinterError's three-argument one.
// So clang saw neither inlined, and the three-argument constructor is defined in another TU than
// CUeCodedPrinterError's; eueprintererror.cpp is a chosen path for it. Where 10257 and CUeCodedPrinterError's
// constructor are defined is chosen (src/units/80-uenux2-cwasmnullprinter.mk lists what was measured).

#include <source_location>
#include <string>
#include <utility>

#include "ecourna/api/exception/cbaseerror.hpp"

namespace api {

// The enumerators' names are chosen from what their throw sites do; the target holds only the numbers.
enum EUePrinterError {
    EUE_PRINTER_DISABLE_SENSORS_NAO_SUPORTADO = 4466, // api::IImpressora::DisableSensors, "Not supported ({})"
    EUE_PRINTER_ENABLE_SENSORS_NAO_SUPORTADO = 4467,  // api::IImpressora::EnableSensors, "Not supported ({})"
    EUE_PRINTER_ESTILO_INVALIDO = 4468,               // api::IImpressoraRelatorios::SetStyle, "Invalid style"
};

class CUePrinterError
    : public ecourna::api::exception::CBaseError<EUePrinterError, ecourna::api::exception::SErrorLimits{4450, 4650}> {
public:
    CUePrinterError(EUePrinterError codigo, std::string mensagem,
                    std::source_location local = std::source_location::current());
    CUePrinterError(EUePrinterError codigo, std::string mensagem, std::string detalhe,
                    std::source_location local = std::source_location::current());

private:
    std::string m_detalhe;
    std::string m_complemento;
};

class CUeCodedPrinterError : public CUePrinterError {
public:
    CUeCodedPrinterError(EUePrinterError codigo, std::string mensagem, std::string detalhe, int erro,
                         std::source_location local = std::source_location::current())
        : CUePrinterError(codigo, std::move(mensagem), std::move(detalhe), local)
        , m_erro(erro)
    {
    }

private:
    int m_erro;
};

} // namespace api
