#pragma once

#include <optional>
#include <string>

#include "api/util/cdatetime.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "app/vota/operador/comum/iinformacaothreadoperador.h"
#include "ecourna/app/dados/resultadournacadastro/capresentacaofotoeleitor.hpp"
#include "ecourna/app/dados/tiposbasicos.hpp"

namespace vota::impl {

// Recovered: the layout (96 bytes) and the virtual members, which IInformacaoThreadOperador declares (most of their
// names are its choices). The destructor is implicit: its bodies (fns 10552 and 10551, vtable slots 0 and 1) are the
// compiler's, the deleting one with the base-object body inlined, and in the target's function order
// (ledger/ordinals.tsv: 10581 ... 10556, then 10552 and 10551) they come after the members, which are in slot order:
// clang emits the members where cinformacaothreadoperador.cpp defines them, out of line (four have their records
// there), and an implicit destructor at the end of the TU with the vtable (members defined in the class would come
// after the destructors, in vtable order). The destructors store no vptr, which clang leaves out of a destructor that
// destroys members only when the class is final. The constructor is inlined into GetInst (fn 599), which calls fn 5412
// for m_dataHora.
// The members, from the bodies that read and write them (their names are not in the target):
// +4  a bool slots 3, 4, 6 and 8 read (slot 8 returns the string "\xC1UDIO ATIVADO" when it is set), 7 sets, 2 clears;
// +8  the EEstado that slots 9 to 15 test, set and return, cleared by slot 2;
// +12 the api::CDateTime slot 17 sets from fn 5412 and slot 18 returns;
// +24 the identity typed (slot 21 sets it, slot 23 returns it), +40 its type (slots 22 and 24), +48 and +68 the
//     voter's and the main voter's identities (slots 25 and 26): each the return type of its getter's record in a
//     std::optional, the four optionals slot 20 resets, and the three with a destructor the ones the destructors destroy;
// +88 and +92 the state and the result of the voter's photo (slots 27 to 29 set them, slot 30 returns a
//     CApresentacaoFotoEleitor built from them, slot 2 clears both).
class CInformacaoThreadOperador final : public IInformacaoThreadOperador {
public:
    CInformacaoThreadOperador();

    virtual void Slot2() override;
    virtual bool Slot3() const override;
    virtual bool Slot4() const override;
    virtual bool Slot5() const override;
    virtual bool Slot6() const override;
    virtual void Slot7(bool valor) override;
    virtual std::string Slot8() const override;
    virtual bool Slot9() const override;
    virtual bool Slot10() const override;
    virtual bool Slot11() const override;
    virtual void Slot12() override;
    virtual void Slot13() override;
    virtual void Slot14() override;
    virtual EEstado Slot15() const override;
    virtual std::string Slot16() const override;
    virtual void Slot17() override;
    virtual api::CDateTime Slot18() const override;
    virtual bool Slot19() const override;
    virtual void Slot20() override;
    virtual void Slot21(const std::string& identidade) override;
    virtual void Slot22(ecourna::app::dados::ETipoIdentificadorEleitor tipo) override;
    virtual std::string GetIdentidadeDigitada() const override;
    virtual ecourna::app::dados::ETipoIdentificadorEleitor GetTipoIdentidadeDigitada() const override;
    virtual comum::md::CEleitorIdentidade GetIdentidadeEleitor() const override;
    virtual comum::md::CEleitorIdentidade GetIdentidadePrincipalEleitor() const override;
    virtual void Slot27() override;
    virtual void Slot28() override;
    virtual void Slot29(ecourna::app::dados::CApresentacaoFotoEleitor::EResultado resultado) override;
    virtual ecourna::app::dados::CApresentacaoFotoEleitor Slot30() const override;

private:
    bool m_audioAtivado;
    EEstado m_estado;
    api::CDateTime m_dataHora;
    std::optional<std::string> m_identidadeDigitada;
    std::optional<ecourna::app::dados::ETipoIdentificadorEleitor> m_tipoIdentidadeDigitada;
    std::optional<comum::md::CEleitorIdentidade> m_identidadeEleitor;
    std::optional<comum::md::CEleitorIdentidade> m_identidadePrincipalEleitor;
    ecourna::app::dados::CApresentacaoFotoEleitor::EEstado m_estadoApresentacaoFoto;
    ecourna::app::dados::CApresentacaoFotoEleitor::EResultado m_resultadoApresentacaoFoto;
};

} // namespace vota::impl
