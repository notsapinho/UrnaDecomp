# uenux2 comum::md::CHorarioVerao, in src/app/comum/dados/md/chorarioverao.cpp, the file its constructor's records name
# (chorarioverao.cpp:29 and :32, which fn 11384 holds with the constructor inlined). The layout is unit 89's, in
# chorarioverao.h. The constructor is written at those records' lines, where it begins is chosen, and Contem moved two
# lines down with it (its line is chosen too); fragment 172 matches 11384, which holds it.
#
# Written: Contem, whether a date lies in [m_inicio, m_fim). It has no target function of its own: fn 11198,
# comum::CRelatorioTesteImpressora::EstaEmHorarioVerao (unit 123), holds its two CDate::operator<=> calls, and 11198 is
# matched over it, the only comparison Contem has. Left unrooted, it has one caller here, and binaryen inlines it there.
# Measured in the whole link with `pnpm wasm score` against 11198:
# - out of line here: 3 over 37 rows, all operand-only, then `match`. The target holds the `&&` as `if (result i32) ...
#   else i32.const 0 end`, its value carried across the stack epilogue.
# - the same compares written in 11198 over two inline getters of the dates: 14 over 40 rows (3 inserted, 3 deleted):
#   ours keeps the result in a local, set inside an `if` with no result, and reads it after the epilogue.
# That the target's 11198 holds a function binaryen inlined from another TU is the reading of these two measurements
# (docs/reference/facts/reading.md R10 has the other signs of such code).
# Chosen: the name Contem, that it is a member (it reads the private dates), its CDate parameter (a CDateTime, whose date
# is at +0, was not linked), its line (after the records' lines).
CHORARIOVERAO_SRCS := src/app/comum/dados/md/chorarioverao.cpp
UENUX2_SRCS += $(CHORARIOVERAO_SRCS)
