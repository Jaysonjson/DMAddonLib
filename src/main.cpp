#include <fstream>
#include "dm/tardis.hpp"
#include "dm/packdata.hpp"
#include "dm/addonpack.hpp"

//TESTING
int main() {
    DM::AddonPack::extract("cool.zip", "test");
    DM::AddonPack addon_pack{};
    addon_pack.packData.id = "cool";
    DM::Tardis::ClientExterior exterior{};
    exterior.setId("testaddon:test");
    exterior.addLayer("test_map", "cool_texture", "default");
    addon_pack.addExterior(exterior, "dalekmod:default");
    addon_pack.addLayer("test_layer");
    addon_pack.addLayerCheck("snow", "test_layer", "minecraft:snow", "block");
    addon_pack.addLayerCheck("snow2", "test_layer", "snow", "weather");
    addon_pack.pack("zip");
    return 0;
}
