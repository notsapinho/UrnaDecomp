// comum::md::CResultadoVotacao (this file's name and path are the reconstruction's choice: no record names the class's
// file; cresultadovotacao.h says what is recovered). It holds the constructor, target fn 3824, which has no record: its
// line is a choice. The constructor is out of line, and in another object than its one target caller's: fn 11629
// (comum::CGravadorBU::GravaResultado, cgravadorbu.cpp's records) calls it three times and does not hold it, and in
// the constructor's use band the functions of other objects lie between the two (fns 3821 to 3823, of
// gravadores/md/cenvelopegenerico.cpp and md/cseguranca.cpp). Its band neighbours on the other side are of
// gravadores/md/ (fns 3825 and 3826, cversoescontratos.cpp's and cdependenciascontratos.cpp's records), which is
// placement rule 2's reading for the directory.

#include "app/comum/gravadores/md/cresultadovotacao.h"

namespace comum::md {

CResultadoVotacao::CResultadoVotacao(uedword tipoCargo, ueword qtdComparecimento,
    const std::vector<CVotosCargo>& totaisVotosCargo)
    : m_tipoCargo(tipoCargo), m_qtdComparecimento(qtdComparecimento), m_totaisVotosCargo(totaisVotosCargo)
{
}

} // namespace comum::md
