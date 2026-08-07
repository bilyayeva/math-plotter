#include <mathplotter/functionRenderer.hpp>
#include <mathplotter/visibleBounds.hpp>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <string>

namespace mathplotter {

    FunctionRenderer::FunctionRenderer(
        const std::string& expression,
        const sf::Color& color)
        : m_expression(expression),
          m_x(0.0),
          m_functionColor(color) {
        m_parser.DefineVar("x", &m_x);
        m_parser.SetExpr(m_expression);
    }

    bool FunctionRenderer::IsValid() const {
        try {
            const auto& variables{m_parser.GetUsedVar()};

            for (const auto& variable : variables) {
                if (variable.first != "x") {
                    return false;
                }
            }

            return true;
        }
        catch (const mu::Parser::exception_type&) {
            return false;
        }
    }

    void FunctionRenderer::Draw(
        sf::RenderWindow& window,
        const VisibleBounds& bounds,
        float majorGridStep
    ) {
        const float functionStep{2.f};

        sf::VertexArray function(sf::PrimitiveType::LineStrip);

        for (
            float worldX{bounds.left - functionStep};
            worldX <= bounds.right + functionStep;
            worldX += functionStep) {
            m_x = static_cast<double>(worldX) / static_cast<double>(majorGridStep);
            const double y     {m_parser.Eval()};
            const double worldY {-y * static_cast<double>(majorGridStep)};
            if (!std::isfinite(worldY)) {
                continue;
            }
            function.append({
                {
                    worldX,
                    static_cast<float>(worldY)
                },
                m_functionColor
            });
        }

        window.draw(function);
    }

} // namespace mathplotter