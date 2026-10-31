#pragma once

// vota::CControladorRegistraMesariosVota: the vota application's comum::IControladorRegistraMesarios. RTTI gives the class,
// a si_class over the interface, and its vtable (@1586600) its 37 slots. Fn 7160 allocates 4 bytes for it and stores only
// the vptr, so it has no data member. Slots 0 and 1 are the shared bodies 174 and 144, an empty D2 and a D0 that frees, so
// the class declares no destructor: its implicit ones merge into those bodies in our link (build/out/wasm-map/vota_web/
// names.tsv has no D0 or D2 of the class). The vtable lies in this class's own run of the data, away from fn 7160's records, so a virtual member is
// out of line in this class's .cpp; which one is first is chosen (AddTick, slot 2). No member has a record, and the class
// is declared here and nowhere else; the path is chosen (unit 119's fragment says from what). The slots are const but
// SetTituloMesario, as the interface's are (its header says why).

#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"

namespace vota {

class CControladorRegistraMesariosVota : public comum::IControladorRegistraMesarios {
public:
    uebyte AddTick(size_t milissegundos) const override;
    void StopTick(uebyte id) const override;
    void StartTick(uebyte id) const override;
    void Slot5() const override;
    int Slot6() const override;
    bool Slot7() const override;
    bool Slot8() const override;
    comum::CAppState& Slot9() const override;
    void Slot10() const override;
    comum::CAppState& Slot11() const override;
    comum::CAppState& Slot12() const override;
    bool Slot13() const override;
    comum::md::CComparecimentoMesario* Slot14() const override;
    void Slot15() const override;
    void Slot16() const override;
    const std::string& GetTituloMesario() const override;
    void SetTituloMesario(const std::string& titulo) override;
    void LogaMesarioRegistrado(const std::string& titulo) const override;
    void LogaRegistrandoMesariosAntesVotacao() const override;
    void LogaRegistrandoMesariosDuranteVotacao() const override;
    void LogaRegistrandoMesariosAposVotacao() const override;
    void LogaIndagaRegistroMesarios() const override;
    void LogaConfirmouRegistroMesarios() const override;
    void LogaCancelouRegistroMesarios() const override;
    void LogaTituloInvalidoRegistroMesario() const override;
    void LogaMesarioJaRegistrado(const std::string& titulo) const override;
    void LogaLimiteMesariosAtingido() const override;
    void LogaEncerrouCicloRegistro() const override;
    void LogaDigitalNaoCorresponde(const std::vector<int>& scores) const override;
    void LogaPedidoBiometriaMesario() const override;
    void LogaMesarioEleitorDaSecao() const override;
    void LogaMesarioNaoEleitorDaSecao() const override;
    void LogaConferenciaBiometriaMesario() const override;
    void LogaIndagaContinuaRegistro() const override;
    void LogaIndagaFinalizaRegistro() const override;
};

} // namespace vota
