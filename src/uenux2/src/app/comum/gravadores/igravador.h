#pragma once

#include "app/comum/gravadores/iresultado.h"

namespace api {
class CFile;
}

namespace comum {

// Recovered: the virtual members. The vtable (@1553648) fills IResultado's two pure slots (fns 11632, 11630), adds
// three slots of its own (fns 11634, 11633, 11631) and a pure one, slot 7, which the recorders' records name
// GravaResultado (cgravadorbu.cpp:484, cgravadorhashes.cpp:112, cgravadorrcsecao.cpp:110). No evidence names slots 2
// to 6: they are named after their slot. Every recorder derives from the class directly (RTTI). It adds no member:
// its constructor (fn 1396, IResultado's inlined) stores only IResultado's and the vptr, and the recorders store
// their own members from +40. The destructor is not declared (implicit): slot 0 holds IResultado's (fn 12090), which
// clang puts in place of an inline destructor with an empty body and no member to destroy, and the recorders'
// destructors inline it and store no vptr of this class (fn 11576; one defined in the class gives the same bytes, one
// defined out of line a call there). The constructor (fn 1396) passes its arguments on to IResultado's and stores the
// vptr; that it is defined in iresultado.cpp is a choice the data allows: the vtable (@1553648) follows that file's
// record (@1553632), so that object can be the one that emits it (unit 122's fragment). Slots 2, 6 and 3 (fns 11632,
// 11631, 11630) are written there, Slot2 the key function, so that object emits the vtable: Slot2 and Slot6 copy the
// result file from the work directory to the result directory (comum::CPath's GetPathTrab and GetPathResult) of the
// internal and of the external flash, and Slot3 copies the work file and the result file from the internal flash to
// the external one, each with api::CSystem::CopyFile. Slots 4 and 5 (fns 11634, 11633) open the file in the work
// directory of each flash with the mode "wb", pass it to GravaResultado and close it. They are pending
// (src/units/60-uenux2-cgravadorwsq-pending.cpp): the file they open is an ecourna::api::io::CFile (fn 517, its
// constructor, builds it), and GravaResultado's records spell their parameter api::CFile, which no header of this tree
// declares as that class; the forward declaration above is that spelling only.
class IGravador : public IResultado {
public:
    IGravador(TMunicipioID municipio, TZonaID zona, TLocalID local, TSecaoID secao, char fase,
        EExtensaoArquivoResultado extensao, ESavdArquivoUE arquivoSavd);

    virtual void Slot2() override;
    virtual void Slot3() override;
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void GravaResultado(api::CFile& arquivo) const = 0;
};

} // namespace comum
