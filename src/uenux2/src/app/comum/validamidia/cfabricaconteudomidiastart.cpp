// comum::CFabricaConteudoMidiaStart::ConteudoIncializacao (inlined into its one caller, fn 11172) and the checks
// CValidaMidia calls (fns 5572, 2784, 5571; src/units/179-uenux2-cvalidamidia.mk). The reconstruction's own note: the
// file's one record is the throw's, line 62 column 19; every other line is chosen; the gaps stand for lost text.
#include "app/comum/validamidia/cfabricaconteudomidiastart.h"

#include <filesystem>
#include <format>
#include <map>

#include "api/util/cdirreader.h"
#include "api/util/csystem.h"
#include "app/comum/validamidia/euecomumvalidamidiaerror.h"

namespace comum {

namespace {

bool IndependeDoTurno(const EAplicativosDeUrna aplicativo);

} // namespace

// (original lines 22-30: content not recovered)
#line 31
std::vector<std::string> CFabricaConteudoMidiaStart::ConteudoIncializacao(const EAplicativosDeUrna aplicativo, const EUrnaTurno turno)
{
    if (turno == TURNO_1 || turno == TURNO_2 || IndependeDoTurno(aplicativo)) {
        std::vector<std::string> conteudo = {"infomidia.dat", "infomidia.vsc"};
        switch (aplicativo) {
        case eAplicativo07:
        case eAplicativo08:
        case eAplicativo09:
        case eAplicativo10:
            return {};
        case eAplicativo11:
        case eAplicativo12:
        case eAplicativo13:
        case eAplicativo14:
        case eAplicativo18:
            return conteudo;
        case eAplicativo15:
            conteudo.push_back("#regex#t[0-9]{5}[a-z]{2}-pkgsa\\.jez");
            conteudo.push_back("#regex#t[0-9]{5}[a-z]{2}-pkgsa\\.vsc");
            return conteudo;
        case eAplicativo16:
            conteudo.push_back("#regex#o[0-9]{5}[a-z]{2}-pkgsa\\.jez");
            conteudo.push_back("#regex#o[0-9]{5}[a-z]{2}-pkgsa\\.vsc");
            return conteudo;
        case eAplicativo17:
            conteudo.push_back("#regex#s[0-9]{5}[a-z]{2}-pkgsa\\.jez");
            conteudo.push_back("#regex#s[0-9]{5}[a-z]{2}-pkgsa\\.vsc");
            return conteudo;
        case eAplicativo20:
            return {"##.pub", "##.id", "##ue", "###ue##.vpe"};
        default:
            throw CUeComumValidaMidiaError(EUE_COMUM_VALIDA_MIDIA_APLICACAO_SEM_CONTEUDO,
                                           std::format("Não há mídia de resultado de inialização para a aplicação '{}'.", aplicativo));
        }
    }
    return {};
}

namespace {

bool IndependeDoTurno(const EAplicativosDeUrna aplicativo)
{
    switch (aplicativo) {
    case eAplicativo11:
    case eAplicativo12:
    case eAplicativo13:
    case eAplicativo14:
    case eAplicativo18:
    case eAplicativo20:
        return true;
    default:
        return false;
    }
}

} // namespace

} // namespace comum

namespace comum::impl {

std::vector<std::string> ArquivosPermitidos()
{
    return {
        "infomidia.dat",
        "infomidia.vsc",
        "turno2.jez",
        "turno2.vsc",
        "#regex#[ost][0-9]{5}[a-z]{2}-pkgsa\\.jez",
        "#regex#[ost][0-9]{5}[a-z]{2}-pkgsa\\.vsc",
        "#regex#[ost][0-9]{5}[a-z]{2}[0-9]{13}-[a-z]+\\.[a-z]+",
        "#regex#[ost][0-9]{5}[0-9]{4}[0-9]{4}[0-9]{8}-[a-z]+\\.[a-z]+",
        "#regex#[0-9]{8}\\.[ste|STE]",
        "ste.config",
        "#regex#[0-9]{2}.pub",
        "#regex#[0-9]{2}.id",
        "#regex#[0-9]{2}ue",
        "#regex#[0-9]{3}ue[0-9]{2}\\.vpe",
    };
}

namespace {

std::map<std::string, std::vector<std::string>> ArquivosDeSistema()
{
    return {
        {"macOS",
         {".DS_Store", ".AppleDouble", ".LSOverride", ".DocumentRevisions-V100", ".fseventsd", ".Spotlight-V100",
          ".TemporaryItems", ".Trashes", ".VolumeIcon.icns", ".com.apple.timemachine.donotpresent"}},
        {"Windows",
         {"Thumbs.db", "Thumbs.db:encryptable", "ehthumbs.db", "ehthumbs_vista.db", "System Volume Information",
          "$RECYCLE.BIN"}},
    };
}

} // namespace

SResultadoValidacao ValidaConteudo(const std::string& caminho, const std::vector<std::string>& esperados)
{
    RemoveArquivosDeSistema(caminho);

    if (!api::CSystem::ExistDir(caminho) || api::CSystem::IsEmptyDir(caminho)) {
        if (esperados.empty()) {
            return {true, 1};
        }
        return {false, 6};
    } else {
        api::CDirReader leitor(caminho);
        std::vector<std::string> arquivos;
        while (leitor.NextEntry()) {
            const std::string nome = leitor.GetEntryName();
            if (nome == "." || nome == "..") {
                continue;
            }
            if (leitor.IsDir()) {
                return {false, 7};
            }
            if (leitor.IsFile()) {
                arquivos.push_back(nome);
            }
        }
        leitor.Close();

        if (!esperados.empty() && esperados.size() > arquivos.size()) {
            return {false, 8};
        }
        if (!api::CasamTodos(arquivos, ArquivosPermitidos())) {
            return {false, 9};
        }
        if (!esperados.empty() && !api::CasamTodos(esperados, arquivos)) {
            return {false, 10};
        }
    }
    return {true, 2};
}

bool ConteudoValido(const std::string& caminho, const std::vector<std::string>& esperados)
{
    return ValidaConteudo(caminho, esperados).m_valida;
}

void RemoveArquivosDeSistema(const std::string& caminho)
{
    for (const auto& [sistema, arquivos] : ArquivosDeSistema()) {
        for (const std::string& arquivo : arquivos) {
            std::filesystem::remove_all(caminho + arquivo);
        }
    }
}

} // namespace comum::impl
