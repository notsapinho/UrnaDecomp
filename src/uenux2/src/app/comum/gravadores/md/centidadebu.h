#pragma once

#include <optional>
#include <string>
#include <vector>

#include "api/util/cdatetime.h"
#include "app/comum/eurnafase.h"
#include "app/comum/gravadores/md/cdadosbusa.h"
#include "app/comum/gravadores/md/cdadosbuvota.h"
#include "app/comum/gravadores/md/chistoricovotoimpresso.h"
#include "app/comum/gravadores/md/cresultadovotacaoporeleicao.h"
#include "app/comum/gravadores/md/curna.h"
#include "app/comum/md/ccabecalhoentidade.h"
#include "app/comum/md/cidentificacaosecao.h"
#include "ecourna/app/dados/cdetalhamentocomparecimento.hpp"

namespace comum::md {

// The BU's data, the DADO of comum::asn::CConversorEntidadeBU (its RTTI's base names the class). Its records are
// centidadebu.cpp's: ValidaCriacao (lines 159 to 177, held by target fn 11629, not written) and GetDadosVota,
// GetDadosSA and GetDetalhamentoComparecimento (lines 186, 196 and 206, held by fn 10273, which binaryen inlines them
// into: each is out of line in centidadebu.cpp, its frame of 16 bytes opening inside 10273's). Recovered: the layout,
// 288 bytes, from the converter's DoConverte (fn 10273), which reads every member, and from the stores of
// comum::CGravadorBU::MontaEntidadeBU (record cgravadorbu.cpp:636, inlined into fn 11629) into +160 to +174:
// - +0, +20 and +24: the entity header, the phase and the urna, which fn 10273 hands to their converters (fn 2275,
//   IConversorASN<ModuloTiposEleitorais::CabecalhoEntidade, md::CCabecalhoEntidade>::Converte; fn 1712,
//   comum::asn::Utils::ConverteFase, which takes a copy of the phase, so GetFase returns it by value; fn 3799, the
//   urna's Converte). CUrna's 136 bytes end at +160;
// - +160 to +175: the section's municipality (32 bits), zone (16), place (32: fn 11629 stores it with i32.store, from
//   the 32-bit word at +12 of a comum::md::CIdentificacaoSecao) and section (16), and the attendance (16, fn 10273's
//   qtdEleitoresCompareceram), the widths of fn 11629's stores; fn 10273 loads the place with i32.load16_u, which
//   GetLocal's ueword gives (returning the member's TLocalID gives an i32.load: unit 321's fragment), a narrowing in
//   the getter or in the converter's call that the bytes do not tell apart;
// - +176 and +188: two vectors, of the 20-byte md::CResultadoVotacaoPorEleicao and of std::string (MontaEntidadeBU's
//   record takes a const std::vector<std::string> &, and fn 10273 builds ModuloRegistroDigitalVoto's
//   HistoricoCodigosCarga from it, a GeneralString per element);
// - +200 and +244: std::optional<md::CDadosBUVota> (40 bytes, engaged at +240) and std::optional<md::CDadosBUSA> (8
//   bytes, engaged at +252): GetDadosVota and GetDadosSA throw when theirs is empty, and fn 10273 tests the two bytes
//   before it calls them;
// - +256: the issue's api::CDateTime (fn 1080, ConverteDataHoraJE, takes its address for dataHoraEmissao);
// - +268: a vector of the 20-byte md::CHistoricoVotoImpresso, which fn 10273 hands one by one to
//   comum::asn::CConversorHistoricoVotoImpresso;
// - +280: std::optional<ecourna::app::dados::CDetalhamentoComparecimento> (6 bytes, engaged at +286), handed to
//   ecourna's CConversorDetalhamentoComparecimento.
// The members follow ModuloBoletimUrna::EntidadeBoletimUrna's fields; their names, the getters' names and whether each
// returns a reference or a value where the bytes do not show it are chosen, and so is the header's path, beside
// centidadebu.cpp in the directory its records name. The constructor is not recovered (MontaEntidadeBU holds it
// inlined), so nothing may construct the class.
class CEntidadeBU {
public:
    const CCabecalhoEntidade& GetCabecalho() const { return m_cabecalho; }
    EUrnaFase GetFase() const { return m_fase; }
    const CUrna& GetUrna() const { return m_urna; }
    TMunicipioID GetMunicipio() const { return m_municipio; }
    TZonaID GetZona() const { return m_zona; }
    ueword GetLocal() const { return m_local; }
    TSecaoID GetSecao() const { return m_secao; }
    ueword GetQtdEleitoresCompareceram() const { return m_qtdEleitoresCompareceram; }
    const std::vector<CResultadoVotacaoPorEleicao>& GetResultadosVotacaoPorEleicao() const
    {
        return m_resultadosVotacaoPorEleicao;
    }
    const std::vector<std::string>& GetHistoricoCodigosCarga() const { return m_historicoCodigosCarga; }
    bool TemDadosVota() const { return m_dadosVota.has_value(); }
    const CDadosBUVota& GetDadosVota() const;
    bool TemDadosSA() const { return m_dadosSA.has_value(); }
    const CDadosBUSA& GetDadosSA() const;
    const api::CDateTime& GetDataHoraEmissao() const { return m_dataHoraEmissao; }
    const std::vector<CHistoricoVotoImpresso>& GetHistoricoVotoImpresso() const { return m_historicoVotoImpresso; }
    bool TemDetalhamentoComparecimento() const { return m_detalhamentoComparecimento.has_value(); }
    const ecourna::app::dados::CDetalhamentoComparecimento& GetDetalhamentoComparecimento() const;

private:
    CCabecalhoEntidade m_cabecalho;
    EUrnaFase m_fase;
    CUrna m_urna;
    TMunicipioID m_municipio;
    TZonaID m_zona;
    TLocalID m_local;
    TSecaoID m_secao;
    ueword m_qtdEleitoresCompareceram;
    std::vector<CResultadoVotacaoPorEleicao> m_resultadosVotacaoPorEleicao;
    std::vector<std::string> m_historicoCodigosCarga;
    std::optional<CDadosBUVota> m_dadosVota;
    std::optional<CDadosBUSA> m_dadosSA;
    api::CDateTime m_dataHoraEmissao;
    std::vector<CHistoricoVotoImpresso> m_historicoVotoImpresso;
    std::optional<ecourna::app::dados::CDetalhamentoComparecimento> m_detalhamentoComparecimento;
};

} // namespace comum::md
