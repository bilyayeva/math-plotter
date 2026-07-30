#include <mathplotter/cameraController.hpp>

namespace mathplotter {

    CameraController::CameraController(sf::View view)
        : m_view(view),
          m_zoomLevel(1.0f) {
    }

} // namespace mathplotter