#include "app/comum/justificativa/cjustificador.h"
#include "app/comum/justificativa/cjustificadordetalhe.h"
#include "app/comum/justificativa/euecomumjustificativaerror.h"

namespace comum {

CJustificadorDetalhe::CJustificadorDetalhe(const CJustificadorDetalhe& outro) = default;

CJustificador::CJustificador() : CDataMap("CJustificador")
{
}

CJustificador::~CJustificador() = default;

CJustificador& CJustificador::GetInst()
{
    std::lock_guard<std::mutex> trava(s_mutex);
    if (!s_inst) {
        s_inst.reset(new CJustificador());
    }
    return *s_inst;
}

std::unique_ptr<CJustificador> CJustificador::s_inst;
std::mutex CJustificador::s_mutex;

// (original lines 27-51: content not recovered)
#line 52
// <stubs>
// f10590 · 4305 B · unmatched · name unknown
// void f10590(i32) { ... }
// </stubs>

// (original lines 57-99: content not recovered)
#line 100
std::string CJustificadorDadoTitulo::Text()
{
    const CJustificador& justificador = CJustificador::GetInst();
    if (justificador.IsFim()) {
        throw CUeComumJustificativaError(EUE_COMUM_JUSTIFICATIVA_INVALIDA, "Justificativa inválida");
    }
    return justificador.GetTituloCorrente().GetNumero();
}

} // namespace comum
