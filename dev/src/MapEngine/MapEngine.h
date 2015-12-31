#ifndef DEF_MAPENGINE_H
#define DEF_MAPENGINE_H

#include <string>
#include <vector>
#include <algorithm>

#include <tmxparser/Tmx.h>

#include "../Misc/Misc.h"
#include "../Misc/Tools.h"
#include "../MD5Engine/md5wrapper.h"

#define MAP_FOLDER "./maps/"
#define TILESETS_FOLDER "./maps/tilesets/"

namespace nsMapEngine
{
    class MapEngine
    {
        public:

            // Constructor / Destructor
            MapEngine(const std::string &p_mapName);
            ~MapEngine();

            // Map properties getters
            std::vector<PLAYER_TYPE>    getPlayers()        const;
            Tmx::MapOrientation         getOrientation()    const;
            Tmx::MapRenderOrder         getRenderOrder()    const;
            unsigned int                getWidth()          const;
            unsigned int                getHeight()         const;
            unsigned int                getTileWidth()      const;
            unsigned int                getTileHeight()     const;
            unsigned int                getNextObjectId()   const;

            // Layers getters
            unsigned int                getLayerWidth(const unsigned int &p_layerId)  const;
            unsigned int                getLayerHeight(const unsigned int &p_layerId) const;
            const Tmx::Layer*           getLayer(const unsigned int &p_layerId)       const;
            std::vector<int>            getLayerTiles(const unsigned int &p_layerId)  const;

			// Misc
			std::string 				getHash() const;
			std::string 				getName() const;

        private:
			
			std::string			m_mapName;
            Tmx::Map            *m_map;
            Tmx::PropertySet    m_properties;

    }; // MapEngine
} // nsMapEngine

#endif
