#pragma once

// api::CLp, the printer the reports print through. Recovered: the name and the file that defines its constructor
// (record 1543108, mock/app/simulador/wasm/cwasmclp.cpp 10:68, api::CLp::CLp(), held inlined by fn 3876, its
// singleton's accessor), and the layout, 12 bytes: fn 3876 allocates 12, stores the word
// CPolySingleton<IImpressoraRelatorios>::instance() returns at +0 and at +4 and clears +8; fn 3875 calls slot 9 of
// +4's IImpressora; the destructor (fn 5978, cwasmclp.cpp) releases +8 as a std::unique_ptr does, clearing the member
// before it deletes the pointee. The pointee's layout is read from that destructor alone: two words it does not touch,
// a std::vector of trivially destructible elements at +8 and an ecourna::api::io::CFile at +20 (its inline destructor,
// `if (m_file) Close();` with fn 336, then its name). That is all that is recovered of either class: the data
// members' names and types (the two words', the vector's element type uebyte), the pointee's name and this header's
// path are chosen. Only the members the record and the destructor need are declared.

#include <memory>
#include <vector>

#include "ecourna/api/io/cfile.hpp"
#include "ecourna/api/uetypes.hpp"

namespace api {

class IImpressora;
class IImpressoraRelatorios;

struct SSaidaLp {
    int m_reservado1;
    int m_reservado2;
    std::vector<uebyte> m_buffer;
    ecourna::api::io::CFile m_arquivo;
};

class CLp {
public:
    ~CLp();

private:
    CLp();

    IImpressoraRelatorios* m_relatorios;
    IImpressora* m_impressora;
    std::unique_ptr<SSaidaLp> m_saida;
};

} // namespace api
