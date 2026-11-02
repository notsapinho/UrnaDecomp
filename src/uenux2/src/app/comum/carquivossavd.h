#pragma once

// comum::CArquivosSavd: the SAVD file names of a package and of a signed file, looked up by identifier. Recovered: the
// three maps, which operator[] reads (fns 275 and 680: a std::map at +0, by ESavdPacote, and at +12, by ESavdArquivoUE,
// each with a std::string at +20 of its node) and the constructor fills (inlined into GetInst, fn 1164, with the three
// maps' entries in the target's order), the 36 bytes GetInst allocates, and the singleton: a std::unique_ptr GetInst
// resets under a std::mutex (fn 1164 unlocks @1838520 through fn 150 and stores the object at @1838544), the order of
// the two statics' exit destructors (table slots 2144 and 2145: fns 11658 and 11657) and the destructor out of line (fn
// 5907, which 1164 and 11658 call). The members' names, the header's path, each member's access and the three loaders'
// split are chosen: the constructor's code holds two stack frames of its own (the +0 map's entries, then the +12
// map's), so it calls functions binaryen inlined, each with one caller; that the +24 map's entries, which need no frame,
// are a third such function and not the constructor's own statements is a choice.

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "app/comum/iinterfacesavd.h"

namespace comum {

// The key of the third map (+24): its 20 entries (1 to 22) name packages ("vota.of", "sa.si", "partido.pub",
// "infomidia.pwd"). The target compares the keys signed (fn 1164's insertions: i32.ge_s), and the map's __tree::destroy
// is an instantiation of its own (fn 3841, beside 3839's and 3840's), so the key is a signed type other than the other
// two maps'. None of fn 1164's nine callers reads the map. The type's name, `: int` and its place are chosen; its
// enumerators are not recovered.
enum ESavdNomePacote : int;

class CArquivosSavd {
public:
    static CArquivosSavd& GetInst();

    ~CArquivosSavd();

    std::string operator[](ESavdPacote pacote) const;
    std::string operator[](ESavdArquivoUE arquivo) const;

private:
    CArquivosSavd();

    void CarregaAssinaturas();
    void CarregaAssinados();
    void CarregaNomesPacotes();

    static std::unique_ptr<CArquivosSavd> s_instancia;
    static std::mutex s_mutex;

    std::map<ESavdPacote, std::string> m_assinaturas;
    std::map<ESavdArquivoUE, std::string> m_assinados;
    std::map<ESavdNomePacote, std::string> m_nomesPacotes;
};

std::string DescricaoArquivo(ESavdArquivoUE arquivo);

} // namespace comum
