#ifndef MATHPLOTTER_THEME_HPP
#define MATHPLOTTER_THEME_HPP

#include <SFML/Graphics/Color.hpp>

namespace mathplotter {
    
    enum class ThemeType {
        Light,
        Dark
    };

    class Theme {
    private:
        ThemeType m_type;
        sf::Color m_backgroundColor;
        sf::Color m_majorGridColor;
        sf::Color m_minorGridColor;
        sf::Color m_axisColor;
        sf::Color m_axisLabelColor;
    public:
        explicit Theme(ThemeType type);
    };

} // namespace mathplotter

#endif