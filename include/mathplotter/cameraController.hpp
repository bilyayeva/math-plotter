#ifndef MATHPLOTTER_CAMERA_CONTROLLER_HPP
#define MATHPLOTTER_CAMERA_CONTROLLER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

namespace mathplotter {

    class CameraController {
    private:
        sf::View m_view;
        float    m_zoomLevel;
    public:
        explicit CameraController(sf::View view);
        void Apply(sf::RenderWindow& window) const;
    };

} // namespace mathplotter

#endif