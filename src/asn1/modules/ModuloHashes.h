#ifndef __MODULOHASHES_H
#define __MODULOHASHES_H

#include "asn1.h"

#include "ModuloTiposEleitorais.h"
#include "ModuloTiposResultadosEcoUrna.h"

namespace ModuloHashes {

//
// ModuloHashes::HashesArquivos   // SYNTHESIZED name (field ['hashesArquivos', 'arquivos'])
//

class HashesArquivos : public ASN1::SEQUENCE_OF<ModuloTiposEleitorais::ArquivoAssinatura>
{
    typedef ASN1::SEQUENCE_OF<ModuloTiposEleitorais::ArquivoAssinatura> Inherited;
protected:
    typedef Inherited::InfoType InfoType;
    HashesArquivos(const void* info) : Inherited(info) {}
public:
    HashesArquivos(size_type n=0) : Inherited(n) {}
    HashesArquivos(size_type n, const ModuloTiposEleitorais::ArquivoAssinatura& val) : Inherited(n, val) {}
    HashesArquivos(const_iterator first, const_iterator last) : Inherited(first, last) {}
    HashesArquivos(const HashesArquivos& that) : Inherited(that) {}
    HashesArquivos * clone() const
    { return static_cast<HashesArquivos*> (Inherited::clone()); }
    static bool equal_type(const ASN1::AbstractData& type)
    { return type.info() == reinterpret_cast<const ASN1::AbstractData::InfoType*>(&theInfo); }
    static const InfoType theInfo;
}; // end class HashesArquivos

//
// ModuloHashes::EntidadeHashes
//

class EntidadeHashes : public ASN1::SEQUENCE
{
    typedef ASN1::SEQUENCE Inherited;
protected:
    typedef Inherited::InfoType InfoType;
    EntidadeHashes(const void* info) : Inherited(info) {}
public:
    EntidadeHashes() : Inherited(&theInfo) {}
    EntidadeHashes(const EntidadeHashes & that) : Inherited(that) {}

    EntidadeHashes& operator=(const EntidadeHashes& that)
    { Inherited::operator=(that); return *this; }

    enum OptionalFields {
      e_identificacaoUrna
    };

    class cabecalho
    {
    public:
        typedef ModuloTiposEleitorais::CabecalhoEntidade value_type;
        typedef value_type&        reference;
        typedef const value_type&  const_reference;
        typedef value_type*        pointer;
        typedef const value_type*  const_pointer;
    }; // end class cabecalho

    cabecalho::const_reference get_cabecalho () const { return *static_cast<cabecalho::const_pointer>(fields[0]); }
    cabecalho::reference ref_cabecalho () { return *static_cast<cabecalho::pointer>(fields[0]); }
    cabecalho::reference set_cabecalho () { return *static_cast<cabecalho::pointer>(fields[0]); }

    class fase
    {
    public:
        typedef ModuloTiposEleitorais::Fase value_type;
        typedef value_type&        reference;
        typedef const value_type&  const_reference;
        typedef value_type*        pointer;
        typedef const value_type*  const_pointer;
    }; // end class fase

    fase::const_reference get_fase () const { return *static_cast<fase::const_pointer>(fields[1]); }
    fase::reference ref_fase () { return *static_cast<fase::pointer>(fields[1]); }
    fase::reference set_fase () { return *static_cast<fase::pointer>(fields[1]); }
    fase::reference set_fase (ModuloTiposEleitorais::Fase::NamedNumber v)
    { return *static_cast<fase::pointer>(fields[1]) = v; }

    class siglaUF
    {
    public:
        typedef ModuloTiposEleitorais::SiglaUF value_type;
        typedef value_type&        reference;
        typedef const value_type&  const_reference;
        typedef value_type*        pointer;
        typedef const value_type*  const_pointer;
    }; // end class siglaUF

    siglaUF::const_reference get_siglaUF () const { return *static_cast<siglaUF::const_pointer>(fields[2]); }
    siglaUF::reference ref_siglaUF () { return *static_cast<siglaUF::pointer>(fields[2]); }
    siglaUF::reference set_siglaUF () { return *static_cast<siglaUF::pointer>(fields[2]); }
    siglaUF::reference set_siglaUF (const ASN1_STD string& v)
    { return *static_cast<siglaUF::pointer>(fields[2]) = v; }

    class identificacaoUrna
    {
    public:
        typedef ModuloTiposResultadosEcoUrna::Identificacao value_type;
        typedef value_type&        reference;
        typedef const value_type&  const_reference;
        typedef value_type*        pointer;
        typedef const value_type*  const_pointer;
    }; // end class identificacaoUrna

    identificacaoUrna::const_reference get_identificacaoUrna () const
    {
      assert(hasOptionalField(e_identificacaoUrna));
      return *static_cast<identificacaoUrna::const_pointer>(fields[3]);
    }
    identificacaoUrna::reference ref_identificacaoUrna ()
    {
      assert(hasOptionalField(e_identificacaoUrna));
      return *static_cast<identificacaoUrna::pointer>(fields[3]);
    }
    identificacaoUrna::reference set_identificacaoUrna ()
    {
      includeOptionalField( e_identificacaoUrna, 3);
      return *static_cast<identificacaoUrna::pointer>(fields[3]);
    }
    void omit_identificacaoUrna () { removeOptionalField( e_identificacaoUrna); }
    bool identificacaoUrna_isPresent () const { return hasOptionalField( e_identificacaoUrna); }

    class versaoUENUX
    {
    public:
        typedef ASN1::GeneralString value_type;
        typedef value_type&        reference;
        typedef const value_type&  const_reference;
        typedef value_type*        pointer;
        typedef const value_type*  const_pointer;
    }; // end class versaoUENUX

    versaoUENUX::const_reference get_versaoUENUX () const { return *static_cast<versaoUENUX::const_pointer>(fields[4]); }
    versaoUENUX::reference ref_versaoUENUX () { return *static_cast<versaoUENUX::pointer>(fields[4]); }
    versaoUENUX::reference set_versaoUENUX () { return *static_cast<versaoUENUX::pointer>(fields[4]); }
    versaoUENUX::reference set_versaoUENUX (const ASN1_STD string& v)
    { return *static_cast<versaoUENUX::pointer>(fields[4]) = v; }

    class hashesArquivos
    {
    public:
        typedef ModuloHashes::HashesArquivos value_type;
        typedef value_type&        reference;
        typedef const value_type&  const_reference;
        typedef value_type*        pointer;
        typedef const value_type*  const_pointer;
    }; // end class hashesArquivos

    hashesArquivos::const_reference get_hashesArquivos () const { return *static_cast<hashesArquivos::const_pointer>(fields[5]); }
    hashesArquivos::reference ref_hashesArquivos () { return *static_cast<hashesArquivos::pointer>(fields[5]); }
    hashesArquivos::reference set_hashesArquivos () { return *static_cast<hashesArquivos::pointer>(fields[5]); }
    void swap(EntidadeHashes& that) { Inherited::swap(that); }
    EntidadeHashes * clone() const
    { return static_cast<EntidadeHashes*> (Inherited::clone()); }
    static const Inherited::InfoType theInfo;

private:
    static const void* fieldInfos[6];
    static int fieldIds[6];
    static const char* fieldNames[6];
}; // end class EntidadeHashes

} // namespace ModuloHashes

#endif // __MODULOHASHES_H
