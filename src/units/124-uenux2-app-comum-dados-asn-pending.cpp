// Pending members: the members the vtables of this unit's comum converters need and no source of ours defines yet.
// Their bodies are NOT the target's; they trap.
#include "app/comum/dados/asn/estadoaplicacao/cconversorestadogeral.h"
#include "app/comum/dados/asn/rdv/cconversorvoto.h"

namespace comum::asn {

// comum::asn::CConversorEstadoGeral::DoDesconverte, slot 3, target fn 11398: its record lines (cconversorestadogeral.cpp
// 87 and 91, DesconverteEstadoUrna inlined) and its callee fn 5637, comum::md::estadoaplicacao::CEstadoGeral's
// constructor, which is not written (5637 calls fn 1249, which has no name).
CConversorEstadoGeral::TDado CConversorEstadoGeral::DoDesconverte(const TEntidade&) const
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
