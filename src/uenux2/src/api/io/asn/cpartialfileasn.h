// Reconstructed. The target's records name this file and put api::CFileSeeder's throws on lines 52, 75, 88, 94 and 106,
// all at column 19 (the error's name after `throw` at 12 spaces). Every other line of this file is a choice, and the
// class api::CPartialFileASN of the records at lines 182, 277 and 285 is not reconstructed.
#pragma once

#include <cstddef>
#include <cstdio>
#include <format>
#include <string>

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

    // (original lines 40-48: content not recovered)
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

} // namespace api
