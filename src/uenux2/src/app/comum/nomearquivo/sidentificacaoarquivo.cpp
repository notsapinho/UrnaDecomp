// The reconstruction's notes, not TSE's text: comum::SIdentificacaoArquivo's constructor, target fn 5726
// (app/comum/nomearquivo/cnomearquivo.h says what it rests on). No record names the file or the function: the path and
// the line are chosen. It is out of line in another TU than comum::CPE::CreateInst's (fn 2787), a reading: CreateInst
// keeps its 35-byte call where clang inlines a single-caller constructor of its own TU.
#include "app/comum/nomearquivo/cnomearquivo.h"

#include "ecourna/api/util/cstringutils.hpp"

namespace comum {

SIdentificacaoArquivo::SIdentificacaoArquivo(const EUrnaFase fase, const uedword idPE, const std::string& uf,
    const md::CPleito& pleito)
    : fase(fase), idPE(idPE), uf(ecourna::api::util::CStringUtils::ToLower(uf)), pleito(pleito)
{
}

} // namespace comum
