#ifndef MATHPLOTTER_CAMERA_CONTROLLER_HPP
#define MATHPLOTTER_CAMERA_CONTROLLER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

namespace mathplotter {

    class CameraController {
    private:
        sf::View        m_view;
        float           m_zoomLevel;
        float           m_zoomInFactor;
        float           m_zoomOutFactor;
        float           m_minZoomLevel;
        float           m_maxZoomLevel;
        bool            m_isDragging;
        sf::Vector2f    m_previousMousePosition;
    public:
        explicit CameraController(sf::View view);
        void Apply(sf::RenderWindow& window) const;
        void HandleResize(
            const sf::Event::Resized& windowResized,
            sf::View& interfaceView
        );
        void HandleZoom(
            const sf::RenderWindow& window,
            const sf::Event::MouseWheelScrolled& mouseScrolled
        );
        void HandleDragStart(
            const sf::RenderWindow& window,
            const sf::Event::MouseButtonPressed& mousePressed
        );
        void HandleDrag(
            sf::RenderWindow& window,
            const sf::Event::MouseMoved& mouseMoved
        );
        void HandleDragEnd(
            const sf::Event::MouseButtonReleased& mouseReleased
        );
        float GetZoomLevel() const;
    };

} // namespace mathplotter

#endif