#ifndef MATHPLOTTER_APPLICATION_HPP
#define MATHPLOTTER_APPLICATION_HPP

#include <mathplotter/cameraController.hpp>
#include <mathplotter/functionRenderer.hpp>
#include <mathplotter/gridRenderer.hpp>
#include <mathplotter/theme.hpp>
#include <mathplotter/userInterface.hpp>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include <vector>

namespace mathplotter {

    class Application {
    private:
        sf::RenderWindow                m_window;
        sf::Font                        m_font;
        sf::View                        m_interfaceView;
        Theme                           m_theme;
        CameraController                m_cameraController;
        GridRenderer                    m_gridRenderer;
        std::vector<FunctionRenderer>   m_functionRenderers;
        UserInterface                   m_userInterface;

        void ProcessEvents();
    public:
        Application();
        void Run();
    };

} // namespace mathplotter

#endif