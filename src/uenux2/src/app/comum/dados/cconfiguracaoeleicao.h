#pragma once

#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <vector>

#include "api/util/cdatetime.h"
#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/md/processoeleitoral/eorigemconfiguracao.h"
#include "app/comum/dados/md/processoeleitoral/cpleito.h"
#include "app/comum/nomearquivo/cnomearquivo.h"
#include "ecourna/app/dados/parametrizacaourna/cparametrosurna.hpp"
#include "ecourna/app/dados/processoeleitoral/cconfiguracaomunicipio.hpp"

namespace comum {

// Recovered: the layout, from the destructor (fn 5792) and the order of the constructor's record (line 239): a string at
// +8, the origin and a flag, a CPleito at +28, a CParametrosUrna at +88 (fn 2267), the municipality, two sets at +592 and
// +604, a string at +628, vectors at +652 and +672. The bytes between them have no reader here but the words the
// accessors below read. Which constructor argument each member holds beyond those, the element types (but +672's, which
// GetTiposIdentificador's comment reads) and the members' names are chosen.
class CConfiguracaoEleicao {
public:
    ~CConfiguracaoEleicao();

    static CConfiguracaoEleicao& GetInst();

    const md::CEleicaoPE& GetEleicao(const TEleicaoID eleicao) const;
    const md::CCargo& GetCargo(const TCargoID cargo) const;
    // Target fn 271 is f5648(this + 28, eleicao): CPleito::GetSituacoesEleicoes on the pleito at +28, out of line. Its
    // callers (1386, 3687, 5577, 5578, 5582, 11558, 11559) pass it GetInst's (fn 187) result at every call, and
    // 11558 and 11559 pass that result to GetCargo (fn 861) as well. No record names it: the name is chosen, from the
    // member it forwards to, and so is the parameter's type, 5648's.
    const md::CSituacoesEleicoes& GetSituacoesEleicoes(const TEleicaoID eleicao) const;

    // The names are chosen: CGravadorUtil::DeterminaNomeArquivoSemLetra (inlined into target fn 3798) reads the pleito's
    // identifier at +28 of the instance, and no record names an accessor; comum::CRelatorioTesteImpressora's slots read
    // the name at +8 (fn 11192), the origin at +20 (fn 11194), the pleito at +28 (fn 11191) and the parameters' header at
    // +188 (fn 11195).
    const std::string& GetNome() const { return m_nome; }
    // The name is chosen: comum::CGeradorBUQRCode's header fields (inlined into target fn 5604) print the word at +0 as
    // "PROC:{} ", an unsigned, under the label "ProcessoEleitoral". Its type beyond that width is chosen too.
    unsigned GetProcessoEleitoral() const { return m_processoEleitoral; }
    md::EOrigemConfiguracao GetOrigem() const { return m_origem; }
    const md::CPleito& GetPleito() const { return m_pleito; }
    const ecourna::app::dados::CParametrosUrna& GetParametrosUrna() const { return m_parametros; }
    // The municipality's configuration at +496: comum::CGeradorRelPU::ImprimeHorarios, held by vota::CImpressaoPU's slot 2
    // (fn 11902), reads the four ptimes of its schedule at +8 to +32 of the address it gets from GetInst() + 496. The
    // name is chosen.
    const ecourna::app::dados::CConfiguracaoMunicipio& GetConfiguracaoMunicipio() const { return m_municipio; }

    // The word at +668: vota::impl::CInformacaoThreadOperador's fn 2225 compares the type of the identity typed with
    // it (`i32.load[f187()+668]`) and, when they are equal, copies that identity into the one slot 26
    // (GetIdentidadePrincipalEleitor) returns. Its type is the type it is compared with; the names are chosen.
    ecourna::app::dados::ETipoIdentificadorEleitor GetTipoIdentificadorPrincipal() const { return m_tipoIdentificadorPrincipal; }

    // The byte at +665, tested as a bool (`i32.load8_u[f187()+665]` in fn 10313):
    // comum::IPedeTituloMesario::ProcessInput (fn 10313) goes on to comum::CPedeDigitalMesario, the request for the
    // mesario's fingerprint, only when it is set and CLocal::EhExterior() is false, and vota::CPedeDigital::StartState
    // (fn 10468), vota::CNomeEleitor's fn 10500 and fn 7787 read it too. That it says the biometric identification is on
    // is a reading of those uses; the names, and the types of the bytes around it, are chosen.
    bool HabilitaBiometria() const { return m_habilitaBiometria; }

    // The vector at +672: vota::CPedeIdentidade's screen (held inlined by fn 652) reads its 4-byte elements in order and
    // names each in "Digite {}" by the values 1, 2 and 3 of ETipoIdentificadorEleitor (TipoIDInscricaoEleitoral,
    // TipoIDCPF, TipoIDNumeroLivre) or else as "a Identidade". Its element type is a reading of that switch, and the
    // accessor's being inline in the class, its name and the member's name are chosen.
    const std::vector<ecourna::app::dados::ETipoIdentificadorEleitor>& GetTiposIdentificador() const
    {
        return m_tiposIdentificador;
    }

