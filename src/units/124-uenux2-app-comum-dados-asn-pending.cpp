// Pending members: the members the vtables of this unit's comum converters need and no source of ours defines yet.
// Each class overrides only DoDesconverte (slot 3); slot 2 is the base's default DoConverte,
// comum::asn::IConversorASN<ENTIDADE, DADO>::DoConverte, a 29-byte thunk of fn 731 in the target, whose record puts a
// throw on line 89 col 15 of src/app/comum/asn/iconversorasn.h. iconversorasn.h does not define that default yet (unit
// 47's pending file says why, and 96-uenux2-app-comum-asn.mk has the measurement of fn 731 at -O3), so this file
// defines each instantiation's member as an explicit specialization, with the symbol the vtable references; its body is
// NOT the target's, it traps. Delete these when iconversorasn.h defines the default DoConverte: a specialization is a
// strong symbol with the name of that template's instantiation, so the link would keep the trap without a word.
// Their source, in the class at lines 87 to 90 of the header (the codes are comum::EUeComumAsnError's):
//     throw CUeComumAsnError(7655, std::format("Método DoConverte() não implementado para {}", typeid(TEntidade).name()));
//   - CConversorComplementosMunicipios: slot 2, target fn 11380
//   - CConversorSuplencia: slot 2, target fn 11358
#include "app/comum/dados/asn/estadoaplicacao/cconversordadocorrespondencia.h"
#include "app/comum/dados/asn/estadoaplicacao/cconversorestadogeral.h"
#include "app/comum/dados/asn/municipiozona/cconversorcomplementosmunicipios.h"
#include "app/comum/dados/asn/processoeleitoral/cconversorsuplencia.h"
#include "app/comum/dados/asn/rdv/cconversorvoto.h"

namespace comum::asn {

template <>
IConversorASN<ModuloComplementosMunicipios::EntidadeComplementosMunicipios, md::CComplementosMunicipiosUF>::TEntidade
IConversorASN<ModuloComplementosMunicipios::EntidadeComplementosMunicipios, md::CComplementosMunicipiosUF>::DoConverte(
    const TDado&) const
{
    __builtin_trap();
}

template <>
IConversorASN<ModuloEleicao::Suplencias, md::CSuplencia>::TEntidade
IConversorASN<ModuloEleicao::Suplencias, md::CSuplencia>::DoConverte(const TDado&) const
{
    __builtin_trap();
}

// comum::asn::CConversorEstadoGeral::DoDesconverte, slot 3, target fn 11398: its record lines (cconversorestadogeral.cpp
// 87 and 91, DesconverteEstadoUrna inlined) and its callee fn 5637, comum::md::estadoaplicacao::CEstadoGeral's
// constructor, which is not written (5637 calls fn 1249, which has no name).
CConversorEstadoGeral::TDado CConversorEstadoGeral::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

// comum::asn::CConversorDadoCorrespondencia, both slots: DoConverte (target fn 11399) and DoDesconverte (fn 11400), which
// build the correspondence's dates through api::CDateTime (fns 1713, 1080, 3604, 3605, 3733, 3734 are their callees).
// This file emits the class's vtable with them; CConversorEstadoGeral::DoConverte (fn 11397) builds one on its stack.
CConversorDadoCorrespondencia::TEntidade CConversorDadoCorrespondencia::DoConverte(const TDado&) const
{
    __builtin_trap();
}

CConversorDadoCorrespondencia::TDado CConversorDadoCorrespondencia::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

// comum::asn::CConversorVoto::DoDesconverte, slot 3, target fn 11354. It builds the md::CVoto through CVoto's
// constructor, fn 2256 (record cvoto.cpp:80), which is not written: 2256 sets m_numero through fn 1374 (the copying
// ecourna::api::util::CStringUtils::Trim, matched) and builds its error message from a name per ETipo, built in each
// case of one switch and joined into two shared tails (" com digitado vazio" and " com digitado nao vazio"); the source
// form of that is not recovered: two helpers over a const std::string& name stay out of line in clang (461 over 660
// rows), a const char* name with the string built after the switch gives 618 over 863 (both measured with the copying
// ToLower in Trim's place, a call of the same shape). With such a constructor out of
// line, 11354 differed from the target in operand rows only (45 over 489 rows), as written
// below with the static DesconverteTipo it inlines, whose throws sit on cconversorvoto.cpp:71 and :75 (their lines 49 to
// 76 stay blank in cconversorvoto.cpp until it lands):
//     md::CVoto::ETipo CConversorVoto::DesconverteTipo(ModuloRegistroDigitalVoto::TipoVoto tipo)
//     {
//         switch (tipo) {
//             case ModuloRegistroDigitalVoto::TipoVoto::legenda:
//                 return md::CVoto::LEGENDA;
//             case ModuloRegistroDigitalVoto::TipoVoto::nominal:
//                 return md::CVoto::NOMINAL;
//             case ModuloRegistroDigitalVoto::TipoVoto::branco:
//                 return md::CVoto::BRANCO;
//             case ModuloRegistroDigitalVoto::TipoVoto::nulo:
//                 return md::CVoto::NULO;
//             case ModuloRegistroDigitalVoto::TipoVoto::brancoAposSuspensao:
//                 return md::CVoto::BRANCO_APOS_SUSPENSAO;
//             case ModuloRegistroDigitalVoto::TipoVoto::nuloAposSuspensao:
//                 return md::CVoto::NULO_APOS_SUSPENSAO;
//             case ModuloRegistroDigitalVoto::TipoVoto::nuloPorRepeticao:
//                 return md::CVoto::NULO_POR_REPETICAO;
//             case ModuloRegistroDigitalVoto::TipoVoto::nuloCargoSemCandidato:
//                 return md::CVoto::NULO_CARGO_SEM_CANDIDATO;
//             case ModuloRegistroDigitalVoto::TipoVoto::nuloAposSuspensaoCargoSemCandidato:
//                 return md::CVoto::NULO_APOS_SUSPENSAO_CARGO_SEM_CANDIDATO;
//             case ModuloRegistroDigitalVoto::TipoVoto::unknownEnumeration_:
//                 throw CUeComumDadosError(EUE_COMUM_DADOS_7974, std::format("Valor inválido para tipo voto eleitor: {}", tipo.asInt()));
//             default:
//                 break;
//         }
//         throw CUeComumDadosError(EUE_COMUM_DADOS_7975, std::format("Valor inválido para tipo voto eleitor: {}", tipo.asInt()));
//     }
//
//     CConversorVoto::TDado CConversorVoto::DoDesconverte(const TEntidade& entidade) const
//     {
//         const md::CVoto::ETipo tipo = DesconverteTipo(entidade.get_tipoVoto());
//         const std::string digitacao =
//             entidade.digitacao_isPresent() ? entidade.get_digitacao() : TEntidade::digitacao::value_type("");
//         return TDado(tipo, digitacao);
//     }
CConversorVoto::TDado CConversorVoto::DoDesconverte(const TEntidade&) const
{
    __builtin_trap();
}

} // namespace comum::asn
