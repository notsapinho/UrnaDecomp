// Copies at the executable TU's rule (VOTA_WEB_CXXFLAGS, -Oz -fexceptions), this object first in APP_OBJS.
// src/units/229-asn1-coderenv.mk has the evidence and the measurements.
// - This file held ASN1::CoderEnv::encode over a std::back_insert_iterator<std::vector<char>> (target fn 9770) and
//   api::CFileASN::CodeObjectFunction for the four ESTADO GERAL entities (fn 2927, binaryen's merge, and its thunks
//   9801, 9702, 9695, 9673), with what they instantiate, until mock/app/comum/cappinfobuilder.cpp (unit 253, at this
//   rule, second on the link line) instantiated both through comum::IServicoEstado's save (unit 206). That object gives
//   those copies now, and the instances here went, with the stand-in that took CodeObjectFunction's four addresses for
//   2891's thunks, which are in the link too: steps 7 to 9 on the link without them moved no row.
// - 1532, encodeBER, has seven direct target callers besides 9770; 11488 is not in our link (11582 is, unit 122, 6006,
//   unit 293's merge of the two writers, 11587, unit 305, 11616 and 5366, unit 122, and 11629, unit 200): the call
//   below stands for it; without it, binaryen inlined 1532 into 9770, its one caller then (measured while this file
//   held 9770). encodeBER is protected, so the call goes through an __asm__ label.
// - 3656, vector<char>::__recommend, has the target callers 1681, 5496 and 5290, all three out of line in our link and
//   calling it (1681 from roots_vector.cpp, unit 11; 5496, whose other caller 5702 is fragment 335's, in the link),
//   so nothing here calls it. A call of it stood here while 1681 was not in the link: without it then, binaryen inlined
//   3656 into 5290 (47 over 158 rows).
#include <new>
#include <string>
#include <vector>

extern "C" int urna_codifica_ber(int, int, int) __asm__("_ZN4ASN18CoderEnv9encodeBERINSt3__220back_insert_iteratorINS2_6vectorIcNS2_9allocatorIcEEEEEEEEbRKNS_12AbstractDataET_");

extern "C" void urna_init_with_size(void*, std::string*, std::string*, unsigned long) __asm__(
    "_ZNSt3__26vectorINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEENS4_IS6_EEE16__init_with_sizeB8ne210108IPS6_SA_EEvT_T0_m");

// std::vector<std::string>'s range construction (fn 5585, below) has two target users, neither written: fn 11332, a
// std::vector<std::string> constructor from a two-word range (table slot 74, which fn 11733 reaches through
// invoke_*; that 11733 is a static initializer is a reading: it is ()->() with landing pads, in table slot 18, and
// no target function calls it directly), calls it directly, and ecourna's CLzmaCompress::DoAdd (fn 9586) passes its
// table slot, 6051. urna_vector_string stands for 11332 and the sink below takes the address for 9586, so binaryen
// keeps 5585 out of line with a slot of its own, as the target does. It builds the vector in place, so this object
// instantiates no ~vector<std::string>: a local's destructor here was a copy that took 2255 from roots_vector.o,
// which links after.
__attribute__((noinline)) static int urna_vector_string(void* destino, std::string* primeiro, std::string* ultimo)
{
    auto* v = ::new (destino) std::vector<std::string>(primeiro, ultimo);
    return static_cast<int>(v->size());
}

void (*volatile urna_sink_init_with_size)(void*, std::string*, std::string*, unsigned long);

// Stands in for 1532's target callers named above, and for 5585's.
int urna_roots_coderenv(int a)
{
    urna_codifica_ber(a, a + 4, a + 8);
    urna_sink_init_with_size = urna_init_with_size;
    return a + urna_vector_string(reinterpret_cast<void*>(a + 48), reinterpret_cast<std::string*>(a),
        reinterpret_cast<std::string*>(a + 24));
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
