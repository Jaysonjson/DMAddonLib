#include "dm/zip.hpp"

#include <fstream>

void DM::Zip::create() {
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

void DM::Zip::unzip(const string& path, const std::filesystem::path& outputDir) {
    mz_zip_archive archive;
    memset(&archive, 0, sizeof(archive));
    if (!mz_zip_reader_init_file(&archive, path.c_str(), 0)) return;

    create_directory(outputDir);
    int files = mz_zip_reader_get_num_files(&archive);

    for (int i = 0; i < files; ++i) {
        mz_zip_archive_file_stat file_stat;
        if (!mz_zip_reader_file_stat(&archive, i, &file_stat)) continue;
        std::filesystem::path outputPath = outputDir / file_stat.m_filename;
        if (file_stat.m_is_directory) {
            create_directories(outputPath);
        } else {
           create_directories(outputPath.parent_path());
            std::ofstream outFile(outputPath, std::ios::binary);
            if (!outFile) continue;
            size_t fileSize = file_stat.m_uncomp_size;
            std::vector<char> fileData(fileSize);
            if (!mz_zip_reader_extract_to_mem(&archive, i, fileData.data(), fileSize, 0)) continue;
            outFile.write(fileData.data(), fileSize);
        }
    }
    mz_zip_reader_end(&archive);
}

void DM::Zip::unzip(const string& path) {
    unzip(path, std::filesystem::path(path).stem());
}

