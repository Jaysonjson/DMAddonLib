#ifndef ADDONPACK_HPP
#define ADDONPACK_HPP

#include "tardis.hpp"
#include "packdata.hpp"
#include "resource.hpp"

namespace DM {

    class AddonPack {
    public:
        PackData packData{};
        vector<Tardis::ClientExterior> clientExteriors{};
        vector<Tardis::ServerExterior> serverExteriors{};
        vector<Tardis::Interior> interiors{};
        vector<string> layers{};
        map<string, Tardis::LayerCheck> layerChecks{};
        vector<Tardis::ClientExterior> clientExteriorOverrides{};
        vector<Resource> resources{};

        void addLayerCheck(const string& fileName, const string& layer, const string& object, const string& type);
        void addLayerCheck(const string& fileName, const Tardis::LayerCheck& layerCheck);
        void addLayer(const string& layer);

        void addExterior(const Tardis::ClientExterior& exterior, const string& builder);
        void addExterior(const string& id, const string& name, const string& description, const string& model, const string& animation, const string& texture, const map<string, Tardis::ClientLayer>& layers, const string& builder);

        void addExteriorOverride(const string& idToOverride, const string& name, const string& description, const string& model, const string& animation, const string& texture, const map<string, Tardis::ClientLayer>& layers);
        void addExteriorOverride(const Tardis::ClientExterior& exterior);

        void addInterior(const Tardis::Interior& interior);
        void addInterior(const string& id, const array<int, 3>& doorOffset, int yaw, const string& description, const string& localNbtPath);

        void addResource(const string& externalPath, const string& name, const ResourceType& type) {
            Resource resource{};
            resource.name = name;
            resource.externalPath = externalPath;
            resource.type = type;
            resources.emplace_back(resource);
        }

        void addTexture(const string& externalPath, const string& name) {
            addResource(externalPath, name, TEXTURE);
        }

        void addModel(const string& externalPath, const string& name) {
            addResource(externalPath, name, MODEL);
        }

        void addAnimation(const string& externalPath, const string& name) {
            addResource(externalPath, name, ANIMATION);
        }

        void pack(const string& extension = "dma");

        static void extract(const string& packFile, const string& outDir);
    };
}

#endif //ADDONPACK_HPP

