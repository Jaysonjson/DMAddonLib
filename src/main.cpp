#include <fstream>
#include "dm/tardis.hpp"
#include "dm/packdata.hpp"
#include "dm/addonpack.hpp"

//TESTING
int main() {
    /*DM::Tardis::ClientExterior exterior{};
exterior.setId("example_addon:test");
exterior.addLayer("tnt_layer", "cool_texture", "default");
addon_pack.addExterior(exterior, "dalekmod:default");*/

    /*
    addon_pack.addTexture("test_tardis.png", "cool_texture.png");
    addon_pack.addModel("test_tardis.geo.json", "test_tardis.geo.json");
    addon_pack.addAnimation("test_tardis.animation.json", "test_tardis.animation.json");
     */
    DM::AddonPack testLoadPack{};
    testLoadPack.load("example_addon.zip", "cache/");
    testLoadPack.packData.id = "example_addon_loaded";
    testLoadPack.pack("zip");
    DM::AddonPack addon_pack{};
    addon_pack.packData.id = "example_addon";

    addon_pack.addExterior("cool_tardis", "dalekmod:default", "Cool Description", "cool_tardis.geo.json",
        "test_tardis.geo.json", "cool_tardis.animation.json", "test_tardis.animation.json", "cool_tardis.png", "test_tardis.png", "dalekmod:default");
    addon_pack.addExteriorLayer("cool_tardis", "tnt_layer", "default", "cool_tardis_tnt_layer.png", "tnt_layer.png");

    addon_pack.addLayer("tnt_layer");
    addon_pack.addLayerCheck("tnt", "tnt_layer", "minecraft:tnt", "block");
    addon_pack.addLayerCheck("snow", "snow_map", "snow", "weather");

    addon_pack.addInterior("example_addon:test", {0, 0, 0}, 5, "Test Description", "test_interior.nbt");
    addon_pack.addExteriorOverride("dalekmod:test", "", "Overriden Description", "", "", "", {});
    addon_pack.pack("zip");
    return 0;
}
