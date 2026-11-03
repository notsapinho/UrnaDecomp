#pragma once

#include <memory>
#include <mutex>
#include <string>

#include "app/comum/dados/md/estadoaplicacao/cestadogeral.h"
#include "app/comum/dados/md/processoeleitoral/cprocessoeleitoral.h"
#include "app/comum/eflashorigem.h"
#include "app/comum/eurnaturno.h"
#include "app/comum/nomearquivo/cnomearquivo.h"

namespace comum {

// Recovered: the layout, 204 bytes: CreateInst (fn 2787) allocates 204, copies a CProcessoEleitoral to +0, stores the
// load's turn at +176 and builds a SIdentificacaoArquivo at +180 through fn 5726; the destructor (fn 5598) frees the string at
// +188 and calls fn 2830 on +0. The members' names are chosen. CreateInst's record names its two parameters
// (cpe.cpp:26); the constructor, which CreateInst holds inlined, is chosen in its parameters as in its name.
class CPE {
public:
    ~CPE();

    static CPE& GetInst();
    static void CreateInst(const md::estadoaplicacao::CEstadoGeral& estadoGeral, const EFlashOrigem origem);
    // Fn 2788 (no record): a lock-guarded test of the pointer, CSubstituidorTitulo::Existe's shape. Its name is chosen.
    static bool Existe();

    // The name is chosen: comum::CRelatorioTesteImpressora's slot 14 (fn 11191) calls GetPleito2 on +0.
    const md::CProcessoEleitoral& GetProcessoEleitoral() const { return m_processo; }

private:
    CPE(const md::CProcessoEleitoral& processo, const EUrnaTurno turno, const EUrnaFase fase, const std::string& uf);

    md::CProcessoEleitoral m_processo;
    EUrnaTurno m_turno;
    SIdentificacaoArquivo m_identificacao;

    static std::mutex s_mutex;
    static std::unique_ptr<CPE> s_instancia;
};

} // namespace comum
