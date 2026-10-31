#pragma once

// comum::CCalculaCV (/home/rubio/tse/uenux2/src/app/comum/relatorios/ccalculacv.cpp, its records' file; the header beside
// it is chosen). RTTI gives the class and no base.
//
// Recovered: the layout, 56 bytes, and the destructor. fn 12110 allocates 56 bytes and holds the constructor inlined
// (records ccalculacv.cpp:58, 65 and 74, `CCalculaCV(const std::string &, const std::string &, char, size_t)`): it copies a
// string to +0, stores a byte at +12 and zeroes +16 to +55. The destructor, fn 5614, destroys a string at +40, a vector at
// +28, a string at +16 and a string at +0, in that order, so the members are declared in this order. fn 942, which holds
// IncluiString's record (line 109), appends to the string at +16, and fn 12110 resizes the vector to 16 elements of one
// byte. The four bytes at +52 are zeroed and not read here. Every member's name, the vector's element type, char for +12
// (the constructor's third parameter's type) and size_t for +52 (its fourth's) are chosen.
//
// The destructor is declared and defined out of line, in ccalculacv.cpp: fn 11263, the __on_zero_shared of the block that
// push<CCalculaCV> builds (fn 12110), calls fn 5614 and then frees, and fn 12110 calls 5614 too. The constructor and
// IncluiString are not reconstructed, so nothing in our link constructs one. typeid in api::CPolySingleton<T> needs the
// class complete.

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace comum {

class CCalculaCV {
public:
    ~CCalculaCV();

private:
    std::string m_identificacao;  // +0
    char m_tipo;                  // +12
    std::string m_texto;          // +16
    std::vector<uint8_t> m_chave; // +28
    std::string m_resultado;      // +40
    size_t m_tamanho;             // +52
};

} // namespace comum
