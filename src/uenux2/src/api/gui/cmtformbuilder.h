#pragma once

// api::CMTFormBuilder: the builder of the forms of the IScreenMT screen. No record, symbol or RTTI names this class; the
// name is chosen after api::CPaperFormBuilder, the name the records give the IPaper one, and its file is the class's in
// lower case, beside cformbuilder.h. What is read from the bytes: the object is 12 bytes built by fn 203, the same body as
// api::CFormBuilder's constructor, and destroyed in line as one vector, fns 180, 941, 728, 435 and 1072 push to a vector at
// this + 0, and they build IFormField<IScreenMT> fields, which api::CFormBuilder's vector cannot hold. So there are two
// vectors' classes, and binaryen keeps one of the two constructors' bodies. That the two classes share no base is a choice.
//
// Each adder's name, and which overloads share a name, are chosen from the field it builds. CTextSource goes by value: the
// adders release its reference at their end, and a class holding a libc++ shared_ptr is trivial-ABI here, so the callee
// destroys it. std::function goes by value by choice: a const reference gives the same rows, since the caller destroys
// either. The alignments of the two overloads that default it are read from fns 5409 and 5419, which store 0 as a constant
// and have no parameter for it. The field's std::shared_ptr is the result of the text adders (each takes the address of
// its result) and they push it through the out-of-line push_back, fn 1400; the four other adders return nothing and clang
// inlines push_back, whose reference argument is then a local (src/units/31-uenux2-cformbuilder.mk).

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "api/gui/cledfieldmt.h"
#include "api/gui/ctextsource.h"
#include "api/gui/iformfield.h"
#include "api/gui/itext.h"
#include "api/gui/primitives.h"

namespace api {

/**
 * Monta os formulários da tela MT.
 */
class CMTFormBuilder {
public:
    using SharedField = std::shared_ptr<IFormField<IScreenMT>>;

    CMTFormBuilder();

    SharedField AddTextField(const std::string& texto, const SPoint& posicao, ETextAlignment alinhamento);

    SharedField AddTextField(std::string (*fonte)(), const SPoint& posicao, ETextAlignment alinhamento);

    SharedField AddTextField(std::string (*fonte)(const std::string&), const SPoint& posicao, const std::string& formato,
                             ETextAlignment alinhamento);

    SharedField AddTextField(CTextSource fonte, const SPoint& posicao, const std::string& formato,
                             ETextAlignment alinhamento);

    SharedField AddTextField(CTextSource fonte, const SPoint& posicao, ETextAlignment alinhamento = ALINHAMENTO_ESQUERDA);

    SharedField AddTextField(std::function<std::string()> fonte, const SPoint& posicao,
                             ETextAlignment alinhamento = ALINHAMENTO_ESQUERDA);

    void AddLed(ELedOperacao operacao);

    void AddBeep(int vezes);

    void AddBuzz(int primeiro, int segundo);

    void AddClock(const SPoint& posicao);

private:
    SharedField AddTextField(const SharedIText& texto, const SPoint& posicao);

    std::vector<SharedField> m_campos;
};

} // namespace api
