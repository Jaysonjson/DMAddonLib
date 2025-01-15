#include <fstream>
#include "dm/tardis.hpp"
#include "dm/packdata.hpp"
#include "dm/addonpack.hpp"

//TESTING
int main() {
    //DM::AddonPack::extract("example_addon.zip", "test");
    DM::AddonPack addon_pack{};
    addon_pack.packData.id = "example_addon";
    DM::Tardis::ClientExterior exterior{};
    exterior.setId("example_addon:test");
    exterior.addLayer("tnt_layer", "cool_texture", "default");
    addon_pack.addExterior(exterior, "dalekmod:default");
    addon_pack.addLayer("tnt_layer");
    addon_pack.addLayerCheck("tnt", "tnt_layer", "minecraft:tnt", "block");
    addon_pack.addLayerCheck("snow", "snow_map", "snow", "weather");
    addon_pack.addInterior("example_addon:test", {0, 0, 0}, 5, "Test Description", "test_interior.nbt");
    addon_pack.addExteriorOverride("dalekmod:test", "", "Overriden Description", "", "", "", {});
    addon_pack.addTexture("test_tardis.png", "cool_texture.png");
    addon_pack.addModel("test_tardis.geo.json", "test_tardis.geo.json");
    addon_pack.addAnimation("test_tardis.animation.json", "test_tardis.animation.json");
    addon_pack.pack("zip");
    return 0;
}
