#include <mathplotter/application.hpp>
#include <mathplotter/theme.hpp>

#include <SFML/Window/VideoMode.hpp>

namespace mathplotter {

    Application::Application()
        : m_window(
            sf::VideoMode({1280u, 720u}),
            "Math Plotter++"
          ),
          m_font("assets/fonts/dejavu/DejaVuSans.ttf"),
          m_interfaceView(m_window.getDefaultView()),
          m_theme(ThemeType::Light),
          m_cameraController(m_interfaceView),
          m_gridRenderer(100.f),
          m_functionRenderers(),
          m_userInterface(m_font) {
    }

} // namespace mathplotter