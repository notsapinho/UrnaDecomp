// api::CUePrinterError's constructors. The reconstruction's file: no record names it.
//   10257  CUePrinterError(EUePrinterError, std::string, std::source_location)
// The three-argument constructor has one caller, CUeCodedPrinterError's constructor, and binaryen inlines both into
// api::IImpressoraRelatorios::SetStyle (fn 10881). eueprintererror.h says why it is defined here and not in the class.

#include "api/hwil/eueprintererror.h"

#include <utility>

namespace api {

CUePrinterError::CUePrinterError(EUePrinterError codigo, std::string mensagem, std::source_location local)
    : CBaseError(codigo, std::move(mensagem), local)
    , m_detalhe("")
    , m_complemento("")
{
}

CUePrinterError::CUePrinterError(EUePrinterError codigo, std::string mensagem, std::string detalhe,
                                 std::source_location local)
    : CBaseError(codigo, std::move(mensagem), local)
    , m_detalhe(std::move(detalhe))
    , m_complemento("")
{
}

} // namespace api
