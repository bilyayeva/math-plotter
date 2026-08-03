#ifndef MATHPLOTTER_COLOR_PALETTE_HPP
#define MATHPLOTTER_COLOR_PALETTE_HPP

#include <SFML/Graphics/Color.hpp>

namespace mathplotter {
    
    struct ColorPalette {
        static constexpr sf::Color kBlack           {0, 0, 0};
        static constexpr sf::Color kWhite           {255, 255, 255};
        static constexpr sf::Color kRed             {255, 0, 0};
        static constexpr sf::Color kGreen           {0, 255, 0};
        static constexpr sf::Color kBlue            {0, 0, 255};
        static constexpr sf::Color kGrey            {150, 150, 150};
        static constexpr sf::Color kLightGrey       {220, 220, 220};
        static constexpr sf::Color kDarkGrey        {100, 100, 100};
        static constexpr sf::Color kVeryDarkGrey    {50, 50, 50};
        static constexpr sf::Color kAlmostBlack     {25, 25, 25};
        static constexpr sf::Color kMatrixGreen     {0, 180, 0};
        static constexpr sf::Color kDarkGreen       {0, 120, 0};
        static constexpr sf::Color kVeryDarkGreen   {0, 50, 0};
    };

} // namespace mathplotter

#endif