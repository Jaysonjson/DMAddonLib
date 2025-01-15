#ifndef ZIP_HPP
#define ZIP_HPP
#include <filesystem>
#include "miniz.h"
#include "defines.hpp"
#include <vector>

namespace DM {
    class Zip {
        mz_zip_archive archive;
        string path;
    public:
        explicit Zip(const string& path): path(path) {
            //create(path);
        }

        void create();
        void addExternalFile(const string& file, const string& entry);
        void addFile(const vector<char>& buffer, const string& entry);
        void addFile(const string& content, const string& entry);
        void save();
        static void unzip(const string& path, const std::filesystem::path& outputDir);
        static void unzip(const string& path);
    };
}

#endif //ZIP_HPP
