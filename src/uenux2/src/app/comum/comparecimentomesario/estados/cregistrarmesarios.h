#pragma once

#include <memory>

#include "api/gui/primitives.h"

namespace api {
class IScreen;
template <typename MEDIA>
class IForm;
} // namespace api

namespace comum {

// The voter's screen while the poll workers register: the status header (date and time, mode, battery icon), "REGISTRO
// DE MESÁRIOS" at (320, 150) in a 35-point font and "Siga as instruções no terminal do mesário." at (320, 250) in a
// 25-point one, centred, colours 2 over 1, as an unnamed api::IForm<api::IScreen> over a clear screen. Target fn 1255
// is its body, which binaryen keeps once for this function and for comum::IPedeTituloMesario::GetTelaEleitor
// (ipedetitulomesario.h says why there are two). Its name, its being a free function of comum, and this header's path,
// beside cregistrarmesarios.cpp, are chosen.
std::shared_ptr<api::IForm<api::IScreen>> TelaRegistroMesarios();

// The two fonts of that screen, SFont {35, 0} and {25, 0}: the target holds them once (@540572 and @540580, between
// the typeinfo names of comum::CRegistrarMesarios and comum::CPedeTituloMesario), and 1255 alone reads them; that both
// functions here read them is part of the reading of two copies. Their names, their being constants of
// cregistrarmesarios.cpp declared here, and that file are chosen.
extern const api::SFont FONTE_TITULO_REGISTRO_MESARIOS;
extern const api::SFont FONTE_TEXTO_REGISTRO_MESARIOS;

} // namespace comum
