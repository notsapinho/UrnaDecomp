#pragma once

#include <cstdint>
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
    // The record names four parameters, the target's type (fn 378) three: every caller passes the same value for one
    // of the two bools, which binaryen's dead-argument elimination folds. Which bool that is, and both bools' names and
    // meanings, are chosen (unit 32's fragment).
    static void CopyFile(const std::string& origem, const std::string& destino, bool preservaAtributos, bool sobrescreve);
    static void Rename(const std::string& origem, const std::string& destino);
    static void ZeroFill(const std::string& arquivo);
    // fn 2760 has no record: the name is chosen from what it does (ZeroFill unless the file is a symbolic link, then
    // remove).
    static void RemoveFile(const std::string& arquivo);
    // The records of TemporaryPath (csystem.cpp 236:15 and 243:15) print it static; target fn 5455 holds it inlined.
    static std::string TemporaryPath(const std::string& caminho);
    // Fn 5455 has no record of its own: its name is chosen from the text "CSystem::ReplaceFile" it passes to
    // PrepareReplace and ReplaceResource of csystem.cpp's anonymous namespace, whose records (lines 916 to 962) it
    // holds. The parameters' names are chosen from what the body does with them (unit 32's fragment).
    static void ReplaceFile(const std::string& origem, const std::string& destino, const std::string& backup);
    // Not in the target: the link drops it, as nothing calls it. A reading, not evidence: clang keeps PrepareReplace and
    // ReplaceResource, single-use internal functions, out of line in fn 5455 (binaryen inlines them, their frames
    // nested in 5455's), which needs a second caller in the TU, and ReplaceResource's directory branch and
    // PrepareReplace's existence test passed as a function pointer fit a directory's replacement. The name, the text
    // and the parameters are chosen after ReplaceFile (unit 32's fragment has the measurement). Without it fn 5455
    // scores 717 over 1984 rows and anchors nothing, so fns 3645 and 5458 lose the names its calls give them.
    static void ReplaceDir(const std::string& origem, const std::string& destino, const std::string& backup);

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

// Fns 5454, 5453 and 5463 have no record: their names are chosen from what they return (std::filesystem::space's free,
// its capacity less its free, and the number on the line of /proc/meminfo that holds the field, MemTotal or MemFree in
// 5463's one caller). They read no state of CSystem, so they are free functions; their namespace and this header are
// chosen (unit 32's fragment says why).
uintmax_t GetFreeSpace(const std::string& caminho);
uintmax_t GetUsedSpace(const std::string& caminho);
uedword GetMemInfo(const std::string& campo);

// Fns 2763 and 5462 have no record: the part of a path held in a std::string after its last '/' (the whole string
// when it holds none) and the part before it. Their callers are comum's and vota's (2763: 1501, 5360, 5461, 12098;
// 5462: 1501, 12098), and both lie in csystem.cpp's run of the use bands. They read no state of CSystem, so they are
// free functions; their names and namespace are chosen.
std::string GetFileName(const std::string& caminho);
std::string GetDirName(const std::string& caminho);

} // namespace api
