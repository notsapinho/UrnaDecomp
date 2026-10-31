#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "app/comum/dados/md/candidatura/cindicesfotos.h"

namespace comum {

// The candidates' photos by code. Recovered: the layout, 28 bytes, from the constructor and destructor (target fns 3756,
// 2818): the map at +0, an iterator of it at +12, and a std::string at +16 that 3756 builds from the literal "CFotos". The
// class's name is that literal and the record of CFotos::Load (cfotos.cpp:111), and the map's key is a std::string by
// its destructor (fn 1934). Its 32-byte value holds a string, 8 bytes and a string; reading the first 20 as an
// md::CIndiceFoto is presumed from that shape. SFotoIndexada, GetInst and the data members' names are chosen.
class CFotos {
public:
    static CFotos& GetInst();

    CFotos();
    ~CFotos();

private:
    static std::unique_ptr<CFotos> s_inst;
    static std::mutex s_mutex;

    struct SFotoIndexada {
        md::CIndiceFoto m_indice;
        std::string m_arquivo;
    };
    using Container = std::map<std::string, SFotoIndexada>;

    explicit CFotos(const std::string& nome) : m_atual(m_fotos.end()), m_nome(nome) {}

    Container m_fotos;
    Container::iterator m_atual;
    std::string m_nome;
};

} // namespace comum
