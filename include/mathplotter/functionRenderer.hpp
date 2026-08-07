#ifndef MATHPLOTTER_FUNCTION_RENDERER_HPP
#define MATHPLOTTER_FUNCTION_RENDERER_HPP

#include <mathplotter/visibleBounds.hpp>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <muParser.h>

#include <string>

namespace mathplotter {

    class FunctionRenderer {
    private:
        std::string m_expression;
        double      m_x;
        mu::Parser  m_parser;
        sf::Color   m_functionColor;
    public:
        FunctionRenderer(
            const std::string& expression,
            const sf::Color& color
        );
        void Draw(
            sf::RenderWindow& window,
            const VisibleBounds& bounds,
            float majorGridStep
        );
        bool IsValid() const;
    };

} // namespace mathplotter

#endif