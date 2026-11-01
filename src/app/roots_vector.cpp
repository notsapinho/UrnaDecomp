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
// Each body is the header's own; in the whole link they pair with 306, 520 and 4967 by address and match.
#include <memory>
#include <vector>

template __attribute__((minsize)) std::__exception_guard_exceptions<std::vector<unsigned char>::__destroy_vector>::~__exception_guard_exceptions();
template __attribute__((minsize)) std::vector<unsigned char>::~vector();

// Stands in for 520's callers in the target that are not in our link (1249 1532 2793 2891 2927 5500 6004 7840 8592 9770
// 10155 10205 10256 10261): two call sites, since binaryen inlines a function called once
// (docs/reference/facts/tool-traps.md X1). 857, the other one, calls it now, from this object's copy below. The
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
//   match with these copies in the link. 857 itself stays differs: our copy inlines ~basic_string at the tree's level,
//   and the target's calls it (fn 149). This object now holds the link's copy of 857, at the tree's flags, and it calls
//   ~vector<unsigned char> (520), the minsize instance above, where cappinfosingleton.cpp.o's copy inlined it.
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

// Three more -Oz copies read as the executable TU's: std::vector<std::string>'s __base_destruct_at_end (target fn 2247,
// target callers 2249 8825 8826 8874) and __destroy_vector::operator() (2249, callers 679 2183 2255 5573 8873), and
// std::string::find_first_not_of(const char*, size_type) (1843, callers 1519 2185 11546 11571 14477).
// docs/reference/facts/asn1.md A5 matched 2247 and 2249 with a probe object at the executable TU's -Oz -fexceptions, and
// A10 reads 1843's loop as -Oz's; their copies had come from the ASN.1 runtime's -Os objects and differed. The executable
// TU's code that would instantiate them is not written (votaInit, 7840, invokes 11546, 11571 and 14477, which call 1843),
// so they come from here until it is, and go then, as 252 did (src/units/README.md "Companion files").
// - Measured: these lines compiled at UENUX2_CXXFLAGS give, for each of the three, the object code (calls and relocated
//   constants masked) the same instantiations without minsize give at VOTA_WEB_CXXFLAGS, the TU's rule.
// - 2247 calls ~basic_string (149) only with allocator_traits::destroy and __destroy_at instantiated with minsize too, 2249
//   calls 2247 only with clear() so, and 1843's loop is not rotated only with __str_find_first_not_of so (each measured on
//   a probe link), read as each callee's own -O3 copy inlining or rotating first (src/units/README.md "Companion files"
//   names 2247's two).
// - Measured on a probe link (docs/reference/facts/levels.md V4, the object first on the link line, scanned with the
//   committed symbol file): the three match and no other row enters or leaves match against an empty probe object; in
//   this link they match under these symbols, which census pairs name (pair-addr for 2247 and 2249, pair-fingerprint for
//   1843), and no match is lost.
#include <string>

template __attribute__((minsize)) void std::vector<std::string>::__base_destruct_at_end(std::string*);
template __attribute__((minsize)) void std::vector<std::string>::__destroy_vector::operator()();
template __attribute__((minsize)) void std::vector<std::string>::clear();
template __attribute__((minsize)) void std::allocator_traits<std::allocator<std::string>>::destroy<std::string, 0>(std::allocator<std::string>&, std::string*);
template __attribute__((minsize)) void std::__destroy_at<std::string, 0>(std::string*);
template __attribute__((minsize)) std::string::size_type std::string::find_first_not_of(const char*, std::string::size_type) const;
template __attribute__((minsize)) unsigned long std::__str_find_first_not_of<char, unsigned long, std::char_traits<char>, 4294967295ul>(const char*, unsigned long, const char*, unsigned long, unsigned long);
