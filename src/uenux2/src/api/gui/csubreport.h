#pragma once

// api::CSubReport: the class is named by RTTI (an si_class of api::ISubReport, typeinfo 1543212), its constructor by
// its vptr store (target fn 3660, which its three callers 2882, 3671 and 11908 call with two strings and a bool). The
// layout (40 bytes, the frame every caller builds it in) is read from the constructor and the destructors (D2 12014,
// D0 12013): the vptr, two strings at +4 and +16 that the constructor moves its arguments into, a shared_ptr at +28
// that it leaves empty, and a bool at +36. The member names, the parameter names and this header's path are chosen:
// no record names the class.
//
// fn 3660 moves both strings out of its arguments before it stores anything into the object, and then stores the
// members from the last to the first and the vptr last: the shape of a constructor that delegates to one taking the
// strings by value again (the moves go into those parameters, which then hold nothing the object's stores depend on).
// The constructor it delegates to takes the part too, the only way the +28 member is set; it has no target function
// of its own (3660, its only user, inlines it), so its parameter order is chosen.
//
// Every virtual member is defined in the class: the target's vtable, its destructors and slots 2 to 7 are linkonce
// copies kept from the first object that uses them (vota::CRelVotaUtil's: the vtable, @1543172, lies right before the
// vtables of CRelVotaUtil::CortaPapel's and CriaCabecalho's lambdas, @1543232 and 1543296, and its slots come right
// before theirs in the table and in the target's function order), not from the object that defines the constructor,
// which the target links among the api/gui objects (fn 3660 lies between CQRCodeImage's functions and
// CTextFieldDoubleLine's constructor). The destructor is implicit: the D0 holds the D2's body. ImprimeParte (slot 6,
// fn 12009) calls slot 2 of the +28 pointee. Its type is chosen: no target code sets it, and IForm's slot 2 gives that call.

#include <memory>
#include <string>

#include "api/gui/isubreport.h"
#include "api/gui/reports/ireportpart.h"

namespace api {

class CSubReport : public ISubReport {
public:
    CSubReport(std::string titulo, std::string subtitulo, bool habilitado);
    CSubReport(std::string titulo, std::string subtitulo, std::shared_ptr<IReportPart> parte, bool habilitado);

    std::string GetTitulo() const override { return m_titulo; }
    std::string GetSubtitulo() const override { return m_subtitulo; }
    bool TemTitulo() const override { return !m_titulo.empty(); }
    bool TemParte() const override { return m_parte != nullptr; }
    void ImprimeParte() const override { m_parte->Imprime(); }
    bool Habilitado() const override { return m_habilitado; }

private:
    std::string m_titulo;
    std::string m_subtitulo;
    std::shared_ptr<IReportPart> m_parte;
    bool m_habilitado;
};

} // namespace api
