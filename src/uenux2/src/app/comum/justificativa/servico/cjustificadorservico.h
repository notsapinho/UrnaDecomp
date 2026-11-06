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
// the member's name are chosen.
//
// Salva and Existe have no target index: CJustificador::SaveCurrentInternal, held by fn 10590, calls Salva, whose
// 32-byte frame binaryen inlined there. It asks the DAO for the record of the justification's número (slot 7,
// RecuperarID) and inserts the justification (slot 3, Inserir) when there is none; Existe, which clang inlines into
// it, is a reading of the point at which fn 10590 reads the DAO pointer. Both are defined in cjustificador.cpp, above
// SaveCurrentInternal, a place measured on fn 10590 (src/units/283-uenux2-app-vota-operador-justificativa.mk has the
// measurement). Their names, Existe being a member and both being const are chosen.
class CJustificadorServico {
public:
    CJustificadorServico();
    virtual ~CJustificadorServico();

    void Salva(const ecourna::app::dados::CIdentificacaoJustificativa& justificativa) const;
    bool Existe(const std::string& titulo) const;
    // RecuperarTodos: the DAO's (slot 8) result handed back. Out of line in cjustificadorservico.cpp: one body with
    // CComparecimentoMesarioServico's, target fn 5723, which both loads fn 6734 holds call
    // (src/units/386-uenux2-carregaeleitores.mk). The name, after the DAO's slot, and the const are chosen.
    std::vector<ecourna::app::dados::CIdentificacaoJustificativa> RecuperarTodos() const;

private:
    std::shared_ptr<dao::IJustificadorDAO> m_dao;
};

} // namespace comum::servico
