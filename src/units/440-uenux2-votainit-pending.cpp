// Pending member of unit 440 (src/units/440-uenux2-votainit.mk), a trap until it is reconstructed (src/units/README.md
// "Pending members"):
// - vota::CarregaVotacao, target fn 7787 (148,912 B), which votaInit (fn 7840, unit 170's TU) invokes through table
//   slot 39: the vote's data load, then CTelasVota::CreateInst (record ctelasvota.cpp:3435, its constructor :3502),
//   CInfoMTLCD::CreateInst (cinfomtlcd.cpp:33) and CInstrucaoVotacaoAcessibilidade::CacheInstructionAudio inlined.
//   No record names 7787 itself, so its name is chosen. It holds the place of votaInit's call, which needs a definition
//   our link has; it is not written, and this file and its rule go when 7787 is.
namespace vota {

void CarregaVotacao()
{
    __builtin_trap();
}

} // namespace vota
