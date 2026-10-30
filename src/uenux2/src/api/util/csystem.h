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
    static uedword GetFileSize(const std::string& arquivo);

    // Reconstruction's note: 24 target functions hold `if (the byte at 1584624 == 1) emscripten_sleep(n)`, each with its
    // own n (fn 8461 with 20, fn 10235 with 1000), and no function stores that byte, a word of .data that starts as 1
    // between csynchronizer.cpp's one record and csystem.cpp's first. So the source holds one inline helper over one
    // global that starts true. That the helper and the flag are CSystem's, their names and this file are chosen: nothing
    // names them, and that word's place says only csynchronizer.cpp, csystem.cpp or a file that sorts between.
    static void Dorme(unsigned int milissegundos)
    {
        if (s_dorme)
            emscripten_sleep(milissegundos);
    }

private:
    static bool s_dorme;
};

} // namespace api
