#pragma once

#include <memory>
#include <mutex>

#include "app/vota/operador/justificativa/iconfirmajustificativa.h"

namespace vota {

// vota::CConfirmaJustificativa (RTTI: si_class of vota::IConfirmaJustificativa; vtable @1589252 [3626, 2748, 10589,
// 7480, 1661, 218, 425, 10588, 425]): the confirmation of the justification of a voter whom the urna does not list,
// the state vota::CIniciaJustificativa (ciniciajustificativa.h) hands IIniciaJustificativa. It overrides no slot but the
// destructors, which are out of line: slot 0 is fn 3626, a call of IConfirmaJustificativa's destructor (fn 1688) that
// returns its result, and the deleting one (slot 1, fn 2748, the body IConfirmaJustificativa's has too) calls 1688,
// drops the result and frees `this` (docs/reference/facts/reading.md R5); defined in the .cpp, the destructor is the key
// function. final: fn 10631 frees a replaced object after a call of fn 1688, with no call through the vtable. A
// singleton: GetInst keeps the 20-byte object in a static std::unique_ptr (@1905700) under a static std::mutex
// (@1905676); the constructor passes IConfirmaJustificativa's (fn 3625) the text comum::md::CTradutorFrase::Traduz (fn
// 654) makes of "não pertence <S|a|ao|à> <SCSN>". fn 10631 holds GetInst inlined, through CIniciaJustificativa's
// constructor, whose object keeps it a call that binaryen inlines (src/units/243-uenux2-app-vota-justificativa.mk).
// The file's name, after the class, is chosen, and so is this header's path.
class CConfirmaJustificativa final : public IConfirmaJustificativa {
public:
    virtual ~CConfirmaJustificativa() override;

    static CConfirmaJustificativa& GetInst();

private:
    CConfirmaJustificativa();

    static std::unique_ptr<CConfirmaJustificativa> s_inst;
    static std::mutex s_mutex;
};

} // namespace vota
