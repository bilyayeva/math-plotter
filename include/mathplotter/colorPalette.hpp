#ifndef MATHPLOTTER_COLOR_PALETTE_HPP
#define MATHPLOTTER_COLOR_PALETTE_HPP

#include <SFML/Graphics/Color.hpp>

namespace mathplotter {
    
    struct ColorPalette {
        static constexpr sf::Color kBlack    {0, 0, 0};
        static constexpr sf::Color kWhite    {255, 255, 255};
        static constexpr sf::Color kRed      {255, 0, 0};
        static constexpr sf::Color kGreen    {0, 255, 0};
        static constexpr sf::Color kBlue     {0, 0, 255};
    };

} // namespace mathplotter

#endif