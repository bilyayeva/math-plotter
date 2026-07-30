#ifndef MATHPLOTTER_CAMERA_CONTROLLER_HPP
#define MATHPLOTTER_CAMERA_CONTROLLER_HPP

#include <SFML/Graphics/View.hpp>

namespace mathplotter {

    class CameraController {
    private:
        sf::View m_view;
        float    m_zoomLevel;
    public:
        explicit CameraController(sf::View view);
    };

} // namespace mathplotter

#endif