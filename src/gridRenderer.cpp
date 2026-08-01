#include <mathplotter/gridRenderer.hpp>
#include <mathplotter/theme.hpp>

#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

#include <cmath>
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

    void GridRenderer::DrawMajorGrid(
        sf::RenderWindow& window,
        const Theme& theme,
        const VisibleBounds& bounds,
        const float majorGridStep
    ) const {
        float verticalLinePosition = 
            std::ceil(bounds.left / majorGridStep) * majorGridStep;
        
        float horizontalLinePosition =
            std::ceil(bounds.top / majorGridStep) * majorGridStep;

        sf::VertexArray gridLine(sf::PrimitiveType::Lines, 2);

        gridLine[0].color = theme.GetMajorGridColor();
        gridLine[1].color = theme.GetMajorGridColor();

        while (verticalLinePosition <= bounds.right) {
            gridLine[0].position = {verticalLinePosition, bounds.top};
            gridLine[1].position = {verticalLinePosition, bounds.bottom};
            if (std::round(verticalLinePosition) != 0.F) {
                window.draw(gridLine);
            }
            verticalLinePosition += majorGridStep;
        }
        while (horizontalLinePosition <= bounds.bottom) {
            gridLine[0].position = {bounds.left, horizontalLinePosition};
            gridLine[1].position = {bounds.right, horizontalLinePosition};
            if (std::round(horizontalLinePosition) != 0.f) {
                window.draw(gridLine);
            }
            horizontalLinePosition += majorGridStep;
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
        
        DrawMajorGrid(window, theme, bounds, m_majorGridStep);
        DrawAxes(window, theme, bounds, worldOrigin);
    }

} // namespace mathplotter