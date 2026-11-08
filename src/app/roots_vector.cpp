// The executable TU's copies of std::vector<unsigned char>'s destruction: the exception guard's destructor (target fn
// 306), ~vector (520) and __destroy_vector::operator() (4967), which both of them call. 306 has 42 callers in the target.
// An ecourna object's copy of the guard inlines operator() (2671, vector<int>'s guard from an ecourna object, is that
// body), so an object ahead of the trees on the link line has to hold the target's copy, as for fn 252
// (src/units/README.md "Companion files", the tree roots).
// - minsize gives each the level of the executable TU's -Oz code, which keeps operator() out of line in both.
// - 4967 needs a second caller in our link: with the guard alone in a tree root, binaryen inlined it into the guard.
//   __destroy_vector is private to vector, so the guard and ~vector are its only callers: ~vector is instantiated too,
//   and urna_roots_vector stands in for 520's callers.
// - The file compiles at UENUX2_CXXFLAGS, not the roots' APP_CXXFLAGS: 4967 loads __vec_ and __begin_ again after its
//   store to __end_, which -fno-strict-aliasing gives and strict aliasing does not (docs/reference/facts/levels.md V1).
// Each body is the header's own; in the whole link they pair with 306, 520 and 4967 by address and match. The link's
// copies of the three are the executable TU's now (unit 170), the same code at that TU's rule and first on the link
// line, ahead of mock/app/comum/cappinfobuilder.cpp's (unit 253) and src/app/roots_coderenv.cpp's (whose vector<char>
// twins of 520 and 4967 named two match lines before), so the lines carry that TU's names:
// vector<comum::teste::EMidia>'s guard and ~vector, and vector<api::IForm<api::IScreen>*>'s __destroy_vector.
#include <memory>
#include <vector>

template __attribute__((minsize)) std::__exception_guard_exceptions<std::vector<unsigned char>::__destroy_vector>::~__exception_guard_exceptions();
template __attribute__((minsize)) std::vector<unsigned char>::~vector();

// Stands in for 520's callers in the target that are not in our link (10155 10205; 2891, unit 206's writer, 5500 and
// 7840, unit 170's, 2793, 6004, 10256 and 10261, which votaInit brings, and 8592, the executable TU's exit
// destructor of CFormStack<IScreen>'s s_forms, are): two call sites, since binaryen inlines a function called once
// (docs/reference/facts/tool-traps.md X1). 857, 1249, 1532, 2927 and 9770, the others, call it now: 857 and 1249
// from mock/app/comum/cappinfobuilder.cpp's object (unit 253), 1532, 2927 and 9770 from src/app/roots_coderenv.cpp. The
// instantiation above keeps clang from inlining ~vector here.
int urna_roots_vector(int a)
{
    auto* v = reinterpret_cast<std::vector<unsigned char>*>(a);
    std::destroy_at(v);
    std::destroy_at(v + 1);
    return a;
}

// The same for std::vector<comum::md::estadoaplicacao::CDadoCorrespondencia>, whose element is 96 bytes: the guard's
// destructor (target fn 5294), ~vector (1698), __destroy_vector::operator() (5532), which both call, and
// _AllocatorDestroyRangeReverse::operator() (9873), the rollback of the guard over __uninitialized_allocator_copy, which
// the target reaches only through its table (slot 473, which 5310 passes to 3895). Their target callers are not
// reconstructed (1698: 5644, 10123, 10212, 10268, 10278; 5294: 10123, which calls invoke_*), and at 1dfd708 no object of
// ours instantiated them (build/out/wasm-map/vota_web/names.tsv). They are libc++'s code over a TSE type; the -Oz shapes
// below are read as the executable TU's copies, as for vector<unsigned char>.
// - 1698 calls operator() through a frame slot, and the loops of 5532 and 9873 are not rotated: -Oz's shapes. minsize on
//   the guard, ~vector, operator() and the rollback alone left clear() and __base_destruct_at_end, which hold 5532's
//   loop, and __allocator_destroy, which holds 9873's, at the tree's -O3, with the loops rotated (pnpm wasm score: 13 over
//   41 rows and 11 over 29); with minsize on those three as well every row is operand-only, and binaryen inlines them
//   into their one caller each, as the target's bodies show.
// - 5532 and 9873 use the this that CDadoCorrespondencia's destructor (857) returns, so binaryen keeps that result in
//   our link: 3792, 6043, 11585, 11621 and 11622, which call 857 and drop it, differed by that drop alone at 1dfd708 and
//   match with these copies in the link. 857 itself differed from this object's copy, at the tree's level, which inlines
//   ~basic_string where the target's calls it (fn 149); it matches since mock/app/comum/cappinfobuilder.cpp's object, at
//   the executable TU's rule and ahead of this one (unit 253), gives the link's copy. That object gives the link's 5294,
//   5532 and 9873 too, the same code as the instances below; 1698 stays this object's.
// - urna_roots_vector_dado stands in for those callers: two call sites each for ~vector and the guard, and 9873's
//   address, which the target's table holds. The guard's type names vector's private __destroy_vector, which an explicit
//   instantiation may name and a function body may not, hence the __asm__ labels; at those calls clang inlined the
//   guard's destructor into the stand-in until [[clang::noinline]] kept the two calls.
// In the whole link 5294, 1698, 5532 and 9873 match by content, each under the symbol of the instance above.
#include "app/comum/dados/md/estadoaplicacao/cdadocorrespondencia.h"

