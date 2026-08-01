#include <mathplotter/cameraController.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>

namespace mathplotter {

    CameraController::CameraController(sf::View view)
        : m_view(view),
          m_zoomLevel(1.0f),
          m_zoomInFactor(0.95f),
          m_zoomOutFactor(1.05f),
          m_minZoomLevel(0.01f),
          m_maxZoomLevel(100.f),
          m_isDragging(false),
          m_previousMousePosition({0.f, 0.f}) {
        m_view.setCenter({0.f, 0.f});
    }

    void CameraController::Apply(sf::RenderWindow& window) const {
        window.setView(m_view);
    }

    void CameraController::HandleResize(
        const sf::Event::Resized& windowResized,
        sf::View& interfaceView
    ) {
        const sf::Vector2f newSize{
            static_cast<float>(windowResized.size.x),
            static_cast<float>(windowResized.size.y)
        };
        m_view.setSize(newSize / m_zoomLevel);
        interfaceView.setSize(newSize);
        interfaceView.setCenter(newSize / 2.f);
    }

    void CameraController::HandleZoom(
        const sf::RenderWindow& window,
        const sf::Event::MouseWheelScrolled& mouseScrolled
    ) {
        sf::Vector2f beforeZoomPosition{
            window.mapPixelToCoords(mouseScrolled.position, m_view)
        };
        float requestedZoom{m_zoomLevel};
        if (mouseScrolled.delta > 0) {
            requestedZoom /= m_zoomInFactor;
        }
        else if (mouseScrolled.delta < 0) {
            requestedZoom /= m_zoomOutFactor;
        }
        requestedZoom = std::clamp(requestedZoom, m_minZoomLevel, m_maxZoomLevel);
        m_view.zoom(m_zoomLevel / requestedZoom);
        m_zoomLevel = requestedZoom;
        sf::Vector2f afterZoomPosition{
            window.mapPixelToCoords(mouseScrolled.position, m_view)
        };
        m_view.move(beforeZoomPosition - afterZoomPosition);
    }

    void CameraController::HandleDragStart(
        const sf::RenderWindow& window,
        const sf::Event::MouseButtonPressed& mousePressed
    ) {
        if (mousePressed.button == sf::Mouse::Button::Left) {
            m_isDragging = true;
            m_previousMousePosition = window.mapPixelToCoords(
                                        mousePressed.position,
                                        m_view
                                    );
        }
    }

    void CameraController::HandleDrag(
        sf::RenderWindow& window,
        const sf::Event::MouseMoved& mouseMoved
    ) {
        if (m_isDragging) {
            const sf::Vector2f currentMousePosition{
                window.mapPixelToCoords(mouseMoved.position, m_view)
            };

            m_view.move(
                m_previousMousePosition - currentMousePosition
            );

            m_previousMousePosition =
                window.mapPixelToCoords(mouseMoved.position, m_view);
        }
    }

    void CameraController::HandleDragEnd(
        const sf::Event::MouseButtonReleased& mouseReleased
    ) {
        if (mouseReleased.button == sf::Mouse::Button::Left) {
            m_isDragging = false;
        }
    }

    float CameraController::GetZoomLevel() const {
        return m_zoomLevel;
    }

} // namespace mathplotter