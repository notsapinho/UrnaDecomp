#pragma once

// api::CImageFieldUpdate (/home/rubio/tse/uenux2/src/api/gui/cimagefieldupdate.cpp names its file: the constructor's
// throw is the record at line 32, column 15, and Rect's at line 80, column 12; the header beside it is chosen).
//
// RTTI makes it an si_class of api::IFormField<api::IScreen> (typeinfo 1579060), not of api::CImageField: its
// destructor (target fn 5531) stores no CImageField vptr between its own members and the IFormFieldBase part. Its
// layout (52 B) is read from that destructor and from the constructor, which binaryen inlined into fn 3059 after
// std::make_shared's control block (a 64-byte allocation, the object at +12):
//   +24 SPoint, +28/+32 SharedIImage (the constructor throws when it is null), +36 an owning pointer the constructor
//   nulls and the destructor frees with plain operator delete, which Draw (fn 11090) passes to IScreen's slot 24 as
//   CImageField::Draw passes its std::unique_ptr<SPoint>, +40 the anchor, +44/+48 the std::shared_ptr that slot 0 of
//   ITimerScheduler::GetInst() (fn 1259, record itimerscheduler.cpp:23) returns for the interval and a lambda of the
//   constructor (the std::function<void()> __func of typeinfo 1579116). Show (fn 11089) and Hide (fn 11088) call that
//   object's slots 2 and 3. RTTI names api::ITimer, whose header is not ours yet, so it is only declared here.
// The member names are chosen, as in cimagefield.h; no evidence gives them.
//
// The destructor is defined in the class: the deleting destructor (fn 11086) is free(D2(this)), a direct call to a D2
// that was not inlined into it. An out-of-line destructor is called through the D1 alias, whose result clang does not
// reuse (D2(this); free(this), as fns 10238 and 4694 read), and an implicit one is inline-specified, which raises the
// inlining threshold enough that the D2 is inlined into the D0 (as CImageField's fn 11098 holds its D2). GetTypeName is
// inline too: in the target's function order it follows the deleting destructor, among the members the vtable
// creates, after Draw, Show, Hide and Rect, which the file defines.

#include <chrono>
#include <memory>
#include <string>

#include "api/gui/iformfield.h"
#include "api/gui/iimage.h"
#include "api/gui/primitives.h"

namespace api {

class IScreen;
class ITimer;

/**
 * Campo que desenha uma imagem numa posição da tela e a atualiza a cada intervalo, enquanto está visível.
 */
class CImageFieldUpdate : public IFormField<IScreen> {
public:
    CImageFieldUpdate(const SPoint& posicao, const SharedIImage& imagem, const std::chrono::milliseconds& intervalo,
                      EAnchorPoint ancora);

    ~CImageFieldUpdate() override = default;

    void Draw(IScreen& screen) const override;

    void Show() override;

    void Hide() override;

    std::string GetTypeName() const override { return "CImageFieldUpdate"; }

    SRect Rect() const override;

    void Move(const SPoint& posicao) override;

private:
    SPoint m_posicao;
    SharedIImage m_imagem;
    std::unique_ptr<SPoint> m_tamanho;
    EAnchorPoint m_ancora;
    std::shared_ptr<ITimer> m_timer;
};

} // namespace api
