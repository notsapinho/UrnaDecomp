// Pending members: the virtual members of comum::CRelatorioTesteImpressora and comum::CImprimirExtratoCarga that
// src/uenux2/src/app/comum/relatorios/crelatoriotesteimpressora.cpp does not hold yet. The derived class's vtable (emitted
// with EhTreinamento, its key function, in that TU) and the base's (emitted here, with the base's key function) need them
// defined; their bodies are NOT the target's, they trap. Each moves into its class's .cpp when it is reconstructed; delete
// this file with the last one.
// - CImprimirExtratoCarga::ImprimeDataHoraEmissao, slot 25, target fn 11216 (799 B), out of line in the base's own file,
//   app/comum/relatorios/cimprimirextratocarga.cpp, not written (cimprimirextratocarga.h says why it is there). It prints
//   "EMISSAO DO RELATORIO" and std::format("DATA: {:.10}       HORA: {:.8}", <now as DD/MM/YYYY>, <now as hh:mm:ss>)
//   through two helpers, fns 5472 and 5473, which build api::CDateTime's "now" (fns 1155, 1000) and format it with
//   fns 706 and 779. It waits for those two helpers, which no evidence names, and for api::CDateTime's members.
// - GetConteudoQRCode, slot 5, fn 11200 (330 B): builds a vector of string pairs from the general state (fn 5636, 3903 B),
//   copies it (fn 1300), adds one tag of two by a switch on 1 (fn 5783) and turns it into the string (fn 5782, 2390 B).
//   It waits for 5636, 5782 and 5783, none named or written.
// - EstaEmHorarioVerao, slot 8, fn 11198 (69 B): GetHorarioVerao()'s start <= now and now < its end, with
//   api::CDateTime's default constructor (fn 479) and its comparison (fn 1261). It waits for those two.
// - InicializaTradutorFrase, slot 10, fn 11196 (631 B): builds a std::map<char, ecourna::app::dados::CLabelParametrizado>
//   of the four labels of CConfiguracaoEleicao's CParametrosUrna ('M' municipio, 'Z' zona, 'S' secao, 'P' partido) and
//   copies it into comum::md::CTradutorFrase's map (@1839056; fn 5794, the copy's __assign_multi, has that map's address
//   folded in). Fn 7787 holds the same code. Written as a named local map built from the list and handed to an inline
//   static setter of the map, it scores 281 over 345 rows in the whole link (a roots stand-in for 7787 kept the
//   callees' count at two): clang inlines the map's initializer-list constructor into it and leaves the insertion's
//   __emplace_hint_unique_extract_key out of line, where the target calls the constructor (fn 5795) with the insertion
//   inlined into that. Passing the list straight to the setter gives 287 over 349. What makes the target's constructor
//   stay out of line is not found; it waits for that, and for a setter of CTradutorFrase's map in ctradutorfrase.h.
// - GetDadosLocal, slot 15, fn 11188 (3304 B), with ConverteTipoAlimentacao's record at line 173 of
//   crelatoriotesteimpressora.cpp inlined: not reconstructed; its callees 654, 1881, 1933, 2816 and 5738 have no name
//   (no match line and no line in splat/symbol_addrs.txt).
#include "app/comum/relatorios/crelatoriotesteimpressora.h"

namespace comum {

void CImprimirExtratoCarga::ImprimeDataHoraEmissao(api::CPaperFormBuilder&) const
{
    __builtin_trap();
}

std::string CRelatorioTesteImpressora::GetConteudoQRCode() const
{
    __builtin_trap();
}

bool CRelatorioTesteImpressora::EstaEmHorarioVerao() const
{
    __builtin_trap();
}

void CRelatorioTesteImpressora::InicializaTradutorFrase() const
{
    __builtin_trap();
}

std::vector<std::string> CRelatorioTesteImpressora::GetDadosLocal() const
{
    __builtin_trap();
}

} // namespace comum
