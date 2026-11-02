// comum::CGravadorBU (/home/rubio/tse/uenux2/src/app/comum/gravadores/cgravadorbu.cpp, the file its records name): the
// static AcrescentaVotoVotavel, target fn 3820, whose throw sits on its record's line and column (221:23); the lines
// above it are blank, the original's content not recovered, and where the function starts is a choice. The file's other
// records (lines 484, 485, 542, 552, 560 and 636) belong to GravaResultado (fn 11629, slot 7), which holds LeChavePublica
// and MontaEntidadeBU inlined and is not written (src/units/200-uenux2-cgravadorbu-pending.cpp); the file ends here.

#include "app/comum/gravadores/cgravadorbu.h"

#include <format>

#include "app/comum/dados/ccandidaturas.h"
#include "app/comum/dados/cpartidos.h"
#include "app/comum/dados/md/processoeleitoral/ccargo.h"
#include "app/comum/gravadores/euecomumgravadoreserror.h"

namespace comum {

// (original lines 18-203: content not recovered)
#line 204
void CGravadorBU::AcrescentaVotoVotavel(TVetorVotosVotaveis& votos, md::CVoto::ETipo tipo, TCandidatoID candidato,
    TQtdEleitor quantidade, const md::CCargo& cargo)
{
    if (quantidade == 0) {
        return;
    }

    if (tipo == md::CVoto::BRANCO || tipo == md::CVoto::NULO || tipo == md::CVoto::NULO_CARGO_SEM_CANDIDATO) {
        votos.push_back(md::CVotosVotavel(tipo, candidato, quantidade));
    } else if (cargo.IsConsulta()) {
        votos.push_back(md::CVotosVotavel(tipo, candidato, quantidade, md::CIdentificacaoVotavel(candidato, 0)));
    } else {
        TPartidoID partido;
        const md::CCandidatura* candidatura = CCandidaturas::GetInst().Busca(cargo.GetID(), candidato);
        if (candidatura == nullptr) {
            const md::CPartido* legenda = CPartidos::GetInst().Find(candidato);
            if (legenda == nullptr) {
                throw CUeComumGravadoresError(EUE_COMUM_GRAVADORES_8638,
                    std::format("Candidato {} / cargo {} não existe", candidato, cargo.GetID()));
            }
            partido = legenda->GetNumero();
        } else {
            partido = candidatura->GetPartidoID();
        }
        votos.push_back(md::CVotosVotavel(tipo, candidato, quantidade, md::CIdentificacaoVotavel(candidato, partido)));
    }
}

} // namespace comum
