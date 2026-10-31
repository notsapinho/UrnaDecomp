// Root callers for the reconstructed uenux2 units (src/uenux2, docs/reference/facts/app-flags.md §F6), with the
// target's call-site counts: a function binaryen sees called once is inlined into its caller and a CBaseError
// ctor thunk with one caller disappears into the throw site, so every unit function is reached from at least
// two places. Compiled as uenux2 code (APP_CXXFLAGS).
#include <memory>
#include <string>
#include <vector>

#include "api/io/cinikey.h"
#include "api/io/eueioerror.h"
#include "api/ipc/eueipcerror.h"
#include "api/ipc/isemaphore.h"
#include "api/ipc/isyncctl.h"
#include "api/ipc/posix/cposixmutex.h"
#include "api/ipc/posix/cposixsemaphore.h"
#include "api/util/cwait.h"
#include "api/util/eueutilerror.h"
#include "ecourna/app/dados/tiposbasicos.hpp"

namespace {

__attribute__((noinline)) int EsperaA(size_t ms)
{
    api::CWait espera(ms);
    return static_cast<int>(sizeof(espera));
}

__attribute__((noinline)) int EsperaB(size_t ms)
{
    api::CWait espera(ms + 1);
    return static_cast<int>(sizeof(espera)) + 1;
}

__attribute__((noinline)) std::string ChaveA(const std::string& nome, const std::string& valor)
{
    api::CIniKey a(nome, valor);
    api::CIniKey b(nome, valor + "b");
    a = b;
    return a.GetValor();
}

__attribute__((noinline)) std::string ChaveB(const std::string& nome, const std::string& valor)
{
    api::CIniKey a(nome + "x", valor);
    const api::CIniKey b(nome, valor);
    a = b;
    return a.GetNome();
}

__attribute__((noinline)) std::shared_ptr<api::ISyncCtl> MutexA() { return std::shared_ptr<api::ISyncCtl>(new api::CPosixMutex()); }
__attribute__((noinline)) std::shared_ptr<api::ISyncCtl> MutexB() { return std::make_shared<api::CPosixMutex>(); }
__attribute__((noinline)) std::shared_ptr<api::ISemaphore> SemaforoA(unsigned int v) { return std::shared_ptr<api::ISemaphore>(new api::CPosixSemaphore(v)); }
__attribute__((noinline)) std::shared_ptr<api::ISemaphore> SemaforoB(unsigned int v) { return std::make_shared<api::CPosixSemaphore>(v + 1); }

__attribute__((noinline)) int UsaSincronizacao(int a)
{
    auto m1 = MutexA();
    auto m2 = MutexB();
    m1->Lock();
    m2->Lock();
    m2->Unlock();
    m1->Unlock();
    auto s1 = SemaforoA(static_cast<unsigned int>(a));
    auto s2 = SemaforoB(static_cast<unsigned int>(a));
    s1->Lock();
    s1->Unlock();
    s2->Wait();
    int r = s1->Wait(static_cast<size_t>(a)) + s2->Wait(0) + s1->GetValue() + s2->GetValue();
    return r;
}

// extra callers of the exception ctor thunks (CBaseError<E, L>::CBaseError has dozens of callers in the target)
__attribute__((noinline)) void LancaUtil1(int c, const std::string& m) { throw api::CUeUtilError(static_cast<api::EUeUtilError>(c), m); }
__attribute__((noinline)) void LancaUtil2(int c, const std::string& m) { throw api::CUeUtilError(static_cast<api::EUeUtilError>(c), m + "2"); }
__attribute__((noinline)) void LancaIo1(int c, const std::string& m) { throw api::CUeIoError(static_cast<api::EUeIoError>(c), m); }
__attribute__((noinline)) void LancaIo2(int c, const std::string& m) { throw api::CUeIoError(static_cast<api::EUeIoError>(c), m + "2"); }
__attribute__((noinline)) void LancaIpc1(int c, const std::string& m) { throw api::CUeIpcError(static_cast<api::EUeIpcError>(c), m); }
__attribute__((noinline)) void LancaIpc2(int c, const std::string& m) { throw api::CUeIpcError(static_cast<api::EUeIpcError>(c), m + "2"); }

} // namespace

// std::vector<double>'s range insert (target fn 2662), which simulador::CWasmScreen::FillPath and DrawPath and RHVoice's
// speech_processor call: the target's copy has TBAA, so this object, ahead of uenux2's on the link line, holds the instance
// (docs/reference/facts/app-flags.md, "The stand-ins keep strict aliasing"; uenux2's -fno-strict-aliasing gives another body)
void urna_insere_doubles(std::vector<double>& valores, const double* inicio, const double* fim)
{
    valores.insert(valores.end(), inicio, fim);
}

// CBaseType's constructors whose target copies are uenux2's: their records name the conan package's installed header
// (p/include/ecourna/api/pattern/cbasetype.hpp) and they have no landing pad, though ecourna's converters call them too.
// The first uenux2 object that used one kept the copy, and ecourna's objects emit their own, so only an object ahead of
// ecourna's can hold them (a fragment's roots link after both trees). The explicit instantiations add no function of
// their own to the link. src/units/112-ecourna-cbasetype.mk has the measurement at uenux2's flags and the real callers.
template CBaseType<unsigned short, 0, 9999, 15>::CBaseType(unsigned short);
template CBaseType<unsigned short, 0, 9999, 36>::CBaseType(unsigned short);
template CBaseType<unsigned short, 0, 999, 38>::CBaseType(unsigned short);
template CBaseType<unsigned short, 0, 9999, 9>::CBaseType(unsigned short);
template CBaseType<unsigned short, 0, 9999, 7>::CBaseType(unsigned short);
template CBaseType<unsigned int, 0, 99999, 6>::CBaseType(unsigned int);
template CBaseType<unsigned int, 0, 9999, 8>::CBaseType(unsigned int);
template CBaseType<unsigned short, 1, 99, 3>::CBaseType(unsigned short);

int urna_roots_uenux2(int a)
{
    std::string s(static_cast<size_t>(a), 'k');
    int r = EsperaA(static_cast<size_t>(a)) + EsperaB(static_cast<size_t>(a));
    r += static_cast<int>(ChaveA(s, s).size() + ChaveB(s, s).size());
    r += UsaSincronizacao(a);
    switch (a) {
    case 1: LancaUtil1(a, s); break;
    case 2: LancaUtil2(a, s); break;
    case 3: LancaIo1(a, s); break;
    case 4: LancaIo2(a, s); break;
    case 5: LancaIpc1(a, s); break;
    case 6: LancaIpc2(a, s); break;
    default: break;
    }
    return r;
}
