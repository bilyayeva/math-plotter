#include <mathplotter/cameraController.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

namespace mathplotter {

    CameraController::CameraController(sf::View view)
        : m_view(view),
          m_zoomLevel(1.0f) {
        m_view.setCenter({0.f, 0.f});
    }

    void CameraController::Apply(sf::RenderWindow& window) const {
        window.setView(m_view);
    }

    void CameraController::HandleResize(
        const sf::Event::Resized& resized,
        sf::View& interfaceView
    ) {
        const sf::Vector2f newSize{
            static_cast<float>(resized.size.x),
            static_cast<float>(resized.size.y)
        };
        m_view.setSize(newSize / m_zoomLevel);
        interfaceView.setSize(newSize);
        interfaceView.setCenter(newSize / 2.f);
    }

} // namespace mathplotter