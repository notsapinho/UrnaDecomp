#pragma once

// comum::CAbstractTelaProgresso: the base of an application's progress screens (RTTI: a class with no base,
// ledger/classes.json; vtable @1551204 [174, 144, 218, 218, 218], ledger/vtables.json). Its destructor destroys nothing
// (fn 174 returns `this`, fn 144 frees it) and slots 2 to 4 have an empty body (fn 218): the three members a progress
// screen overrides, as vota::CProgressoEncerramento does (fns 12103, 12102, 12101: it sets its bar to the lower limit
// and calls its form's slot 2, sets the bar to the upper limit, advances the bar). No record, symbol or caller names
// the three members or this header: their names and the directory (the root of app/comum/, beside the other interfaces
// comum declares for the applications, iinterfacesavd.h) are chosen. The constructor is not recovered: fn 12098 stores
// this class's vptr before the derived one, which clang leaves in only when the base constructor is not inlined into
// the derived constructor, so the original's is out of line.

namespace comum {

/**
 * Tela que mostra o andamento de uma tarefa demorada.
 */
class CAbstractTelaProgresso {
public:
    virtual ~CAbstractTelaProgresso() = default;

    virtual void Inicia() {}

    virtual void Finaliza() {}

    virtual void Incrementa() {}
};

} // namespace comum
