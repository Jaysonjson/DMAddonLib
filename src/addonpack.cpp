#include "dm/addonpack.hpp"

#include <fstream>
#include <iostream>

#include "dm/zip.hpp"


void packPackData(DM::Zip& archive, const DM::PackData& packData) {
    nlohmann::json js;
    to_json(js, packData);
    archive.addFile(js.dump(4), "pack.json");
}

void packExteriors(DM::Zip& archive, DM::AddonPack* addonPack, string clientPath, string serverPath) {
    for (auto exterior : addonPack->clientExteriors) {
        nlohmann::json js;
        to_json(js, exterior);
        archive.addFile(js.dump(4), clientPath + Identifier::extractPath(exterior.getId()) + ".json");
    }
    nlohmann::json js = addonPack->serverExteriors;
    archive.addFile(js.dump(4), serverPath + "exteriors.json");
}

void packLayers(DM::Zip& archive, DM::AddonPack* addonPack, const string& layerPath) {

    for (auto layer_check : addonPack->layerChecks) {
        nlohmann::json js;
        to_json(js, layer_check.second);
        archive.addFile(js.dump(4), layerPath + "checks/" + layer_check.first + ".json");
    }

    nlohmann::json js = addonPack->layers;
    archive.addFile(js.dump(4), layerPath + "layers.json");
}

void DM::AddonPack::pack(const string& extension) {
    Zip archive{packData.id + "." + extension};
    string texturePath = packData.id + "/textures/";
    string modelPath = packData.id + "/geo/";
    string animationPath = packData.id + "/animation/";
    packPackData(archive, packData);
    packExteriors(archive, this, "tardis/exterior/client/", "tardis/exterior/server/");
    packLayers(archive, this, "tardis/layer/");
    archive.save();
}

void DM::AddonPack::addExterior(Tardis::ClientExterior exterior, const string& builder) {
    clientExteriors.emplace_back(exterior);
    Tardis::ServerExterior server_exterior{};
    server_exterior.setBuilder(builder);
    server_exterior.setId(exterior.getId());
    serverExteriors.emplace_back(server_exterior);
}

void DM::AddonPack::addExterior(const string &id, const string &name, const string &description, const string &model, const string &animation, const string &texture, const map<string, Tardis::ClientLayer>& layers, const string& builder) {
    addExterior(id, name, description, model, animation, texture, layers, builder);
}

void DM::AddonPack::addLayer(const string& layer) {
    layers.emplace_back(layer);
}

void DM::AddonPack::addLayerCheck(const string& fileName, const string& layer, const string& object, const string& type) {
    Tardis::LayerCheck layerCheck{};
    layerCheck.setObject(object);
    layerCheck.layer = layer;
    layerCheck.type = type;
    addLayerCheck(fileName, layerCheck);
}

void DM::AddonPack::addLayerCheck(const string& fileName, const Tardis::LayerCheck& layerCheck) {
    layerChecks.emplace(fileName, layerCheck);
}

void DM::AddonPack::extract(const string &packFile, const string &outDir) {

}

