// The executable TU's copies of ASN1::CoderEnv::encode over a std::back_insert_iterator<std::vector<char>> (target fn 9770)
// and of what it instantiates, among them encodeBER (1532), ~AVNEncoder (3559), std::copy into the iterator (5290),
// vector<char>::reserve (2706) and its growth (5282, 9722, 3656), and basic_ostringstream's members (220, 1001, 10998,
// 11016, 11235). The same copies give 3666, 3694 and 10983 (~basic_stringbuf, basic_ios::init, string::resize, from
// libc++.a before), 674 (basic_stringbuf<char>::__init_buf_ptrs, the target's copy over roots_iconversorasn.o's: this
// object links first for it) and 520 and 4967 (vector<char>'s ~vector and __destroy_vector, the bodies of
// roots_vector.cpp's vector<unsigned char> copies); 3656's body is the executable TU's object's, the same code.
// src/units/229-asn1-coderenv.mk has the evidence and the measurements.
// - Whose copy. 9770, 1532, 2706 and 5290 have landing pads, so an -fexceptions object's: the ASN.1 runtime compiles at
//   -Os without them (docs/reference/facts/asn1.md A1, A2) and uenux2 without -fexceptions. 3559 matched a probe object
//   at -Oz -fexceptions and not at uenux2's flags (docs/reference/facts/levels.md V4). So this file compiles at
//   VOTA_WEB_CXXFLAGS, the rule of the executable TU, whose object is first on the link line; that the copies are that
//   TU's is a reading.
// - 9770 is reached only through table slot 482, which 2927 (CFileASN's CodeObjectFunction merge, not written) passes to
//   invoke_iiii: urna_roots_coderenv takes its address.
// - 1532 has seven direct target callers besides 9770 (11488 11582 11587 11616 11629 5366 6006), none in our link:
//   without the call below, binaryen inlined it into 9770, its one caller. encodeBER is protected, so the call goes
//   through an __asm__ label, with [[clang::noinline]] on the call as roots_vector.cpp has it (src/units/README.md
//   "Companion files").
// - 3656, vector<char>::__recommend, has the target callers 1681, 5496 and 5290. 1681 is not in our link and 5496 is
//   inlined into its one caller there (10949): without the second call below, binaryen inlined 3656 into 5290 (47 over
//   158 rows). __recommend is private to vector, hence the label too.
#include <iterator>
#include <vector>

#include "asn1.h"

template bool ASN1::CoderEnv::encode<std::back_insert_iterator<std::vector<char>>>(const ASN1::AbstractData&,
                                                                                  std::back_insert_iterator<std::vector<char>>);

extern "C" int urna_codifica(int, int, int) __asm__("_ZN4ASN18CoderEnv6encodeINSt3__220back_insert_iteratorINS2_6vectorIcNS2_9allocatorIcEEEEEEEEbRKNS_12AbstractDataET_");
extern "C" int urna_codifica_ber(int, int, int) __asm__("_ZN4ASN18CoderEnv9encodeBERINSt3__220back_insert_iteratorINS2_6vectorIcNS2_9allocatorIcEEEEEEEEbRKNS_12AbstractDataET_");
extern "C" int urna_recomenda(int, int) __asm__("_ZNKSt3__26vectorIcNS_9allocatorIcEEE11__recommendB8ne210108Em");

// Stands in for 9770's, 1532's and 3656's target callers named above.
int urna_roots_coderenv(int a)
{
    [[clang::noinline]] urna_codifica_ber(a, a + 4, a + 8);
    int n;
    [[clang::noinline]] n = urna_recomenda(a, a + 12);
    return n + reinterpret_cast<int>(&urna_codifica);
}
