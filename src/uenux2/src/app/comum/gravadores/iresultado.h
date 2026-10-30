#pragma once

#include <string>

#include "app/comum/iinterfacesavd.h"
#include "ecourna/app/dados/tiposbasicos.hpp"

namespace comum {

// Recovered: the section identifiers IResultado's constructor takes, as its record (iresultado.cpp:40) spells them;
// comum's records write them unqualified, and comum::TZonaID once. That they are ecourna's types, brought into comum
// by using-declarations, is a choice: ecourna's are as wide as the constructor's stores (fn 1396: TMunicipioID and
// TLocalID with i32.store, TZonaID and TSecaoID with i32.store16).
using ecourna::app::dados::TLocalID;
using ecourna::app::dados::TMunicipioID;
using ecourna::app::dados::TSecaoID;
using ecourna::app::dados::TZonaID;

// Recovered: only the type of a result file's extension that IResultado's constructor, CArquivosResultado::operator[]
// (carquivosresultado.cpp:99) and CLogComum's records take: 4 bytes wide (the constructor stores it at +32 with an
// i32.store). Its enumerators are in app/comum/carquivosresultado.h, and that it is declared here is a choice.
enum EExtensaoArquivoResultado : int;

// Recovered: the layout (40 bytes) and the virtual members. The vtable (@1541020) is the destructors and two pure
// slots; comum::IGravador derives from the class and fills both. The constructor (record iresultado.cpp:40) is inlined
// into IGravador's, fn 1396, which stores its arguments, in the record's order, at +4, +8, +12, +16, the fase at +18,
// the file name fn 3798 (CGravadorUtil::DeterminaNomeArquivoSemLetra) builds from them at +20, then +32 and +36; it
// is not reconstructed, so not declared. The destructor is defined in the class: every derived class's destructor
// inlines it (fn 11576: the vptr store of 1541028 and the free of the string at +20; defined out of line, it is a
// call there), so the class has no key function: its vtable and typeinfo lie among those of vota::CGravaResultado's
// TU, which builds the recorders. Its own body is fn 12090, slot 0 of this vtable, of IGravador's and of
// CGravadorRCSecao's. No evidence names the two pure slots: they are named after their slot. The member names are not
// in the target.
class IResultado {
public:
    virtual ~IResultado() = default;

    virtual void Slot2() = 0;
    virtual void Slot3() = 0;

protected:
    TMunicipioID m_municipio;
    TZonaID m_zona;
    TLocalID m_local;
    TSecaoID m_secao;
    char m_fase;
    std::string m_nomeArquivo;
    EExtensaoArquivoResultado m_extensao;
    ESavdArquivoUE m_arquivoSavd;
};

} // namespace comum
