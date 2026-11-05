#pragma once

#include <filesystem>

#include "app/comum/eurnaturno.h"

namespace comum {

// The WSQ directories of the load's turn: CPath::GetPathWsq of the internal or the external flash and a subdirectory,
// "habilitado/", "nao-habilitado/", "operador/" and "nao-registrado/". The functions with no argument are target fns
// 5819, 5818 and 3795 (internal flash), 5817, 5816 and 3794 (external flash) and 3793 ("nao-registrado/", internal
// flash): each reads the turn of CAppInfo::GetGeral() (the word at +32) and calls its overload with the turn, which
// binaryen inlines into it, so the turn's load comes ahead of that overload's stack frame (docs/reference/facts/
// reading.md R10, statements ahead of the body's only prologue). binaryen then merges the bodies that differ in the
// literal only, fn 2298 for the internal flash and fn 3898 for the external one, and each function becomes a thunk that
// passes its literal's ends. No record names any of them: the names, the overloads with the turn, their being free
// functions of comum, this header and pathwsq.cpp, and their directory, are chosen.
std::filesystem::path GetPathWsqHabilitado(EUrnaTurno turno);
std::filesystem::path GetPathWsqHabilitado();
std::filesystem::path GetPathWsqNaoHabilitado(EUrnaTurno turno);
std::filesystem::path GetPathWsqNaoHabilitado();
std::filesystem::path GetPathWsqHabilitadoExterno(EUrnaTurno turno);
std::filesystem::path GetPathWsqHabilitadoExterno();
std::filesystem::path GetPathWsqNaoHabilitadoExterno(EUrnaTurno turno);
std::filesystem::path GetPathWsqNaoHabilitadoExterno();
std::filesystem::path GetPathWsqOperador(EUrnaTurno turno);
std::filesystem::path GetPathWsqOperador();
std::filesystem::path GetPathWsqOperadorExterno(EUrnaTurno turno);
std::filesystem::path GetPathWsqOperadorExterno();
std::filesystem::path GetPathWsqNaoRegistrado(EUrnaTurno turno);
std::filesystem::path GetPathWsqNaoRegistrado();
std::filesystem::path GetPathWsqRegistrado(EUrnaTurno turno);
std::filesystem::path GetPathWsqRegistrado();
std::filesystem::path GetPathWsqRegistradoExterno(EUrnaTurno turno);
std::filesystem::path GetPathWsqRegistradoExterno();

} // namespace comum
