// Reconstruction's note: comum::md::CDependenciasContratos (the file the records name): the constructor, which target
// fn 12098 holds inlined (no index; unrooted), and GetValor, their throws on their records' lines (27 and 59, column
// 15); their first lines are a choice (src/units/227-uenux2-contratos-cmontadorhash.mk says what each rests on).
#include "app/comum/gravadores/md/cdependenciascontratos.h"

#include <format>

#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum::md {

// (original lines 12-21: content not recovered)
#line 22
CDependenciasContratos::CDependenciasContratos(const std::string& arquivo)
    : m_arquivo(api::CIniFile::Carrega(arquivo))
{

    if (GetValor("tag") != "20260601173148") {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8662,
            std::format("Tag do arquivo de dependências de contratos inválida: [{}]. Tag atual: [{}]",
                GetValor("tag"), "20260601173148"));
    }
}

// (original lines 33-54: content not recovered)
#line 55
const std::string CDependenciasContratos::GetValor(const std::string& chave)
{
    const auto it = m_arquivo.FindKey(chave);
    if (it == m_arquivo.EndKey()) {
        throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8663, std::format("Propriedade inexistente: {}", chave));
    }
    return it->second.GetValor();
}

} // namespace comum::md
