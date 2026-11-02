// std::basic_regex<char>'s copies that are an -fexceptions object's code in the target: its constructor from a
// std::string (target fn 9534, which only table slot 6142 reaches, and only comum::CGravadorWSQ's writer, fn 5821, passes
// that slot, to an invoke_* thunk) and what the constructor instantiates over the string's iterators: 9534 calls 9518
// through table slot 6153, which calls 2689, then 2688; the rows that match from this object are 424 (a shared_ptr
// destructor of the parser), 3523, 3524, 5184 to 5188 and 9511 to 9514. 9534's target body has landing pads, and those
// rows equal the copies of these ECOURNA_CXXFLAGS (-fexceptions, without strict aliasing); the flags of 5821's own object
// are not measured. UrnaRegexTexto stands for 5821, not written: it builds the regex from a std::string, and its address
// in a sink keeps it in the link, as 5821's table slot keeps the target's constructor. It goes when 5821 is in the link.
// The parser over const char* and the token iterator's members are uenux2's code in the target, without landing pads:
// src/app/roots_cbasetype.cpp holds them, ahead of this object (the constructor from a C string, 2416, comes from
// cinputmenufield.cpp's object). Before, this file held the const char* copies at these flags, which have the same
// bodies as the std::string ones (the rows above matched so) and differ from the target's const char* copies
// (src/units/97-uenux2-cvotacaostateaudio.mk has the measurement).
#include <regex>
#include <string>

namespace {

__attribute__((noinline)) unsigned UrnaRegexTexto(const std::string& padrao)
{
    const std::regex re(padrao);
    return re.mark_count();
}

const void* volatile urna_regex_sink;

struct SUrnaRegexRoots {
    SUrnaRegexRoots()
    {
        urna_regex_sink = reinterpret_cast<const void*>(&UrnaRegexTexto);
    }
} urna_regex_roots;

} // namespace
