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
