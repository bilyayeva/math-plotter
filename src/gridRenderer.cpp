#include <mathplotter/gridRenderer.hpp>
#include <mathplotter/theme.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <stdexcept>

namespace mathplotter {

    GridRenderer::GridRenderer(float majorGridStep)
        : m_majorGridStep(majorGridStep),
          m_minorGridStep(majorGridStep / 4.f) {
        if (majorGridStep <= 0.f) {
            throw std::invalid_argument("GridRenderer: Invalid value.");
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

        const float left    {center.x - halfSize.x};
        const float right   {center.x + halfSize.x};
        const float top     {center.y - halfSize.y};
        const float bottom  {center.y + halfSize.y};

        if (top <= worldOrigin.y && bottom >= worldOrigin.y) {
            sf::VertexArray xAxis(sf::PrimitiveType::Lines, 2);
            xAxis[0].position = {left, worldOrigin.y};
            xAxis[1].position = {right, worldOrigin.y};
            xAxis[0].color = theme.GetAxisColor();
            xAxis[1].color = theme.GetAxisColor();
            window.draw(xAxis);
        }

        if (left <= worldOrigin.x && right >= worldOrigin.x) {
            sf::VertexArray yAxis(sf::PrimitiveType::Lines, 2);
            yAxis[0].position = {worldOrigin.x, top};
            yAxis[1].position = {worldOrigin.x, bottom};
            yAxis[0].color = theme.GetAxisColor();
            yAxis[1].color = theme.GetAxisColor();
            window.draw(yAxis);
        }
    }

} // namespace mathplotter