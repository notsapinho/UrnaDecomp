// CBaseType's constructors whose target copies are uenux2's: their records name the conan package's installed header
// (p/include/ecourna/api/pattern/cbasetype.hpp) and they have no landing pad, though ecourna's converters call them too.
// The first uenux2 object that used one kept the copy, and no such object is written yet, while ecourna's objects emit
// their own. A fragment's roots link after those, so only an object ahead of them can hold the copies. It compiles at
// UENUX2_CXXFLAGS, the tree's own flags, unlike the other roots: everything the instances bring is then uenux2's code. Each
// line goes when a real uenux2 caller instantiates that constructor. src/units/112-ecourna-cbasetype.mk has the evidence.
//
// The same holds for the token iterator over a std::string: std::sregex_token_iterator's constructor and operators and
// the matchers under them (4307, 6970, 3137, 2054, 2056, 4276, 4279, 6897, 6942) and std::regex_replace into a
// std::string (6958, `no-candidate`: unit 97's fragment says why). The TSE functions that use them in the target are
// uenux2's (5492 in api/gui/cinputmenufield.cpp, 6999 in app/vota/eleitor/cvotacaostateaudio.cpp), and these rows match
// at this flag set, without strict aliasing and without -fexceptions, while of their users in our link
// cinputmenufield.cpp's object builds with strict aliasing, with which they match fewer rows (unit 97's fragment has
// the measurements), and links ahead of cvotacaostateaudio.cpp's, which UENUX2_NOTBAA_FILES builds without it.
// urna_regex_tokens only instantiates: nothing calls it and it leaves the link. It goes when a uenux2 object without
// strict aliasing that uses the token iterator links ahead of cinputmenufield.cpp's. Not when both users build without
// it: with both so and this stand-in and the parser's gone, cinputmenufield.cpp.o's copies take every row, but its
// destructor (5491) needs strict aliasing and stops matching; with cvotacaostateaudio.cpp alone so, the copies of
// cinputmenufield.cpp.o, ahead of it, take the rows and 32 stop matching (docs/reference/facts/app-flags.md §F6, at
// b7c2e8a5). The constructor from a std::string and what it instantiates are an -fexceptions object's in the target:
// ecourna's api/compression/icompressor.cpp.o gives them (unit 06's fragment). The parser over const char*
// (__parse<const char*>, fn 2062, and the members it calls; its target callers are 2416, 5782, 6833 and 6999, all in
// the link) has no stand-in here: comum::CQRCodeDS::operator() (5782, app/comum/dados/cqrcodeds.cpp, fragment 299),
// built without strict aliasing, links ahead of cinputmenufield.cpp's object and gives those copies (without the
// former stand-in no match row moves).
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
