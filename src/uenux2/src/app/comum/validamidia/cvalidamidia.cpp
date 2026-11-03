// comum::impl::CValidaMidia's slots 2 to 9 (target fns 11173 to 11166), with
// EhValida (slot 2) its key function (cvalidamidia.h), and comum::impl::IValidaMidia::GetInst (target fn 5575). The
// reconstruction's own note: the file's one record is GetInst's, line 182 column 76, the closing parenthesis of
// POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO's invocation (api/pattern/polysingletongetinst.h;
// src/units/179-uenux2-cvalidamidia.mk says what the target shows); no record places the slots, so their lines, above
// GetInst in the order the target's use band gives, are chosen.
#include "app/comum/validamidia/cvalidamidia.h"

#include <format>
#include <string>
#include <vector>

#include "api/pattern/polysingletongetinst.h"
#include "api/util/csystem.h"
#include "api/util/uedebug.h"
#include "app/comum/cpath.h"
#include "app/comum/validamidia/cfabricaconteudomidiastart.h"

namespace comum::impl {

bool CValidaMidia::EhValida(EAplicativosDeUrna aplicativo, EUrnaTurno turno)
{
    return Valida(aplicativo, turno).m_valida;
}

SResultadoValidacao CValidaMidia::Valida(EAplicativosDeUrna aplicativo, EUrnaTurno turno)
{
    if (aplicativo < eAplicativo01 || aplicativo > eAplicativo20) {
        return {false, 4};
    }

    if (turno != TURNO_1 && turno != TURNO_2 &&
        (aplicativo == eAplicativo07 || aplicativo == eAplicativo08 || aplicativo == eAplicativo09 ||
         aplicativo == eAplicativo10 || aplicativo == eAplicativo16 || aplicativo == eAplicativo17 ||
         aplicativo == eAplicativo15)) {
        return {false, 5};
    }

    const std::vector<std::string> conteudo = CFabricaConteudoMidiaStart::ConteudoIncializacao(aplicativo, turno);
    const SResultadoValidacao resultado = ValidaConteudo(CPath::GetPathMR(), conteudo);
    if (resultado.m_motivo >= 4) {
        DepuraInfo("mídia inválida [%d] arquivos:", resultado.m_motivo);
        for (const std::string& arquivo : conteudo) {
            DepuraInfo("- %s", arquivo.c_str());
        }
    }
    return resultado;
}

bool CValidaMidia::ContemApenasArquivosPermitidos()
{
    return ConteudoValido(CPath::GetPathMR(), {});
}

bool CValidaMidia::ContemResultado(unsigned int municipio, const std::string& uf, unsigned int zona, unsigned int secao,
                                   unsigned int numero, char fase)
{
    const std::string padrao =
        std::format("#regex#{}{:05}{}{:05}{:04}{:04}-[a-z]+\\.[a-z]+", fase, municipio, uf, zona, secao, numero);
    const std::vector<std::string> esperados = {padrao};
    return ConteudoValido(CPath::GetPathMR(), esperados);
}

bool CValidaMidia::ContemArquivosResultado()
{
    const std::vector<std::string> esperados = {"#regex#[ost][0-9]{5}[a-z]{2}[0-9]{13}-[a-z]+\\.[a-z]+"};
    return ConteudoValido(CPath::GetPathMR(), esperados);
}

bool CValidaMidia::ContemArquivo(const std::string& arquivo)
{
    const std::vector<std::string> esperados = {arquivo};
    return ConteudoValido(CPath::GetPathMR(), esperados);
}

bool CValidaMidia::ContemApenasArquivosResultado()
{
    const std::vector<std::string> esperados = {"#regex#[ost][0-9]{5}[a-z]{2}[0-9]{13}-[a-z]+\\.[a-z]+"};
    return api::DiretorioContemApenas(CPath::GetPathMR(), esperados);
}

void CValidaMidia::LimpaMidia()
{
    RemoveArquivosDeSistema(CPath::GetPathMR());
}

// (original lines 87-181: content not recovered)
#line 182
POLYSINGLETON_IMPL_GET_INST_COM_INSTANCIA_PADRAO(IValidaMidia, CValidaMidia)

} // namespace comum::impl
