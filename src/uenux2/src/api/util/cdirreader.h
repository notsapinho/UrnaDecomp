#pragma once

#include <dirent.h>
#include <string>

namespace api {

/**
 * Percorre as entradas de um diretório.
 */
class CDirReader {
public:
    explicit CDirReader(const std::string& diretorio);
    ~CDirReader();

    bool NextEntry();

    // Open, Close, IsDir, IsFile and IsLink (target fns 5470, 2232, 1912, 2231 and 5469) have no record: their names are
    // chosen from what they do (opendir, closedir, and stat or lstat of the current entry's path tested for S_IFDIR,
    // S_IFREG and S_IFLNK).
    bool Open(const std::string& diretorio);
    void Close();
    bool IsDir() const;
    bool IsFile() const;
    bool IsLink() const;

    // The current entry's name, "" when there is none: api::RemoveTree (fn 5458, csystem.cpp) reads it inline. No
    // record names it: its name is chosen.
    std::string GetEntryName() const { return m_entrada != nullptr ? m_entrada->d_name : ""; }

private:
    std::string m_diretorio = "";
    DIR* m_dir = nullptr;
    dirent* m_entrada = nullptr;
};

} // namespace api
