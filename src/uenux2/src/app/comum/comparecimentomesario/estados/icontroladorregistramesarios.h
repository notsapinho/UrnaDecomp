#pragma once

// comum::IControladorRegistraMesarios: what comum's registration of mesarios asks of the application. RTTI gives the class
// and no base; the target has no vtable of its own (the one word of the data that points at its typeinfo, @1534552, is the
// base in its implementer's typeinfo, @1586764), so every slot past the destructors is pure here, and its one implementer, vota::CControladorRegistraMesariosVota (vtable @1586600, 37 slots), gives the slots'
// order and wasm types. The virtual destructor is in the first slot, as the control block's __on_zero_shared shows (fn 172
// calls vtable + 4). No member has a record: the names are chosen from what the implementer's bodies do (the ticks of
// vota::CThreadOperador, the titulo it holds, the text each log slot writes), else from the slot. The parameter and result
// types are the bodies' widths; the result of slots 9, 11 and 12 is chosen as the state class their callees return, and
// slot 14's as the mapped type of the map whose node fn 2264 returns (+32 into a node of fn 1703's tree).
// Every slot but SetTituloMesario is const. The states call them through GetControlador, whose records return
// `const IControladorRegistraMesarios &` (cconfirmafimregistromesarios.cpp:60 and nine more files), and the target calls
// 28 of the 35 slots through such a reference: 2 to 7, 9 to 17, 19, 23 to 31 and 34 to 36, in fns 10313, 10316, 10318,
// 10337, 10339, 10343, 10358, 10380, 10383, 10385, 10392, 5382, 6010 and 6011. Slot 18 is called only through the
// non-const reference of ipedetitulomesario.cpp's anonymous GetControlador (line 30, fn 10313). Const on slots 8, 20 to
// 22, 32 and 33, which no body here shows called, and its absence on slot 18 are chosen.
// The path is chosen: 11 records in 11 files of this directory name the class, and no record names a file of its own.

#include <cstddef>
#include <string>
#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace comum {

class CAppState;

namespace md {
class CComparecimentoMesario;
} // namespace md

class IControladorRegistraMesarios {
public:
    virtual ~IControladorRegistraMesarios() = default;

    virtual uebyte AddTick(size_t milissegundos) const = 0;
    virtual void StopTick(uebyte id) const = 0;
    virtual void StartTick(uebyte id) const = 0;
    virtual void Slot5() const = 0;
    virtual int Slot6() const = 0;
    virtual bool Slot7() const = 0;
    virtual bool Slot8() const = 0;
    virtual CAppState& Slot9() const = 0;
    virtual void Slot10() const = 0;
    virtual CAppState& Slot11() const = 0;
    virtual CAppState& Slot12() const = 0;
    virtual bool Slot13() const = 0;
    virtual md::CComparecimentoMesario* Slot14() const = 0;
    virtual void Slot15() const = 0;
    virtual void Slot16() const = 0;
    virtual const std::string& GetTituloMesario() const = 0;
    virtual void SetTituloMesario(const std::string& titulo) = 0;
    virtual void LogaMesarioRegistrado(const std::string& titulo) const = 0;
    virtual void LogaRegistrandoMesariosAntesVotacao() const = 0;
    virtual void LogaRegistrandoMesariosDuranteVotacao() const = 0;
    virtual void LogaRegistrandoMesariosAposVotacao() const = 0;
    virtual void LogaIndagaRegistroMesarios() const = 0;
    virtual void LogaConfirmouRegistroMesarios() const = 0;
    virtual void LogaCancelouRegistroMesarios() const = 0;
    virtual void LogaTituloInvalidoRegistroMesario() const = 0;
    virtual void LogaMesarioJaRegistrado(const std::string& titulo) const = 0;
    virtual void LogaLimiteMesariosAtingido() const = 0;
    virtual void LogaEncerrouCicloRegistro() const = 0;
    virtual void LogaDigitalNaoCorresponde(const std::vector<int>& scores) const = 0;
    virtual void LogaPedidoBiometriaMesario() const = 0;
    virtual void LogaMesarioEleitorDaSecao() const = 0;
    virtual void LogaMesarioNaoEleitorDaSecao() const = 0;
    virtual void LogaConferenciaBiometriaMesario() const = 0;
    virtual void LogaIndagaContinuaRegistro() const = 0;
    virtual void LogaIndagaFinalizaRegistro() const = 0;
};

} // namespace comum
