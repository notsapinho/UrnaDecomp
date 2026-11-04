#pragma once

#include <string>

#include "app/vota/eleitor/iajusteinicial.h"

// vota::CAjusteInicial (RTTI: si_class of vota::IAjusteInicial; vtable @1534236 [174, 144, 7160, 7480, 1661, 218, 425,
// 218, 425]): the first state of the voter's thread. Slot 2, StartState (fn 7160), is its own; the rest are
// comum::CAppState's or the shared bodies of states with no member (fns 174 and 144). IAjusteInicial::GetInst allocates
// 12 bytes for it, the base's size, so it adds no data member, and builds it over the base's constructor with 0. The
// constructor is out of line: fn 7061, which holds GetInst inlined, keeps operator new's pointer and stores the vptr
// through the base constructor's returned this, which an implicit constructor does not give (measured, unit 329's
// fragment). The four members the records name (cajusteinicial.cpp:74 to :245) are non-virtual, each called once by
// StartState, which holds each behind a stack frame of its own. Their access, the constructor's and the header's path,
// beside the .cpp, are chosen; src/units/329-uenux2-cajusteinicial.mk says what else is.

namespace api {
class CDirReader;
}

namespace vota {

class CAjusteInicial : public IAjusteInicial {
public:
    CAjusteInicial();

    virtual void StartState() override;

private:
    void ValidaTemposDesligamento();
    void InicioVota();
    void LimpaMidiaResultado();
    void AjustaDataHora();
};

// Two functions StartState holds behind frames of their own with no record, so their names, their being free
// functions of vota and their files are chosen (unit 329's fragment says from what). CriaControladorRegistraMesarios
// reads the poly singletons' info and then builds vota::CControladorRegistraMesariosVota and sets it as the
// comum::IControladorRegistraMesarios, in that order; AbreDiretorio returns a directory reader that
// LimpaMidiaResultado tests for null, so it is another TU's (cthreadeleitor.cpp's).
void CriaControladorRegistraMesarios();
api::CDirReader* AbreDiretorio(const std::string& caminho);

} // namespace vota
