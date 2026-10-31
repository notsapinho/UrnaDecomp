#pragma once

// comum::CArquivosResultado: the file name of each kind of result file. operator[] reads nothing of the object (fn 347
// has lost `this`: binaryen removed the unused parameter), so no member is recovered and the class's other members are
// not reconstructed. The header's path is chosen. A one-byte singleton: fn 348, called just before each operator[] with
// its result dropped (fns 1164, 3798, 5876, 6045), is GetInst, one of the four thunks of fn 2900 that allocate one byte
// and keep it in a static std::unique_ptr under a static std::mutex. The statics are defined in carquivosresultado.cpp:
// their destructors' table slots 2140 and 2141 lie in that object's run. The constructor and the destructor are out of
// line and GetInst is in the class: unit 111's fragment has the measurement. GetInst and its statics' names are chosen,
// from the project's other singletons.

#include <memory>
#include <mutex>
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
    ~CArquivosResultado();

    static CArquivosResultado& GetInst()
    {
        std::lock_guard<std::mutex> trava(s_mutex);
        if (!s_instancia) {
            s_instancia.reset(new CArquivosResultado);
        }
        return *s_instancia;
    }

    const std::string operator[](EExtensaoArquivoResultado extensao) const;

private:
    CArquivosResultado();

    static std::unique_ptr<CArquivosResultado> s_instancia;
    static std::mutex s_mutex;
};

} // namespace comum
