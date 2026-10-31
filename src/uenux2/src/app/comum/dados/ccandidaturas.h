#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "api/io/cdatamap.h"
#include "app/comum/dados/md/candidatura/ccandidatura.h"

namespace comum {

// Recovered: the layout, 44 bytes, from the constructor and destructor (target fns 5811, 3786): an
// api::CDataMap<uedword, md::CCandidatura> at +0 (the candidacies by candidate, the cursor at +12, the name at +16, which
// 5811 builds from the literal "CCandidaturas"), a flag at +28, and the package versions by post at +32. That the first 28
// bytes are the base is evidence: fns 2268 and 2838 pass the singleton's own pointer to that CDataMap's GetCurrent (fn
// 1200). What the flag is for is not read. RecuperaVersaoPacote's record spells the parameter TCargoID, and the records of
// LoadFromFile the map's types (CCandidaturas::Container is the base's alias here, a choice). The other members are not
// reconstructed, and the data members' names are chosen.
class CCandidaturas : public api::CDataMap<uedword, md::CCandidatura> {
public:
    using TCargoID = md::TCargoID;

    static CCandidaturas& GetInst();

    CCandidaturas();
    ~CCandidaturas();

    const std::string RecuperaVersaoPacote(TCargoID cargo) const;

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
