#ifndef PACK_H
#define PACK_H
#include <string>

#include "defines.hpp"
#include "json.hpp"
#include "macros.hpp"
namespace DM {
    class PackData {
    public:
        string version = "0.1";
        string id = "daddon";
        int protocol = CURRENT_PROTOCOL;
        vector<string> authors{};

        explicit PackData(const string& json) { fromJson(json); }
        PackData() = default;

        void fromJson(const string& json) {
            if(!nlohmann::json::accept(json)) return;
            nlohmann::json data = nlohmann::json::parse(json);
            EXTRACT(id, "id", data);
            EXTRACT(authors, "authors", data);
            EXTRACT(version, "version", data);
            EXTRACT(protocol, "protocol", data);
        }

        friend void to_json(nlohmann::json& json, const PackData& pack) {
            json = nlohmann::json{
                            {"authors", pack.authors},
                            {"id", pack.id},
                            {"version", pack.version},
                            {"protocol", pack.protocol}
            };
        }
    };
}
#endif //PACK_H
