#pragma once

// comum::CEleitoresAptos. Reconstruction notes, not TSE's text: no record, slot or RTTI names this class, its members,
// this header or its .cpp; src/units/317-uenux2-relatorios-aptos.mk has the evidence and the measurements.
//
// The reports' lines of the voters able to vote. The six target callers of fns 1921 and 1922 (3871, 5977, 11223, 11908,
// 12105, 12110) each build a std::function<comum::SQtdeAptos()> from a lambda (RTTI names one lambda's __func per
// caller); the three read (3871, 11223, 11908) pass it to fn 1922, which copies it into a 20-byte object and returns
// that object, call fn 1921 on the object, and destroy the object's std::function and then their own. 1922 is a
// constructor (it returns its first argument, the object it fills), kept out of line in every caller where libc++'s
// std::function copy, which is its body, is inlined (cost 40, threshold 250, -Rpass=inline on
// cgeradorrelversaopacotedados.cpp's object; cost 50 in a probe with the source a reference parameter), so it is
// defined in another TU than its callers (a reading). 1921 takes that object: it calls the std::function once (slot 6;
// an empty one throws through fn 648, __throw_bad_function_call) and returns "Eleitores aptos" with the sum of the two
// 16-bit counts, then the section's own voters and those on a temporary transfer, each as "{:04}". So the object is a
// class holding the std::function, with that constructor and member. The constructor takes the std::function by value:
// in fn 11223 a later temporary takes the frame slot of 1921's result, not that of the std::function the caller built
// (docs/reference/facts/codegen.md C10; measured on 11223 both ways), and it copies it into the member (1922's body
// clones; a move does not). Chosen: the class, its name, the members' names, the member's const and its being a member
// (a free function taking the object by reference gives the same code), and the implicit destructor (the callers
// destroy the member inline).

#include <functional>
#include <string>

namespace comum {

struct SQtdeAptos;

class CEleitoresAptos {
public:
    explicit CEleitoresAptos(std::function<SQtdeAptos()> qtdeAptos);

    std::string Formata() const;

private:
    std::function<SQtdeAptos()> m_qtdeAptos;
};

} // namespace comum
