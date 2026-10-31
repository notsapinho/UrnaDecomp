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

// Stands in for 520's callers in the target (857 1249 1532 2793 2891 2927 5500 6004 7840 8592 9770 10155 10205 10256
// 10261), none of which calls it in our link: two call sites, since binaryen inlines a function called once
// (docs/reference/facts/tool-traps.md X1). The instantiation above keeps clang from inlining ~vector here.
int urna_roots_vector(int a)
{
    auto* v = reinterpret_cast<std::vector<unsigned char>*>(a);
    std::destroy_at(v);
    std::destroy_at(v + 1);
    return a;
}
