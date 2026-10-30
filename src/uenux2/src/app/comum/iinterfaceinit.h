#pragma once

// comum::IInterfaceInit: what the application asks of the platform it starts on; simulador::CWasmInit implements it
// (its RTTI names this class as its only base). The vtable (@1552152, 8 slots, ledger/vtables.json) holds the
// destructor (slot 0, fn 5898; slot 1 is fn 325, the trap an abstract class's deleting destructor gets),
// CurrentBootDevice (slot 2, fn 11646, record iinterfaceinit.cpp:47) and five pure virtual members (slots 3-7).
// - The destructor and the constructor are defined in iinterfaceinit.cpp. The target functions 5898 to 5894 are
//   consecutive in one use-count band (two uses each), which lists functions in reverse link order
//   (docs/reference/link-order.md section 1), and 5897, 5896 and 5894 are IsMRMontadoSemHabilitar (line 148),
//   MontarMRSemHabilitar (159) and DesligarUrna (522): the destructor comes before line 148, which a destructor
//   defined inline, emitted after the file's other functions, could not. simulador's setup (fn 8302), into which
//   binaryen inlined the constructor, keeps this class's vptr store under CWasmInit's: with an inline base constructor
//   clang drops that store from the derived constructor, and no other base's survives among the objects 8302 builds.
//   The destructor stores the vptr, so the class is not final.
// - The members: +4 the std::shared_ptr<bool> that GetDemoMode (fn 729) fills once with a new bool and reads after,
//   +12 the std::string that MontarMRSemHabilitar (fn 5896) compares with the serial number GetSerialNumberMR reads
//   and assigns when they differ. Their names are chosen from those uses: no evidence names them.
// - The pure members: no record, symbol or caller names them. Slot 5 is the one the members call:
//   EnviarMensagemThrowVoid (fn 3833) passes its message to it, and fns 729 and 11646 read the std::vector<int> it
//   returns, so its name and types are chosen from those uses. Slots 3, 4, 6 and 7 are named after their slot, with
//   the wasm types of CWasmInit's overriders (fns 434, 9418, 340, 425).
// - EBootDeviceId: CurrentBootDevice's record spells it unqualified; its enumerators (fn 11646 returns 0, 1 or 2) and
//   its underlying type are not recovered.
// - The other members are declared from their records in iinterfaceinit.cpp; none of them is reconstructed yet. The
//   header's path, the access of each member and the parameter names are not in the target.

#include <memory>
#include <string>
#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace comum {

enum EBootDeviceId : int;

/**
 * Interface de inicialização da plataforma: dispositivo de boot, mídia de resultado (MR), modo de demonstração e
 * desligamento da urna.
 */
class IInterfaceInit {
public:
    IInterfaceInit();
    virtual ~IInterfaceInit();

    virtual EBootDeviceId CurrentBootDevice();

    virtual bool Slot3() = 0;
    virtual int Slot4() = 0;
    virtual std::vector<int> EnviarMensagem(ueint32 mensagem) = 0;
    virtual bool Slot6() = 0;
    virtual void Slot7(int) = 0;

    bool IsMRPresenteSemHabilitar();
    bool IsMRMontadoSemHabilitar();
    void MontarMRSemHabilitar();
    void DesmontarMRSemDesabilitar();
    void LogDiskInfo();
    void DesligarUrna();
    int DispositivoMR();
    void EnviarMensagemThrowVoid(ueint32 mensagem, const std::string& descricao);
    bool GetDemoMode();
    std::string GetSerialNumberMR(int dispositivo);

private:
    std::shared_ptr<bool> m_demoMode;
    std::string m_serialMR;
};

} // namespace comum
