#ifndef MATHPLOTTER_GRID_RENDERER_HPP
#define MATHPLOTTER_GRID_RENDERER_HPP

#include <mathplotter/theme.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

namespace mathplotter {

    class GridRenderer {
    private:
        float m_majorGridStep;
        float m_minorGridStep;
    public:
        explicit GridRenderer(float majorGridStep);
        void Draw(sf::RenderWindow& window, const Theme& theme) const; 
    };

} // namespace mathplotter

#endif