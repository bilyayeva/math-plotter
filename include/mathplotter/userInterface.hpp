#ifndef MATHPLOTTER_USER_INTERFACE_HPP
#define MATHPLOTTER_USER_INTERFACE_HPP

#include <mathplotter/theme.hpp>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace mathplotter {

    class UserInterface {
    private:
        sf::Text m_title;

        void ConfigureTitle(const Theme& theme);
    public:
        UserInterface(const sf::Font& font, const Theme& theme);
        void Draw(sf::RenderWindow& window) const;
    };

} // namespace mathplotter

#endif