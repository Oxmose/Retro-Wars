/**
 *
 * @file GameEngine.h
 *
 * @authors : T. Stérin, A. Torres
 *
 * @date : 10/11/2015
 *
 * @version : 1.0
 *
 * @brief Game engine header file
 *
 * @see GameEngine.cpp
 *
 **/

#ifndef DEF_GAMEENGINE_H
#define DEF_GAMEENGINE_H

#include <SFML/Graphics.hpp>    // sf::RenderWindow, sf::VideoMode
#include <string>                // std::string

#include "GameEngine.h"            // nsGameEngine::GameEngine
#include "../GraphicEngine/GraphicEngine.h"        // nsGraphicEngine::GraphicEngine
#include "../MapEngine/MapEngine.h"
#include "../NetEngine/NetEngine.h"
#include "World.h"
#include "Player.h"
#include "../Misc/Misc.h"

namespace nsNetEngine
{
    class NetEngine;
}

/// @namespace nsGameEngine
/// @brief The GameEngine namespace.
/// @details The GameEngine namespace gather all the classes that are related to the game engine.
namespace nsGameEngine
{
    /// @class GameEngine GameEngine.h
    /// @brief The main class of the game
    /// @details This is the game engine. This class manages the whole lifecycle of the game.
    /// It manages the links between the diferent modules such as the graphic engine, the audio angine, etc...
    /// The class also process all the computing part of the game.
    class GameEngine
    {
        public:
            /// @fn GameEngine(const unsigned int & p_width, const unsigned int & p_height, const std::string & p_title) noexcept;
            /// @param p_width The width of the window.
            /// @param p_height The height of the window.
            /// @param p_title The title of the window.
            /// @brief The detailed constructor of the GameEngine class.
            /// @details It creates a new instance of the game, load some basics parameters and initialize the window context.
            /// It will also initialize the graphic engine.
            GameEngine(const unsigned int & p_width, const unsigned int & p_height, const std::string & p_title, 
                       nsMapEngine::MapEngine* p_mapEngine, PLAYER_TYPE p_playerType, nsNetEngine::NetEngine* p_netEngine) noexcept;

            /// @fn ~GameEngine();
            /// @brief The destructor.
            /// @details It will get rid of the window context pointer and the other module's pointers.
            ~GameEngine();

            void loadWorld();

            Terrain gidToTerrain(int p_gid, int p_x, int p_y);
            Unit gidToUnit(int p_gid, int p_x, int p_y);

            /// @fn void frame();
            /// @brief The main loop.
            /// @details The frame function is the main loop of the game, where all the game management will take place.
            void frame() ;

            void notify(const std::string &p_message);

            void test();

            
        private:
            /// @brief The window dimension variable.
            sf::VideoMode     m_windowDim;

            /// @brief The window title.
            std::string     m_windowTitle;
            
            /// @brief The pointer to the window object.
            sf::RenderWindow* m_window;
        
            std::string m_mapName;

            nsMapEngine::MapEngine* m_mapEngine;
            /// @brief The pointer to the graphic engine.
            nsGraphicEngine::GraphicEngine*    m_graphicEngine;


            World* m_world;
            Player* m_player;
            nsNetEngine::NetEngine *m_netEngine;
    };
}

#endif /* DEF_GAMEENGINE_H */
