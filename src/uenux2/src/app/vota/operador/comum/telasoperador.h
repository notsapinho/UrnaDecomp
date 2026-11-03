#pragma once

#include <memory>
#include <string>

namespace api {
class IScreenMT;
class IInputMT;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// The form vota::CPedeIdentidade's constructor gives its +24 member from a copy of +16 (fn 652 holds both inlined):
// the training screen or the voting one, by comum::CAppInfo::EhTreinamentoEleitor. Its name, its file (this header's
// path is chosen, beside telasoperador.cpp) and its being a free function of vota are chosen; the copy is a by-value
// parameter, as the second frame of fn 652 shows (src/units/51-uenux2-ctextfieldupdatemt.mk).
std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> MontaTelaPedeIdentidade(std::shared_ptr<std::string> aviso);

} // namespace vota
