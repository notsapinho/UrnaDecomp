// comum::CArquivosResultado (/home/rubio/tse/uenux2/src/app/comum/carquivosresultado.cpp). Its throw is a record of the
// target:
//   347  operator[](EExtensaoArquivoResultado) const  record at line 99, column 11

#include "app/comum/carquivosresultado.h"

#include <format>

#include "app/comum/euecomumerror.h"

namespace comum {

// (original lines 13-53: content not recovered)
#line 54
const std::string CArquivosResultado::operator[](EExtensaoArquivoResultado extensao) const
{
    switch (extensao) {
    case EXTENSAO_VOTA_VSC:
        return "vota.vsc";
    case EXTENSAO_SA_VSC:
        return "sa.vsc";
    case EXTENSAO_RED_VSC:
        return "red.vsc";
    case EXTENSAO_BU_DAT:
        return "bu.dat";
    case EXTENSAO_BUSA_DAT:
        return "busa.dat";
    case EXTENSAO_RDV_DAT:
        return "rdv.dat";
    case EXTENSAO_RDVRED_DAT:
        return "rdvred.dat";
    case EXTENSAO_JUFA_DAT:
        return "jufa.dat";
    case EXTENSAO_IMGBU_DAT:
        return "imgbu.dat";
    case EXTENSAO_IMGBUSA_DAT:
        return "imgbusa.dat";
    case EXTENSAO_IMGZE_DAT:
        return "imgze.dat";
    case EXTENSAO_HASH_DAT:
        return "hash.dat";
    case EXTENSAO_LOG_JEZ:
    case EXTENSAO_LOG_JEZ_2:
        return "log.jez";
    case EXTENSAO_LOGSA_JEZ:
        return "logsa.jez";
    case EXTENSAO_WSQBIO_JEZ:
        return "wsqbio.jez";
    case EXTENSAO_WSQMAN_JEZ:
        return "wsqman.jez";
    case EXTENSAO_WSQMES_JEZ:
        return "wsqmes.jez";
    case EXTENSAO_MR_VER:
        return "mr.ver";
    case EXTENSAO_ASW_VSC:
        return "asw.vsc";
    case EXTENSAO_AHW_VSC:
        return "ahw.vsc";
    }
    throw CUeComumError(EUE_COMUM_EXTENSAO_RESULTADO_NAO_ENCONTRADA, std::format("Extensão de arquivo de resultado associada ao identificador {} não encontrada", static_cast<int>(extensao)));
}

} // namespace comum
