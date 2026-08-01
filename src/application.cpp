#include <mathplotter/application.hpp>
#include <mathplotter/theme.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <optional>

namespace mathplotter {

    Application::Application()
        : m_window(
            sf::VideoMode({1280u, 720u}),
            "Math Plotter++"
          ),
          m_font("assets/fonts/dejavu/DejaVuSans.ttf"),
          m_interfaceView(m_window.getDefaultView()),
          m_theme(ThemeType::Dark),
          m_cameraController(m_interfaceView),
          m_gridRenderer(100.f),
          m_functionRenderers(),
          m_userInterface(m_font, m_theme) {
    }

    void Application::ProcessEvents() {
        while (const std::optional event{m_window.pollEvent()}) {
            if (event->is<sf::Event::Closed>()) {
                m_window.close();
            }
            // auto deducts sf::Event::Resized
            if (const auto* windowResized{event->getIf<sf::Event::Resized>()}) {
                m_cameraController.HandleResize(*windowResized, m_interfaceView);
            }
        }
    }

    void Application::Run() {
        while (m_window.isOpen()) {
            ProcessEvents();

            m_window.clear(m_theme.GetBackgroundColor());

            // Render World
            m_cameraController.Apply(m_window);
            m_gridRenderer.Draw(m_window, m_theme);

            // Render User Interface
            m_window.setView(m_interfaceView);
            m_userInterface.Draw(m_window);

            m_window.display();
        }
    }

} // namespace mathplotter