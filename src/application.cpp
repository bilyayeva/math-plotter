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
            // auto deducts sf::Event::MouseWheelScrolled
            if (const auto* mouseScrolled{event->getIf<sf::Event::MouseWheelScrolled>()}) {
                m_cameraController.HandleZoom(*mouseScrolled);
            }
            // auto deducts sf::Event::MouseButtonPressed
            if (const auto* mousePressed{event->getIf<sf::Event::MouseButtonPressed>()}) {
                m_cameraController.HandleDragStart(m_window, *mousePressed);
            }
            // auto deducts sf::Event::MouseMoved
            if (const auto* mouseMoved{event->getIf<sf::Event::MouseMoved>()}) {
                m_cameraController.HandleDrag(m_window, *mouseMoved);
            }
            // audo deducts sf::Event::MouseButtonReleased
            if (const auto* mouseReleased{event->getIf<sf::Event::MouseButtonReleased>()}) {
                m_cameraController.HandleDragEnd(*mouseReleased);
            }
        }
    }

    void Application::Run() {
        while (m_window.isOpen()) {
            ProcessEvents();

            m_window.clear(m_theme.GetBackgroundColor());

            // Render World
            m_cameraController.Apply(m_window);
            m_gridRenderer.Draw(
                m_window, m_theme,
                m_cameraController.GetZoomLevel()
            );

            // Render User Interface
            m_window.setView(m_interfaceView);
            m_userInterface.Draw(m_window);

            m_window.display();
        }
    }

} // namespace mathplotter