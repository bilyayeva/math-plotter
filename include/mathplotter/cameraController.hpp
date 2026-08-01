#ifndef MATHPLOTTER_CAMERA_CONTROLLER_HPP
#define MATHPLOTTER_CAMERA_CONTROLLER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

namespace mathplotter {

    class CameraController {
    private:
        sf::View m_view;
        float    m_zoomLevel;
        float    m_zoomInFactor;
        float    m_zoomOutFactor;
        float    m_minZoomLevel;
        float    m_maxZoomLevel;
    public:
        explicit CameraController(sf::View view);
        void Apply(sf::RenderWindow& window) const;
        void HandleResize(
            const sf::Event::Resized& windowResized,
            sf::View& interfaceView
        );
        void HandleZoom(
            const sf::Event::MouseWheelScrolled& mouseScrolled
        );
    };

} // namespace mathplotter

#endif