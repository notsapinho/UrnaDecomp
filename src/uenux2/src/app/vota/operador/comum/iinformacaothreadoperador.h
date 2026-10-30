#pragma once

#include <string>

#include "api/util/cdatetime.h"
#include "app/comum/dados/md/eleitor/celeitoridentidade.h"
#include "ecourna/app/dados/resultadournacadastro/capresentacaofotoeleitor.hpp"
#include "ecourna/app/dados/tiposbasicos.hpp"

namespace vota::impl {

// Recovered: the virtual destructor and the 29 members of slots 2 to 30, from the vtable of
// vota::impl::CInformacaoThreadOperador (vtable @1590108), the one class that implements it, and GetInst (record
// cinformacaothreadoperador.cpp:554, target fn 599). The target has this class's typeinfo and no vtable: every member
// is inline or pure. Four members are named by their records (slots 23 to 26, cinformacaothreadoperador.cpp:474 to
// :504), with the return types and const those records spell. No record, symbol or string names the other 25. Their
// names, their const (on the ones whose target body only reads) and their parameter and return types (from the wasm
// signatures and what the bodies store or return) are choices, as are the EEstadoBiometria type and its enumerators,
// and each name comes from what the callers of fn 599 and the strings beside them show:
//   slots 3 to 8  the audio flag. CHabilitaAudioManualmente (fn 10751) sets it through slot 7, reads it back through
//                 slot 6 and logs "Áudio ativado pelo mesário"; slot 5 reads the voter's register, and
//                 CHabilitaAudioEleitor (fn 10523) logs "Áudio ativado conforme cadastro" when it is true; slot 3 is
//                 the flag or slot 5; slot 8 returns the text of fn 10751's "ÁUDIO ATIVADO" label. Slot 4 reads the
//                 same flag as slot 6 and no call to it was found, so it keeps its slot's name.
//   slots 9 to 15 which fingerprint habilitated the voter: CDigitalReconhecida (fn 10481) sets 1 through slot 13,
//                 CRegistraDigitalOperador::ProcessTick (fn 10451) sets 2 through slot 12, and fn 10425, which
//                 holds CMostraEleitorVotando::SalvaHabilitacaoEleitor's records, switches on slot 15: 1 reads the
//                 voter's saved biometric data, 2 the operator's ("_Operador", "...biometria do mesário.").
//   slot 2        the only call is in CCancelaHabilitacaoEleitor's slot 2 (fn 10646).
//   slot 16       formats "{:04}" over a count: CEleitores +104, which fn 10566 tests beside "Nenhum eleitor votou".
//   slots 17, 18  CPedeIdentidade's slot 8 (fn 10676, which holds "Inspecione cabina e urna") compares slot 18 with
//                 now and, past it, calls slot 17, which draws a time 60 to 90 minutes from now (fn 5412).
//   slot 19       when it is true, CPedeIdentidade's slot 8 (fn 10676, through fn 2226) logs "Votacao foi bloqueada
//                 por horario"; the body compares now with an election date and the last vote.
//   slots 20-22   slot 20 resets the four optionals, called from CPedeIdentidade's slot 2 (fn 10680) right after
//                 "Aguardando digitação do identificador do eleitor"; 21 and 22 set what slots 23 and 24 return.
//   slots 27-30   the CApresentacaoFotoEleitor state and result: slot 27 EleitorSemFoto, 28 Apresentada, 29
//                 NaoApresentadaPorErro with its result, and slot 30 returns them built into one.
// No record names this header's file: the interface goes beside its implementation's file.
class IInformacaoThreadOperador {
public:
    // the three values slots 9 to 15 test, set and return (fns 10576 ... 2587); not in the target: the name and the
    // enumerators are chosen, see above
    enum EEstadoBiometria {
        SemBiometria,
        BiometriaEleitor,
        BiometriaOperador,
    };

    virtual ~IInformacaoThreadOperador() = default;

    virtual void CancelaHabilitacao() = 0;
    virtual bool IsAudioAtivado() const = 0;
    virtual bool Slot4() const = 0;
    virtual bool IsAudioAtivadoCadastro() const = 0;
    virtual bool IsAudioAtivadoMesario() const = 0;
    virtual void SetAudioAtivadoMesario(bool ativado) = 0;
    virtual std::string GetTextoAudio() const = 0;
    virtual bool IsBiometriaOperador() const = 0;
    virtual bool IsBiometriaEleitor() const = 0;
    virtual bool IsSemBiometria() const = 0;
    virtual void SetBiometriaOperador() = 0;
    virtual void SetBiometriaEleitor() = 0;
    virtual void LimpaBiometria() = 0;
    virtual EEstadoBiometria GetEstadoBiometria() const = 0;
    virtual std::string GetTextoComparecimento() const = 0;
    virtual void AgendaInspecao() = 0;
    virtual api::CDateTime GetDataHoraInspecao() const = 0;
    virtual bool IsVotacaoBloqueadaPorHorario() const = 0;
    virtual void LimpaIdentidades() = 0;
    virtual void SetIdentidadeDigitada(const std::string& identidade) = 0;
    virtual void SetTipoIdentidadeDigitada(ecourna::app::dados::ETipoIdentificadorEleitor tipo) = 0;
    virtual std::string GetIdentidadeDigitada() const = 0;
    virtual ecourna::app::dados::ETipoIdentificadorEleitor GetTipoIdentidadeDigitada() const = 0;
    virtual comum::md::CEleitorIdentidade GetIdentidadeEleitor() const = 0;
    virtual comum::md::CEleitorIdentidade GetIdentidadePrincipalEleitor() const = 0;
    virtual void SetEleitorSemFoto() = 0;
    virtual void SetFotoApresentada() = 0;
    virtual void SetFotoNaoApresentada(ecourna::app::dados::CApresentacaoFotoEleitor::EResultado resultado) = 0;
    virtual ecourna::app::dados::CApresentacaoFotoEleitor GetApresentacaoFotoEleitor() const = 0;

    static IInformacaoThreadOperador& GetInst();
};

} // namespace vota::impl
