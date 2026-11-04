// comum::md::CVotosCargo's constructor (no record; this file's name and path are the reconstruction's choice,
// cvotoscargo.h says why it is out of line): its one target caller, fn 3819 (comum::MontaVotosCargos), holds it inlined
// by binaryen, so it has no index of its own and is compared only inside 3819.
#include "app/comum/gravadores/md/cvotoscargo.h"

namespace comum::md {

CVotosCargo::CVotosCargo(TCargoID codigoCargo, uebyte ordemImpressao, const std::vector<CVotosVotavel>& votosVotaveis)
    : m_codigoCargo(codigoCargo), m_ordemImpressao(ordemImpressao), m_votosVotaveis(votosVotaveis)
{
}

} // namespace comum::md
