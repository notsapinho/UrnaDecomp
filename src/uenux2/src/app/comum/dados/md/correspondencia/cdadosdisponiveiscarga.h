#pragma once

#include <string>
#include <vector>

#include "app/comum/dados/md/cinfomunicipio.h"
#include "app/comum/dados/md/csecaoeleitoral.h"
#include "app/comum/eurnafase.h"
#include "app/comum/md/ccabecalhopacote.h"
#include "app/comum/md/cidentificacaourna.h"
#include "ecourna/api/uetypes.hpp"

namespace comum {

// The constructor's record spells these two comum:: (cdadosdisponiveiscarga.cpp:41); the bodies give their width, the
// 32-bit stores at +4 and +8 of CDadosDisponiveisCarga. uedword among the 32-bit unsigned types, and declaring them here,
// are choices.
using TProcessoEleitoralID = uedword;
using TPleitoID = uedword;

namespace md {

// Recovered: the layout only, 56 bytes, from comum::asn::CConversorDadosDisponiveisCarga::DoDesconverte (target fn
// 11423), which builds one per ModuloDadosDisponiveisCarga::MunicipioDisponivel from a CInfoMunicipio and the vector of
// its sections, then copies it into the vector CDadosDisponiveisCarga's constructor takes: the CInfoMunicipio at +0 (its
// code, its name, then 25 bytes as words) and the sections' vector at +44, copied through fn 2807. The vector's destroy
// (fn 5956) frees the same two. No record names the class: the record of CDadosDisponiveisCarga's constructor prints it
// unqualified, inside std::vector. Its name, its namespace, the composition (a CInfoMunicipio member, not a base), the
// getters and the member names are chosen, and so is declaring it in this header. The constructor is out of line, in
// cdadosdisponiveiscarga.cpp (a choice of file; fragment 245 has the measurement that puts it in another TU than
// DoDesconverte).
class CMunicipioDisponivel {
public:
    CMunicipioDisponivel(const CInfoMunicipio& municipio, const std::vector<CSecaoEleitoral>& secoes);

    const CInfoMunicipio& GetMunicipio() const { return m_municipio; }
    const std::vector<CSecaoEleitoral>& GetSecoes() const { return m_secoes; }

private:
    CInfoMunicipio m_municipio;
    std::vector<CSecaoEleitoral> m_secoes;
};

// Recovered: the layout, 88 bytes, and the constructor (records cdadosdisponiveiscarga.cpp:41 to :69), which target fn
// 11423, comum::asn::CConversorDadosDisponiveisCarga::DoDesconverte, holds inlined by binaryen (a second stack-pointer
// prologue): the phase at +0, the electoral process at +4, the pleito at +8, four strings at +12, +24, +36 and +48, the
// zone at +60 (a 16-bit store), the municipalities at +64 and the imported packages at +76. Which string is which is
// read from the entity's fields DoDesconverte copies into each, which the constructor's messages agree with: +12 is
// serialFlashCarga (code 8043 when its size is not 8), +24 pais, +36 and +48 the UF's sigla and nome. The order of the
// four string parameters is chosen (the members' order), and so are the member and getter names. The getters are what
// CConversorDadosDisponiveisCarga::DoConverte (target fn 11424) reads.
class CDadosDisponiveisCarga {
public:
    CDadosDisponiveisCarga(EUrnaFase fase, comum::TProcessoEleitoralID idPE, comum::TPleitoID idPleito,
        const std::string& serialFlashCarga, const std::string& pais, const std::string& siglaUF,
        const std::string& nomeUF, comum::TZonaID zona, const std::vector<CMunicipioDisponivel>& municipios,
        const std::vector<CCabecalhoPacote>& pacotes);

    EUrnaFase GetFase() const { return m_fase; }
    comum::TProcessoEleitoralID GetIdPE() const { return m_idPE; }
    comum::TPleitoID GetIdPleito() const { return m_idPleito; }
    const std::string& GetSerialFlashCarga() const { return m_serialFlashCarga; }
    const std::string& GetPais() const { return m_pais; }
    const std::string& GetSiglaUF() const { return m_siglaUF; }
    const std::string& GetNomeUF() const { return m_nomeUF; }
    comum::TZonaID GetZona() const { return m_zona; }
    const std::vector<CMunicipioDisponivel>& GetMunicipios() const { return m_municipios; }
    const std::vector<CCabecalhoPacote>& GetPacotes() const { return m_pacotes; }

private:
    EUrnaFase m_fase;
    comum::TProcessoEleitoralID m_idPE;
    comum::TPleitoID m_idPleito;
    std::string m_serialFlashCarga;
    std::string m_pais;
    std::string m_siglaUF;
    std::string m_nomeUF;
    comum::TZonaID m_zona;
    std::vector<CMunicipioDisponivel> m_municipios;
    std::vector<CCabecalhoPacote> m_pacotes;
};

} // namespace md
} // namespace comum
