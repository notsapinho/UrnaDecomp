#pragma once

#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <vector>

#include "app/comum/dados/ccargos.h"
#include "app/comum/dados/md/processoeleitoral/eorigemconfiguracao.h"
#include "app/comum/dados/md/processoeleitoral/cpleito.h"
#include "ecourna/app/dados/parametrizacaourna/cparametrosurna.hpp"
#include "ecourna/app/dados/processoeleitoral/cconfiguracaomunicipio.hpp"

namespace comum {

// Recovered: the layout, from the destructor (fn 5792) and the order of the constructor's record (line 239): a string at
// +8, the origin and a flag, a CPleito at +28, a CParametrosUrna at +88 (fn 2267), the municipality, two sets at +592 and
// +604, a string at +628, vectors at +652 and +672. The bytes between them have no reader here. Which constructor
// argument each member holds beyond those, the element types and the members' names are chosen.
class CConfiguracaoEleicao {
public:
    ~CConfiguracaoEleicao();

    static CConfiguracaoEleicao& GetInst();

    const md::CEleicaoPE& GetEleicao(const TEleicaoID eleicao) const;
    const md::CCargo& GetCargo(const TCargoID cargo) const;

    // The names are chosen: comum::CRelatorioTesteImpressora's slots read the name at +8 (fn 11192), the origin at +20
    // (fn 11194), the pleito at +28 (fn 11191) and the parameters' header at +188 (fn 11195).
    const std::string& GetNome() const { return m_nome; }
    md::EOrigemConfiguracao GetOrigem() const { return m_origem; }
    const md::CPleito& GetPleito() const { return m_pleito; }
    const ecourna::app::dados::CParametrosUrna& GetParametrosUrna() const { return m_parametros; }

private:
    unsigned m_naoRecuperado1[2];
    std::string m_nome;
    md::EOrigemConfiguracao m_origem;
    bool m_flag;
    md::CPleito m_pleito;
    ecourna::app::dados::CParametrosUrna m_parametros;
    ecourna::app::dados::CConfiguracaoMunicipio m_municipio;
    unsigned char m_naoRecuperado2[56];
    std::set<TCargoID> m_cargos;
    std::set<ecourna::app::dados::ETipoIdentificadorEleitor> m_tipos;
    unsigned m_naoRecuperado3[3];
    std::string m_descricao;
    unsigned m_naoRecuperado4[3];
    std::vector<int> m_lista1;
    unsigned m_naoRecuperado5[2];
    std::vector<int> m_lista2;

    static std::unique_ptr<CConfiguracaoEleicao> s_instance;
    static std::mutex s_mutex;
};

} // namespace comum
