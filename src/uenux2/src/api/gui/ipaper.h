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
// (api::CQRCodeImageFieldPaper's Draw 10963). The slots between them are IPaper's too, since a base's come first. Slots
// 13 and 14 could be IPaperRelatorios's: no evidence separates the two, and they are left here. Five more slots have
// callers through api::CPolySingleton<api::IPaperRelatorios>::instance (fn 905). api::CScopedReportFile's constructor
// and destructor, inlined into fn 3654, call slot 5 with a copy of the string of the path the record gives the
// constructor, and slot 6. vota::CImprimirBJust's slot 2 (fn 12068) and five other functions call slot 7 with a saved
// report's file name, the comum::CSigVerifier fn 1540 builds and two strings, the report's title ("boletim de
// justificativa eleitoral") and its copy. vota::CImprimindoBU::ImprimeBU (fn 2890) calls slot 8 with the same arguments
// and, third, a std::shared_ptr by value that the callee releases (fn 8371): RTTI makes it a
// std::shared_ptr<IForm<IPaper>>, since its control block, vptr 1581324, is
// __shared_ptr_pointer<IFormImpressao<IPaperRelatorios>*, shared_ptr<IForm<IPaper>>::__shared_ptr_default_delete<...>>.
// Slot 10 takes no argument, and all eight of its calls, in those seven functions, are the next call on the paper after
// slot 7 or slot 8, inside the bracket of fns 1488 and 1487, which both load "dinamico/imprimindo". Slots 9, 11, 13 and
// 14 have no call on fn 905's result in its eleven callers, or in the fields' Draws fn 11006's result reaches, so they
// are read from CWasmNullPaper's bodies alone (fns 340, 1870, 371, 1528), which give their wasm types: their names are
// their slots', and their arguments' types beyond their size are chosen. So are the parameter types of slots 5, 7 and
// 8, but for slot 8's std::shared_ptr: the strings could be std::string by value (the caller owns such a copy) and the
// verifier another base of CSigVerifier. The names PrintText, Cut, NewLine, PrintQRCode, StartReportFile,
// EndReportFile, PrintFile and EndPrintFile are chosen from those callers, and that slots 7 and 8 are overloads; no
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
};

} // namespace api
