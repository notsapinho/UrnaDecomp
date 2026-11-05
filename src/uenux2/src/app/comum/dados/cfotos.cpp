// Reconstruction: comum::CFotos's singleton (target fns 2819, 11512, 11513), its constructor (3756) and destructor (2818).
// Their lines are a choice, above the records of GetFotoPara (lines 39, 51) and CFotos::Load (lines 111, 121, not
// reconstructed). GetImagem (3755) follows GetFotoPara, its line chosen: use band 3 puts it after the constructor.
#include "app/comum/dados/cfotos.h"

#include <format>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "api/util/csystem.h"
#include "app/comum/asn/cleitorasn.h"
#include "app/comum/dados/euecomumdadoserror.h"

namespace comum {

CFotos& CFotos::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst = std::make_unique<CFotos>();
    }
    return *s_inst;
}

std::unique_ptr<CFotos> CFotos::s_inst;
std::mutex CFotos::s_mutex;

CFotos::CFotos() : CFotos("CFotos") {}

CFotos::~CFotos() = default;


md::CFotoCandidato GetFotoPara(const std::string& nome, const SIndiceFoto& foto)
{
    const std::string arquivo = foto.arquivo;
    if (!api::CSystem::ExistFile(arquivo)) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7860, std::format("{} - arquivo [{}] da foto [{}] não encontrado", nome, arquivo, foto.indice.GetCodigo()));
    }
    return CLeitorASN::LeFotoCandidato(arquivo, foto.indice);
}

// (original lines 44-45: content not recovered)
#line 46
md::CFotoCandidato GetFotoPara(const std::string& nome, const std::string& id)
{
    CFotos& fotos = CFotos::GetInst();
    const auto it = fotos.m_fotos.find(id);
    if (it == fotos.m_fotos.end()) {
        throw CUeComumDadosError(EUE_COMUM_DADOS_7861, std::format("{} - id de foto [{}] não encontrado", nome, id));
    }
    fotos.m_atual = it;
    return GetFotoPara(nome, it->second);
}

std::vector<uint8_t> CFotos::GetImagem(const std::string& id)
{
    return GetFotoPara("CFotos::GetImagem(id)", id).GetFoto().GetImagem();
}

} // namespace comum
