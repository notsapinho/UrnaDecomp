// CBaseType's constructors whose target copies are uenux2's: their records name the conan package's installed header
// (p/include/ecourna/api/pattern/cbasetype.hpp) and they have no landing pad, though ecourna's converters call them too.
// The first uenux2 object that used one kept the copy, and no such object is written yet, while ecourna's objects emit
// their own. A fragment's roots link after those, so only an object ahead of them can hold the copies. It compiles at
// UENUX2_CXXFLAGS, the tree's own flags, unlike the other roots: everything the instances bring is then uenux2's code. Each
// line goes when a real uenux2 caller instantiates that constructor. src/units/112-ecourna-cbasetype.mk has the evidence.
#include <vector>

#include "ecourna/app/dados/tiposbasicos.hpp"

template CBaseType<unsigned short, 0, 9999, 15>::CBaseType(unsigned short);
template CBaseType<unsigned short, 0, 9999, 36>::CBaseType(unsigned short);
template CBaseType<unsigned short, 0, 999, 38>::CBaseType(unsigned short);
template CBaseType<unsigned short, 0, 9999, 9>::CBaseType(unsigned short);
template CBaseType<unsigned short, 0, 9999, 7>::CBaseType(unsigned short);
template CBaseType<unsigned int, 0, 99999, 6>::CBaseType(unsigned int);
template CBaseType<unsigned int, 0, 9999, 8>::CBaseType(unsigned int);
template CBaseType<unsigned short, 1, 99, 3>::CBaseType(unsigned short);

// std::vector<char>'s insert of a range of unsigned char, which ecourna's converters 9063, 9201 and 9227 invoke (table
// slot 6666): the target holds one body for it and for std::vector<unsigned char>'s, 1927, which api::CEncryptedFile::Save
// (uenux2) calls and which matches from that object at UENUX2_CXXFLAGS. ecourna's objects emit a copy of their own at
// their flags, which differs from 1927 (+0x16, the locals), so this copy holds the instance for them and binaryen merges
// it with uenux2's. It goes when a uenux2 object ahead of ecourna's instantiates it.
template std::vector<char>::iterator std::vector<char>::__insert_with_size<std::__wrap_iter<const unsigned char*>, std::__wrap_iter<const unsigned char*>>(
    std::vector<char>::const_iterator, std::__wrap_iter<const unsigned char*>, std::__wrap_iter<const unsigned char*>, std::ptrdiff_t);
