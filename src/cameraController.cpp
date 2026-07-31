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

} // namespace mathplotter