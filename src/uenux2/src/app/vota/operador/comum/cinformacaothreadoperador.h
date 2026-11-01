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
// after the destructors, in vtable order). CancelaHabilitacao, the first member declared, is the key function. The
// destructors store no vptr, which clang leaves out of a destructor that destroys members only when the class is final.
// The constructor is inlined into GetInst (fn 599): it clears +4 and +8, sets +12 from SorteiaDataHoraInspecao (fn
// 5412), clears the optionals' flags and stores 0 into +88 and +92. SorteiaDataHoraInspecao draws the time of the next
// inspection, 60 to 90 minutes from now; slot 17 calls it too. Its name and its being a static member are chosen (it is
// external: src/units/50-uenux2-cinformacaothreadoperador.mk says how that was measured), and so is the constructor's
// being out of line in the .cpp.
// The members, from the bodies that read and write them (their names are not in the target):
// +4  a bool slots 3, 4, 6 and 8 read (slot 8 returns the string "\xC1UDIO ATIVADO" when it is set), 7 sets, 2 clears;
// +8  the EEstadoBiometria that slots 9 to 15 test, set and return, cleared by slot 2;
// +12 the api::CDateTime slot 17 sets from fn 5412 and slot 18 returns;
// +24 the identity typed (slot 21 sets it, slot 23 returns it), +40 its type (slots 22 and 24), +48 and +68 the
//     voter's and the main voter's identities (slots 25 and 26), which AtualizaIdentidadesEleitor (fn 2225, a chosen
//     name) sets from the first two after slots 21 and 22: each the return type of its getter's record in a
//     std::optional, the four optionals slot 20 resets, and the three with a destructor the ones the destructors
//     destroy;
// +88 and +92 the state and the result of the voter's photo (slots 27 to 29 set them, slot 30 returns a
//     CApresentacaoFotoEleitor built from them, slot 2 clears both).
class CInformacaoThreadOperador final : public IInformacaoThreadOperador {
public:
    CInformacaoThreadOperador();

    virtual void CancelaHabilitacao() override;
    virtual bool IsAudioAtivado() const override;
    virtual bool Slot4() const override;
    virtual bool IsAudioAtivadoCadastro() const override;
    virtual bool IsAudioAtivadoMesario() const override;
    virtual void SetAudioAtivadoMesario(bool ativado) override;
    virtual std::string GetTextoAudio() const override;
    virtual bool IsBiometriaOperador() const override;
    virtual bool IsBiometriaEleitor() const override;
    virtual bool IsSemBiometria() const override;
    virtual void SetBiometriaOperador() override;
    virtual void SetBiometriaEleitor() override;
    virtual void LimpaBiometria() override;
    virtual EEstadoBiometria GetEstadoBiometria() const override;
    virtual std::string GetTextoComparecimento() const override;
    virtual void AgendaInspecao() override;
    virtual api::CDateTime GetDataHoraInspecao() const override;
    virtual bool IsVotacaoBloqueadaPorHorario() const override;
    virtual void LimpaIdentidades() override;
    virtual void SetIdentidadeDigitada(const std::string& identidade) override;
    virtual void SetTipoIdentidadeDigitada(ecourna::app::dados::ETipoIdentificadorEleitor tipo) override;
    virtual std::string GetIdentidadeDigitada() const override;
    virtual ecourna::app::dados::ETipoIdentificadorEleitor GetTipoIdentidadeDigitada() const override;
    virtual comum::md::CEleitorIdentidade GetIdentidadeEleitor() const override;
    virtual comum::md::CEleitorIdentidade GetIdentidadePrincipalEleitor() const override;
    virtual void SetEleitorSemFoto() override;
    virtual void SetFotoApresentada() override;
    virtual void SetFotoNaoApresentada(ecourna::app::dados::CApresentacaoFotoEleitor::EResultado resultado) override;
    virtual ecourna::app::dados::CApresentacaoFotoEleitor GetApresentacaoFotoEleitor() const override;

private:
    static api::CDateTime SorteiaDataHoraInspecao();
    void AtualizaIdentidadesEleitor();

    bool m_audioAtivado;
    EEstadoBiometria m_estadoBiometria;
    api::CDateTime m_dataHoraInspecao;
    std::optional<std::string> m_identidadeDigitada;
    std::optional<ecourna::app::dados::ETipoIdentificadorEleitor> m_tipoIdentidadeDigitada;
    std::optional<comum::md::CEleitorIdentidade> m_identidadeEleitor;
    std::optional<comum::md::CEleitorIdentidade> m_identidadePrincipalEleitor;
    ecourna::app::dados::CApresentacaoFotoEleitor::EEstado m_estadoApresentacaoFoto;
    ecourna::app::dados::CApresentacaoFotoEleitor::EResultado m_resultadoApresentacaoFoto;
};

} // namespace vota::impl
