#pragma once

// api::CLp, the printer the reports print through. Recovered: the name and the file that defines its constructor
// (record 1543108, mock/app/simulador/wasm/cwasmclp.cpp 10:68, api::CLp::CLp(), held inlined by fn 3876, its
// singleton's accessor), and the layout, 12 bytes: fn 3876 allocates 12, stores the word
// CPolySingleton<IImpressoraRelatorios>::instance() returns at +0 and at +4 and clears +8; fn 3875 calls slot 9 of
// +4's object; the destructor (fn 5978, cwasmclp.cpp) releases +8 as a std::unique_ptr does, clearing the member
// before it deletes the pointee. The pointee's layout is read from that destructor alone: two words it does not touch,
// a std::vector of trivially destructible elements at +8 and an ecourna::api::io::CFile at +20 (its inline destructor,
// `if (m_file) Close();` with fn 336, then its name). That is all that is recovered of either class: the data
// members' names and types (the two words', the vector's element type uebyte), the pointee's name and this header's
// path are chosen. Only the members the record and the destructor need are declared. The constructor assigns +4 first
// and copies it to +0 (src/units/219-uenux2-cwasmclp.mk has the store order measured); +0's type, IImpressora*, and
// +4's, IImpressoraRelatorios*, are chosen.
//
// A singleton: GetInst (fn 3876, a chosen name) keeps the object in a static std::unique_ptr (@1834044, destroyed at
// exit by fn 12016)
// under a static std::mutex (@1834020, by fn 12015), the shape of the vota states' accessors, with the constructor out
// of line. Fn 3875 is a member: it reads +4. Its three callers (fns 2882, 3671, 11908) pass a CSubReport and a
// std::function<void()> they build (a lambda's __func); it calls the printer's slot 9 when +4 is set, the
// sub-report's slots 5 and 6 (api/gui/isubreport.h: TemParte, ImprimeParte) and then the function. Its name and its
// parameters' types are chosen: the body reads the second only through ISubReport's slots and calls the third through
// std::function's.

#include <functional>
#include <memory>
#include <mutex>
#include <vector>

#include "ecourna/api/io/cfile.hpp"
#include "ecourna/api/uetypes.hpp"

namespace api {

class IImpressora;
class IImpressoraRelatorios;
class ISubReport;

struct SSaidaLp {
    int m_reservado1;
    int m_reservado2;
    std::vector<uebyte> m_buffer;
    ecourna::api::io::CFile m_arquivo;
};

class CLp {
public:
    ~CLp();

    static CLp& GetInst();

    void Imprime(const ISubReport& subRelatorio, const std::function<void()>& corpo);

private:
    CLp();

    static std::unique_ptr<CLp> s_inst;
    static std::mutex s_mutex;

    IImpressora* m_impressora;
    IImpressoraRelatorios* m_impRel;
    std::unique_ptr<SSaidaLp> m_saida;
};

} // namespace api