using comum::md::estadoaplicacao::CDadoCorrespondencia;

template __attribute__((minsize)) std::__exception_guard_exceptions<std::vector<CDadoCorrespondencia>::__destroy_vector>::~__exception_guard_exceptions();
template __attribute__((minsize)) std::vector<CDadoCorrespondencia>::~vector();
template __attribute__((minsize)) void std::vector<CDadoCorrespondencia>::__destroy_vector::operator()();
template __attribute__((minsize)) void std::vector<CDadoCorrespondencia>::clear();
template __attribute__((minsize)) void std::vector<CDadoCorrespondencia>::__base_destruct_at_end(CDadoCorrespondencia*);
template __attribute__((minsize)) void std::_AllocatorDestroyRangeReverse<std::allocator<CDadoCorrespondencia>, CDadoCorrespondencia*>::operator()() const;
template __attribute__((minsize)) void std::__allocator_destroy(std::allocator<CDadoCorrespondencia>&, std::reverse_iterator<CDadoCorrespondencia*>, std::reverse_iterator<CDadoCorrespondencia*>);

extern "C" int urna_guarda_dado(int) __asm__("_ZNSt3__228__exception_guard_exceptionsINS_6vectorIN5comum2md15estadoaplicacao20CDadoCorrespondenciaENS_9allocatorIS5_EEE16__destroy_vectorEED2B8ne210108Ev");
extern "C" void urna_desfaz_dado(int) __asm__("_ZNKSt3__229_AllocatorDestroyRangeReverseINS_9allocatorIN5comum2md15estadoaplicacao20CDadoCorrespondenciaEEEPS5_EclB8ne210108Ev");

// Stands in for the target callers of 1698 and 5294 named above, none of which is in our link.
int urna_roots_vector_dado(int a)
{
    auto* v = reinterpret_cast<std::vector<CDadoCorrespondencia>*>(a);
    std::destroy_at(v);
    std::destroy_at(v + 2);
    [[clang::noinline]] urna_guarda_dado(a + 4);
    [[clang::noinline]] urna_guarda_dado(a + 12);
    return reinterpret_cast<int>(&urna_desfaz_dado);
}

// std::vector<std::string>::~vector() (target fn 2255), the executable TU's -Oz copy, which that TU's AssinaArquivos
// (11733) instantiates now. Its other target callers are ecourna's CStringUtils::Split (1880, in our link) and 9586,
// not written: urna_roots_vector_cadeias stands for 9586 with one call.
#include <string>

int urna_roots_vector_cadeias(int a)
{
    auto* v = reinterpret_cast<std::vector<std::string>*>(a);
    std::destroy_at(v + 3);
    return a;
}

// std::vector<unsigned char>::__assign_with_size over two iterator kinds, which ecourna's CAesCipher calls
// (src/ecourna/api/security/caescipher.cpp, unit 11) and whose copies from that object are not the target's:
// - Over unsigned char* (target fn 1681), the -Oz copy, read as the executable TU's as the instances above are: it calls
//   __vdeallocate (5493), __recommend (3656) and __vallocate (2769), which of -O2, -O3, -Os and -Oz only -Oz gives
//   (src/units/11-ecourna-api-security.mk has the measurement). Its target callers are 2772, 5635, 10451 and 10465,
//   whose records are uenux2 files', and CAesCipher's 9494, and 9491 and 9493 through table slot 6264: none is that
//   TU's code, which is not written. Measured: this line compiled at UENUX2_CXXFLAGS gives the object code (calls
//   masked) the same instantiation without minsize gives at VOTA_WEB_CXXFLAGS. ckey.cpp.o's copy, which the link kept
//   before, scored 68 over 162 rows against 1681.
// - Over __wrap_iter<const unsigned char*>, the tree's -O3 code. The target's 1158 is one body for this instance and
//   vector<char>'s over __wrap_iter<const char*>, which cconversorseguranca.cpp.o gives: two table slots, 6259, which
//   only 9491 and 9493 hold (their assigns from a vector's iterators), and 7008. caescipher.cpp.o's copy, at ecourna's
//   flags, scored 39 over 175 rows against 1158. This one merges with cconversorseguranca.cpp.o's in our link and,
//   linking first, gives 1158's match line its name. No uenux2 caller of this instance is identified in the target, so
//   the instance stays until a uenux2 object that instantiates it is in the link.
// In our link SetKey's two calls and Encrypt's and Decrypt's table slots reach the first, and their slots and
// cconversorseguranca.cpp.o's callers the second: both stay out of line, and both match.
template __attribute__((minsize)) void std::vector<unsigned char>::__assign_with_size<unsigned char*, unsigned char*>(unsigned char*, unsigned char*, std::ptrdiff_t);
template void std::vector<unsigned char>::__assign_with_size<std::__wrap_iter<const unsigned char*>, std::__wrap_iter<const unsigned char*>>(std::__wrap_iter<const unsigned char*>, std::__wrap_iter<const unsigned char*>, std::ptrdiff_t);
