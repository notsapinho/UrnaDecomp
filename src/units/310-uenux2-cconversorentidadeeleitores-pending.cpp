// Pending members: the virtual member of comum::asn::CConversorEntidadeEleitores that
// src/uenux2/src/app/comum/dados/asn/eleitor/cconversorentidadeeleitores.cpp does not hold yet. It is the class's key
// function, so the vtable (@1566768) is emitted here until it lands; this body is NOT the target's, it traps. It moves
// into that file when it is reconstructed; delete this file with it.
// - CConversorEntidadeEleitores::DoDesconverte, vtable slot 2, target fn 11411 (7299 B, 256-byte frame), not written.
//   Every callee has a name but 2805, libc++'s hinted __find_equal of a tree keyed by md::CEleitorIdentidade, which the
//   TU that writes 11411 instantiates. What the target's body holds, read from its folded readout (pnpm wasm fn), in
//   order: the header through CConversorCabecalhoEntidade (vptr at frame +252, fn 3738); the identificacao's
//   municipioZona and secao words; when the seguranca field is present (hasOptionalField 0), CConversorSeguranca (vptr
//   at +224, fn 3730) and its key copied into a byte vector at +212 (fn 1158); when the voters field is present, a map
//   at +188 filled from the visitor's identities (+52 of CVisitanteEleitor) with hinted inserts (2805, then
//   __tree_balance_after_insert), and per voter (ModuloEleitores::EleitorSequencia, copied: fn 853) the records' inlined
//   members: GetInscricoesEleitor (records :49 and :76, behind a 528-byte frame: the identifiers' SEQUENCE_OF copied
//   (fn 2656), each CHOICE turned into a CEleitorIdentidade of type 1, 2 or 3 (fn 566) and pushed, then a duplicate
//   test that throws 7900 "Identidade duplicada ({}) para o eleitor ({})", and 7899 "Inscrição não encontrada" at
//   record :49), ConverteNecessidadeEspecial (record :38, the EleitorUrna copied, 0 or 1, else 7898 "Tipo de
//   necessidade inválido: {}"), two of the voter's strings (the second when its optional field is present) each cut to 40
//   characters,
//   DesconverteTipoTransferenciaTemporaria (record :210, an 11-way br_table, else 7901 "Tipo de transferência inválido:
//   {}"), DesconverteTransferenciaTemporaria (record :236, 7902 "Eleitor de voto em trânsito sem informações de
//   domicílio eleitoral.", over md::CTransferenciaTemporaria's constructor and ValidaConstrucao, record
//   ctransferenciatemporaria.cpp:35, 8070 "Construtor exclusivo para transferências de fato."), md::CDataJE's
//   constructor (record md/cdataje.cpp:26: a string of 8 digits, else 8002 "DataJE com formato inválido: {}"), the
//   voter's biometry index found in the map by identity, CEleitor's two constructors (fns 5668 and 5666, with and
//   without it) and the voters' vector's growth (fn 5700, unit 225's roots stand-in); then the entity built in the
//   result (centidadeeleitores.h's layout), with the seguranca converted again when present.
#include "app/comum/dados/asn/eleitor/cconversorentidadeeleitores.h"

namespace comum::asn {

CConversorEntidadeEleitores::TDado CConversorEntidadeEleitores::DoDesconverte(const TEntidade&, const TVisitor&) const
{
    __builtin_trap();
}

} // namespace comum::asn
