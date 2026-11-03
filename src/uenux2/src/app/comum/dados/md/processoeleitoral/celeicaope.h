#pragma once

#include <set>
#include <string>
#include <vector>

#include "app/comum/dados/md/processoeleitoral/ccargo.h"
#include "app/comum/dados/md/rdv/cvotoscargos.h"

namespace comum::md {

// Recovered: the layout, 52 bytes (the stride of CPleito::GetEleicao, fn 5651), as the constructor, which fn 11371
// (comum::asn::CConversorEleicaoPE::DoDesconverte) holds inlined, stores it: the id at +0, which GetEleicao compares,
// the entity's idPleito at +4 and its optional idEleicaoPleito2 at +8 (0 when absent), the name at +12 (ValidaNome
// reads it), the abrangencia at +24, the cargos at +28 (GetCargos, fn 2257) and the entity's municipios, a std::vector
// of 4-byte elements, at +40. Records give ValidaNome's, ValidaOrdem's, ValidaCargos's and GetCargos's signatures,
// TVectorCargo included. The constructor's parameters, their order (the members') and every member's name are chosen;
// the names of +4 and +8 follow the entity's fields.
using TVectorCargo = std::vector<CCargo>;

class CEleicaoPE {
public:
    // Out of line in celeicaope.cpp, binaryen inlined it into fn 11371 (its frame opens there), with ValidaNome inlined
    // and ValidaCargos behind a frame of its own.
    CEleicaoPE(TEleicaoID id, unsigned int idPleito, TEleicaoID idEleicaoPleito2, const std::string& nome,
               ETipoAbrangencia abrangencia, const TVectorCargo& cargos, const std::vector<unsigned int>& municipios);

    TEleicaoID GetID() const { return m_id; }
    const TVectorCargo& GetCargos() const;
    // fn 5654: the set of the cargos' ids (byte +0 of each 140-byte element of +28), in a std::set of one-byte keys; fn
    // 5653: whether any cargo holds a candidate's detail (+84, CCargo's engaged flag of m_detalheCandidato). Both are out
    // of line (5654's caller 7787 and 5653's 3744 and 7787 keep the calls) and no record names them, so their names and
    // file are chosen.
    std::set<TCargoID> GetIDsCargos() const;
    bool PossuiCargoCandidato() const;
    // The name at +12, which comum::NomeEleicaoCorrente (fn 11556) copies; no record names it, so its name and its being
    // inline in the class are chosen.
    const std::string& GetNome() const { return m_nome; }

private:
    void ValidaNome() const;
    void ValidaOrdem(std::set<uebyte>& ordens, uebyte ordem, const std::string& nome) const;
    void ValidaCargos() const;

    TEleicaoID m_id;
    unsigned int m_idPleito;
    TEleicaoID m_idEleicaoPleito2;
    std::string m_nome;
    ETipoAbrangencia m_abrangencia;
    TVectorCargo m_cargos;
    std::vector<unsigned int> m_municipios;
};

} // namespace comum::md
