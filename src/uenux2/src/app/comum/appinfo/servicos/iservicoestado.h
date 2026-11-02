#pragma once

#include <filesystem>

namespace comum {

// A service that keeps one ESTADO of the urna in a file, through its ASN.1 CONVERSOR. RTTI names the template and its
// four instances, each the only base of one class (comum::CServicoEstadoGeral, -Vota, -Gap, -SA in
// ledger/classes.json); slots 0 and 1 of the four vtables are the shared 174 and 144 (an empty D2, and a D0 that only
// frees), slot 2 is GetPathArquivo, which -Vota's, -Gap's and -SA's records name and the template's save and read (fns
// 2894, 3791) call through slot 2, so CServicoEstadoGeral's is the same member. The destructor's spelling is chosen
// ({} and = default give the same bodies, docs/reference/facts/reading.md R4, measured on plain classes), and so is
// GetPathArquivo being pure here: no vtable of the template is in the target's data, and every instance's class
// overrides it. This path and the template's parameter names are chosen: no record names the header.
//
// Not written: the template's members the target holds as binaryen merges of the four instances, each with landing
// pads. Target fn 2894 (thunks 3592, 5329, 10089, 10112, which pass the converter's vptr and two table slots) saves an
// ESTADO: it takes GetPathArquivo's path and a copy of its string, builds the CONVERSOR on its stack, converts the
// ESTADO (IConversorASN::Converte, merged as fn 2893) and passes the string and the entity to a CFileASN writer (merged
// as fn 2892). Fn 3791 reads CServicoEstadoGeral's file back, with CFileASN's reading inlined: a reading of its callers
// and strings. src/units/206-uenux2-app-comum-appinfo-servicos.mk says what each waits for.
template <typename ESTADO, typename CONVERSOR>
class IServicoEstado {
public:
    virtual ~IServicoEstado() {}

    virtual std::filesystem::path GetPathArquivo() = 0;
};

} // namespace comum
