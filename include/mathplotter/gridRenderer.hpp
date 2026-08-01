#ifndef MATHPLOTTER_GRID_RENDERER_HPP
#define MATHPLOTTER_GRID_RENDERER_HPP

#include <mathplotter/theme.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

namespace mathplotter {

    class GridRenderer {
    private:
        float m_majorGridStep;
        float m_minorGridStep;
        struct VisibleBounds {
            float left;
            float right;
            float top;
            float bottom;
        };

        void DrawAxes(
            sf::RenderWindow& window,
            const Theme& theme,
            const VisibleBounds& bounds,
            const sf::Vector2f& worldOrigin
        ) const;
        void DrawMajorGrid(
            sf::RenderWindow& window,
            const Theme& theme,
            const VisibleBounds& bounds,
            const float majorGridStep
        ) const;
    public:
        explicit GridRenderer(float majorGridStep);
        void Draw(sf::RenderWindow& window, const Theme& theme) const; 
    };

} // namespace mathplotter

#endif