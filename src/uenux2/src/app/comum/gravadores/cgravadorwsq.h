#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "api/util/cdatetime.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "app/comum/eurnafase.h"
#include "app/comum/gravadores/igravador.h"

namespace comum {

// The kind of biometrics a WSQ recorder writes, 4 bytes at +68 of CGravadorWSQ. Evidence: the constructor (fn 3796)
// throws when it is 3 or more with an unsigned compare; GetCaminhoCorretoInternal and GetCaminhoCorretoExternal (records
// cgravadorwsq.cpp:175 and :192, inlined into fn 5821) switch on 0, 1 and 2, and their throws format it through table
// slot 2327, fn 536, the handle body of the enums that have a formatter of their own (eurna.h's SFormatoEnum); 0 selects
// the WSQ directory "habilitado/", 1 "nao-habilitado/" and 2 "operador/". Measured: with `: unsigned int` and this
// formatter 3796 still matches and 5821's throws store the argument type 15 and the handle's slot where the target's
// do (pnpm wasm score); a plain enum was not measured. The
// enum's name, its enumerators' names (after those directories), the fixed type's spelling and this header are chosen.
enum ETipoBiometria : unsigned int {
    TIPO_BIOMETRIA_HABILITADO = 0,
    TIPO_BIOMETRIA_NAO_HABILITADO = 1,
    TIPO_BIOMETRIA_OPERADOR = 2,
};

// Recovered: the layout (88 bytes: vota::CGravaResultado::StartState, fn 12098, allocates it with f137(88)) and the
// virtual members. The constructor is fn 3796 (it stores the vptr @1557300), with ValidaTipoBiometria inlined (record
// cgravadorwsq.cpp:73, the throw when m_tipoBiometria is 3 or more): after IGravador's constructor it copies its first
// argument, the api::CDateTime 12098 builds with fn 479, to +40, stores ConverteFase(fase) at +52, "wsq.pk1" at +56,
// its tipo de biometria at +68, "10.23.0.1 - DESENVOLVIMENTO" at +72 and its last argument at +84, which slots 3 and
// 6 test before they write to the second medium. The destructor
// is not declared (implicit): its bodies (fns 11576, 11575, vtable slots 0 and 1) are the compiler's, the deleting one
// with the base-object body inlined, as is the libc++ deleter of the std::shared_ptr<IGravador> 12098 makes (fn
// 12092); one defined in the class gives the same bytes, one defined out of line a call in the deleting one.
// They store no vptr of this class, which clang leaves out of a destructor that destroys members only when the class
// is final. Slots 4, 5 and 7 hold the target's empty bodies (fns 218 and 425, shared by many classes); that they are
// defined in the class is a choice. cgravadorwsq.cpp defines the constructor, ValidaTipoBiometria, Slot2 (fn 11579, the
// class's key function, so that object emits the vtable and the two destructors), Slot6 and Slot3, CompactaWsq (fn
// 5821) and the records' GetCaminhoCorretoInternal and GetCaminhoCorretoExternal, which binaryen inlines into 5821.
// Slot3 and Slot6 differ in the bool they pass on alone, and binaryen merges them into fn 6041, the slots' 9-byte
// thunks 11577 and 11578 passing 0 and 1. The constructor's parameter types beyond the record's IResultado ones, the
// type of +84, CompactaWsq's name and parameters, every member name, and that CompactaWsq, the two GetCaminhoCorreto
// members and ValidaTipoBiometria are private are chosen.
class CGravadorWSQ final : public IGravador {
public:
    CGravadorWSQ(const api::CDateTime& dataHora, TMunicipioID municipio, TZonaID zona, TLocalID local, TSecaoID secao,
        char fase, EExtensaoArquivoResultado extensao, ESavdArquivoUE arquivoSavd, ETipoBiometria tipoBiometria,
        bool gravaMidiaExterna);

    virtual void Slot2() override;
    virtual void Slot3() override;
    virtual void Slot4() override {}
    virtual void Slot5() override {}
    virtual void Slot6() override;
    virtual void GravaResultado(api::CFile&) const override {}

private:
    void ValidaTipoBiometria() const;
    void CompactaWsq(bool midiaExterna, const std::string& arquivo) const;
    std::vector<std::string> GetCaminhoCorretoInternal() const;
    std::vector<std::string> GetCaminhoCorretoExternal() const;

    api::CDateTime m_dataHora;
    EUrnaFase m_faseUrna;
    std::string m_arquivoChave;
    ETipoBiometria m_tipoBiometria;
    std::string m_versao;
    bool m_gravaMidiaExterna;
};

} // namespace comum

template <>
struct std::formatter<comum::ETipoBiometria> : comum::SFormatoEnum {};
