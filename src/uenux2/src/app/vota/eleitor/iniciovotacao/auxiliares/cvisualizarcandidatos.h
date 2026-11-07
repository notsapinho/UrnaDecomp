#pragma once

#include <memory>
#include <mutex>
#include <optional>
#include <set>
#include <vector>

#include "app/comum/cappstate.h"
#include "app/comum/dados/md/candidatura/ccandidatura.h"

namespace comum::md {
class CCargo;
} // namespace comum::md

namespace vota {

// vota::CVisualizarCandidatos (RTTI: si_class of comum::CAppState; vtable @1545664 [2871, 11877, 11876, 7480, 1661,
// 218, 425, 218, 425]): it overrides StartState (slot 2, fn 11876, records cvisualizarcandidatos.cpp:132 and :140,
// written; src/units/150-uenux2-eleitor-estados.mk says what it differs in) and the destructors. The destructor is out
// of line: the deleting one (fn 11877) calls it and frees `this`; fn 2871 stores no vptr, as a final class's
// (docs/reference/facts/reading.md R4). Fn 2871 destroys a std::vector of 72-byte elements at +12, each one's members
// where comum::md::CCandidatura has them (ccandidatura.h): the substitutes' vector at +60 through fn 1719, then the
// holder's optional string and two strings at +32, +20 and +8. A singleton: GetInst (fn 1279) keeps the object (40 B)
// in a static std::unique_ptr (@1834660) under a static std::mutex (@1834636); the constructor passes 2 to the base's
// and zeroes +12 to +25 (two overlapping 8-byte stores) and the bytes at +28, +32, +36 and +38, which is what three
// std::optional give, over one byte at +24, four bytes at +28 and two at +36, each with its null state and its flag
// zeroed. Their types are chosen from those widths, as comum::md::TCargoID, comum::TCandidatoID and comum::TPartidoID;
// every member name, GetInst's, and this header's path beside cvisualizarcandidatos.cpp are chosen.
class CVisualizarCandidatos final : public comum::CAppState {
public:
    virtual ~CVisualizarCandidatos() override;

    static CVisualizarCandidatos& GetInst();

    virtual void StartState() override;

    // Fn 5951: the byte at +24 when +25 is set, else 0, so m_cargo's value or 0. Out of line, in this class's .cpp:
    // vota::CMenuFiltrarCandidatosPorNumero's two slots (fns 11891 and 11892, another file) call it on GetInst()'s
    // result. No record names it; the name is chosen from what it returns.
    comum::md::TCargoID GetCargo() const;

    // Clears the three filters: vota::CMenuVisualizarCandidatos::StartState (fn 11881) resets the optionals' flags at
    // +25, +38 and +32, in that order, on GetInst()'s result (each `if (flag == 1) flag = 0`, std::optional::reset).
    // Out of line in cvisualizarcandidatos.cpp, so binaryen inlines it into its one caller, as the target's last test
    // (an `if` where an inline member gives a `br_if`) shows: measured in src/units/104-uenux2-app-vota-estados.mk. The
    // name, its being one member and its line in the .cpp (after GetCargo, in the blank run there) are chosen.
    void LimpaFiltros();

    // The posts of the candidatures the filters let through, each once, ordered by CCargo's operator<=> (fn 5655):
    // vota::CMenuFiltrarCandidatosPorCargo::StartState (fn 11888) holds it behind a second stack-pointer prologue (a
    // 16-byte frame, which holds the pair the set's insert returns: our object keeps std::set's
    // __emplace_unique_key_args out of line and binaryen inlines it, which gives that frame, a reading of the
    // target's), so it is out of line here and binaryen inlines it into its one caller. Evidence, the body:
    // CarregaCandidaturas (fn 5953), comum::CConfiguracaoEleicao::GetInst() (fn 187) before the set, then for each
    // candidature the three filters in StartState's order (candidate +28, post +24, party +36, each only when set and
    // not 0) and CConfiguracaoEleicao::GetCargo (fn 861) of its post inserted; the post is read once, after the
    // candidate's filter, for its filter and for GetCargo, which a local declared there gives
    // (src/units/104-uenux2-app-vota-estados.mk has the forms measured). The name, its being a member and public, and
    // the local are chosen; the set is returned by value into 11888's frame.
    std::set<comum::md::CCargo> GetCargos();

    // 11888's CONFIRMA case stores the chosen post and its engaged flag at +24 in one 16-bit store, after std::any_cast
    // and CVisualizarCandidatos::GetInst(): std::optional's assignment. The name and its being an inline member are
    // chosen.
    void SetCargo(comum::md::TCargoID cargo) { m_cargo = cargo; }

    // The parties of the candidatures the filters let through, each once, in order:
    // vota::CMenuFiltrarCandidatosPorPartido::StartState (fn 11884) holds it with no prologue of its own (it has no
    // frame) and stores the set through a local that holds its address, at +0 and +4 from it, where code clang inlines
    // addresses the caller's frame directly (docs/reference/facts/reading.md R10, the frame-address sign), so it is out
    // of line here and binaryen inlines it into its one caller. Evidence, the body: CarregaCandidaturas (fn 5953), then
    // for each candidature the candidate's and the post's filters (+28, +24, each only when set and not 0), the party
    // (+2) read once, before its filter (+36), which a local declared there gives
    // (src/units/104-uenux2-app-vota-estados.mk has the forms measured), and its insertion into a std::set of 16-bit
    // values (std::set<unsigned short>'s tree destroy, fn 2872, frees it in 11884). The name, its being a member and
    // public, and the local's name are chosen; the set is returned by value into 11884's frame.
    std::set<comum::TPartidoID> GetPartidos();

    // 11884's CONFIRMA case stores the chosen party's engaged flag (+38) and its value (+36), after std::any_cast and
    // CVisualizarCandidatos::GetInst(): std::optional's assignment. The name and its being an inline member are chosen.
    void SetPartido(comum::TPartidoID partido) { m_partido = partido; }

    // 11891's CONFIRMA case stores the candidate's engaged flag (+32) and its number (+28), after
    // CVisualizarCandidatos::GetInst(), when comum::CCandidaturas::Busca finds the number: std::optional's assignment.
    // The name and its being an inline member are chosen.
    void SetCandidato(comum::TCandidatoID candidato) { m_candidato = candidato; }

private:
    // Fn 5953: when m_candidaturas is empty, the posts comum::CCargos::GetMapaCargos (fn 2834) gives and, over
    // comum::CCandidaturas' map, a push_back of each candidature whose post is there with a candidate's detail (CCargo
    // +84): its copy is std::construct_at (fn 5952, called twice, both paths) and its reallocation
    // std::__uninitialized_allocator_relocate (fn 5950), both instances this class's object emits first. Its two target
    // callers are 11884 and 11888 (through GetPartidos and GetCargos, which they hold inlined); band 2 runs 5953, 5952,
    // 5951 (GetCargo), 5950 in reverse link order, so it is defined above GetCargo in the .cpp. The name and its being
    // a private member are chosen.
    void CarregaCandidaturas();

    CVisualizarCandidatos();

    static std::mutex s_mutex;
    static std::unique_ptr<CVisualizarCandidatos> s_inst;

    std::vector<comum::md::CCandidatura> m_candidaturas;
    std::optional<comum::md::TCargoID> m_cargo;
    std::optional<comum::TCandidatoID> m_candidato;
    std::optional<comum::TPartidoID> m_partido;
};

} // namespace vota
