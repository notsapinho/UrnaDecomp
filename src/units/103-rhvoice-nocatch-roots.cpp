// Roots: what RHVoice's landing pads used to keep in the link. Reached the way the target reaches each one.
// RHVoice is built with no landing pads (src/Makefile, docs/reference/facts/libraries.md B6), so no RHVoice object takes
// a table slot for a callee any more. binaryen then inlines or drops those callees and removes results no caller
// reads, which changes the callees' callers too (docs/reference/facts/tool-traps.md X1).
// - Through a table slot in the target, by an invoke_* in code not written yet, so the address is taken here. The callers
//   listed pass the slot to an invoke_*, read from their rows. Each list is a floor: a small constant at another site can
//   be a slot or an integer, and frame offsets of the same value are not slots.
//   string::assign(const char*) (12979, elem[168]: 212). It is the only reader of __assign_external's result, so it also
//   keeps 276's type.
//   string::operator=(const string&) (1700, elem[30]: 212, 7840, 10619).
//   ostream::operator<<(unsigned short) (4755, elem[96] and elem[103]).
//   string::reserve (7735, elem[465]: 5360, 9963).
// - Called directly in the target by callers not written yet, so two noinline callers stand in for them:
//   the push_back of std::vector<std::pair<std::string, unsigned short>> (1682: 727, 855, 3577, 5298, 5318, 9869, 9911),
//   and the D2 of std::__split_buffer<std::string, std::allocator<std::string>&> (5184: 9516; 9404, unit 00's, is in the link).
// Declared through asm labels with the objects' signatures, so this file instantiates nothing and every body comes from
// the object that defines it. Compiled as uenux2 code.
extern "C" {
int w12979_root_0(int, int) __asm__("_ZNSt3__212basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6assignEPKc");
int w1700_root_0(int, int) __asm__("_ZNSt3__212basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEaSERKS5_");
int w4755_root_0(int, int) __asm__("_ZNSt3__213basic_ostreamIcNS_11char_traitsIcEEElsEt");
void w7735_root_0(int, int) __asm__("_ZNSt3__212basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE7reserveEm");
void w1682_root_0(int, int) __asm__("_ZNSt3__26vectorINS_4pairINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEEtEENS5_IS8_EEE9push_backB8ne210108EOS8_");
int w5184_root_0(int) __asm__("_ZNSt3__214__split_bufferINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEERNS4_IS6_EEED2Ev");
}

namespace {

__attribute__((noinline)) void InsereSimbolo(int simbolos, int primeiro, int segundo)
{
    w1682_root_0(simbolos, primeiro);
    w1682_root_0(simbolos + 12, segundo);
}

__attribute__((noinline)) void InsereSimboloOutro(int simbolos, int primeiro)
{
    w1682_root_0(simbolos + 24, primeiro + 16);
}

// A D2 returns this in the object, and neither caller reads it, so binaryen removes the result as the target's did.
__attribute__((noinline)) void LiberaTemporarios(int primeiro, int segundo)
{
    w5184_root_0(primeiro);
    w5184_root_0(segundo + 20);
}

void* volatile w103_sink;

struct SW103Roots {
    SW103Roots()
    {
        w103_sink = reinterpret_cast<void*>(&w12979_root_0);
        w103_sink = reinterpret_cast<void*>(&w1700_root_0);
        w103_sink = reinterpret_cast<void*>(&w4755_root_0);
        w103_sink = reinterpret_cast<void*>(&w7735_root_0);
        w103_sink = reinterpret_cast<void*>(&InsereSimbolo);
        w103_sink = reinterpret_cast<void*>(&InsereSimboloOutro);
        w103_sink = reinterpret_cast<void*>(&LiberaTemporarios);
    }
} w103_roots;

} // namespace
