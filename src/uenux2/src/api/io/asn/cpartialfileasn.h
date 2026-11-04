// Reconstructed. The target's records name this file and put api::CFileSeeder's throws on lines 52, 75, 88, 94 and 106,
// and api::CPartialFileASN's on 182, 277 and 285, all at column 19 (the error's name after `throw` at 12 spaces). Every
// other line of this file is a choice.
#pragma once

#include <cstddef>
#include <cstdio>
#include <format>
#include <sstream>
#include <string>

#include "api/io/cfile.h"
#include "api/io/eueioerror.h"
#include "asn1/asn1.h"
#include "ecourna/api/io/cfile.hpp"

namespace api {

// Recovered: the vtable @1564400, an si_class of ASN1::ISeeder (ledger/classes.json), a file at +4 and a size at +8.
// Not final: decodeByte and skip call eof and seek through the vtable, which `final` devirtualizes. No key function:
// the vtable, the typeinfos and the members' records lie among the data of the TU that uses them, after its record of
// line 182 (ledger/vtables.json, ledger/source-locations.tsv), so every member is inline; in the class is a choice the
// column fits. Slots 0 and 1 are the shared empty destructors (174, 144): the destructor is inline, implicit or defined
// in the class (the same bytes, the fragment lists the forms), and implicit is chosen. The constructor has no function
// of its own (11523 and 7787 hold it); it stores -1 at +8, then measures the file. Chosen, no evidence names them: the
// data members and the names of slots 2 and 7 to 10 (asn1.h says which of ISeeder's names are the records').
class CFileSeeder : public ASN1::ISeeder {
public:
    explicit CFileSeeder(const ecourna::api::io::CFile& arquivo) : m_arquivo(arquivo), m_tamanho(static_cast<size_t>(-1))
    {
        const long posicao = m_arquivo.Position();
        m_arquivo.Seek(0, SEEK_END);
        m_tamanho = m_arquivo.Position();
        m_arquivo.Seek(posicao, SEEK_SET);
    }

    virtual bool eof() const override
    {
        return m_arquivo.Eof();
    }

    // (original lines 42-48: content not recovered)
#line 49
    virtual unsigned char decodeByte() override
    {
        if (eof()) {
            throw CUeIoError(EUE_IO_SEEDER_SEM_BYTES, std::format("Não há mais bytes disponíveis em {}", m_arquivo.GetNome()));
        }
        unsigned char byte;
        m_arquivo.RawRead(&byte, 1);
        return byte;
    }

    // (original lines 59-68: content not recovered)
#line 69
    virtual size_t decodeBlock(char* buffer, size_t size) override
    {
        const size_t posicao = m_arquivo.Position();
        const size_t quantidade = (posicao + size > m_tamanho) ? m_tamanho - posicao : size;

        if (m_arquivo.RawRead(buffer, quantidade) != quantidade) {
            throw CUeIoError(EUE_IO_SEEDER_FALHA_LER, std::format("Não foi possível ler {} bytes em {}", quantidade, m_arquivo.GetNome()));
        }
        return quantidade;
    }

    // (original lines 80-84: content not recovered)
#line 85
    virtual void seek(size_t position) override
    {
        if (position > m_tamanho) {
            throw CUeIoError(EUE_IO_SEEDER_POSICAO_INVALIDA, std::format("Não é possível reposicionar para {} em {}", position, m_arquivo.GetNome()));
        }

        // (original lines 91-92: content not recovered)
#line 93
        if (!m_arquivo.Seek(position, SEEK_SET)) {
            throw CUeIoError(EUE_IO_SEEDER_FALHA_REPOSICIONAR, std::format("Não é possível reposicionar para {} em {}", position, m_arquivo.GetNome()));
        }
    }

    // (original lines 98-101: content not recovered)
#line 102
    virtual void skip(size_t size) override
    {
        const size_t destino = m_arquivo.Position() + size;
        if (destino > m_tamanho) {
            throw CUeIoError(EUE_IO_SEEDER_SALTO_INVALIDO, std::format("Não é possível saltar {} bytes em {}", size, m_arquivo.GetNome()));
        }
        seek(destino);
    }

    virtual unsigned size() const override
    {
        return m_tamanho;
    }

    virtual unsigned remaining() const override
    {
        return m_tamanho - m_arquivo.Position();
    }

    virtual unsigned tell() const override
    {
        return m_arquivo.Position();
    }

    virtual void resize(unsigned size) override
    {
        m_tamanho = size;
    }

private:
    const ecourna::api::io::CFile& m_arquivo;
    size_t m_tamanho;
};

// Reads an ASN.1 entity from a file with the partial BER decoder, which hands the nodes the visitors' paths name to
// them as it decodes (records cpartialfileasn.h:182, 277 and 285, which print the two static member templates; target
// fn 11523 holds their instances for ModuloEleitores::EntidadeEleitores, each behind a frame of its own, and fn 7787
// those for ModuloFotosCandidatos::EntidadeFotosCandidatos). Its being a class is the records' (they print `static`);
// `class` over `struct`, the lines of every statement but the throws and the names of the locals are chosen. What the
// bodies hold is the targets': ReadFromFile tests that the file is open, builds the seeder over a new CFileSeeder and
// decodes under the name "ReadFromFile de " + the file's; DecodeObjectFunction sets the coder to the partial BER rule
// (the 2 it stores), assigns it the visitors, decodes, and throws when decoding fails or the entity is not valid or the
// coder's log is not empty, a std::stringstream traced and the log formatted into each message.
class CPartialFileASN {
public:

    // (original lines 148-177: content not recovered)
#line 178
    template <typename T>
    static T ReadFromFile(const CFile& arquivo, const ASN1::TVectorAbstractVisitor& visitantes)
    {
        if (!arquivo.IsOpen()) {
            throw CUeIoError(EUE_IO_ARQUIVO_PARCIAL_NAO_ABERTO, std::format("O arquivo [{}] não estava aberto", arquivo.GetNome()));
        }

        ASN1::TSharedSeeder seeder(new CFileSeeder(arquivo));
        return DecodeObjectFunction<T>(seeder, visitantes, "ReadFromFile de " + arquivo.GetNome());
    }

    // (original lines 189-266: content not recovered)
#line 267
    template <typename T>
    static T DecodeObjectFunction(ASN1::TSharedSeeder& seeder, const ASN1::TVectorAbstractVisitor& visitantes, const std::string& nome)
    {
        ASN1::CoderEnv env;
        env.set_encodingRule(ASN1::CoderEnv::ber_partial);
        env.setVisitors(visitantes);
        T objeto;
        if (!env.decode(seeder, objeto)) {
            std::stringstream erro;
            ASN1::trace_invalid(erro, "", objeto);
            throw CUeIoError(EUE_IO_CONTEUDO_PARCIAL_NAO_DECODIFICADO, std::format("Conteúdo não foi decodificado para {}:{}", nome, env.getLog()));
        }

        // (original lines 280-281: content not recovered)
#line 282
        if (!objeto.isValid() || !objeto.isStrictlyValid() || !env.getLog().empty()) {
            std::stringstream erro;
            ASN1::trace_invalid(erro, "", objeto);
            throw CUeIoError(EUE_IO_CONTEUDO_PARCIAL_INVALIDO, std::format("Conteúdo inválido para {}:{}", nome, env.getLog()));
        }

        return objeto;
    }
};

} // namespace api
