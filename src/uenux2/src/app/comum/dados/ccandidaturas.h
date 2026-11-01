#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "api/io/cdatamap.h"
#include "app/comum/dados/md/candidatura/ccandidatura.h"

namespace comum {

// Recovered: the layout, 44 bytes, from the constructor and destructor (target fns 5811, 3786): an
// api::CDataMap<uedword, md::CCandidatura> at +0 (the candidacies by candidate, the cursor at +12, the name at +16, which
// 5811 builds from the literal "CCandidaturas"), a flag at +28, and the package versions by post at +32. The CDataMap at
// +0 is evidence (fns 2268 and 2838 pass the singleton's own pointer to its GetCurrent, fn 1200); that it is the base and
// not a member is a choice, read from siblings such as CEleitores, whose RTTI lists CDataMap as a base. The flag's use is
// not read. RecuperaVersaoPacote's record spells the parameter TCargoID, and the records of LoadFromFile the map's types
// (CCandidaturas::Container is the base's alias, a choice). Other members: not reconstructed; data members' names: chosen.
class CCandidaturas : public api::CDataMap<uedword, md::CCandidatura> {
public:
    using TCargoID = md::TCargoID;

    static CCandidaturas& GetInst();

    CCandidaturas();
    ~CCandidaturas();

    const std::string RecuperaVersaoPacote(TCargoID cargo) const;

    // Target fns 2272, 2271, 2840 and 1273. 2272 and 2271 share a use band, and the file defines them in its order
    // (ld_index). No record names them, and their names are chosen from what they return. The first three walk the candidacies (the base's map) and keep
    // those of one post whose holder's situation is 0, the value of an ESituacao enumerator not recovered;
    // GetCandidatosPartido keeps those of one party too when the party is not 0 (the target holds the loop twice, one
    // copy for each value of that test). Busca looks a candidacy up by the base's key, the post times 1000000 plus the
    // candidate, as Localiza (record line 56, not written) does, and moves the cursor to it: the base's Find, inlined.
    std::vector<TCandidatoID> GetCandidatosPartido(TCargoID cargo, TPartidoID partido) const;
    bool ExisteCandidato(TCargoID cargo) const;
    std::vector<TCandidatoID> GetCandidatos(TCargoID cargo) const;
    md::CCandidatura* Busca(TCargoID cargo, TCandidatoID candidato);

private:
    static std::unique_ptr<CCandidaturas> s_inst;
    static std::mutex s_mutex;

    bool m_carregado;
    std::map<uedword, std::string> m_versoesPacote;
};

// Record ccandidaturas.cpp:261 names it. Its target callers are CCandidaturasDSSexo's and CCandidaturasDSNome's call
// operators and the texts that hold CCandidaturasDSNumero's and CCandidaturasDSFoto's (fns 5806, 5807, 12742, 12641).
// The record does not show the linkage: external is chosen, and so is this declaration's place.
const md::CCandidatura& GetCandidaturaAtual(const std::string& funcao);

} // namespace comum
