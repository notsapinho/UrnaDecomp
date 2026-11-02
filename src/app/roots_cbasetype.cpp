// CBaseType's constructors whose target copies are uenux2's: their records name the conan package's installed header
// (p/include/ecourna/api/pattern/cbasetype.hpp) and they have no landing pad, though ecourna's converters call them too.
// The first uenux2 object that used one kept the copy, and no such object is written yet, while ecourna's objects emit
// their own. A fragment's roots link after those, so only an object ahead of them can hold the copies. It compiles at
// UENUX2_CXXFLAGS, the tree's own flags, unlike the other roots: everything the instances bring is then uenux2's code. Each
// line goes when a real uenux2 caller instantiates that constructor. src/units/112-ecourna-cbasetype.mk has the evidence.
//
// The same holds for std::regex's internals over const char* and for the token iterator over a std::string: the parser
// (__parse<const char*>, fn 2062, and the members it calls), std::sregex_token_iterator's constructor and operators and
// the matchers under them (4307, 6970, 3137, 2054, 2056, 4276, 4279, 6897, 6942) and std::regex_replace into a
// std::string (6958, `no-candidate`: unit 97's fragment says why). The TSE functions that use them in the target are
// uenux2's (5492 in api/gui/cinputmenufield.cpp, 6999 in app/vota/eleitor/cvotacaostateaudio.cpp, and 5782, which has
// no record or stub and calls 2062), and these rows match at this flag set, without strict aliasing and without
// -fexceptions, while the objects that instantiate them in our link, cinputmenufield.cpp's and cvotacaostateaudio.cpp's,
// build in UENUX2_TBAA_DIRS: with strict aliasing they match fewer rows (src/units/97-uenux2-cvotacaostateaudio.mk has
// the measurements). urna_regex_uenux2 and urna_regex_tokens only instantiate: nothing calls them and they leave the
// link. They go when the objects that use std::regex so build without strict aliasing, or when a uenux2 object outside
// UENUX2_TBAA_DIRS that uses it links ahead of them. The constructor from a std::string and what it instantiates are an
// -fexceptions object's in the target: src/app/roots_regex.cpp holds them.
#include "ecourna/app/dados/tiposbasicos.hpp"

#include <regex>
#include <string>

template CBaseType<unsigned short, 0, 9999, 15>::CBaseType(unsigned short);
template CBaseType<unsigned short, 0, 9999, 36>::CBaseType(unsigned short);
template CBaseType<unsigned short, 0, 999, 38>::CBaseType(unsigned short);
template CBaseType<unsigned short, 0, 9999, 9>::CBaseType(unsigned short);
template CBaseType<unsigned short, 0, 9999, 7>::CBaseType(unsigned short);
template CBaseType<unsigned int, 0, 99999, 6>::CBaseType(unsigned int);
template CBaseType<unsigned int, 0, 9999, 8>::CBaseType(unsigned int);
template CBaseType<unsigned short, 1, 99, 3>::CBaseType(unsigned short);

void urna_regex_uenux2(const char* padrao)
{
    const std::regex re(padrao);
}

std::string urna_regex_tokens(const std::string& texto, const std::regex& re)
{
    std::string resultado;
    std::sregex_token_iterator it(texto.begin(), texto.end(), re, {-1, 0});
    std::sregex_token_iterator fim;
    for (; it != fim; ++it) {
        resultado += *it;
    }
    return std::regex_replace(resultado, re, ", $&");
}