    // Two api::CDateTime of 12 bytes inside the bytes after the municipality: vota::CConfirmaImpressaoZeresima::GetInst
    // (fn 5959) and vota::CVerificaHorarioZeresima::GetInst (fn 5947) copy +544 (`i64.load[+544]`, `i32.load[+552]`),
    // the time the zerésima waits for (fn 11870 compares the current time with the copy); vota::CInicioVotacao::GetInst
    // (fn 2880) copies +556, formats the copy's time (fn 779, CTime::Format) and builds a form with "Votação a partir
    // das ", the start of the voting by a reading. The names are chosen from those uses.
    const api::CDateTime& GetDataHoraZeresima() const { return m_dataHoraZeresima; }
    const api::CDateTime& GetDataHoraInicioVotacao() const { return m_dataHoraInicioVotacao; }
    // A fourth api::CDateTime at +568: vota::CIniciaFinalizacao::StartState (fn 10706) lets the voting close only when
    // the current time is not before it, else logs "Encerramento só pode ser solicitado após as {} horas" with its time;
    // vota::CPedeTituloEncerramento::GetInst (fn 3631) copies it (`i64.load[+568]`, `i32.load[+576]`), and
    // vota::CEncerramentoHorarioInvalido::StartState (fn 10710) builds a time 10 seconds before it (CTime's -, fn 3641,
    // on +576). The earliest time to close the voting by a reading; the name is chosen from that.
    const api::CDateTime& GetDataHoraEncerramento() const { return m_dataHoraEncerramento; }

    // A third api::CDateTime at +580: vota::CVerificaEleicaoPassou::StartState (fn 11914) copies it (`i64.load[+580]`,
    // `i32.load[+588]`) and, when the current time is not before it, logs "Data da eleição inválida", posts message 0
    // with priority 100 to CThreadOperador's queue, beeps and stays in its state (that the message shuts the urna down
    // is a reading); vota::CInformacaoThreadOperador's slot 19 (fn 10566) compares the current time with it in place.
    // The end of the election by a reading; the name is chosen from that.
    const api::CDateTime& GetDataHoraFimEleicao() const { return m_dataHoraFimEleicao; }

    // The ids of the pleito's elections, in their order: target fn 5791, out of line (its callers, fns 1269 and 5735,
    // call it with GetInst()'s result), pushed one by one through std::vector's push_back(const&) (fn 543). Each cargo
    // of each election with that election's id, in that order: target fn 3774, out of line (fns 4454 and 7787 call it on
    // GetInst()'s result; 7787 holds CCargos::CreateInst, which builds CCargos' two vectors with it), each pair pushed
    // as one 8-byte value (src/units/88-uenux2-app-comum-dados-md-processoeleitoral.mk has the measurement). No record
    // names them: their names and their being members (they read m_pleito) are chosen.
    std::vector<md::TEleicaoID> GetIDsEleicoes() const;
    std::vector<CCargos::TCargoEleicao> GetCargosEleicoes() const;
    // A copy of the cargos of the pleito's election with that id, empty when the pleito has no such election, sorted by
    // the order of printing (the byte at +16) when the bool says so: target fn 3775, out of line (fns 5735, 7787 and
    // 11629 call it on GetInst()'s result). It reads m_pleito, calls CPleito::GetEleicao (fn 5651) and copies
    // CEleicaoPE::GetCargos (fn 2257); the sort's comparator is a function, passed by table slot 2363 (fn 11547). No
    // record names it: its name, the parameters' names, its being a member and the comparator's name and linkage are
    // chosen.
    std::vector<md::CCargo> GetCargos(const TEleicaoID eleicao, const bool ordenados) const;

    // +620 to +651: the election's part of a section's file name at +620 (SIdentificacaoArquivo, cnomearquivo.h, whose
    // string is the one at +628 the destructor frees), and the municipality at +644 and the 16-bit zone at +648, which
    // comum::CEleitorDetalhe::GetBiometria (fn 1937) and fn 7787 pass with it to fns 3745 and 5727. The members'
    // types are those widths and their names and the accessors' are chosen.
    const SIdentificacaoArquivo& GetIdentificacaoArquivo() const { return m_identificacaoArquivo; }
    uedword GetMunicipioSecao() const { return m_municipioSecao; }
    ueword GetZonaSecao() const { return m_zonaSecao; }
    // A copy of the set at +604. vota::CEleitorEncontrado::StartState (fn 10635) and fn 7787 each build an empty set in
    // their frame and fill it with fn 6733, std::set's range insert, from +604's begin and end: the copy constructor's
    // code. 10635 then looks for an element that is not 0 and destroys the copy with fn 1594, the destroy
    // splat/matched.txt names for this element type (the member's, chosen). The accessor, its name and its result by
    // value are chosen.
    std::set<ecourna::app::dados::ETipoIdentificadorEleitor> GetTipos() const { return m_tipos; }

private:
    unsigned m_processoEleitoral;
    unsigned m_naoRecuperado1;
    std::string m_nome;
    md::EOrigemConfiguracao m_origem;
    bool m_flag;
    md::CPleito m_pleito;
    ecourna::app::dados::CParametrosUrna m_parametros;
    ecourna::app::dados::CConfiguracaoMunicipio m_municipio;
    unsigned char m_naoRecuperado2[8];
    api::CDateTime m_dataHoraZeresima;
    api::CDateTime m_dataHoraInicioVotacao;
    api::CDateTime m_dataHoraEncerramento;
    api::CDateTime m_dataHoraFimEleicao;
    std::set<TCargoID> m_cargos;
    std::set<ecourna::app::dados::ETipoIdentificadorEleitor> m_tipos;
    unsigned m_naoRecuperado3;
    SIdentificacaoArquivo m_identificacaoArquivo;
    uedword m_municipioSecao;
    ueword m_zonaSecao;
    std::vector<int> m_lista1;
    unsigned char m_naoRecuperado5;
    bool m_habilitaBiometria;
    unsigned char m_naoRecuperado7[2];
    ecourna::app::dados::ETipoIdentificadorEleitor m_tipoIdentificadorPrincipal;
    std::vector<ecourna::app::dados::ETipoIdentificadorEleitor> m_tiposIdentificador;

    static std::unique_ptr<CConfiguracaoEleicao> s_instance;
    static std::mutex s_mutex;
};

} // namespace comum
