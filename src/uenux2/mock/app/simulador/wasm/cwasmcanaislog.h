#pragma once

#include <deque>
#include <functional>
#include <mutex>
#include <string>
#include <unordered_map>

namespace simulador {

// Recovered: the wasm simulator's log lines, kept per channel. No record, symbol, string or RTTI names the class, its
// file or any member: every name here is chosen, from what the bodies do. What the target shows:
// - one object of 168 bytes at 1832676, a function-local static of an inline function: fns 1524 and 8327 build it in
//   place under a guard byte (1832844) they read with `i32.const 1; i32.and`, which a static of an inline function gives
//   (docs/reference/facts/reading.md R17), and its destructor, fn 5154, fills two table slots, 534 and 741. Ours does
//   too: each object that holds the inline GetInst (cwasminit.cpp's and cwasmlogd.cpp's) emits a destructor stub, and
//   binaryen merges the two into one function in two slots;
// - its layout, from the constructor those two hold inlined and from fn 5154: a std::mutex at +0 (24 bytes, unlocked by
//   fn 150 at the end of fn 5152 and destroyed last by fn 5154) and three channels of 48 bytes from +24, each a
//   std::deque<std::string> (fn 5152 pushes a 12-byte string into 341-element blocks), an std::unordered_map whose
//   max_load_factor the constructor sets to 1.0f, with nodes that hold a std::function at +16 (fn 5152 copies each
//   into a std::vector and calls slot 6, operator(), with a std::string; fn 5154 destroys each through slot 4 or 5),
//   and an int the constructor sets to 1, which none of the four target functions that address the object reads;
// - Escreve is fn 5152, (canal, texto): every caller passes the same object, and binaryen's dead-argument elimination
//   drops such a parameter (docs/how-to-decompile.md step 2), from ours too. Its body holds two other functions
//   binaryen inlined (a second and a third stack-pointer prologue, docs/reference/facts/reading.md R10), so they are
//   out of line here: Agora, the "[%Y-%m-%d %H:%M:%S]" time stamp, and Adiciona, which keeps the last 2000 lines of the
//   channel and hands the new one to the channel's observers.
// Chosen beyond the names: the map's int key, that the channels are a plain array, the mutex's place in this class,
// Agora as a static member, and the int types of the channel and of the counter.
class CWasmCanaisLog {
public:
    static CWasmCanaisLog& GetInst()
    {
        static CWasmCanaisLog s_inst;
        return s_inst;
    }

    void Escreve(int canal, const std::string& texto);

private:
    struct SCanal {
        std::deque<std::string> m_historico;
        std::unordered_map<int, std::function<void(const std::string&)>> m_observadores;
        int m_proximoId = 1;
    };

    static std::string Agora();
    void Adiciona(int canal, std::string linha);

    std::mutex m_mutex;
    SCanal m_canais[3];
};

} // namespace simulador
