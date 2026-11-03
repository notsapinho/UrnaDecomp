// The reports' shared helpers (a note of the reconstruction, not TSE's text): no record names this file or its lines;
// auxiliaresrelatorio.h says what each function is.
#include "app/comum/relatorios/auxiliaresrelatorio.h"

#include "api/gui/cpaperformbuilder.h"
#include "app/comum/dados/md/chorarioverao.h"
#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"

namespace comum {

void ImprimeSeparador(api::CPaperFormBuilder& builder)
{
    builder.AddTextField(std::string(38, '='), static_cast<api::IPaper::EStyle>(1), api::ALINHAMENTO_CENTRO);
}

std::string FormataCodigoCarga(const md::estadoaplicacao::CDadoCorrespondencia& correspondencia)
{
    const std::string& codigo = correspondencia.GetCodigoCarga();
    return codigo.substr(0, 3) + "." + codigo.substr(3, 3) + "." + codigo.substr(6, 3) + "." + codigo.substr(9, 3) +
           "." + codigo.substr(12, 3) + "." + codigo.substr(15, 3) + "." + codigo.substr(18, 3) + "." +
           codigo.substr(21);
}

std::string FormataCodigoCargaResumido(const md::estadoaplicacao::CDadoCorrespondencia& correspondencia)
{
    const std::string& codigo = correspondencia.GetCodigoCarga();
    return codigo.substr(18, 3) + "." + codigo.substr(21);
}

void ImprimeAssinaturas(api::CPaperFormBuilder& builder)
{
    builder.AddTextField("ASSINATURAS", static_cast<api::IPaper::EStyle>(2), api::ALINHAMENTO_CENTRO);
    builder.AddNewLine(8);
}

std::string FormataInicioHorarioVerao(const md::CHorarioVerao& horarioVerao)
{
    return horarioVerao.GetInicio().Format("DD/MM/YYYY");
}

std::string FormataFimHorarioVerao(const md::CHorarioVerao& horarioVerao)
{
    return horarioVerao.GetFim().Format("DD/MM/YYYY");
}

} // namespace comum
