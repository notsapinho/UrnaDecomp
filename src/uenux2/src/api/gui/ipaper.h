#pragma once

// api::IPaper, the paper the report forms print on. No record names its header, so the file is chosen, beside
// iscreen.h. Its RTTI is a class with no base (typeinfo 1531164, ledger/classes.json); api::IPaperRelatorios derives
// from it, and simulador::CWasmNullPaper from that (vtable @1530564, 15 slots, ledger/vtables.json). IPaper has no
// vtable of its own in the target.
//
// The paper fields' Draw(IPaper&) members call four of its slots through the IPaper they get, so those are IPaper's
// own: slot 2 prints a text (api::CTextFieldPaper::Draw, target fn 10920, passes the field's IText and its EStyle),
// slots 3 and 4 take no argument (api::CCutFieldPaper's Draw 11015 calls slot 3, api::CNewLineFieldPaper's 11012 calls
// slot 4 once per line) and slot 12 takes the three members of a CQRCodeImagePaper::QrcodeData
// (api::CQRCodeImageFieldPaper's Draw 10963). The slots between them are IPaper's too, since a base's come first.
// Slots 13 and 14 could be IPaperRelatorios's: no evidence separates the two, and they are left here. Three more slots
// have callers through api::CPolySingleton<api::IPaperRelatorios>::instance (fn 905). api::CScopedReportFile's
// constructor and destructor, inlined into fn 3654, call slot 5 with a copy of the string of the path the record gives
// the constructor, and slot 6. vota::CImprimirBJust's slot 2 (fn 12068) and five others call slot 7 with a saved
// report's file name, the comum::CSigVerifier fn 1540 builds and two strings, the report's title ("boletim de
// justificativa eleitoral") and its copy. Slot 10 is called by fn 2890 after it prints, which shows no role of its own.
// The others are read from CWasmNullPaper's bodies alone (fns 218, 8371, 340, 1870, 371, 1528): their wasm types, and
// slot 8's third argument, a std::shared_ptr by value that the callee releases (fn 8371). No call in the target has
// slot 8's offset and type, so the element type of that std::shared_ptr and each argument's type beyond its size are
// chosen. The parameter types of slots 5 and 7 are chosen too: the strings could be std::string by value (the caller
// owns such a copy) and the verifier another base of CSigVerifier. The names PrintText, Cut, NewLine, PrintQRCode,
// StartReportFile, EndReportFile and PrintFile are chosen from those callers, and the others are their slots'; no
// record or symbol names any of them.
//
// EStyle is the record's `IPaper::EStyle` (ctextfieldpaper.cpp:23:15). The target's callers of the CTextFieldPaper
// constructor pass 1 and 2; no evidence names the values, so the enumerators are not recovered.

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "ecourna/api/uetypes.hpp"
#include "api/gui/itext.h"

namespace api {

class IImage;
class ISigVerifier;

/**
 * Papel onde os formulários são impressos.
 */
class IPaper {
public:
    /**
     * Estilo do texto impresso.
     */
    enum EStyle {
    };

    virtual ~IPaper() = default;

    /**
     * Imprime o texto de @p text no estilo @p estilo.
     */
    virtual void PrintText(const IText& text, EStyle estilo) = 0;

    virtual void Cut() = 0;
    virtual void NewLine() = 0;
    virtual void StartReportFile(const std::string& arquivo) = 0;
    virtual void EndReportFile() = 0;
    virtual void PrintFile(const std::string& arquivo, const ISigVerifier& verificador, const std::string& titulo,
                           const std::string& via) = 0;
    virtual void Slot8(int a, int b, std::shared_ptr<IImage> imagem, int c, int d) = 0;
    virtual int Slot9() = 0;
    virtual void Slot10() = 0;
    virtual void Slot11(int a, int b, int c) = 0;
    virtual void PrintQRCode(const std::vector<uebyte>& imagem, size_t tamanho, uebyte escala) = 0;
    virtual int Slot13(int a) = 0;
    virtual void Slot14(int a, int b) = 0;
};

} // namespace api
