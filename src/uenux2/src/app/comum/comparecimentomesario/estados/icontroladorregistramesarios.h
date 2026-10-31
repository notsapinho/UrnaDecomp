#pragma once

// comum::IControladorRegistraMesarios: what comum's registration of mesarios asks of the application. RTTI gives the class
// and no base; the target has no vtable of its own (the one word of the data that points at its typeinfo, @1534552, is the
// base in its implementer's typeinfo, @1586764), so every slot past the destructors is pure here, and its one implementer, vota::CControladorRegistraMesariosVota (vtable @1586600, 37 slots), gives the slots'
// order and wasm types. The virtual destructor is in the first slot, as the control block's __on_zero_shared shows (fn 172
// calls vtable + 4). No member has a record: the names are chosen from what the implementer's bodies do (the ticks of
// vota::CThreadOperador, the titulo it holds, the text each log slot writes), else from the slot. The parameter and result
// types are the bodies' widths; the result of slots 9, 11 and 12 is chosen as the state class their callees return, and
// slot 14's as the mapped type of the map whose node fn 2264 returns (+32 into a node of fn 1703's tree).
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

    virtual uebyte AddTick(size_t milissegundos) = 0;
    virtual void StopTick(uebyte id) = 0;
    virtual void StartTick(uebyte id) = 0;
    virtual void Slot5() = 0;
    virtual int Slot6() = 0;
    virtual bool Slot7() = 0;
    virtual bool Slot8() = 0;
    virtual CAppState& Slot9() = 0;
    virtual void Slot10() = 0;
    virtual CAppState& Slot11() = 0;
    virtual CAppState& Slot12() = 0;
    virtual bool Slot13() = 0;
    virtual md::CComparecimentoMesario* Slot14() = 0;
    virtual void Slot15() = 0;
    virtual void Slot16() = 0;
    virtual const std::string& GetTituloMesario() = 0;
    virtual void SetTituloMesario(const std::string& titulo) = 0;
    virtual void LogaMesarioRegistrado(const std::string& titulo) = 0;
    virtual void LogaRegistrandoMesariosAntesVotacao() = 0;
    virtual void LogaRegistrandoMesariosDuranteVotacao() = 0;
    virtual void LogaRegistrandoMesariosAposVotacao() = 0;
    virtual void LogaIndagaRegistroMesarios() = 0;
    virtual void LogaConfirmouRegistroMesarios() = 0;
    virtual void LogaCancelouRegistroMesarios() = 0;
    virtual void LogaTituloInvalidoRegistroMesario() = 0;
    virtual void LogaMesarioJaRegistrado(const std::string& titulo) = 0;
    virtual void LogaLimiteMesariosAtingido() = 0;
    virtual void LogaEncerrouCicloRegistro() = 0;
    virtual void LogaDigitalNaoCorresponde(const std::vector<int>& scores) = 0;
    virtual void LogaPedidoBiometriaMesario() = 0;
    virtual void LogaMesarioEleitorDaSecao() = 0;
    virtual void LogaMesarioNaoEleitorDaSecao() = 0;
    virtual void LogaConferenciaBiometriaMesario() = 0;
    virtual void LogaIndagaContinuaRegistro() = 0;
    virtual void LogaIndagaFinalizaRegistro() = 0;
};

} // namespace comum
