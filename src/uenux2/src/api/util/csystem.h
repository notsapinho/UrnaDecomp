#pragma once

#include <emscripten/emscripten.h>
#include <string>

#include "ecourna/api/uetypes.hpp"

namespace api {

/**
 * Operações sobre arquivos e diretórios do sistema.
 */
class CSystem {
public:
    // ExistFile and ExistDir (target fns 412 and 5459) have no record: their names are chosen from what they test
    // (S_IFREG, S_IFDIR) after api::ExistResource, whose record names it.
    static bool ExistFile(const std::string& arquivo);
    static bool ExistDir(const std::string& diretorio);
    static uedword GetFileSize(const std::string& arquivo);
    static void ZeroFill(const std::string& arquivo);

    // Reconstruction's note. The flag is evidence: the target reads the byte at 1584624 30 times, in 24 functions, and
    // nothing stores it, a word of .data that starts as 1 between csynchronizer.cpp's one record and csystem.cpp's
    // first. 23 of those guard emscripten_sleep(n) with it, each with its own n. Fn 5446, CWait's wait, only tests it,
    // in a usleep loop, so it is public here, a choice. CSystem::Dorme is not shown to be a real member: no record,
    // symbol or out-of-line copy names it. Chosen too: that either is CSystem's, both names, the parameter's type and
    // this file, where the word's place allows csynchronizer.cpp, csystem.cpp or a file that sorts between.
    static bool s_dorme;

    static void Dorme(unsigned int milissegundos)
    {
        if (s_dorme)
            emscripten_sleep(milissegundos);
    }
};

} // namespace api
