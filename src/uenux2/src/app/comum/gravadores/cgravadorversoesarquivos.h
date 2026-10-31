#pragma once

#include "app/comum/gravadores/igravador.h"
#include "app/comum/gravadores/md/cversoesarquivos.h"

namespace comum {

// RTTI: an si_class of comum::IGravador. vota::CGravaResultado::StartState (fn 12098) builds it as a
// std::shared_ptr<IGravador>(new CGravadorVersoesArquivos), whose control block's __on_zero_shared is the shared call
// through the vtable (fn 172), so the class is not final. Recovered: the layout, 64 bytes (12098 allocates it with
// f137(64)), and the virtual members. The constructor, which 12098 holds inlined, copies a string to +40 and a
// std::map<std::string, std::string> to +52, md::CVersoesArquivos's two members (cversoesarquivos.h); the base-object
// destructor (fn 11581, slot 0) destroys the map's tree (fn 720) and the string. That the two are one
// md::CVersoesArquivos is chosen: two members of those types give the same offsets. The destructor is not declared
// (implicit): the deleting one (fn 11580, slot 1) holds the base-object body and frees `this`. GravaResultado (slot 7,
// fn 11582) is out of line, so it is the key function; it is not reconstructed, and no record names this class's file
// (the path follows igravador.h). The constructor is not declared; the member name is chosen.
class CGravadorVersoesArquivos : public IGravador {
public:
    virtual void GravaResultado(api::CFile& arquivo) const override;

private:
    md::CVersoesArquivos m_versoesArquivos;
};

} // namespace comum
