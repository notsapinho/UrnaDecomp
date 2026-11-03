// Reconstruction: comum::md::CIDEleitoral's three factories (records cideleitoral.cpp:21, 29 and 37), which target fn
// 11437 holds inlined, each behind a stack-pointer prologue of its own (binaryen inlined them into
// Utils::DesconverteIdEleitoral). Each calls the constructor, which fn 1081 is; fragment 273 says where it is and why.
// The lines of the functions are the records'; the rest is blank where the original is not recovered.
#include "app/comum/md/cideleitoral.h"

#include "app/comum/md/euecomummderror.h"

namespace comum::md {

// (original lines 11-17: content not recovered)
#line 18
CIDEleitoral CIDEleitoral::CriaProcessoEleitoral(uedword id)
{
    if (id > 99999) {
        throw CUeComumMdError(EUE_COMUM_MD_8911, "ID inválido.");
    }
    return CIDEleitoral(id, TIPO_PROCESSO_ELEITORAL);
}

CIDEleitoral CIDEleitoral::CriaPleito(uedword id)
{
    if (id > 99999) {
        throw CUeComumMdError(EUE_COMUM_MD_8912, "ID inválido.");
    }
    return CIDEleitoral(id, TIPO_PLEITO);
}

CIDEleitoral CIDEleitoral::CriaEleicao(uedword id)
{
    if (id > 99999) {
        throw CUeComumMdError(EUE_COMUM_MD_8913, "ID inválido.");
    }
    return CIDEleitoral(id, TIPO_ELEICAO);
}

} // namespace comum::md
