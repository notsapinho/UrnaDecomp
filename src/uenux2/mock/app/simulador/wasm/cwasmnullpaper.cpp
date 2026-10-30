#include "cwasmnullpaper.h"

namespace simulador {

void CWasmNullPaper::PrintText(const api::IText&, EStyle)
{
}

void CWasmNullPaper::Cut()
{
}

void CWasmNullPaper::NewLine()
{
}

void CWasmNullPaper::StartReportFile(const std::string&)
{
}

void CWasmNullPaper::EndReportFile()
{
}

void CWasmNullPaper::PrintFile(const std::string&, const api::ISigVerifier&, const std::string&, const std::string&)
{
}

void CWasmNullPaper::PrintFile(const std::string&, const api::ISigVerifier&, std::shared_ptr<api::IForm<api::IPaper>>,
                               const std::string&, const std::string&)
{
}

int CWasmNullPaper::Slot9()
{
    return 0;
}

void CWasmNullPaper::EndPrintFile()
{
}

void CWasmNullPaper::Slot11(int, int, int)
{
}

void CWasmNullPaper::PrintQRCode(const std::vector<uebyte>&, size_t, uebyte)
{
}

int CWasmNullPaper::Slot13(int)
{
    return 1;
}

void CWasmNullPaper::Slot14(int, int)
{
}

} // namespace simulador
