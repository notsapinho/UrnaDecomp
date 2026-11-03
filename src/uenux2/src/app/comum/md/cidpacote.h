#pragma once

#include <optional>
#include <string>

#include "app/comum/eurnafase.h"
#include "app/comum/md/cideleitoral.h"
#include "app/comum/md/cidentificacaourna.h"

namespace comum::md {

// Recovered: the layout, 40 bytes: a CIDEleitoral at +0, the phase at +8, then three optional fields, each with its
// engaged flag: a string at +12 (flag at +24), a 32-bit word at +28 (flag at +32) and a 16-bit word at +36 (flag at +38).
// fn 11437 holds Utils::DesconverteIdPacote, and in it four constructors, one per count of optional fields present, each
// behind a stack-pointer prologue of its own (binaryen inlined them from cidpacote.cpp); each stores the identifier
// and the phase, the fields it takes and the empty ones, then tests the phase (CIDPacoteValidar, record
// cidpacote.cpp:21). The elements' copy (fn 5669) and the vector's destroy (fn 3863) read the same layout. The three
// getters are the records' (cidpacote.cpp:67, 75 and 83, whose return types say which optional is which; fn 11438 holds
// them, each testing the flag before it reads). The constructors' parameters, the inline getters, the member names and
// this header's path are chosen.
class CIDPacote {
public:
    CIDPacote(const CIDEleitoral& idEleitoral, const EUrnaFase fase);
    CIDPacote(const CIDEleitoral& idEleitoral, const EUrnaFase fase, const std::string& uf);
    CIDPacote(const CIDEleitoral& idEleitoral, const EUrnaFase fase, const std::string& uf, const TMunicipioID municipio);
    CIDPacote(const CIDEleitoral& idEleitoral, const EUrnaFase fase, const std::string& uf, const TMunicipioID municipio,
        const TZonaID zona);

    const CIDEleitoral& GetIdEleitoral() const { return m_idEleitoral; }
    EUrnaFase GetFase() const { return m_fase; }
    bool TemUF() const { return m_uf.has_value(); }
    bool TemMunicipio() const { return m_municipio.has_value(); }
    bool TemZona() const { return m_zona.has_value(); }

    std::string UF() const;
    TMunicipioID Municipio() const;
    TZonaID Zona() const;

private:
    CIDEleitoral m_idEleitoral;
    EUrnaFase m_fase;
    std::optional<std::string> m_uf;
    std::optional<TMunicipioID> m_municipio;
    std::optional<TZonaID> m_zona;
};

} // namespace comum::md
