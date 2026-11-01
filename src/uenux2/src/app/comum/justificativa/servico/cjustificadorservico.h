#pragma once
#include <memory>

#include "app/comum/justificativa/dao/ijustificadordao.h"

namespace comum::servico {

// The name is RTTI's (vtable 1560928, typeinfo of kind "class": no base). Two slots, the destructors: fn 3740 (D2, a
// thunk into binaryen's 2899, which releases one std::shared_ptr at +4) and fn 11464 (D0: it calls the D2 and then frees
// this, the shape of a destructor defined out of line, docs/reference/facts/reading.md R5). The D2 stores the class's
// vptr, so the class is not final (R4).
//
// The member at +4 is the DAO that api::persistencia::CDAORepositorio::Entregar<comum::dao::IJustificadorDAO> returns:
// fn 3742, comum::CJustificador's constructor, stores this class's vptr at +28 and then the result of the inlined
// Entregar at +32 and +36, with the control block of a std::shared_ptr<IJustificadorDAO>. The constructor calls
// Entregar: its record follows this class's typeinfo in the data, in this object's run. No record names this file or
// the .cpp: their path, in a servico/ beside the DAO's dao/ (the vtable lies right after cjustificadordao.cpp's data), and
// the member's name are chosen. No other member is recovered.
class CJustificadorServico {
public:
    CJustificadorServico();
    virtual ~CJustificadorServico();

private:
    std::shared_ptr<dao::IJustificadorDAO> m_dao;
};

} // namespace comum::servico
