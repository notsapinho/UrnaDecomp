// The reconstruction's notes. The records name four static members of api::CFileASN, each a member template over
// the ASN.1 entity it reads or writes (they print "[T = ...]"): ReadFromFile(const CFile &) at lines 48 and 60,
// ReadFromFile(const std::string &) at 78, DecodeObjectFunction(const std::vector<char> &, const std::string &) at
// 135 and 143, and CodeObjectFunction(std::vector<char> &, const T &, const std::string &) at 161 and 171.
// CodeObjectFunction is written from target fn 2927, binaryen's merge of its instances for the four ESTADO GERAL
// entities, whose thunks 9801, 9702, 9695 and 9673 pass each instance's two records (src/units/229-asn1-coderenv.mk
// has the evidence); the three readers from target fn 3791, which holds their instances for
// ModuloEstadoGeralUrna::EstadoGeralUrna, each behind a prologue of its own; and two writers no record names, from
// fns 2892 and 2891, binaryen's merges of their instances for the four entities: WriteToFile(const std::string &,
// const T &), which opens the file "wb" and calls the other, and WriteToFile(const CFile &, const T &), which codes
// the entity with CodeObjectFunction under the name "WriteToFile de " + the file's name and writes the buffer. Their
// name is read from that literal, as ReadFromFile's "ReadFromFile de " is its record's; their lines, between the
// readers and DecodeObjectFunction, are chosen (src/units/206-uenux2-app-comum-appinfo-servicos.mk has the evidence).
// Chosen: that CFileASN is a class, the lines of every statement but the throws, and the names of the locals.
#pragma once

#include <format>
#include <sstream>
#include <string>
#include <vector>

#include "api/io/cfile.h"
#include "api/io/eueioerror.h"
#include "api/util/csystem.h"
#include "asn1/asn1.h"

namespace api {

class CFileASN {
public:

    // (original lines 32-43: content not recovered)
#line 44
    template <typename T>
    static T ReadFromFile(const CFile& arquivo)
    {
        if (!arquivo.IsOpen()) {
            throw CUeIoError(EUE_IO_ARQUIVO_NAO_ABERTO, std::format("O arquivo [{}] não estava aberto", arquivo.GetNome()));
        }

        const long posicao = arquivo.Position();
        arquivo.Seek(0, SEEK_END);
        const uedword tamanho = arquivo.Position() - posicao;
        arquivo.Seek(posicao, SEEK_SET);

        // (original lines 56-58: content not recovered)
#line 59
        if (tamanho > 5 * 1024 * 1024) {
            throw CUeIoError(EUE_IO_ARQUIVO_MUITO_GRANDE, std::format("O arquivo [{}] é muito grande para ser lido", arquivo.GetNome()));
        }

        std::vector<char> buffer(tamanho);
        arquivo.RawRead(buffer.data(), buffer.size());

        return DecodeObjectFunction<T>(buffer, "ReadFromFile de " + arquivo.GetNome());
    }

    // (original lines 69-73: content not recovered)
#line 74
    template <typename T>
    static T ReadFromFile(const std::string& nome)
    {
        if (!CSystem::ExistFile(nome)) {
            throw CUeIoError(EUE_IO_ARQUIVO_NAO_EXISTE, std::format("O arquivo [{}] não existe", nome));
        }

        CFile arquivo(nome, "rb");
        T objeto = ReadFromFile<T>(arquivo);
        arquivo.Close();

        return objeto;
    }

    // (original lines 88-94: content not recovered)
#line 95
    template <typename T>
    static void WriteToFile(const CFile& arquivo, const T& objeto)
    {
        std::vector<char> buffer;
        CodeObjectFunction(buffer, objeto, "WriteToFile de " + arquivo.GetNome());
        arquivo.RawWrite(buffer.data(), buffer.size());
    }

    template <typename T>
    static void WriteToFile(const std::string& nome, const T& objeto)
    {
        CFile arquivo(nome, "wb");
        WriteToFile(arquivo, objeto);
    }

    // (original lines 110-125: content not recovered)
#line 126
    template <typename T>
    static T DecodeObjectFunction(const std::vector<char>& buffer, const std::string& nome)
    {
        ASN1::CoderEnv env;
        env.set_ber();
        T objeto;
        if (!env.decode(buffer.begin(), buffer.end(), objeto, false)) {
            std::ostringstream erro;
            ASN1::trace_invalid(erro, "", objeto);
            throw CUeIoError(EUE_IO_CONTEUDO_NAO_DECODIFICADO, std::format("Conteúdo não foi decodificado para {}: {}", nome, erro.str()));
        }

        // (original lines 138-139: content not recovered)
#line 140
        if (!objeto.isValid() || !objeto.isStrictlyValid()) {
            std::ostringstream erro;
            ASN1::trace_invalid(erro, "", objeto);
            throw CUeIoError(EUE_IO_CONTEUDO_INVALIDO, std::format("Conteúdo inválido para {}: {}", nome, erro.str()));
        }

        return objeto;
    }

    // (original lines 149-154: content not recovered)
#line 155
    template <typename T>
    static void CodeObjectFunction(std::vector<char>& buffer, const T& objeto, const std::string& nome)
    {
        if (!objeto.isValid()) {
            std::ostringstream erro;
            ASN1::trace_invalid(erro, "", objeto);
            throw CUeIoError(EUE_IO_OBJETO_INVALIDO, std::format("Objeto com conteúdo inválido para {}: {}", nome, erro.str()));
        }

        ASN1::CoderEnv env;
        env.set_ber();

        std::vector<char> codificado;
        const bool codificou = env.encode(objeto, std::back_inserter(codificado));

        if (!codificou) {
            throw CUeIoError(EUE_IO_OBJETO_NAO_CODIFICADO, "Arquivo não foi codificado para " + nome);
        }

        buffer.swap(codificado);
    }
};

} // namespace api
