#pragma once

#include <string>

#include "app/comum/gravadores/igravadorenvelope.h"

namespace comum {

// RTTI: an si_class of comum::IGravadorEnvelope. vota::CGravaResultado::StartState (fn 12098) builds it as a
// std::shared_ptr<IGravador>(new CGravadorEnvelopeArquivo), whose control block's __on_zero_shared is the shared call
// through the vtable (fn 172), so the class is not final. Recovered: the layout, 184 bytes (12098 allocates it with
// f137(184)), and the virtual members. The constructor (fn 5856) builds IGravadorEnvelope's members, stores this vptr
// and copies its last argument, a string, to +172. The destructor is not declared (implicit): the base-object one (fn
// 11622, slot 0) frees that string and holds IGravadorEnvelope's inline, the deleting one (fn 11621, slot 1) the same
// body and the free of `this`. Slot 7 is IGravadorEnvelope's (fn 11626); slot 8, LeConteudo (fn 11623), is out of
// line, so it is the key function, in cgravadorenvelopearquivo.cpp: it reads the whole file the string at +172 names,
// so that string is the envelope's file name. No record names this class's file (the path follows igravador.h). The
// constructor (fn 5856) is in cgravadorenvelopearquivo.cpp. fn 12098, its one caller, copies the string into its own
// frame just before each call, which a by-value parameter or a temporary bound to a const reference both give; the
// constructor copies it to +172 (no move). Its parameters are in the order fn 5856 uses its arguments in. Chosen: the
// const reference, the parameters' types beyond IGravador's constructor's, and the member's name.
class CGravadorEnvelopeArquivo : public IGravadorEnvelope {
public:
    CGravadorEnvelopeArquivo(const api::CDateTime& dataHora, TMunicipioID municipio, TZonaID zona, TLocalID local,
        TSecaoID secao, char fase, EExtensaoArquivoResultado extensao, ESavdArquivoUE arquivoSavd,
        md::CEnvelopeGenerico::Tipo tipoEnvelope, const md::estadoaplicacao::CDadoCorrespondencia& correspondencia,
        const std::string& nomeArquivoEnvelope);

    virtual std::vector<uebyte> LeConteudo() const override;

private:
    std::string m_nomeArquivoEnvelope;
};

} // namespace comum
