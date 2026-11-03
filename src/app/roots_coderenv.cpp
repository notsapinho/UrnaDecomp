// Copies at the executable TU's rule (VOTA_WEB_CXXFLAGS, -Oz -fexceptions), this object first in APP_OBJS.
// src/units/229-asn1-coderenv.mk has the evidence and the measurements.
// - This file held ASN1::CoderEnv::encode over a std::back_insert_iterator<std::vector<char>> (target fn 9770) and
//   api::CFileASN::CodeObjectFunction for the four ESTADO GERAL entities (fn 2927, binaryen's merge, and its thunks
//   9801, 9702, 9695, 9673), with what they instantiate, until mock/app/comum/cappinfobuilder.cpp (unit 253, at this
//   rule, second on the link line) instantiated both through comum::IServicoEstado's save (unit 206). That object gives
//   those copies now, and the instances here went, with the stand-in that took CodeObjectFunction's four addresses for
//   2891's thunks, which are in the link too: steps 7 to 9 on the link without them moved no row.
// - 1532, encodeBER, has seven direct target callers besides 9770 (11488 11582 11587 11616 11629 5366 6006), none in
//   our link: without the call below, binaryen inlined it into 9770, its one caller (measured while this file held
//   9770). encodeBER is protected, so the call goes through an __asm__ label.
// - 3656, vector<char>::__recommend, has the target callers 1681, 5496 and 5290, all three out of line in our link and
//   calling it (1681 from roots_vector.cpp, unit 11; 5496 with unit 170's roots standing for its other caller, 5702),
//   so nothing here calls it. A call of it stood here while 1681 was not in the link: without it then, binaryen inlined
//   3656 into 5290 (47 over 158 rows).
#include <vector>

extern "C" int urna_codifica_ber(int, int, int) __asm__("_ZN4ASN18CoderEnv9encodeBERINSt3__220back_insert_iteratorINS2_6vectorIcNS2_9allocatorIcEEEEEEEEbRKNS_12AbstractDataET_");
// Stands in for 1532's target callers named above.
int urna_roots_coderenv(int a)
{
    urna_codifica_ber(a, a + 4, a + 8);
    return a;
}

// std::vector<std::string>'s range construction from std::string* (target fn 5585): __vallocate and __construct_at_end
// out of line (fns 11180 and 11177, table slots 232 and 233) and a landing pad, the -Oz -fexceptions shape this file's
// rule gives. Its target users are ecourna's CLzmaCompress::DoAdd (fn 9586), through table slot 6051, and fn 11332
// (elem[74], a std::vector<std::string> constructor from a two-word range), which calls it directly; neither is
// written, and the instance goes when the code that gives this copy (read as the executable TU's, below) is. Without
// this copy the link's is an ecourna object's (app_dados_asn_datahoraasn.cpp.o), whose body differs from the
// vector<path> one of ICompressor::Add (fn 9531, icompressor.cpp.o's) in one table slot alone, and binaryen merges the
// two, so 9531 has no body of its own (src/units/122-uenux2-app-comum-gravadores.mk). That the copy is the executable
// TU's is a reading.
// 5585 itself stays unresolved: its callees 11180 and 11177 have no name.
#include <string>

template void std::vector<std::string>::__init_with_size<std::string*, std::string*>(std::string*, std::string*, std::size_t);
