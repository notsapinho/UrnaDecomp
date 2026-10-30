#pragma once

// api::ISubReport: the class is named by RTTI (N3api10ISubReportE, a class with no base, typeinfo 1543224), the only
// base of api::CSubReport (api/gui/csubreport.h). It has no vtable in the target: no function stores one, as an
// interface whose members are all inline or pure gives. Its slots are read from CSubReport's vtable (@1543172): 0 and 1
// the destructors, 2 to 7 the members below. No record, symbol or caller names them, so their names, their constness
// and this header's path are chosen (the role each name says is the body's in CSubReport; the helper that prints a
// sub-report, fn 3875, calls slot 5 and, when it is true, slot 6). They are declared pure: nothing in the target
// gives a body of this class for them.

#include <string>

namespace api {

class ISubReport {
public:
    virtual ~ISubReport() = default;

    virtual std::string GetTitulo() const = 0;
    virtual std::string GetSubtitulo() const = 0;
    virtual bool TemTitulo() const = 0;
    virtual bool TemParte() const = 0;
    virtual void ImprimeParte() const = 0;
    virtual bool Habilitado() const = 0;
};

} // namespace api
