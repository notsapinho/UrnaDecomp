#pragma once

#include <string>

namespace api {
class CPaperFormBuilder;
} // namespace api

namespace comum {

namespace md {
class CHorarioVerao;
namespace estadoaplicacao {
class CDadoCorrespondencia;
} // namespace estadoaplicacao
} // namespace md

// Reconstruction notes, not TSE's text. Helpers the reports share, none of them named by a record, slot or RTTI: their
// names, their being free functions of comum (they read nothing but their arguments' public members), their
// parameters' forms, this header and its .cpp are chosen. src/units/296-uenux2-relatorios-impressao.mk has the
// evidence and the places.
// - ImprimeSeparador (target fn 1156): a centred line of 38 '=' (the target stores the bytes, no literal).
// - FormataCodigoCarga (fn 2252): the load's code (CDadoCorrespondencia's string at +28) in groups of three digits
//   joined by '.', the last group the rest; FormataCodigoCargaResumido (fn 2792): its last two groups only.
// - ImprimeAssinaturas, FormataInicioHorarioVerao and FormataFimHorarioVerao have no target index: fn 5591 holds each
//   behind a stack frame of its own, as binaryen inlines a function of another TU with one caller.
void ImprimeSeparador(api::CPaperFormBuilder& builder);
std::string FormataCodigoCarga(const md::estadoaplicacao::CDadoCorrespondencia& correspondencia);
std::string FormataCodigoCargaResumido(const md::estadoaplicacao::CDadoCorrespondencia& correspondencia);
void ImprimeAssinaturas(api::CPaperFormBuilder& builder);
std::string FormataInicioHorarioVerao(const md::CHorarioVerao& horarioVerao);
std::string FormataFimHorarioVerao(const md::CHorarioVerao& horarioVerao);

} // namespace comum
