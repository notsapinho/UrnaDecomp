#pragma once

#include <cstddef>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "app/vota/eleitor/cestadocomdesligamentoautomatico.h"

namespace api {
class IScreen;
class IInputKbd;
template <typename MEDIA, typename INPUT>
class CInteractiveForm;
} // namespace api

namespace vota {

// Recovered: the class name and its vtable (RTTI N4vota11IQRCodeBUDSE: no base, slots 0 and 1 the destructors, fns
// 12050 and 12049), the constructor's signature (record cmostraqrcodebu.cpp:38) and the 20-byte object GetQRDSInst
// (fn 1956, which inlines the constructor) builds: the vptr, the vector of strings the constructor moves its argument
// into (+4), and the index at +16 it sets to 0, which CMostraQRCodeBU::ProcessInput (fn 12051) steps within the
// vector's size and fn 12053 reads the vector at. The member names are not in the target. The destructor is defined here, in the class: the
// target's D0 (12049) holds the D2's body, which clang gives only for an inline destructor (an out-of-line one is
// called through the D1 alias). It stores the vptr, so the class is not final. This header's path is chosen: the
// class's only record is in cmostraqrcodebu.cpp, which defines its members, and no record names a header.
class IQRCodeBUDS {
public:
    IQRCodeBUDS(std::vector<std::string> partes);
    virtual ~IQRCodeBUDS() = default;

private:
    std::vector<std::string> m_partes;
    std::size_t m_atual = 0;
};

// vota::CMostraQRCodeBU (RTTI: si_class of vota::CEstadoComDesligamentoAutomatico; vtable @1542116 [785, 1560, 12055,
// 7480, 1661, 218, 425, 12051, 12061, 425]): it overrides StartState (slot 2, fn 12055, record line 70) and
// ProcessInput (slot 7, fn 12051, record line 85), both pending in 37-uenux2-iqrcodebuds-pending.cpp. The destructors
// are vota::testeteclado::CErroTesteTecladoFim's bodies: the D2 (fn 785) stores no vptr before it releases +32, so the
// class is final, and the D0 (fn 1560) calls the D2 and frees `this`, so the destructor is out of line
// (docs/reference/facts/reading.md R4, R5). A singleton: GetInst (fn 2888) keeps the object in a static std::unique_ptr
// (@1833848, destroyed at exit by fn 12057) under a static std::mutex (@1833824, by fn 12056), and builds it as the
// base's constructor with 2 and a null +28. +28 is the form ProcessInput reads (fn 12051 reads the input fields at +72
// and the focus at +84 of it, CInteractiveForm's layout, and gets CPolySingleton<IInputKbd>'s instance, fn 455);
// ProcessInput passes it to AjustaTela (fn 5982), whose record (line 195) takes a CFormInterativoTelaVota &, so that is
// its type, spelled out here, where app/vota/eleitor/cvotacaostateaudio.h, which defines that alias, is not included.
// Chosen: the member's name, the names GetInst, s_inst and s_mutex (the ones the
// project's singletons use), the destructor declared first, and the definitions' lines.
class CMostraQRCodeBU final : public CEstadoComDesligamentoAutomatico {
public:
    virtual ~CMostraQRCodeBU() override;

    static CMostraQRCodeBU& GetInst();

    virtual void StartState() override;

    virtual void ProcessInput() override;

private:
    CMostraQRCodeBU();

    static std::mutex s_mutex;
    static std::unique_ptr<CMostraQRCodeBU> s_inst;

    std::shared_ptr<api::CInteractiveForm<api::IScreen, api::IInputKbd>> m_form;
};

} // namespace vota
