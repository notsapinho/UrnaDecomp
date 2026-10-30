#pragma once

#include "api/gui/ipaperrelatorios.h"

namespace simulador {

// Recovered: RTTI names the class (an si_class of api::IPaperRelatorios, vtable @1530564, 15 slots), the wasm build's
// paper, which prints nothing. The object is 4 bytes, the vptr only (simulador's init, fn 8302, into which the
// constructor is inlined, allocates 4 and stores the vptr). The destructors (slots 0 and 1) are the shared empty bodies
// 174 and 144, an implicit destructor. Slots 7 and 8 have bodies of their own (fns 8372, 8371); the others are the
// shared empty bodies of their wasm types, or return 0 (slot 9) or 1 (slot 13); which of them are defined in the class
// is chosen, here all in the .cpp. `final` gives the same object.
class CWasmNullPaper : public api::IPaperRelatorios {
public:
    void PrintText(const api::IText& text, EStyle estilo) override;
    void Cut() override;
    void NewLine() override;
    void StartReportFile(const std::string& arquivo) override;
    void EndReportFile() override;
    void PrintFile(const std::string& arquivo, const api::ISigVerifier& verificador, const std::string& titulo,
                   const std::string& via) override;
    void PrintFile(const std::string& arquivo, const api::ISigVerifier& verificador,
                   std::shared_ptr<api::IForm<api::IPaper>> formulario, const std::string& titulo,
                   const std::string& via) override;
    int Slot9() override;
    void EndPrintFile() override;
    void Slot11(int a, int b, int c) override;
    void PrintQRCode(const std::vector<uebyte>& imagem, size_t tamanho, uebyte escala) override;
    int Slot13(int a) override;
    void Slot14(int a, int b) override;
};

} // namespace simulador
