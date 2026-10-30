#include "cwasmnullprinter.h"

namespace simulador {

int CWasmNullPrinter::Slot0()
{
    return 0;
}

void CWasmNullPrinter::Slot1(int)
{
}

void CWasmNullPrinter::Slot2()
{
}

void CWasmNullPrinter::Slot3()
{
}

void CWasmNullPrinter::Slot8()
{
}

void CWasmNullPrinter::Slot9()
{
}

void CWasmNullPrinter::ApplyStyle(api::ELPStyle style)
{
    m_style = style;
}

int CWasmNullPrinter::Slot13()
{
    return 0;
}

void CWasmNullPrinter::Slot14(int, int, int)
{
}

} // namespace simulador
