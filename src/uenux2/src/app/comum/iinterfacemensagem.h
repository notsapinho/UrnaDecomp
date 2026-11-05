#pragma once

#include <string>

// comum::IInterfaceMensagem and comum::CInterfaceMensagemVazia: the object comum::CPacoteArquivos::Validar (its record
// spells the parameter IInterfaceMensagem &) tells of each validation it makes. The target holds them as RTTI only
// (typeinfos N5comum18IInterfaceMensagemE and N5comum23CInterfaceMensagemVaziaE, the second a __si_class_type_info over
// the first) and CInterfaceMensagemVazia's vtable @1532496, [174, 144, 425, 1528]: a destructor that returns this, a
// deleting destructor that frees it, and two empty members. Fn 4625 builds one on its stack (vptr store 1532504), and
// Validar calls slot 2 with the package before it validates the whole package and slot 3 with the package and the file
// before it validates each file. No key function: the vtable and both typeinfos are a copy in 4625's object, so every
// member is inline. The slots' names and parameter types (references to the package and the file Validar passes), that
// IInterfaceMensagem's are pure, the inline defaulted destructor and the header's path (both classes in it, beside
// cpacotearquivos.h) are chosen; no record, string or slot names them.
namespace comum {

class CPacoteArquivos;

class IInterfaceMensagem {
public:
    virtual ~IInterfaceMensagem() = default;

    virtual void ValidandoPacote(const CPacoteArquivos& pacote) = 0;
    virtual void ValidandoArquivo(const CPacoteArquivos& pacote, const std::string& arquivo) = 0;
};

class CInterfaceMensagemVazia : public IInterfaceMensagem {
public:
    void ValidandoPacote(const CPacoteArquivos&) override {}
    void ValidandoArquivo(const CPacoteArquivos&, const std::string&) override {}
};

} // namespace comum
