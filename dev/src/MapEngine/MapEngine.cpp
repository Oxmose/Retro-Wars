#include <string>
#include <vector>
#include <algorithm>

#include <iostream>

#include <tmxparser/Tmx.h>

#include "MapEngine.h"
#include "../Misc/Misc.h"
#include "../Misc/Tools.h"

using namespace std;
using namespace nsTools;

#define MAPENGINE nsMapEngine::MapEngine

MAPENGINE::MapEngine(const string &p_mapName)
{
    // Init
    m_map = new Tmx::Map();
    m_map->ParseFile(MAP_FOLDER + p_mapName);
    cout << MAP_FOLDER + p_mapName << endl;
    m_properties = m_map->GetProperties();
} // MapEngine()

MAPENGINE::~MapEngine()
{
    delete m_map;
} // ~MapEngine()

vector<PLAYER_TYPE> MAPENGINE::getPlayers() const
{
    vector<PLAYER_TYPE> result;
    string players = m_properties.GetStringProperty("Players");
    transform(players.begin(), players.end(), players.begin(),(int (*)(int))tolower);
    vector<string> playersTypeStr = splitString(players, ",");
    for (string type : playersTypeStr)
    {    
        if(type == "blue")
            result.push_back(BLUE);
        else if(type == "red")
            result.push_back(RED);
        else if(type == "green")
            result.push_back(GREEN);
        else if(type == "yellow")
            result.push_back(YELLOW);
        else if(type == "black")
            result.push_back(BLACK);
    }

    return result;
} // getPlayers()

Tmx::MapOrientation MAPENGINE::getOrientation() const
{
    return m_map->GetOrientation();
} // getOrientation()

Tmx::MapRenderOrder MAPENGINE::getRenderOrder() const
{
    return m_map->GetRenderOrder();
} // getRenderOrder()

unsigned int MAPENGINE::getWidth() const
{
    return m_map->GetWidth();
} // getWidth()

unsigned int MAPENGINE::getHeight() const
{
    return m_map->GetHeight();
} // getHeight()

unsigned int MAPENGINE::getTileWidth() const
{
    return m_map->GetTileWidth();
} // getTileWidth()

unsigned int MAPENGINE::getTileHeight() const
{
    return m_map->GetTileHeight();
} // getTileHeight()

unsigned int MAPENGINE::getNextObjectId() const
{
    return m_map->GetNextObjectId();
} // getNextObjectId()

unsigned int MAPENGINE::getLayerWidth(const unsigned int &p_layerId) const
{
    return getLayer(p_layerId)->GetWidth();
} // getLayerWidth()

unsigned int MAPENGINE::getLayerHeight(const unsigned int &p_layerId) const
{
    return getLayer(p_layerId)->GetHeight();
} // getLayerHeight()

const Tmx::Layer* MAPENGINE::getLayer(const unsigned int &p_layerId) const
{
    return m_map->GetLayer(p_layerId);
} // getLayer()

vector<int> MAPENGINE::getLayerTiles(const unsigned int &p_layerId) const
{
    vector<int> result;
    const Tmx::TileLayer *tiles = m_map->GetTileLayer(p_layerId);
    const unsigned int width = getLayerWidth(p_layerId);
    const unsigned int height = getLayerHeight(p_layerId);

    for(unsigned int i = 0; i < height; ++i)
    {
        for(unsigned int j = 0; j < width; ++j)
        {
            result.push_back(tiles->GetTileGid(j, i));
        }
    }
    return result;
} // getLayerTiles()


