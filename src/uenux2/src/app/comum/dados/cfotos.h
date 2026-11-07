#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "app/comum/dados/md/candidatura/cfotocandidato.h"
#include "app/comum/dados/md/candidatura/cindicesfotos.h"

namespace comum {

// One photo of the candidates' photo files, the value of CFotos's map: the record cfotos.cpp:39,
// md::CFotoCandidato comum::GetFotoPara(const std::string &, const SIndiceFoto &), spells the type unqualified inside
// namespace comum, and that function's code, which target fn 3755 (CFotos::GetImagem) holds, reads through its parameter
// the code at +0 (a std::string it formats as the photo's), the position and the length at +12 and +16 (the seek and
// the read) and the file name at +20 (a std::string it tests with api::CSystem::ExistFile): the map's 32-byte value
// (CFotos's destructor, fn 2818, frees two strings in it). Reading the first 20 bytes as an md::CIndiceFoto is a
// reading from that layout (CIndicesFotos holds them, cindicesfotos.h). The members' names are chosen.
struct SIndiceFoto {
    md::CIndiceFoto indice;
    std::string arquivo;
};

// The candidates' photos by code. Recovered: the layout, 28 bytes, from the constructor and destructor (target fns 3756,
// 2818): the map at +0, an iterator of it at +12, and a std::string at +16 that 3756 builds from the literal "CFotos". The
// class's name is that literal and the record of CFotos::Load (cfotos.cpp:111), and the map's key is a std::string by
// its destructor (fn 1934). Its 32-byte value is SIndiceFoto (above). GetInst and the data members' names are chosen.
class CFotos {
public:
    static CFotos& GetInst();

    CFotos();
    ~CFotos();

    // Whether the map at +0 holds the code: comum::VerificaFotoCandidatura (fn 5746) calls the map's find (fn 163,
    // matched under another std::map<std::string, ...>'s find, into whose body our link merges this map's) on the CFotos
    // fn 7787 passes it, and compares the result with the end node at +4. The name, and that the search is a member of
    // CFotos, are chosen.
    bool ExisteFoto(const std::string& codigo) const { return m_fotos.find(codigo) != m_fotos.end(); }

    // Fn 3755: the photo's bytes, through GetFotoPara (below) under the name "CFotos::GetImagem(id)", the literal it
    // builds; the name is read from it. Static: its callers, the CDataImage<...> sources of the candidate's screen (fn
    // 12520, which calls GetInst() before it and drops the result) and of the vote screens (fn 12641), pass no instance,
    // and it reaches the instance through GetFotoPara. That it is a member, and its parameter's name, are chosen.
    static std::vector<uint8_t> GetImagem(const std::string& id);
    // Whether the map holds the code, keeping it in m_atual when it does: the code target fn 12641
    // (CDataImage<CCandidaturasDSFoto>::GetData, which holds CCandidaturasDSFoto's call operator) holds after a call of
    // GetInst whose result it drops, with GetInst's own code inlined (fn 2819 is its body elsewhere), which only
    // cfotos.cpp can inline: a static member called through the instance, as fn 12520's source calls GetImagem, frameless,
    // with one caller, inlined by binaryen (a reading). Its name, its being static and a member, and its body's form are
    // chosen.
    static bool Posiciona(const std::string& id);

private:
    // GetFotoPara(const std::string &, const std::string &) finds the photo in m_fotos and keeps it in m_atual (fn 3755
    // holds it): a friend is a choice, as are public accessors that give the same code.
    friend md::CFotoCandidato GetFotoPara(const std::string& nome, const std::string& id);

    static std::unique_ptr<CFotos> s_inst;
    static std::mutex s_mutex;

    using Container = std::map<std::string, SIndiceFoto>;

    explicit CFotos(const std::string& nome) : m_atual(m_fotos.end()), m_nome(nome) {}

    Container m_fotos;
    Container::iterator m_atual;
    std::string m_nome;
};

// The two functions of cfotos.cpp its records name (:39 and :51, md::CFotoCandidato comum::GetFotoPara), which fn 3755
// holds, each behind a stack frame of its own (528 and 496 bytes): out of line, one caller each, inlined by binaryen
// (docs/reference/facts/reading.md R10). The second finds the photo of a code and reads it with the first; the
// parameters' names are chosen.
md::CFotoCandidato GetFotoPara(const std::string& nome, const SIndiceFoto& foto);
md::CFotoCandidato GetFotoPara(const std::string& nome, const std::string& id);

} // namespace comum
