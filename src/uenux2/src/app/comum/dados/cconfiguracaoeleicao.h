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
#include "ecourna/app/dados/parametrizacaourna/cparametrosurna.hpp"
#include "ecourna/app/dados/processoeleitoral/cconfiguracaomunicipio.hpp"

namespace comum {

// Recovered: the layout, from the destructor (fn 5792) and the order of the constructor's record (line 239): a string at
// +8, the origin and a flag, a CPleito at +28, a CParametrosUrna at +88 (fn 2267), the municipality, two sets at +592 and
// +604, a string at +628, vectors at +652 and +672. The bytes between them have no reader here but the words the
// accessors below read. Which constructor argument each member holds beyond those, the element types and the members'
// names are chosen.
class CConfiguracaoEleicao {
public:
    ~CConfiguracaoEleicao();

    static CConfiguracaoEleicao& GetInst();

    const md::CEleicaoPE& GetEleicao(const TEleicaoID eleicao) const;
    const md::CCargo& GetCargo(const TCargoID cargo) const;

    // The names are chosen: CGravadorUtil::DeterminaNomeArquivoSemLetra (inlined into target fn 3798) reads the pleito's
    // identifier at +28 of the instance, and no record names an accessor; comum::CRelatorioTesteImpressora's slots read
    // the name at +8 (fn 11192), the origin at +20 (fn 11194), the pleito at +28 (fn 11191) and the parameters' header at
    // +188 (fn 11195).
    const std::string& GetNome() const { return m_nome; }
    md::EOrigemConfiguracao GetOrigem() const { return m_origem; }
    const md::CPleito& GetPleito() const { return m_pleito; }
    const ecourna::app::dados::CParametrosUrna& GetParametrosUrna() const { return m_parametros; }

    // The word at +668: vota::impl::CInformacaoThreadOperador's fn 2225 compares the type of the identity typed with
    // it (`i32.load[f187()+668]`) and, when they are equal, copies that identity into the one slot 26
    // (GetIdentidadePrincipalEleitor) returns. Its type is the type it is compared with; the names are chosen.
    ecourna::app::dados::ETipoIdentificadorEleitor GetTipoIdentificadorPrincipal() const { return m_tipoIdentificadorPrincipal; }

    // Two api::CDateTime of 12 bytes inside the bytes after the municipality: vota::CConfirmaImpressaoZeresima::GetInst
    // (fn 5959) and vota::CVerificaHorarioZeresima::GetInst (fn 5947) copy +544 (`i64.load[+544]`, `i32.load[+552]`),
    // the time the zerésima waits for (fn 11870 compares the current time with the copy); vota::CInicioVotacao::GetInst
    // (fn 2880) copies +556, formats the copy's time (fn 779, CTime::Format) and builds a form with "Votação a partir
    // das ", the start of the voting by a reading. The names are chosen from those uses.
    const api::CDateTime& GetDataHoraZeresima() const { return m_dataHoraZeresima; }
    const api::CDateTime& GetDataHoraInicioVotacao() const { return m_dataHoraInicioVotacao; }

    // A third api::CDateTime at +580: vota::CVerificaEleicaoPassou::StartState (fn 11914) copies it (`i64.load[+580]`,
    // `i32.load[+588]`) and, when the current time is not before it, logs "Data da eleição inválida" and shuts the urna
    // down; vota::CInformacaoThreadOperador's slot 19 (fn 10566) compares the current time with it in place. The end of
    // the election by a reading; the name is chosen from that.
    const api::CDateTime& GetDataHoraFimEleicao() const { return m_dataHoraFimEleicao; }

private:
    unsigned m_naoRecuperado1[2];
    std::string m_nome;
    md::EOrigemConfiguracao m_origem;
    bool m_flag;
    md::CPleito m_pleito;
    ecourna::app::dados::CParametrosUrna m_parametros;
    ecourna::app::dados::CConfiguracaoMunicipio m_municipio;
    unsigned char m_naoRecuperado2[8];
    api::CDateTime m_dataHoraZeresima;
    api::CDateTime m_dataHoraInicioVotacao;
    unsigned char m_naoRecuperado6[12];
    api::CDateTime m_dataHoraFimEleicao;
    std::set<TCargoID> m_cargos;
    std::set<ecourna::app::dados::ETipoIdentificadorEleitor> m_tipos;
    unsigned m_naoRecuperado3[3];
    std::string m_descricao;
    unsigned m_naoRecuperado4[3];
    std::vector<int> m_lista1;
    unsigned m_naoRecuperado5;
    ecourna::app::dados::ETipoIdentificadorEleitor m_tipoIdentificadorPrincipal;
    std::vector<int> m_lista2;

    static std::unique_ptr<CConfiguracaoEleicao> s_instance;
    static std::mutex s_mutex;
};

} // namespace comum
