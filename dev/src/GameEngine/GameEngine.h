#ifndef DEF_GAMEENGINE_H
#define DEF_GAMEENGINE_H

// STD LIB INCLUDES
#include <string>
#include <utility>
#include <atomic>
#include <tuple>

// SFML LIB INCLUDES
#include <SFML/Graphics.hpp> 

// INCLUDES FROM PACKAGE
#include "World.h"
#include "Player.h"

// OTHER INCLUDES FOM PROJECT
#include "../GraphicEngine/GraphicEngine.h"
#include "../MapEngine/MapEngine.h"
#include "../NetEngine/NetEngine.h"
#include "../Misc/Misc.h"

// Forward declaration
namespace nsNetEngine
{
    class NetEngine;
}

namespace nsGameEngine
{
    class GameEngine
    {
        public:
            // Constructor / Destructor
            GameEngine(const int & p_width, const int & p_height, const std::string & p_title,nsMapEngine::MapEngine* p_mapEngine, PLAYER_TYPE p_playerType, nsNetEngine::NetEngine* p_netEngine);
            ~GameEngine();

            // Load world from map file
            void loadWorld();

            // Tools functions
            Terrain gidToTerrain(int p_gid, int p_x, int p_y);
            Unit gidToUnit(int p_gid, int p_x, int p_y);
            int unitNPlayerTypeToGid(UNITTYPE p_UNITTYPE, PLAYER_TYPE p_playerType);
            std::string coordToString(std::pair<int,int> p_coord);

            // Gameloop
            void frame() ;

            // Notify the game engine on new message
            void notify(const nsNetEngine::Action &p_action);

            // Win condition validation
            void winCondition();
            
        private:
            /// @brief The window dimension variable.
            sf::VideoMode     m_windowDim;
            int m_fps;

            /// @brief The window title.
            std::string     m_windowTitle;
            
            /// @brief The pointer to the window object.
            sf::RenderWindow* m_window;
        
            /// @brief The pointer to the graphic engine.
            nsGraphicEngine::GraphicEngine*    m_graphicEngine;

            // Game objects
            World* m_world;
            Player* m_player;

            std::string m_mapName;
            nsMapEngine::MapEngine *m_mapEngine;
            nsNetEngine::NetEngine *m_netEngine;

            // Attack notification
            std::atomic<bool>   m_attackNotify;
            std::atomic<int>    m_attackNotifyStep;
            std::pair<int, int> m_attackPos;
            std::pair<int, int> m_attackFrom;

            // Movement notification
            std::atomic<bool>                m_moveUnit;
            std::vector<std::pair<int, int>> m_interMove;
            std::atomic<int>                 m_counter;
            std::atomic<int>                 m_interPos;
            Unit                             m_movingUnit;

            // Turn management
            std::atomic<bool> m_turn;
            std::atomic<bool> m_waitingForPlayers;
            std::atomic<int>  m_playerLeft;

            // Capture management
            std::vector<std::tuple<std::pair<int, int>, Unit, bool>> m_capturingBuilding;
            
            // Win management
            std::atomic<bool> m_win;
            std::atomic<bool> m_loose;
    }; // GameEngine
} // nsGameEngine

#endif // DEF_GAMEENGINE_H
