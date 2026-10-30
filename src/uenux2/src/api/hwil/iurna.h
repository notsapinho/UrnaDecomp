#pragma once

#include <string>

#include "ecourna/api/uetypes.hpp"

namespace api {

// Recovered: RTTI names api::IUrna (typeinfo 1530936), a class with no base, and its one implementer in the wasm build,
// api::teste::CUrnaMock (vtable @1530880, 9 slots), which fn 8302 builds and registers; the target has this class's
// typeinfo and no vtable of its own, and the callers reach it through fn 923. Slots 0 to 6 are the members, the
// destructor's two come last. The callers give the roles: slot 0 is the model year (compared with 2009, 2010, 2020 and
// 2022 by comum::CPedeDigitalMesario::ProcessTick, fn 10316, and with 2020 by vota::CPedeIdentidade::StartState, fn
// 10680, read as signed, so int); slot 6 fills the buffer ecourna::api::security::CHKDFSeed::GetSeed (fn 7787) works
// from; slot 4 fills the buffer of comum::CControlaArmazenamentoDeImagens::GerarCaminhosUnicos (fn 2725) and
// comum::md::CEntidadeBU::ValidaCriacao (fn 11629). Slot 1 is the model year's last two digits as text (the mock's fn
// 8168). Slots 2 and 3 return ints; slot 2's name is chosen from the mock's value alone, 87654321, and slots 3, 4 and 5
// have no caller that says what they are, so they keep their slot. No record or symbol names any member or this file:
// every member name, their const (without it the bytes are the same) and the path, beside the hardware interfaces
// whose records name api/hwil/ (ipower.h, iinput.h, iimpressora.h), are chosen. How many bytes each buffer takes is
// the mock's (1024, 32 and 128); a pointer, and not a reference to a std::array of that size, is chosen: the same bytes.
// That the members are pure here is chosen too: the one implementer overrides every slot.
class IUrna {
public:
    virtual int Modelo() const = 0;
    virtual std::string ModeloAbreviado() const = 0;
    virtual int NumeroSerie() const = 0;
    virtual int Slot3() const = 0;
    virtual void Slot4(uebyte* destino) const = 0;
    virtual void Slot5(uebyte* destino) const = 0;
    virtual void Semente(uebyte* destino) const = 0;

    virtual ~IUrna() = default;
};

} // namespace api
