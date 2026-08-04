#include <mathplotter/application.hpp>
#include <mathplotter/theme.hpp>
#include <mathplotter/visibleBounds.hpp>

#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

#include <optional>
#include <stdexcept>

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
          m_userInterface(m_font, m_theme) {
        if (!ImGui::SFML::Init(m_window)) {
            throw std::runtime_error("Application: Failed to initialize ImGui.");
        }
        ImGuiStyle& style{ImGui::GetStyle()};
        style.ScaleAllSizes(2.f);
        ImGuiIO& io{ImGui::GetIO()};
        io.Fonts->Clear();
        io.FontDefault = io.Fonts->AddFontFromFileTTF(
            "assets/fonts/dejavu/DejaVuSans.ttf",
            15.f
        );
        if (io.FontDefault == nullptr) {
            throw std::runtime_error("Application: Failed to load ImGui font.");
        }
        if (!ImGui::SFML::UpdateFontTexture()) {
            throw std::runtime_error("Application: Failed to update ImGui font.");
        };
    }

    void Application::ProcessEvents() {
        while (const std::optional event{m_window.pollEvent()}) {
            ImGui::SFML::ProcessEvent(m_window, *event);

            if (event->is<sf::Event::Closed>()) {
                m_window.close();
            }
            // auto deducts sf::Event::Resized
            if (const auto* windowResized{event->getIf<sf::Event::Resized>()}) {
                m_cameraController.HandleResize(*windowResized, m_interfaceView);
            }
            if (!ImGui::GetIO().WantCaptureMouse) {
                // auto deducts sf::Event::MouseWheelScrolled
                if (const auto* mouseScrolled{event->getIf<sf::Event::MouseWheelScrolled>()}) {
                    m_cameraController.HandleZoom(m_window, *mouseScrolled);
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
    }

    void Application::Run() {
        sf::Clock deltaClock;

        m_functionRenderers.emplace_back("x^3", m_theme.GetFunctionColor());
        while (m_window.isOpen()) {
            ProcessEvents();
            ImGui::SFML::Update(m_window, deltaClock.restart());

            m_cameraController.Apply(m_window);

            const sf::View     view         {m_window.getView()};
            const sf::Vector2f center       {view.getCenter()};
            const sf::Vector2f halfSize     {view.getSize() / 2.f};

            const VisibleBounds bounds {
                center.x - halfSize.x,
                center.x + halfSize.x,
                center.y - halfSize.y,
                center.y + halfSize.y
            };

            m_window.clear(m_theme.GetBackgroundColor());

            // Render World
            m_gridRenderer.Draw(
                m_window,
                m_interfaceView,
                m_theme,
                m_font,
                m_cameraController.GetZoomLevel(),
                bounds
            );

            // Render Function
            for (auto& function: m_functionRenderers) {
                function.Draw(m_window, bounds, m_gridRenderer.GetMajorGridStep());
            }

            // Render User Interface
            m_window.setView(m_interfaceView);
            m_userInterface.Draw(m_window, m_theme);

            ImGui::SFML::Render(m_window);
            m_window.display();
        }

        ImGui::SFML::Shutdown();
    }

} // namespace mathplotter