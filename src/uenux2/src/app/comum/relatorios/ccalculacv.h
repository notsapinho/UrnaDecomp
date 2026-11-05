#pragma once

// comum::CCalculaCV (/home/rubio/tse/uenux2/src/app/comum/relatorios/ccalculacv.cpp, its records' file; the header beside
// it is chosen). RTTI gives the class and no base.
//
// Recovered: the layout, 56 bytes, and the destructor. fn 12110 allocates 56 bytes and holds the constructor inlined
// (records ccalculacv.cpp:58, 65 and 74, `CCalculaCV(const std::string &, const std::string &, char, size_t)`): it copies a
// string to +0, stores a byte at +12 and zeroes +16 to +55. The destructor, fn 5614, destroys a string at +40, a vector at
// +28, a string at +16 and a string at +0, in that order, so the members are declared in this order. IncluiString (fn
// 942, record line 109) appends its argument to the string at +16, and fn 12110 resizes the vector to 16 elements of one
// byte. CalculaCodigo (fn 3700) increments the four bytes at +52 and appends their decimal text to the string at +16, then
// takes the SipHash MAC of that text under the vector as its key (GeraMacHexa, which 3700 holds inlined by binaryen: a
// private member that takes the text and reads the key, the form src/units/121-uenux2-datasources.mk measures); it
// reads the MAC's hexadecimal text as a 64-bit number, hands its decimal text to Reinicia and returns its last ten digits.
// Reinicia (fn 5615), which 3700 and 12110 call, starts the string at +16 again from the byte at +12, the string at +0
// and its argument, and copies the argument to +40. Every member's name, the vector's element type, char for +12 (the
// constructor's third parameter's type) and size_t for +52 (its fourth's) are chosen. The call on +52 does not tell size_t
// from unsigned int: ccalculacv.cpp.o calls std::to_string(unsigned long), our link holds no body of that name, and the
// call lands on std::to_string(unsigned)'s (build/out/wasm-map/vota_web/names.tsv), which re-points to the target's 327.
//
// The destructor is declared and defined out of line, in ccalculacv.cpp: fn 11263, the __on_zero_shared of the block that
// push<CCalculaCV> builds (fn 12110), calls fn 5614 and then frees, and fn 12110 calls 5614 too. The constructor is not
// reconstructed, so nothing in our link constructs one. typeid in api::CPolySingleton<T> needs the
// class complete.
//
// DestroyInst removes the class's api::CPolySingleton instance: fn 3698 holds it inlined by binaryen (a frame of its own
// that gets the singletons' info, then builds the type's name and calls CPolySingletonList::remove, fn 640, with no
// has<T> test). Its name and its being a static member are chosen; unit 139's fragment has the measurements.

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace comum {

class CCalculaCV {
public:
    ~CCalculaCV();

    static void DestroyInst();

    void IncluiString(const std::string& str);
    // Appends the last result (+40) as IncluiString does, IncluiString inlined (its record, line 109). No target
    // function of its own: fn 5967 (CDataSourcesRelatorio<CRdvVota, CEleitores>'s helper, read as another object's
    // code: unit 220's fragment) holds it behind a 16-byte frame of its own, binaryen's inlining of a function of this
    // TU with one caller. Its name is chosen.
    void IncluiResultado();
    void Reinicia(const std::string& valor);
    std::string CalculaCodigo();

private:
    std::string GeraMacHexa(const std::string& texto) const;

    std::string m_identificacao;  // +0
    char m_tipo;                  // +12
    std::string m_texto;          // +16
    std::vector<uint8_t> m_chave; // +28
    std::string m_resultado;      // +40
    size_t m_contador;            // +52
};

} // namespace comum
