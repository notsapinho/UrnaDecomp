#pragma once

#include <cstddef>
#include <string>

namespace comum {

// Where one photo sits in the candidates' photo file. The record cfotos.cpp:39 names the type,
// md::CFotoCandidato comum::GetFotoPara(const std::string &, const SIndiceFoto &), spelled unqualified inside
// namespace comum; its two members are the position and the length that CVisitanteFoto::visit receives (size_t in
// visit's record) and stores side by side (target fn 11442).
struct SIndiceFoto {
    size_t posicao;
    size_t tamanho;
};

namespace md {

// One entry of md::CIndicesFotos (record cindicesfotos.cpp:30, const CIndiceFoto &comum::md::CIndicesFotos::at(size_t)
// const). Its layout is CVisitanteFoto's vector element: a std::string followed by an SIndiceFoto, 20 bytes. That the
// visitor's element is this class is presumed, not read: target fn 5659, which builds such a 20-byte object from a
// std::string and an SIndiceFoto (called by CVisitanteFoto::visit 11442 and CIndexadorFotos 11441), has no name yet.
// The member names are not recovered.
class CIndiceFoto {
public:
    CIndiceFoto(const std::string& codigo, const SIndiceFoto& indice);

private:
    std::string m_codigo;
    SIndiceFoto m_indice;
};

} // namespace md
} // namespace comum
