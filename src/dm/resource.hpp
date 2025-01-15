#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include "packdata.hpp"

namespace DM {

    enum ResourceType {
        TEXTURE, MODEL, ANIMATION
    };

    class Resource {
    public:
        string name;
        string externalPath;
        ResourceType type;

        string getPath(const PackData& pack) const {
            switch (type) {
                case TEXTURE: {
                    return pack.id + "/textures/" + name;
                }
                case MODEL: {
                    return pack.id + "/geo/" + name;
                }
                case ANIMATION: {
                    return pack.id + "/animation/" + name;
                }
            }
            return "";
        }

    };
}

#endif //RESOURCE_HPP
