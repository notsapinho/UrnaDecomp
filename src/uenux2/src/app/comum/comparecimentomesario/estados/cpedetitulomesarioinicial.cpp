#include "app/comum/comparecimentomesario/estados/cpedetitulomesarioinicial.h"

#include <format>

#include "api/gui/cinteractiveform.h"
#include "api/gui/cmtformbuilder.h"
#include "api/pattern/cpolysingleton.h"
#include "app/comum/comparecimentomesario/cregistradormesario.h"
#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"
#include "app/vota/operador/outrasopcoes/cescolheopcao.h"

namespace comum {
namespace {

class CComparecimentoMesariosDS {
public:
    std::string operator()(const std::string& formato) const
    {
        const std::size_t quantidade = CRegistradorMesario::GetInst().QuantidadeMesariosInicio();
        return std::vformat(formato, std::make_format_args(quantidade));
    }
};

std::shared_ptr<api::CInteractiveForm<api::IScreenMT, api::IInputMT>> TelaPedeTituloMesario()
{
    api::CMTFormBuilder builder;
    builder.AddTextField("Informe o título do mesário: ", api::SPoint{1, 1}, api::ALINHAMENTO_ESQUERDA);
    builder.AddClock(api::SPoint{33, 1});
    builder.AddTextField("Quantidade de mesários registrados:", api::SPoint{1, 3}, api::ALINHAMENTO_ESQUERDA);
    builder.AddTextField(CComparecimentoMesariosDS(), api::SPoint{39, 3}, "{:02}");
    vota::AdicionaCampoNumerico(builder, 12, true, api::SPoint{1, 2});
    builder.AddTextField("CORRIGE: Encerrar  CONFIRMA: Prosseguir", api::SPoint{1, 4}, api::ALINHAMENTO_ESQUERDA);
    return builder.GetInteractiveForm("", true);
}

} // namespace

// (original lines 38-40: content not recovered)
#line 41
CPedeTituloMesarioInicial::CPedeTituloMesarioInicial()
    : IPedeTituloMesario(TelaPedeTituloMesario(), TelaEleitorRegistroMesarios(1))
{
    api::CPolySingleton<IControladorRegistraMesarios>::instance().LogaRegistrandoMesariosAntesVotacao();
}

CPedeTituloMesarioInicial& CPedeTituloMesarioInicial::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CPedeTituloMesarioInicial());
    }
    return *s_inst;
}

std::unique_ptr<CPedeTituloMesarioInicial> CPedeTituloMesarioInicial::s_inst;
std::mutex CPedeTituloMesarioInicial::s_mutex;

CPedeTituloMesarioInicial::~CPedeTituloMesarioInicial() = default;

int CPedeTituloMesarioInicial::Slot9() const
{
    return 1;
}

} // namespace comum
