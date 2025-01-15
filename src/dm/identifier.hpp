#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP
#include <regex>
#include <string>
#include "defines.hpp"

class Identifier {
    string namespace_ = "";
    string path_ = "";
public:
    Identifier() = default;
    Identifier(string namespaceIn, string path): namespace_(std::move(namespaceIn)), path_(std::move(path)) {}

    constexpr static const char* keyPattern_ = "[a-z0-9/._-]{2,31}";
    constexpr static const char* fullPattern_ = "[a-z0-9/._-]{2,31}:[a-z0-9/._-]{2,31}";
    constexpr static int AR_NAMESPACE = 0;
    constexpr static int AR_KEY = 1;

public:
    string getNameSpace() const { return namespace_; }
    string getPath() const { return path_; }

    bool empty() {
        return namespace_.empty() && path_.empty();
    }

    bool valid() const {
        return valid(asString());
    }

    static bool valid(const string& str) {
        return std::regex_match(str, std::regex{fullPattern_});
    }

    string asString() const {
        return getNameSpace() + ":" + getPath();
    }

    static Identifier fromString(const string& str) {
        if(valid(str)) {
            auto delimeter = str.find(':');
            return Identifier{str.substr(0, delimeter), str.substr(delimeter + 1)};
        }
        return Identifier{};
    }

    static string extractPath(const string& str) {
        return fromString(str)[1];
    }

    friend std::ostream& operator<<(std::ostream& os, const Identifier& key) {
        os << key.asString();
        return os;
    }

    friend bool operator==(const Identifier& key0, const Identifier& key) {
        return key.asString() == key0.asString();
    }

    string operator[](const int i) const {
        if (i == 0) return getNameSpace();
        if (i == 1) return getPath();
        return "";
    }
};
#endif // IDENTIFIER_HPP
