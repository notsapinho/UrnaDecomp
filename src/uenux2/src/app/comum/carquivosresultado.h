#pragma once

// comum::CArquivosResultado: the file name of each kind of result file. operator[] reads nothing of the object (fn 347
// has lost `this`: binaryen removed the unused parameter), so no member is recovered and the class's other members are
// not reconstructed. The header's path is chosen.

#include <string>

namespace comum {

// The kinds of result file. iresultado.h declares the type (opaque, as comum::IResultado keeps it); its values are the
// cases of fn 347. Each name is chosen from the file name the case returns: no evidence names an enumerator. 13 and 14
// return the same name, and which of them is the log of a second file is not recovered.
enum EExtensaoArquivoResultado : int {
    EXTENSAO_VOTA_VSC = 1,
    EXTENSAO_SA_VSC = 2,
    EXTENSAO_RED_VSC = 3,
    EXTENSAO_BU_DAT = 4,
    EXTENSAO_BUSA_DAT = 5,
    EXTENSAO_RDV_DAT = 6,
    EXTENSAO_RDVRED_DAT = 7,
    EXTENSAO_JUFA_DAT = 8,
    EXTENSAO_IMGBU_DAT = 9,
    EXTENSAO_IMGBUSA_DAT = 10,
    EXTENSAO_IMGZE_DAT = 11,
    EXTENSAO_HASH_DAT = 12,
    EXTENSAO_LOG_JEZ = 13,
    EXTENSAO_LOG_JEZ_2 = 14,
    EXTENSAO_LOGSA_JEZ = 15,
    EXTENSAO_WSQBIO_JEZ = 16,
    EXTENSAO_WSQMAN_JEZ = 17,
    EXTENSAO_WSQMES_JEZ = 18,
    EXTENSAO_MR_VER = 19,
    EXTENSAO_ASW_VSC = 20,
    EXTENSAO_AHW_VSC = 21,
};

class CArquivosResultado {
public:
    const std::string operator[](EExtensaoArquivoResultado extensao) const;
};

} // namespace comum
