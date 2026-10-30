#pragma once

#include <string>

#include "api/util/cdatetime.h"
#include "app/comum/gravadores/igravador.h"

namespace comum {

// Recovered: only the type of the urna's phase that CGravadorUtil::ConverteFase returns (record cgravadorutil.cpp:97,
// fn 2274) and comum::md::CDadosDisponiveisCarga's constructor takes: 4 bytes wide (CGravadorWSQ's constructor stores
// ConverteFase's result at +52 with an i32.store). Its enumerators are not recovered, and that it is declared here is
// a choice.
enum EUrnaFase : int;

// Recovered: the layout (88 bytes: vota::CGravaResultado::StartState, fn 12098, allocates it with f137(88)) and the
// virtual members. The constructor is fn 3796 (it stores the vptr @1557300), with ValidaTipoBiometria inlined (record
// cgravadorwsq.cpp:73, the throw when m_tipoBiometria is 3 or more): after IGravador's constructor it copies its first
// argument, the api::CDateTime 12098 builds with fn 479, to +40, stores ConverteFase(fase) at +52, "wsq.pk1" at +56,
// its tipo de biometria at +68, "10.23.0.1 - DESENVOLVIMENTO" at +72 and its last argument at +84, which slots 3 and
// 6 (fn 6041) test before they write to the second medium. The destructor
// is not declared (implicit): its bodies (fns 11576, 11575, vtable slots 0 and 1) are the compiler's, the deleting one
// with the base-object body inlined, as is the libc++ deleter of the std::shared_ptr<IGravador> 12098 makes (fn
// 12092); one defined in the class gives the same bytes, one defined out of line a call in the deleting one.
// They store no vptr of this class, which clang leaves out of a destructor that destroys members only when the class
// is final. Slots 4, 5 and 7 hold the target's empty bodies (fns 218 and 425, shared by many classes); that they are
// defined in the class is a choice. The constructor, ValidaTipoBiometria and GetCaminhoCorretoInternal/External (fn
// 5821) are not reconstructed, so not declared. The types of +68 and +84 and every member name are chosen.
class CGravadorWSQ final : public IGravador {
public:
    virtual void Slot2() override;
    virtual void Slot3() override;
    virtual void Slot4() override {}
    virtual void Slot5() override {}
    virtual void Slot6() override;
    virtual void GravaResultado(api::CFile&) const override {}

private:
    api::CDateTime m_dataHora;
    EUrnaFase m_faseUrna;
    std::string m_arquivoChave;
    unsigned int m_tipoBiometria;
    std::string m_versao;
    bool m_gravaMidiaExterna;
};

} // namespace comum
