#pragma once

// comum::CAbstractTelaProgresso: the base of an application's progress screens (RTTI: a class with no base,
// ledger/classes.json; vtable @1551204 [174, 144, 218, 218, 218], ledger/vtables.json). Its destructor destroys nothing
// (fn 174 returns `this`, fn 144 frees it) and slots 2 to 4 have an empty body (fn 218): the three members a progress
// screen overrides, as vota::CProgressoEncerramento does (fns 12103, 12102, 12101: it sets its bar to the lower limit
// and calls its form's slot 2, sets the bar to the upper limit, advances the bar). No record, symbol or caller names
// the three members or this header: their names and the directory (the root of app/comum/, beside the other interfaces
// comum declares for the applications, iinterfacesavd.h) are chosen. The constructor is out of line, in
// cabstracttelaprogresso.cpp (the file chosen, beside this header): fn 12098, which holds CProgressoEncerramento's
// constructor inlined, stores this class's vptr before the derived one, and clang leaves that store in the derived
// constructor's object only when the base's constructor is another TU's call (measured on cprogressoencerramento.cpp.o:
// the implicit constructor is inlined there and its store goes; declared here and defined in another TU, the object
// calls it and then stores +4, the vptr, +12 to +36 in the target's order). The target's data put the vtable
// (@1551204) right before comum::CAppState's (cappstate.cpp's); that a TU of its own, beside cappstate.cpp, emits it
// with this constructor is a reading.

namespace comum {

/**
 * Tela que mostra o andamento de uma tarefa demorada.
 */
class CAbstractTelaProgresso {
public:
    CAbstractTelaProgresso();
    virtual ~CAbstractTelaProgresso() = default;

    virtual void Inicia() {}

    virtual void Finaliza() {}

    virtual void Incrementa() {}
};

} // namespace comum
