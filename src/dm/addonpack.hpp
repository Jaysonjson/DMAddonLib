#ifndef ADDONPACK_HPP
#define ADDONPACK_HPP

#include "tardis.hpp"
#include "packdata.hpp"

namespace DM {

    class AddonPack {
    public:
        PackData packData{};
        vector<Tardis::ClientExterior> clientExteriors{};
        vector<Tardis::ServerExterior> serverExteriors{};
        vector<Tardis::Interior> interiors{};
        vector<string> layers{};
        map<string, Tardis::LayerCheck> layerChecks{};

        void addLayerCheck(const string& fileName, const string& layer, const string& object, const string& type);
        void addLayerCheck(const string& fileName, const Tardis::LayerCheck& layerCheck);
        void addLayer(const string& layer);
        void addExterior(Tardis::ClientExterior exterior, const string& builder);
        void addExterior(const string& id, const string& name, const string& description, const string& model, const string& animation, const string& texture, const map<string, Tardis::ClientLayer>& layers, const string& builder);
        void pack(const string& extension = "dma");

        static void extract(const string& packFile, const string& outDir);
    };
}

#endif //ADDONPACK_HPP

