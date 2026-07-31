#include <mathplotter/gridRenderer.hpp>
#include <mathplotter/theme.hpp>

#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

#include <stdexcept>

namespace mathplotter {

    GridRenderer::GridRenderer(float majorGridStep)
        : m_majorGridStep(majorGridStep),
          m_minorGridStep(majorGridStep / 4.f) {
        if (majorGridStep <= 0.f) {
            throw std::invalid_argument("GridRenderer: Invalid value.");
        }
    }

    void GridRenderer::DrawAxes(
        sf::RenderWindow& window,
        const Theme& theme,
        const VisibleBounds& bounds,
        const sf::Vector2f& worldOrigin
    ) const {
        if (bounds.top <= worldOrigin.y && bounds.bottom >= worldOrigin.y) {
            sf::VertexArray xAxis(sf::PrimitiveType::Lines, 2);
            xAxis[0].position = {bounds.left, worldOrigin.y};
            xAxis[1].position = {bounds.right, worldOrigin.y};
            xAxis[0].color = theme.GetAxisColor();
            xAxis[1].color = theme.GetAxisColor();
            window.draw(xAxis);
        }

        if (bounds.left <= worldOrigin.x && bounds.right >= worldOrigin.x) {
            sf::VertexArray yAxis(sf::PrimitiveType::Lines, 2);
            yAxis[0].position = {worldOrigin.x, bounds.top};
            yAxis[1].position = {worldOrigin.x, bounds.bottom};
            yAxis[0].color = theme.GetAxisColor();
            yAxis[1].color = theme.GetAxisColor();
            window.draw(yAxis);
        }
    }

    void GridRenderer::Draw(
        sf::RenderWindow& window,
        const Theme& theme
    ) const {
        const sf::View     view         {window.getView()};
        const sf::Vector2f center       {view.getCenter()};
        const sf::Vector2f halfSize     {view.getSize() / 2.f};
        const sf::Vector2f worldOrigin  {0.f, 0.f};

        const VisibleBounds bounds {
            center.x - halfSize.x,
            center.x + halfSize.x,
            center.y - halfSize.y,
            center.y + halfSize.y
        };

        DrawAxes(window, theme, bounds, worldOrigin);
    }

} // namespace mathplotter