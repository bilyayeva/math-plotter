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
        sf::Color m_titleFillColor;
        sf::Color m_titleOutlineColor;
    public:
        explicit Theme(ThemeType type);
        sf::Color GetBackgroundColor() const;
        sf::Color GetMajorGridColor() const;
        sf::Color GetMinorGridColor() const;
        sf::Color GetAxisColor() const;
        sf::Color GetTitleFillColor() const;
        sf::Color GetTitleOutlineColor() const;
    };

} // namespace mathplotter

#endif