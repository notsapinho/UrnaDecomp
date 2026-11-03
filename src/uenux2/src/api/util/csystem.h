#pragma once

#include <cstdint>
#include <emscripten/emscripten.h>
#include <string>
#include <vector>

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
    // Record csystem.cpp:255 (fn 2762): it throws when the directory does not exist, and is true when the directory holds
    // no file and no subdirectory but "." and "..".
    static bool IsEmptyDir(const std::string& diretorio);
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
// 5463's one caller). They read no state of CSystem; that they are free functions and not static members of CSystem
// is a choice (a static member gives the same code), and so are their namespace and this header (unit 32's fragment
// says why).
uintmax_t GetFreeSpace(const std::string& caminho);
uintmax_t GetUsedSpace(const std::string& caminho);
uedword GetMemInfo(const std::string& campo);
// The two fields vota::CThreadMonitor::Run (fn 10226) reads: it holds each inlined after a stack frame of its own that
// builds the field's name, "MemTotal" or "MemFree", for GetMemInfo, and widens the result as a signed number. No
// target index and no record: their names, their being free functions here, and their long result are chosen.
long GetMemTotal();
long GetMemFree();

// Fns 2763 and 5462 have no record: the part of a path held in a std::string after its last '/' (the whole string
// when it holds none) and the part before it. Their callers are comum's and vota's (2763: 1501, 5360, 5461, 12098;
// 5462: 1501, 12098), and both lie in csystem.cpp's run of the use bands. They read no state of CSystem; that they are
// free functions and not static members of CSystem is a choice, the file's GetMemInfo's form (a static member gives
// the same code: unit 32's fragment), and so are their names and namespace.
std::string GetFileName(const std::string& caminho);
std::string GetDirName(const std::string& caminho);

// Target fn 2758: true when every name of the first list matches one of the second, neither list empty. A pattern and a
// name match when either begins with "#regex#" (CStringUtils::CasaRegex over the rest), or when they have one length and
// each pair of characters is equal or passes CStringUtils::CasaCaractere one way or the other. Its callers are
// comum::impl::ValidaConteudo (fn 5572) and DiretorioContemApenas, below, twice (inlined into fn 11167). No record: its
// name, its being a free function here and its place in csystem.cpp are chosen (src/units/179-uenux2-cvalidamidia.mk).
bool CasamTodos(const std::vector<std::string>& nomes, const std::vector<std::string>& padroes);

// True when a directory holds files only, at least as many as the patterns, each file matching one of the patterns and
// each pattern one of the files (CasamTodos both ways); false for no pattern, a directory that is missing or empty, or
// one that holds a directory other than "." and "..". No record and no target index: binaryen inlines it into its one
// caller, fn 11167 (comum::impl::CValidaMidia's slot 8), where it keeps its own 128-byte frame and holds
// CSystem::ExistDir's code inlined (the file-static api::ExistResource, fn 1690, called from there), which only
// csystem.cpp's own functions can do, so it is here, as CreateDir is. Its name, its being a free function, its
// namespace and its place after CasamTodos are chosen (src/units/179-uenux2-cvalidamidia.mk).
bool DiretorioContemApenas(const std::string& diretorio, const std::vector<std::string>& padroes);

// Creates each missing directory of a path held in a std::string, from its first component on, with the mode 0755;
// false when a mkdir fails. It has no record and no target index: binaryen inlines it into its one caller, fn 5821
// (comum::CGravadorWSQ::CompactaWsq), where it keeps its own stack frame and inlines CSystem::ExistDir, which only
// csystem.cpp's own functions can inline (api::ExistResource is file-static). Its name, its result, its being a free
// function and its namespace are chosen, as GetFileName's are.
bool CreateDir(const std::string& diretorio);

// Fn 5461 (no record): the path held in a std::string with the extension after its last '.' replaced, its directory
// read with GetDirName's code twice (inlined: the target makes the two substr copies) and its name with GetFileName (a
// call); the path as it is when the name holds no '.'. Its callers are comum's (5778, 7787), and 5778 passes "pid". In
// use band 2 it lies next to GetDirName (5462), in csystem.cpp's run. Its name, its being a free function and its
// namespace are chosen, as GetFileName's are.
std::string TrocaExtensao(const std::string& arquivo, const std::string& extensao);

} // namespace api
