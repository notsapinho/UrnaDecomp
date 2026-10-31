#pragma once

// vota::CControladorRegistraMesariosVota: the vota application's comum::IControladorRegistraMesarios. RTTI gives the class,
// a si_class over the interface, and its vtable (@1586600) its 37 slots. Fn 7160 allocates 4 bytes for it and stores only
// the vptr, so it has no data member. Slots 0 and 1 are the shared bodies 174 and 144, an empty D2 and a D0 that frees, so
// the class declares no destructor: its implicit ones merge into those bodies in our link (build/out/wasm-map/vota_web/
// names.tsv has no D0 or D2 of the class). The vtable lies in this class's own run of the data, away from fn 7160's records, so a virtual member is
// out of line in this class's .cpp; which one is first is chosen (AddTick, slot 2). No member has a record, and the class
// is declared here and nowhere else; the path is chosen (unit 119's fragment says from what).

#include "app/comum/comparecimentomesario/estados/icontroladorregistramesarios.h"

namespace vota {

class CControladorRegistraMesariosVota : public comum::IControladorRegistraMesarios {
public:
    uebyte AddTick(size_t milissegundos) override;
    void StopTick(uebyte id) override;
    void StartTick(uebyte id) override;
    void Slot5() override;
    int Slot6() override;
    bool Slot7() override;
    bool Slot8() override;
    comum::CAppState& Slot9() override;
    void Slot10() override;
    comum::CAppState& Slot11() override;
    comum::CAppState& Slot12() override;
    bool Slot13() override;
    comum::md::CComparecimentoMesario* Slot14() override;
    void Slot15() override;
    void Slot16() override;
    const std::string& GetTituloMesario() override;
    void SetTituloMesario(const std::string& titulo) override;
    void LogaMesarioRegistrado(const std::string& titulo) override;
    void LogaRegistrandoMesariosAntesVotacao() override;
    void LogaRegistrandoMesariosDuranteVotacao() override;
    void LogaRegistrandoMesariosAposVotacao() override;
    void LogaIndagaRegistroMesarios() override;
    void LogaConfirmouRegistroMesarios() override;
    void LogaCancelouRegistroMesarios() override;
    void LogaTituloInvalidoRegistroMesario() override;
    void LogaMesarioJaRegistrado(const std::string& titulo) override;
    void LogaLimiteMesariosAtingido() override;
    void LogaEncerrouCicloRegistro() override;
    void LogaDigitalNaoCorresponde(const std::vector<int>& scores) override;
    void LogaPedidoBiometriaMesario() override;
    void LogaMesarioEleitorDaSecao() override;
    void LogaMesarioNaoEleitorDaSecao() override;
    void LogaConferenciaBiometriaMesario() override;
    void LogaIndagaContinuaRegistro() override;
    void LogaIndagaFinalizaRegistro() override;
};

} // namespace vota
