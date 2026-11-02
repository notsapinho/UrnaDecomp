#pragma once

// comum::CSubstituidorTitulo. Reconstruction notes, not TSE's text. The records of csubstituidortitulo.cpp name the class
// and two static members, GetInst (line 21) and CreateInst (line 26, which takes a const std::map<std::string,
// std::string>&); fn 3689 holds both, inlined by binaryen. The layout is a reading of that code: CreateInst allocates 12
// bytes and copies the map into them, and the destructor (fn 5576) destroys a map at +0. The pointer and the mutex are
// the .bss words 1839140 and 1839116, which fn 3689 and the exit destructors fns 11175 and 11174 read.
// Chosen: this header's path (beside the .cpp), the members' names and access, Existe (a lock-guarded test of the
// pointer, which fn 3689 holds inlined) and Substitui (the map's replacements applied in turn, which fn 3689 holds
// inlined by binaryen behind a frame of its own), the constructor's explicit.
#include <map>
#include <memory>
#include <mutex>
#include <string>

namespace comum {

class CSubstituidorTitulo {
public:
    ~CSubstituidorTitulo();

    static CSubstituidorTitulo& GetInst();
    static void CreateInst(const std::map<std::string, std::string>& substituicoes);
    static bool Existe();

    std::string Substitui(const std::string& texto) const;

private:
    explicit CSubstituidorTitulo(const std::map<std::string, std::string>& substituicoes);

    static std::unique_ptr<CSubstituidorTitulo> s_instancia;
    static std::mutex s_mutex;

    std::map<std::string, std::string> m_substituicoes;
};

} // namespace comum
