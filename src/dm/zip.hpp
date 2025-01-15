#ifndef ZIP_HPP
#define ZIP_HPP
#include "miniz.h"
#include "defines.hpp"
#include <vector>
namespace DM {
    class Zip {
        mz_zip_archive archive;
        string path;
    public:

        Zip() = default;
        explicit Zip(const string& path) {
            create(path);
        }

        void create(const string& path);
        void addExternalFile(const string& file, const string& entry);
        void addFile(const vector<char>& buffer, const string& entry);
        void addFile(const string& content, const string& entry);
        void save();
    };
}

#endif //ZIP_HPP
