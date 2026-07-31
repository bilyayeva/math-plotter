#include <mathplotter/cameraController.hpp>

namespace mathplotter {

    CameraController::CameraController(sf::View view)
        : m_view(view),
          m_zoomLevel(1.0f) {
        m_view.setCenter({0.f, 0.f});
    }

} // namespace mathplotter