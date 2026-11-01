#pragma once

// comum::CInfoMTLCD: what the urna shows on the LCD of its terminal (api::IScreenMT). RTTI gives an si_class of
// api::IObserver<std::shared_ptr<api::IImage>>; its vtable (@1551820) is [5902, 11654, 11653]: the destructor, the
// deleting destructor and Update (IObserver's slot 2), whose records (cinfomtlcd.cpp:50 and :51) name the class, the
// member and its parameter type. The records of cinfomtlcd.cpp also name CreateInst (:33, static, inlined into fn 7787)
// and MostrarImagemNoLCD (:84, inlined into fns 11653 and 3836).
// Recovered:
// - +4, the battery icon the class observes, an api::BatteryIconDataSource<Vertical> held by value: the constructor (fn
//   5904, which fn 2284 calls on a new 64-byte object) stores this class's vptr and then builds that template's
//   instance in place at +4 (its record, cpowerinformation.cpp:119, names the Vertical instance), and the destructor
//   (fn 5902) detaches `this` from it (the search of its observers' vector at +16 for `this`, under its mutex at +28,
//   IObservable::Detach inlined) and then calls that instance's destructor on +4 (fn 3837).
// - The destructor is defined out of line: the deleting destructor (fn 11654, 13 B) calls fn 5902 and frees `this`
//   (docs/reference/facts/reading.md R5). Declaring it first is a choice: Update is out of line in the same .cpp, so
//   either order emits the vtable there.
// - Update (fn 11653): with a non-null image it centres it on the LCD, from IScreen's image surface ops (slot 34, then
//   their slot 13, ImageSize) and IScreenMT's GetWidth and GetHeight (slots 17 and 18), and shows it there with
//   MostrarImagemNoLCD and `false`.
// - MostrarImagemNoLCD: one call of IScreenMT's slot 4, ShowImage(position, image, flag), its record at line 84.
// - MostraImagem (fn 3836): no record names it. Its callers (fns 3616 and 3617) call it on fn 2284's result, the
//   instance, with an image and a position; it detaches the instance from the battery icon, as the destructor does,
//   and shows the image with `true` when the image's GetData() (IImage's slot 2) is not empty. Its name is chosen from
//   that, and so is the name of MostrarImagemNoLCD's bool.
// - The constructor (fn 5904): after the vptr store and the member's constructor (BatteryIconDataSource's, from
//   cpowerinformation.cpp, which binaryen inlined: its own frame inside 5904's) it attaches `this` to the member,
//   IObservable::Attach, in 5904's own frame, so clang inlined it in this file. The constructor calls MostraIconeBateria,
//   which clang inlines; a constructor that calls Attach itself compiles to the same function (object compare, masked),
//   so which of the two is written is a choice.
// - MostraIconeBateria (fn 5903): Attach on the member with `this`, the counterpart of MostraImagem's detach. Its callers
//   (fns 10427 and 10680, two vota states) call it on fn 2284's result. Its name is chosen from that role.
// Not recovered: GetInst (fn 2284) and CreateInst. The member's name and this header's path, beside cinfomtlcd.cpp, are
// chosen.

#include <memory>

#include "api/gui/cpowerinformation.h"
#include "api/gui/iimage.h"
#include "api/gui/primitives.h"
#include "api/pattern/iobserver.h"

namespace comum {

class CInfoMTLCD : public api::IObserver<api::SharedIImage> {
public:
    CInfoMTLCD();
    ~CInfoMTLCD() override;

    static void CreateInst();

    void Update(const api::SharedIImage& imagem) override;
    void MostraIconeBateria();
    void MostraImagem(const api::IImage& imagem, const api::SPoint& posicao);

private:
    void MostrarImagemNoLCD(const api::IImage& imagem, const api::SPoint& posicao, bool opcao);

    api::BatteryIconDataSource<api::CPowerInformation::IconOrientation::Vertical> m_bateria;
};

} // namespace comum
