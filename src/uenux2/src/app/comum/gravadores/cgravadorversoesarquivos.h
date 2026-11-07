#pragma once

#include "app/comum/gravadores/igravador.h"
#include "app/comum/gravadores/md/cversoesarquivos.h"

namespace comum {

// RTTI: an si_class of comum::IGravador. vota::CGravaResultado::StartState (fn 12098) builds it as a
// std::shared_ptr<IGravador>(new CGravadorVersoesArquivos), whose control block's __on_zero_shared is the shared call
// through the vtable (fn 172), so the class is not final. Recovered: the layout, 64 bytes (12098 allocates it with
// f137(64)), and the virtual members. The constructor, which 12098 holds inlined behind a 16-byte frame of its own (the
// map copy's hinted inserts, fn 1221, return their pair there; no target index: written in
// cgravadorversoesarquivos.cpp, unrooted), calls IGravador's constructor (fn 1396) with the extension 19 and the SAVD
// file 70, then copies a string to +40 and a std::map<std::string, std::string> to +52, md::CVersoesArquivos's two
// members (cversoesarquivos.h), from the md::CVersoesArquivos 12098 builds (fn 5867); the base-object
// destructor (fn 11581, slot 0) destroys the map's tree (fn 720) and the string. That the two are one
// md::CVersoesArquivos is chosen: two members of those types give the same offsets. The destructor is not declared
// (implicit): the deleting one (fn 11580, slot 1) holds the base-object body and frees `this`. GravaResultado (slot 7,
// fn 11582) is out of line, so it is the key function: cgravadorversoesarquivos.cpp writes it, with
// comum::asn::GravaArquivo, and no record names this class's file (the path follows igravador.h). The member name is
// chosen, and so are the constructor's parameters (their order and form, and the extension and the SAVD file as its own
// constants rather than 12098's arguments: one call cannot tell them apart).
class CGravadorVersoesArquivos : public IGravador {
public:
    CGravadorVersoesArquivos(TMunicipioID municipio, TZonaID zona, TLocalID local, TSecaoID secao, char fase,
        const md::CVersoesArquivos& versoesArquivos);

    virtual void GravaResultado(api::CFile& arquivo) const override;

private:
    md::CVersoesArquivos m_versoesArquivos;
};

} // namespace comum
