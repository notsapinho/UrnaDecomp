#pragma once

#include <map>
#include <optional>
#include <vector>

#include "app/comum/dados/md/eleitor/cdedo.h"
#include "app/comum/dados/md/estadoaplicacao/eurna.h"
#include "ecourna/app/dados/cfoto.hpp"

namespace comum::md {

// The code at +36 of a CBiometriaEleitor: vota::CDigitalNaoReconhecidaDecBiometria::StartState (fn 10478) logs "Erro ao
// decifrar a biometria do eleitor - Código ({})" when it is above 0, a signed compare (`i32.le_s` with 0), formatting it
// through a handle of its own (argument code 15, table slot 4091, which holds fn 536, the body of the handles that
// format as unsigned). So it is an enum with no fixed type and a formatter over unsigned int (comum::SFormatoEnum); 0
// is no error, a reading of that test. The enum's name is chosen and its enumerators are not recovered.
enum EErroDecifracaoBiometria {};

// A voter's biometrics. No vtable and no RTTI. Recovered: the layout, 40 bytes. fn 11422 builds one: an optional
// ecourna::app::dados::CFoto at +0 (its flag at +16, the record of GetFoto at line 115 names the type), an optional
// map of the fingers at +20 (its flag at +32; the map's root at +24, a node's key at +16 and a CDedo at +20) and 4
// bytes at +36 it sets to 0, the decryption's error code (EErroDecifracaoBiometria above). The members' names are
// chosen. CriaComum's parameter is the record's, a by-value std::vector<CDedo>; private is chosen.
// TemDedos, the test of +32 that fn 10512 (vota::CControlaReconhecimento::StartState) reads on GetCurrentBiometriaEleitor's
// result, and GetErroDecifracao, the read of +36 fn 10478 makes, are inline; their names are chosen.
class CBiometriaEleitor {
public:
    CDedo GetDedo(CDedo::TipoDedo tipo) const;
    bool TemDedo(CDedo::TipoDedo tipo) const;
    bool TemDedos() const { return m_dedos.has_value(); }
    EErroDecifracaoBiometria GetErroDecifracao() const { return m_erroDecifracao; }

private:
    void CriaComum(std::vector<CDedo> dedos);

    std::optional<ecourna::app::dados::CFoto> m_foto;
    std::optional<std::map<CDedo::TipoDedo, CDedo>> m_dedos;
    EErroDecifracaoBiometria m_erroDecifracao;
};

} // namespace comum::md

template <>
struct std::formatter<comum::md::EErroDecifracaoBiometria> : comum::SFormatoEnum {};
