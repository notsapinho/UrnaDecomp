#pragma once

#include <filesystem>
#include <string>

#include "api/io/asn/cfileasn.h"

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
// Salva is target fn 2894, binaryen's merge of the four instances (thunks 3592, 5329, 10112, 10089, which pass the
// converter's vptr and two table slots), an -Oz -fexceptions TU's copies (our link's are cappinfobuilder.cpp's; that
// the target's are that TU's is a reading): it takes GetPathArquivo's path and a copy of its string, builds the
// CONVERSOR on its stack, converts the ESTADO (IConversorASN::Converte, merged as fn 2893) and passes the string and
// the entity to CFileASN::WriteToFile (merged as fn 2892). Carrega is fn 3791, CServicoEstadoGeral's instance at
// uenux2's flags, with CFileASN::ReadFromFile, its DecodeObjectFunction and IConversorASN::Desconverte inlined by
// binaryen. No record names either: both names are chosen. Salva's parameter is a reference: fn 6039 (comum::CAppInfo's
// saves) passes the state its singleton holds, with no copy. Each goes through a file-static helper that clang inlines;
// the helpers' names and their being free functions are chosen, the internal linkage measured
// (src/units/206-uenux2-app-comum-appinfo-servicos.mk).
template <typename CONVERSOR>
static typename CONVERSOR::TDado CarregaArquivo(const std::string& arquivo)
{
    CONVERSOR conversor;
    return conversor.Desconverte(api::CFileASN::ReadFromFile<typename CONVERSOR::TEntidade>(arquivo));
}

template <typename CONVERSOR>
static void SalvaArquivo(const std::string& arquivo, const typename CONVERSOR::TDado& dado)
{
    CONVERSOR conversor;
    api::CFileASN::WriteToFile(arquivo, conversor.Converte(dado));
}

template <typename ESTADO, typename CONVERSOR>
class IServicoEstado {
public:
    virtual ~IServicoEstado() {}

    virtual std::filesystem::path GetPathArquivo() = 0;

    void Salva(const ESTADO& estado);

    ESTADO Carrega();
};

template <typename ESTADO, typename CONVERSOR>
void IServicoEstado<ESTADO, CONVERSOR>::Salva(const ESTADO& estado)
{
    SalvaArquivo<CONVERSOR>(GetPathArquivo(), estado);
}

template <typename ESTADO, typename CONVERSOR>
ESTADO IServicoEstado<ESTADO, CONVERSOR>::Carrega()
{
    return CarregaArquivo<CONVERSOR>(GetPathArquivo());
}

} // namespace comum
