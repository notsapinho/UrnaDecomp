// Roots: libc++'s std::__thread_struct constructor (target fn 2541, from libc++'s thread.cpp) has four direct callers in
// the target, fns 5392, 5568, 10226 and 10850. 10850 (api::CTimer::Start, in itimerscheduler.cpp) and 5392
// (vota::CSuspensaoAutomaticaEleitor::DisparaSinalizacaoSonora, unit 152) are in the link; NovaThread stands for 5568
// and 10226. Its body, the constructor on two objects, is no
// target function's. Declared through asm labels: a constructor returns this in the object
// (docs/reference/facts/units.md U1). Compiled with APP_CXXFLAGS, like the other stand-ins.
extern "C" {
int w101_thread_struct(void*) __asm__("_ZNSt3__215__thread_structC1Ev");
}

namespace {

__attribute__((noinline)) void NovaThread(void* a, void* b)
{
    w101_thread_struct(a);
    w101_thread_struct(b);
}

void* volatile w101_sink;

struct SW101Roots {
    SW101Roots() { w101_sink = reinterpret_cast<void*>(&NovaThread); }
} w101_roots;

} // namespace
