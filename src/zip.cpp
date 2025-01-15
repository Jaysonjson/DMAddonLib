#include "dm/zip.hpp"

#include <fstream>

void DM::Zip::create(const string& path) {
    this->path = path;
    memset(&archive, 0, sizeof(archive));
    mz_zip_writer_init_file(&archive, path.c_str(), 0);
}

void DM::Zip::addFile(const vector<char>& buffer, const string& entry) {
    if (!mz_zip_writer_add_mem(&archive, entry.c_str(), buffer.data(), buffer.size(), MZ_DEFAULT_COMPRESSION)) mz_zip_writer_end(&archive);
}

void DM::Zip::addFile(const string& content, const string &entry) {
    addFile(vector<char>{content.begin(), content.end()}, entry);
}


void DM::Zip::addExternalFile(const string &file, const string& entry) {
    std::ifstream inputFile(file, std::ios::binary | std::ios::ate);
    if (!inputFile.is_open()) return;
    std::streamsize fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);
    vector<char> buffer(fileSize);
    if (!inputFile.read(buffer.data(), fileSize)) return;
    inputFile.close();
    addFile(buffer, entry);
}

void DM::Zip::save() {
    mz_zip_writer_finalize_archive(&archive);
    mz_zip_writer_end(&archive);
}

