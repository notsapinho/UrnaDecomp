#pragma once

// comum::CMenuBase: the base of a menu of options built into a form. Its RTTI names no base;
// vota::CMenuMaisInformacoesVota is the one class derived from it and overrides nothing (its vtable, @1539812, holds
// the same three functions). This class's vtable (@1550924, ledger/vtables.json) holds the destructor (slot 0, fn
// 12235; slot 1, the deleting destructor, fn 6188) and MontaMenu (slot 2, fn 5913).
// Recovered: the layout (32 bytes) and the virtual members.
// - The destructor is virtual and, the class having no base, declared. It is defined inline in this header: the
//   deleting destructor holds the base-object destructor's body inlined, which a destructor defined out of line does
//   not give (docs/reference/facts/reading.md R5), nor one defined in the class without `inline`: clang gives that one
//   no inline hint and its deleting destructor calls it (measured). `inline virtual ~CMenuBase() = default;` in the
//   class gives the same bytes. So the class's key function is MontaMenu, and the TU that defines it emits the vtable
//   and both destructors. The destructor stores the vptr, so the class is not final (R4).
// - The members, from the bodies that build and read them (their names are not in the target):
//   +4  the items, a std::vector<std::shared_ptr<CItemMenu>>: the destructor releases its 8-byte elements from the
//       back, and the builder of the "Mais informa\xE7\xF5es" menu (fn 6599) adds five items through fn 2285, each a
//       std::shared_ptr<comum::CItemMenu> (the RTTI names of the control blocks it makes);
//   +16 the std::string that MontaMenu copies into the api::COptionValidation of the menu's input field: the keys of
//       the options;
//   +28 the api::CFormBuilder the menu is built into: fn 6599 stores there the address of the builder it calls
//       AddStatusHeader (fn 502) on, and MontaMenu passes it to fn 202 for each line it adds, as fn 6599 does. A
//       pointer would give the same bytes.
// - MontaMenu: no record, symbol or caller names slot 2, so the name is chosen from the body, which writes a line
//   "[{}] - {}" for each item and the prompt "Escolha a sua op\xE7\xE3o:" into the form builder, then the input field.
// - The constructor is declared only: binaryen inlined it into fn 6599, so the target has no function of it.
// - The header's path is chosen: no record names a file of the class, and the stub comments' app/comum/dados/ is the
//   tool's class convention. MontaMenu, the key function (ledger/tu-clusters.tsv stretch 853), is linked right after
//   the functions of app/comum/informacao/cinformacaoeleicao.cpp (stretch 854) and before those of
//   app/comum/cinfomtlcd.cpp (851). app/comum/ links its own files in name order (cinfomtlcd.cpp, cpacotearquivos.cpp,
//   iinterfaceinit.cpp, iinterfacesavd.cpp: stretches 851, 850, 849, 847), where a cmenubase.cpp would come after
//   cinfomtlcd.cpp; after cinformacaoeleicao.cpp in informacao/ it is in name order. The file name is the class's in
//   lower case.
// - CItemMenu is only declared here: the destructor needs no more of it.

#include <memory>
#include <string>
#include <vector>

namespace api {
class CFormBuilder;
} // namespace api

namespace comum {

class CItemMenu;

class CMenuBase {
public:
    explicit CMenuBase(api::CFormBuilder& form);
    virtual ~CMenuBase();

    virtual void MontaMenu();

protected:
    std::vector<std::shared_ptr<CItemMenu>> m_itens;
    std::string m_opcoes;
    api::CFormBuilder& m_form;
};

inline CMenuBase::~CMenuBase() = default;

} // namespace comum
