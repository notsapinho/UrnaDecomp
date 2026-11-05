#pragma once
#include <filesystem>
#include <string>

#include <minizip/zip.h>

#include "ecourna/api/compression/icompressor.hpp"
#include "ecourna/api/uetypes.hpp"

namespace ecourna::api::compression {

// A zip archive written through zlib's minizip (zipOpen64/zipOpenNewFileInZip2_64/zipWriteInFileInZip/zipClose).
// Layout (40 bytes): ICompressor(16) + m_arquivo(12) + m_zip(4) + m_nivel(4) + m_modo(4). The destructor is defined in
// czip.cpp: CompactaWsq calls its D2 (target fn 2690) out of line, which a definition in the class does not give
// (src/units/06-ecourna-api-compression.mk).
class CZip : public ICompressor {
public:
    enum class EModoAbertura {
        CRIAR = 0,
        ADICIONAR = 1,
    };

    // Defined in czip.cpp (target fn 5193), where comum::CGravadorWSQ::CompactaWsq calls it out of line
    // (src/units/06-ecourna-api-compression.mk).
    CZip(const std::filesystem::path& arquivo, ENivelCompressao nivel);
    // Has no target index: binaryen inlined it into its one caller, comum::CGravadorLog::GravaResultado (target fn
    // 11584), where its code follows ICompressor's constructor (fn 5192) and this class's vptr store: the path's string
    // copied to +16, then 0, 2 (PADRAO) and 0 stored apart at +36, +32 and +28, as fn 5193 stores them, CreateZipFile
    // invoked, and ICompressor::Add(map) invoked inside a catch (...) that invokes SafeClose and rethrows; its landing
    // pads free +16 and call ICompressor's base-object destructor (fn 1526). uenux2's code has no landing pads
    // (docs/reference/facts/app-flags.md F6), so this code is an ecourna object's, and a constructor's: the pads
    // destroy the members and the base, not the object. The level is a parameter: written as ENivelCompressao::PADRAO
    // in the initializer, clang stores +28 and +32 as one i64 (measured in the whole link), where the target's three
    // stores are those of a level the caller passes, which binaryen folds once it inlines the one call (a reading). Its
    // file, czip.cpp, and its parameters' forms (references) and order are chosen
    // (src/units/136-uenux2-app-comum-gravadores-md.mk).
    CZip(const std::filesystem::path& arquivo, const std::map<std::filesystem::path, std::filesystem::path>& arquivos,
        ENivelCompressao nivel);
    ~CZip() override;

    void Close() override;
    bool SuportaGlob() const override { return true; }
    void SafeClose();

protected:
    void DoAdd(const std::filesystem::path& arquivo, const std::filesystem::path& nome) override;

private:
    int ConvertToOpen();
    void CreateZipFile();
    void AssertZipIsOpened();
    int ConvertToCompressLevel();
    static std::string ConvertToErrorMessage(int erro);
    void AtualizaProgresso(ueqword atual, ueqword total, const std::string& arquivo);

    std::string m_arquivo;
    zipFile m_zip;
    ENivelCompressao m_nivel;
    EModoAbertura m_modo;
};

} // namespace ecourna::api::compression
