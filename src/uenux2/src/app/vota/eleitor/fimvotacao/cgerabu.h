#pragma once

#include <memory>
#include <mutex>

#include "app/comum/cappstate.h"

namespace api {
class IScreen;
template <typename MEDIA>
class IForm;
} // namespace api

namespace vota {

// vota::CGeraBU (RTTI: si_class of comum::CAppState; vtable @1540364 [448, 765, 12110, 7480, 1661, 218, 425, 218,
// 425]): it overrides StartState (slot 2, fn 12110, record cgerabu.cpp:54), pending, and the destructors, the bodies
// the states over two std::shared_ptr at +12 and +20 share (fns 448 and 765): final, and out of line
// (docs/reference/facts/reading.md R4, R5). A singleton: GetInst (fn 6129) keeps the object in a static
// std::unique_ptr (@1833496) under a static std::mutex (@1833472), unit 104's shape, and builds the 28-byte object as
// the base's constructor with 0, at +12 the form "Votação encerrada" (TelaVotacaoEncerrada, app/vota/eleitor/comum/
// ctelasvota.cpp, which binaryen inlines here behind a second stack-pointer prologue) and at +20 the form "Preparando
// dados para encerramento" (fn 6583, called). Chosen: the members' names and their type (the std::shared_ptr of
// api::IForm<api::IScreen> that both functions return, which the target only stores), the names GetInst, s_inst and
// s_mutex, the destructor declared first. This header's path is chosen, beside the .cpp the record names.
class CGeraBU final : public comum::CAppState {
public:
    virtual ~CGeraBU() override;

    static CGeraBU& GetInst();

    virtual void StartState() override;

private:
    CGeraBU();

    static std::mutex s_mutex;
    static std::unique_ptr<CGeraBU> s_inst;

    std::shared_ptr<api::IForm<api::IScreen>> m_telaVotacaoEncerrada;
    std::shared_ptr<api::IForm<api::IScreen>> m_telaPreparandoDados;
};

} // namespace vota
