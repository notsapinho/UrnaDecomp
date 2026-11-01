#pragma once

// api::CFormBuilder (/home/rubio/tse/uenux2/src/api/gui/cformbuilder.cpp, the file of the records of AddStatusHeader and
// GetLabeledKeyPos). The records name the class, those two members and, in app/vota/eleitor/comum/ctelasvota.cpp, its
// passing by reference; the header's path follows the .cpp. The layout is a reading: fn 203, the constructor, zeroes 12
// bytes, and fn 426 walks a vector of two-word elements at this + 0, so the class holds the fields it has built in one
// std::vector. Its destructor is implicit: the callers destroy the vector in line. Fn 203 stays out of line in the target,
// with 88 callers and 18 bytes, which clang would inline from a header, so the constructor is defined in the .cpp. No
// record names an adder: every adder's name, and which overloads share a name, are chosen from the field each builds.
//
// GetForm (fn 5550) builds the api::IForm<IScreen> of the fields added, names it, and clears the vector: its name and
// its parameters are chosen. m_campos is protected because api::CInteractiveFormBuilder (cinteractiveformbuilder.h)
// builds its forms from it, a choice that goes with deriving that class.
//
// AddStatusHeader (fn 502, records cformbuilder.cpp 292:30 and 305:24) adds up to four fields, one per bit of its
// argument: 1 the date and time, 8 the battery's charge, 4 the battery's icon, 2 the mode's text. RTTI types the
// argument unsigned int (CDataText<api::CFormBuilder::AddStatusHeader(unsigned int)::$_0>) and the record spells it
// StatusHeaderFields. The alias's being a member, and the enumerators and their names, are chosen; the values are the
// bits the body tests.
//
// The two AddTextFieldUpdate templates: fn 3058 is the first's instance over std::string (*)(const std::string &),
// called by 502 and 7787 (vota::CTelasVota's constructor); the second's instance over 502's lambda is inlined into
// 502. That 3058 is linkonce, an inline or template definition, is evidence of two kinds. Its vtables (CDataTextFmt
// over that pointer, @1539160, and the control blocks of it and of CTextFieldUpdate, @1539120 and @1539196) lie among
// the data of app/vota/eleitor/comum/ctelasvota.cpp, not of cformbuilder.cpp: the kept copy is the first object's to
// emit them. And 502 tests the format string's long flag before freeing it after its call of 3058, where 502 with
// 3058 a plain member of cformbuilder.cpp frees it with no test (measured in the link); that clang drops the test
// because it infers the callee's attributes, and infers none for a linkonce one, is a reading. Templates rather than
// plain inline members, the names and the parameters' order beyond the wasm's are chosen.

#include <chrono>
#include <memory>
#include <string>
#include <vector>

#include "api/gui/cdatatext.h"
#include "api/gui/cdatatextfmt.h"
#include "api/gui/ctextfieldupdate.h"
#include "api/gui/iform.h"
#include "api/gui/iformfield.h"
#include "api/gui/iimage.h"
#include "api/gui/ipreshow.h"
#include "api/gui/itext.h"
#include "api/gui/primitives.h"

namespace api {

/**
 * Monta os formulários da interface.
 */
class CFormBuilder {
public:
    using SharedField = std::shared_ptr<IFormField<IScreen>>;

    using StatusHeaderFields = unsigned int;

    enum : StatusHeaderFields {
        STATUS_DATA_HORA = 1,
        STATUS_MODO = 2,
        STATUS_ICONE_BATERIA = 4,
        STATUS_CARGA_BATERIA = 8,
    };

    CFormBuilder();

    void AddField(SharedField campo);

    SharedField AddTextField(const std::string& texto, const SPoint& posicao, const SFont& fonte,
                             ETextAlignment alinhamento, TColor corTexto, TColor corFundo);

    SharedField AddTextField(std::string (*fonte)(), const SPoint& posicao, const SFont& font, ETextAlignment alinhamento);

    // a CTextFieldBlinking over a CFixedText of texto, in the colours 2 and 3 over 1: target fn 1265. The name is chosen,
    // and so is having the colours in the body rather than as parameters every caller passes the same
    SharedField AddBlinkingTextField(const std::string& texto, const SPoint& posicao, const SFont& fonte,
                                     ETextAlignment alinhamento);

    SharedField AddDoubleLineField(std::string (*fonte)(), const SPoint& linha1, const SPoint& linha2, TPosition maxX,
                                   const SFont& font, TColor corFundo);

    template <typename FONTE>
    SharedField AddTextFieldUpdate(FONTE fonte, const SPoint& posicao, const std::chrono::milliseconds& intervalo,
                                   const SFont& font, const std::string& formato, ETextAlignment alinhamento)
    {
        const auto text = std::make_shared<CDataTextFmt<FONTE>>(fonte, formato, alinhamento);
        SharedField campo = std::make_shared<CTextFieldUpdate>(posicao, text, intervalo, font, static_cast<TColor>(2),
                                                               static_cast<TColor>(1));
        AddField(campo);
        return campo;
    }

    template <typename FONTE>
    SharedField AddTextFieldUpdate(FONTE fonte, const SPoint& posicao, const std::chrono::milliseconds& intervalo,
                                   const SFont& font, ETextAlignment alinhamento)
    {
        const auto text = std::make_shared<CDataText<FONTE>>(fonte, alinhamento);
        SharedField campo = std::make_shared<CTextFieldUpdate>(posicao, text, intervalo, font, static_cast<TColor>(2),
                                                               static_cast<TColor>(1));
        AddField(campo);
        return campo;
    }

    SharedField AddImage(SharedIImage imagem, const SPoint& posicao);

    SharedField AddLine(const SPoint& inicio, const SPoint& fim, TColor cor);

    SharedField AddFill(const SPoint& canto, const SPoint& oposto, TColor cor);

    SharedField AddRect(const SPoint& canto, const SPoint& oposto);

    void AddStatusHeader(StatusHeaderFields campos);

    static SPoint GetLabeledKeyPos(const SRect& area, ETextAlignment alinhamento, TPosition deslocamento);

    std::shared_ptr<IForm<IScreen>> GetForm(const std::shared_ptr<IPreShow<IScreen>>& preShow, const std::string& nome);

protected:
    std::vector<SharedField> m_campos;

private:
    SharedField AddRect(const SRect& rect);

    std::string GeraNome(const IFormField<IScreen>& campo) const;
};

} // namespace api
