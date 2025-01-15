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

        /*
         * the add functions are just helper/utility classes to make it easier to add data to the pack, they will be used to generate the json files.
         * Adding own implementations is possible and sometimes recommended.
         */
        void addLayerCheck(const string& fileName, const string& layer, const string& object, const string& type);
        void addLayerCheck(const string& fileName, const Tardis::LayerCheck& layerCheck);
        void addLayer(const string& layer);

        void addExterior(const Tardis::ClientExterior& exterior, const string& builder);
        void addExterior(const string& id, const string& name, const string& description, const string& model, const string& animation, const string& texture, const map<string, Tardis::ClientLayer>& layers, const string& builder);

        /*
         * Adds a new Texture
         * ID should not include a normal Identifier (dalekmod:exterior) but just exterior, the ID will be set using your pack id
         * texture will be the output name inside the archive, externalTexture is the path to the texture to be archived,
         * same goes for model and animation
         */
        void addExterior(const string& id, const string& name, const string& description, const string& model, const string& externalModel, const string& animation, const string& externalAnimation, const string& texture, const string& externalTexture, const string& builder);

        /*
         * Adds a layer to an Exterior, the exterior must exist in the clientExteriors array.
         * target should not include a normal Identifier (dalekmod:exterior) but just exterior, the ID will be set using your pack id
         * texture will be the output name inside the archive, externalTexture is the path to the texture to be archived
         */
        void addExteriorLayer(const string& target, const string& layer, const string& type, const string& texture, const string& externalTexture);

        void addExteriorOverride(const string& idToOverride, const string& name, const string& description, const string& model, const string& animation, const string& texture, const map<string, Tardis::ClientLayer>& layers);
        void addExteriorOverride(const Tardis::ClientExterior& exterior);

        void addInterior(const Tardis::Interior& interior);
        void addInterior(const string& id, const array<int, 3>& doorOffset, int yaw, const string& description, const string& localNbtPath);

        /*
         * Adds a new Resource to the pack and will archive it into its respective folder
         */
        Resource& addResource(const string& externalPath, const string& name, const ResourceType& type) {
            Resource resource{};
            resource.name = name;
            resource.externalPath = externalPath;
            resource.type = type;
            resources.emplace_back(resource);
            return resources.back();
        }

        Resource& addTexture(const string& externalPath, const string& name) {
            return addResource(externalPath, name, TEXTURE);
        }

        Resource& addModel(const string& externalPath, const string& name) {
            return addResource(externalPath, name, MODEL);
        }

        Resource& addAnimation(const string& externalPath, const string& name) {
            return addResource(externalPath, name, ANIMATION);
        }

        void pack(const string& extension = "dma");

        static void extract(const string& packFile, const string& outDir);
    };
}

#endif //ADDONPACK_HPP

