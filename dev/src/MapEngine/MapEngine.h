#ifndef DEF_MAPENGINE_H
#define DEF_MAPENGINE_H

#include <string>
#include <vector>
#include <algorithm>

#include <tmxparser/Tmx.h>

#include "../Misc/Misc.h"
#include "../Misc/Tools.h"

#define MAP_FOLDER "./maps/"
#define TILESETS_FOLDER "./maps/tilesets/"

namespace nsMapEngine
{
	class MapEngine
	{
		public:
			MapEngine(const std::string &p_mapName);
			~MapEngine();

			std::vector<PLAYER_TYPE> 	getPlayers() 	  const;

			Tmx::MapOrientation			getOrientation()  const;
			Tmx::MapRenderOrder			getRenderOrder()  const;
			unsigned int				getWidth()		  const;
			unsigned int 				getHeight() 	  const;
			unsigned int 				getTileWidth()	  const;
			unsigned int				getTileHeight()	  const;
			unsigned int				getNextObjectId() const;

			unsigned int				getLayerWidth(const unsigned int &p_layerId)  const;
			unsigned int				getLayerHeight(const unsigned int &p_layerId) const;
			const Tmx::Layer*		    getLayer(const unsigned int &p_layerId)       const;
			std::vector<int>			getLayerTiles(const unsigned int &p_layerId)  const;
		private:
			Tmx::Map 			*m_map;
			Tmx::PropertySet 	m_properties;

	};
}

#endif
