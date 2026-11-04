#pragma once

#include <format>
#include <memory>
#include <sstream>
#include <string>
#include <typeinfo>

#include "api/io/asn/cpartialfileasn.h"
#include "api/io/cfile.h"
#include "app/comum/asn/euecomumasnerror.h"
#include "asn1/asn1.h"

namespace comum::asn {

// Converts the part of a generated ASN.1 entity a visitor collects while the partial BER decoder reads it. The record
// iconversorparcialasn.h:52 is the throw of Desconverte(const api::CFile &, const std::shared_ptr<TVisitor> &), which
// target fns 11523 (EntidadeEleitores) and 7787 (EntidadeFotosCandidatos) hold behind a 720-byte frame of their own: an
// out-of-line instance with one caller, which binaryen inlined. The RTTI of comum::asn::CIndexadorFotos and
// CConversorEntidadeEleitores names this base, whose vtable slot 2 (target fns 11441, 11411) takes the entity and the
// visitor; 11523 calls it through the vtable with the visitor shared_ptr's object. What Desconverte does is the
// target's: it lets the visitor class set itself up and name its paths (a store into the visitor and the list of
// pairs, which differ between the two instances: TVisitor::Prepara), reads the entity with
// api::CPartialFileASN::ReadFromFile, throws code 7665 with the entity's trace when it is not valid, the typeid name
// copied into a std::string first, and returns DoDesconverte's result. Chosen: the slot's name, its parameters' form,
// TEntidade's name (after IConversorASN's), Prepara's name and its being TVisitor's static member, the locals' names
// and every line but the throw's.
template <typename ENTIDADE, typename DADO, typename VISITOR>
class IConversorParcialASN {
public:
    typedef ENTIDADE TEntidade;
    typedef DADO TDado;
    typedef VISITOR TVisitor;

    virtual ~IConversorParcialASN() {}

    // (original lines 37-43: content not recovered)
#line 44
    TDado Desconverte(const api::CFile& arquivo, const std::shared_ptr<TVisitor>& visitante) const
    {
        const ASN1::TVectorAbstractVisitor visitantes = TVisitor::Prepara(visitante);
        TEntidade entidade = api::CPartialFileASN::ReadFromFile<TEntidade>(arquivo, visitantes);
        if (!entidade.isValid() || !entidade.isStrictlyValid()) {
            const std::string tipo = typeid(TEntidade).name();
            std::ostringstream erro;
            ASN1::trace_invalid(erro, tipo.c_str(), entidade);
            throw CUeComumAsnError(EUE_COMUM_ASN_ENTIDADE_PARCIAL_ESTADO_INVALIDO, std::format("Entidade deixada em estado inválido: {}", erro.str()));
        }
        return DoDesconverte(entidade, *visitante);
    }

protected:
    virtual TDado DoDesconverte(const TEntidade& entidade, const TVisitor& visitante) const = 0;
};

} // namespace comum::asn
