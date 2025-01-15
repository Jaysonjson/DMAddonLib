#include "dm/tardis.hpp"
#include "dm/macros.hpp"

namespace DM::Tardis {
    void ClientExterior::fromJson(const std::string &json) {
        if(!nlohmann::json::accept(json)) return;
        nlohmann::json data = nlohmann::json::parse(json);
        EXTRACT(id, "id", data);
        EXTRACT(name, "name", data);
        EXTRACT(description, "description", data);
        EXTRACT(model, "model", data);
        EXTRACT(animation, "animation", data);
        EXTRACT(texture, "texture", data);
        for (const auto& [id, layer] : data["layers"].items()) {
            layers.emplace(id, ClientLayer(layer["texture"], layer["type"]));
        }
    }

    void ClientExterior::addLayer(const string &layer, const string& texture, const string& type) {
        layers.emplace(layer, ClientLayer{texture, type});
    }


    void Interior::fromJson(const std::string &json) {
        if(!nlohmann::json::accept(json)) return;
        nlohmann::json data = nlohmann::json::parse(json);
        EXTRACT(id, "id", data);
        EXTRACT(name, "name", data);
        EXTRACT(doorOffset, "door_offset", data);
        EXTRACT(yaw, "yaw", data);
        EXTRACT(description, "description", data);
        EXTRACT(path, "path", data);
    }

    void LayerCheck::fromJson(const std::string &json) {
        if(!nlohmann::json::accept(json)) return;
        nlohmann::json data = nlohmann::json::parse(json);
        EXTRACT(object, "object", data);
        EXTRACT(type, "type", data);
        EXTRACT(layer, "layer", data);
    }
}