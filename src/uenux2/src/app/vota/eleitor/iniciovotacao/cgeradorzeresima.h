#pragma once

// The zeresima's report and its file, which fn 11946 (vota::CGeraZeresimaBase::StartState, cgerazeresimabase.cpp)
// holds behind stack frames of their own: a 64-byte one for GeraZeresima (LogaGerandoRelatorio with
// RELATORIO_ZERESIMA and 0, the report written to GetPathTrab(FLASH_INTERNA) / "ze.dat", SincronizaRelatorios("ze.dat"),
// LogaGerandoRelatorio with 1) and a 400-byte one for CriaRelatorioZeresima (the report's parts), binaryen's inlining
// of a function with one caller (docs/reference/facts/reading.md R10). Neither has a target index or a record. Their
// names, their being free functions of vota, this file's path and name (beside cgeradorresumozeresima.cpp, the
// summary's report, by analogy) and this header are chosen. The object's place in the link, between
// cgeradorresumozeresima.cpp's and cgerazeresimabase.cpp's, is the one the target's data give the control blocks the
// report builds: src/units/325-uenux2-geradores-zeresima.mk has that evidence and the places measured.

namespace api {
class CReport;
} // namespace api

namespace vota {

api::CReport CriaRelatorioZeresima();
void GeraZeresima();

} // namespace vota
