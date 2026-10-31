#pragma once
#include <memory>

#include "app/comum/comparecimentomesario/dao/icomparecimentomesariodao.h"

namespace comum::servico {

// The name is RTTI's (vtable 1595668, typeinfo of kind "class": no base). Two slots, the destructors: fn 3607 (D2, a
// thunk into binaryen's 2899, which releases one std::shared_ptr at +4) and fn 10312 (D0: it calls the D2 and then frees
// this, the shape of a destructor defined out of line, docs/reference/facts/reading.md R5). The D2 stores the class's
// vptr, so the class is not final (R4).
//
// The member at +4 is the DAO that api::persistencia::CDAORepositorio::Entregar<comum::dao::IComparecimentoMesarioDAO>
// returns: fn 815, which builds comum::CRegistradorMesario, stores this class's vptr at +40 and then the result of the
// inlined Entregar at +44 and +48, with the control block of a std::shared_ptr<IComparecimentoMesarioDAO>; the
// registrador's destructor (fn 5380) calls 3607 on +40. The constructor calls Entregar: its record follows this class's
// typeinfo in the data, in this object's run. No record names this file or the .cpp: their path, in a servico/ beside
// the DAO's dao/ (the vtable lies after estados/' data and before cregistradormesario.cpp's), and the member's name are
// chosen. No other member is recovered.
class CComparecimentoMesarioServico {
public:
    CComparecimentoMesarioServico();
    virtual ~CComparecimentoMesarioServico();

private:
    std::shared_ptr<dao::IComparecimentoMesarioDAO> m_dao;
};

} // namespace comum::servico
