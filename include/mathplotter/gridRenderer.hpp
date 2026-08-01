#ifndef MATHPLOTTER_GRID_RENDERER_HPP
#define MATHPLOTTER_GRID_RENDERER_HPP

#include <mathplotter/theme.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include <cstddef>

namespace mathplotter {

    class GridRenderer {
    private:
        float       m_majorGridStep;
        float       m_minorGridStep;
        float       m_maxMajorGridStep;
        float       m_minMajorGridStep;
        float       m_stepScale;
        float       m_stepFactors[3];
        std::size_t m_factorIndex;
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
        void DrawMinorGrid(
            sf::RenderWindow& window,
            const Theme& theme,
            const VisibleBounds& bounds,
            const float minorGridStep
        ) const;
        void UpdateGridStep(
            const float zoomLevel
        );
    public:
        explicit GridRenderer(float majorGridStep);
        void Draw(
            sf::RenderWindow& window,
            const Theme& theme,
            const float zoomLevel
        ); 
    };

} // namespace mathplotter

#endif