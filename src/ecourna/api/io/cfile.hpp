#pragma once
#include <cstdio>
#include <filesystem>
#include <string>
#include <vector>

#include "ecourna/api/uetypes.hpp"

namespace ecourna::api::io {

// Flags applied with fcntl after Open (bit 0 -> O_SYNC, bit 1 -> O_NOATIME).
enum FileMode {
    FM_NORMAL = 0,
    FM_SYNC = 1,
    FM_NOATIME = 2,
};

class CFile {
public:
    // The constructor is out of line in cfile.cpp: its target body (fn 517) has the landing pad of an -fexceptions
    // object, and uenux2 callers such as api::CEncryptedFile::Save (2767) call it where an inline one would be inlined.
    // The destructor is inline: every uenux2 caller holds it as `if (m_file) Close();`, the catch gone in a TU without
    // -fexceptions. In -fexceptions code the target keeps the catch: CZip::DoAdd (9538) holds it inlined, and fn 3564,
    // the out-of-line copy fns 2892 and 9538 call, catches what Close throws and drops it (__cxa_begin_catch, then
    // __cxa_end_catch through invoke_v), so the try and the empty catch (...) are evidence. That the test sits inside
    // the try is chosen (src/units/206-uenux2-app-comum-appinfo-servicos.mk; the test ahead of the try was not tried).
    CFile(const std::string& nome, const std::string& modo, FileMode fileMode = FM_NORMAL);
    ~CFile()
    {
        try {
            if (m_file != nullptr) {
                Close();
            }
        } catch (...) {
        }
    }

    bool Open(const std::string& nome, const std::string& modo, FileMode fileMode);
    void Close();
    bool SetFileMode(FileMode fileMode);
    int Flush() const;
    void Sync() const;
    uedword RawWrite(const void* buffer, uedword tamanho) const;
    // Target fn 5180, no record: writes a buffer with RawWrite unless it is empty. Its target callers, fn 5371
    // (api::CFileASN::CodeObjectFunction for ModuloRegistroDigitalVoto::EntidadeResultadoRDV, whose record spells the
    // buffer std::vector<char> &, cfileasn.h:161) and fn 11587 (comum::CGravadorRDV::GravaResultado), are not written.
    // In use band 2 it links right after Sync (fn 5181), so it is cfile.cpp's, defined after Sync (a reading; its line,
    // the file's last, is a choice). The result is RawWrite's count, 0 for an empty buffer: the target keeps a `return`
    // in the empty branch and drops the call's result, which reads as binaryen's removal of a result no caller uses;
    // written void, with an early return or with the call in an `if`, it scored 5 over 20 rows against the target, and
    // with the result 1 over 19, the call's operand. Chosen: the name, that it is a const member (as WriteLine, a
    // recorded const member of this file, is; a free function of ecourna::api::io taking the CFile by reference
    // compiles to the same instructions) and that the result is RawWrite's.
    uedword Write(const std::vector<char>& dados) const;
    uedword WriteLine(const std::string& linha) const;
    uedword RawRead(void* buffer, uedword tamanho) const;
    uedword ReadLine(std::string& linha) const;
    bool Seek(int deslocamento, int origem) const;
    bool Eof() const;
    long Position() const;

    const std::string& GetNome() const { return m_nome; }
    bool IsOpen() const { return m_file != nullptr; }

    static std::string ReadFileContent(const std::string& nome);
    static std::vector<uebyte> ReadFileBinary(const std::filesystem::path& caminho);

private:
    static const int TAMANHO_BUFFER_LINHA = 128;

    FILE* m_file;
    std::string m_nome;
    bool m_escrita;
};

} // namespace ecourna::api::io
