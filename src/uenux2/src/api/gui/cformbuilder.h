#pragma once

// api::CFormBuilder (/home/rubio/tse/uenux2/src/api/gui/cformbuilder.cpp, the file of the records of AddStatusHeader and
// GetLabeledKeyPos). The records name the class, those two members and, in app/vota/eleitor/comum/ctelasvota.cpp, its
// passing by reference; the header's path follows the .cpp. The layout is a reading: fn 203, the constructor, zeroes 12
// bytes, and fn 426 walks a vector of two-word elements at this + 0, so the class holds the fields it has built in one
// std::vector. Its destructor is implicit: the callers destroy the vector in line. Fn 203 stays out of line in the target,
// with 88 callers and 18 bytes, which clang would inline from a header, so the constructor is defined in the .cpp. No
// record names an adder: every adder's name, and which overloads share a name, are chosen from the field each builds.

#include <memory>
#include <string>
#include <vector>

#include "api/gui/iformfield.h"
#include "api/gui/iimage.h"
#include "api/gui/itext.h"
#include "api/gui/primitives.h"

namespace api {

/**
 * Monta os formulários da interface.
 */
class CFormBuilder {
public:
    using SharedField = std::shared_ptr<IFormField<IScreen>>;

    CFormBuilder();

    void AddField(SharedField campo);

    SharedField AddTextField(const std::string& texto, const SPoint& posicao, const SFont& fonte,
                             ETextAlignment alinhamento, TColor corTexto, TColor corFundo);

    SharedField AddTextField(std::string (*fonte)(), const SPoint& posicao, const SFont& font, ETextAlignment alinhamento);

    SharedField AddDoubleLineField(std::string (*fonte)(), const SPoint& linha1, const SPoint& linha2, TPosition maxX,
                                   const SFont& font, TColor corFundo);

    SharedField AddImage(SharedIImage imagem, const SPoint& posicao);

    SharedField AddLine(const SPoint& inicio, const SPoint& fim, TColor cor);

    SharedField AddFill(const SPoint& canto, const SPoint& oposto, TColor cor);

    SharedField AddRect(const SPoint& canto, const SPoint& oposto);

    static SPoint GetLabeledKeyPos(const SRect& area, ETextAlignment alinhamento, TPosition deslocamento);

private:
    SharedField AddRect(const SRect& rect);

    std::string GeraNome(const IFormField<IScreen>& campo) const;

    std::vector<SharedField> m_campos;
};

} // namespace api
