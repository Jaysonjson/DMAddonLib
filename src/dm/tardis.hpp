#ifndef TARDIS_H
#define TARDIS_H

#include <map>
#include <string>
#include <utility>
#include "json.hpp"
#include "identifier.hpp"

namespace DM::Tardis {

    class ClientLayer {
    public:
        string texture;
        string type;

        ClientLayer(string texture, string type): texture(std::move(texture)), type(std::move(type)) {}

        friend void to_json(nlohmann::json& json, const ClientLayer& layer) {
            json = nlohmann::json{{"texture", layer.texture},{"type", layer.type}};
        }
    };

    class ClientExterior {
    protected:
        string id = "";
    public:
        string name = "";
        string description = "";
        string model = "";
        string animation = "";
        string texture = "";
        map<string, ClientLayer> layers{};

        explicit ClientExterior(const string& json) { fromJson(json); }
        ClientExterior() = default;
        ClientExterior(string id, string name, string description, string model, string animation, string texture, const map<string, ClientLayer>& layers):
            id(std::move(id)), name(std::move(name)), description(std::move(description)), model(std::move(model)), animation(std::move(animation)), texture(std::move(texture)), layers(layers)
        {}

        string getId() const { return this->id; }
        void setId(const string& id) { if(Identifier::valid(id)) this->id = id; }
        void fromJson(const string& json);
        void addLayer(const string& layer, const string& texture, const string& type);
        friend void to_json(nlohmann::json& json, const ClientExterior& exterior) {
            if(!exterior.id.empty()) json["id"] = exterior.id;
            if(!exterior.name.empty()) json["name"] = exterior.name;
            if(!exterior.description.empty()) json["description"] = exterior.description;
            if(!exterior.model.empty()) json["model"] = exterior.model;
            if(!exterior.animation.empty()) json["animation"] = exterior.animation;
            if(!exterior.texture.empty()) json["texture"] = exterior.texture;
            if(!exterior.layers.empty()) json["layers"] = exterior.layers;

            //Update to include overrides
            /*json = nlohmann::json{
                {"id", exterior.id},
                {"name", exterior.name},
                {"description", exterior.description},
                {"model", exterior.model},
                {"animation", exterior.animation},
                {"texture", exterior.texture},
                {"layers", exterior.layers}
            };*/
        }
    };

    class ServerExterior {
        string id;
        string builder;
    public:
        string getId() { return this->id; }
        string getBuilder() { return this->builder; }
        void setId(const string& id) { if(Identifier::valid(id)) this->id = id; }
        void setBuilder(const string& builder) { if(Identifier::valid(builder)) this->builder = builder; }

        friend void from_json(const nlohmann::json& js, ServerExterior& exterior) {
            exterior.setId(js["id"]);
            exterior.setBuilder(js["builder"]);
        }
        friend void to_json(nlohmann::json& json, const ServerExterior& exterior) {
            json = nlohmann::json{{"id", exterior.id},{"builder", exterior.builder}};
        }

    };

    class LayerCheck {
        string object;
    public:
        string type;
        string layer;

        void setObject(const string& object) { if(Identifier::valid(object)) this->object = object; }
        string getObject() { return this->object; }
        void fromJson(const string& json);

        friend void to_json(nlohmann::json& json, const LayerCheck& layerCheck) {
            json = nlohmann::json{{"object", layerCheck.object},{"type", layerCheck.type},{"layer", layerCheck.layer}};
        }
    };

    class Interior {
        string id;
    public:
        string name;
        array<int, 3> doorOffset;
        int yaw;
        string description;
        string path;
        string localNbtPath;

        void setId(const string& id) { if(Identifier::valid(id)) this->id = id; }
        string getId() { return this->id; }

        void fromJson(const string& json);

        friend void to_json(nlohmann::json& json, const Interior& interior) {
            json = nlohmann::json{
                {"id", interior.id},
                {"name", interior.name},
                {"door_offset", interior.doorOffset},
                {"yaw", interior.yaw},
                {"description", interior.description},
                {"path", interior.path}
            };
        }

    };
}

#endif // TARDIS_H
