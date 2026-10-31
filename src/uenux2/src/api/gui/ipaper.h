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
// (api::CQRCodeImageFieldPaper's Draw 10963). The slots between are IPaper's too: a base's come first. Slots 13 and 14
// could be IPaperRelatorios's: no evidence separates the two, and they are left here. Five more slots have callers
// through api::CPolySingleton<api::IPaperRelatorios>::instance (fn 905). api::CScopedReportFile's constructor and
// destructor (in fn 3654) call slot 5 with a copy of its path's string, and slot 6. vota::CImprimirBJust's slot 2 (fn
// 12068) and five other functions call slot 7 with a file name, the comum::CSigVerifier fn 1540 builds and two strings,
// the title ("boletim de justificativa eleitoral") and the copy. vota::CImprimindoBU::ImprimeBU (fn 2890) calls slot 8
// with the same arguments and, third, a std::shared_ptr by value that the callee releases (fn 8371), by RTTI a
// std::shared_ptr<IForm<IPaper>> (its control block's vptr, 1581324, names that type). Slot 10 takes no argument and is
// called once per printed file: eight sites in seven functions. In fns 2890, 12068, 12071 and 12074 it follows the
// file's one slot 8 or 7 call, inside the bracket of fns 1488 and 1487 (both load "dinamico/imprimindo"). In fns 11852,
// 11855 and 11991 (twice) a loop calls slot 7 once per copy of the file, each pass in that bracket, and slot 10 comes
// once after it, outside, also when a count <= 0 skips the loop and no slot 7 call precedes it. No call of slots 9, 11,
// 13 or 14 was found on fn 905's result in its eleven callers or in the Draws fn 11006's result reaches: they keep
// their slots' names, and CWasmNullPaper's bodies (fns 340, 1870, 371, 1528) give only their wasm types, so their
// arguments' types beyond their size are chosen, as are those of slots 5, 7 and 8 but slot 8's std::shared_ptr: the
// strings could be std::string by value (the caller owns a copy), and the verifier comum::CSigVerifier itself, whose
// only RTTI base is api::ISigVerifier (the same bytes). The names PrintText, Cut, NewLine, PrintQRCode,
// StartReportFile, EndReportFile, PrintFile and EndPrintFile are chosen from those callers (EndPrintFile: once per
// file, after its copies), and that slots 7 and 8 are overloads; no record or symbol names them.
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

template <typename MEDIA>
class IForm;
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
    virtual void PrintFile(const std::string& arquivo, const ISigVerifier& verificador,
                           std::shared_ptr<IForm<IPaper>> formulario, const std::string& titulo,
                           const std::string& via) = 0;
    virtual int Slot9() = 0;
    virtual void EndPrintFile() = 0;
    virtual void Slot11(int a, int b, int c) = 0;
    virtual void PrintQRCode(const std::vector<uebyte>& imagem, size_t tamanho, uebyte escala) = 0;
    virtual int Slot13(int a) = 0;
    virtual void Slot14(int a, int b) = 0;

    // Not a slot: api::IForm<IPaper>'s Refresh and Slot7 (fns 11007, 11005) call GetRenderForm where the screens' call
    // it and then their media's Refresh, and do nothing with the paper it returns. So the paper's Refresh is empty and
    // not virtual: a virtual one would be a sixteenth slot, and simulador::CWasmNullPaper's vtable has 15. That it is a
    // member of this class, and its name, are chosen.
    void Refresh() {}
};

} // namespace api
