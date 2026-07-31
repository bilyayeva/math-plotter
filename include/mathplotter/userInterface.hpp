#ifndef MATHPLOTTER_USER_INTERFACE_HPP
#define MATHPLOTTER_USER_INTERFACE_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace mathplotter {

    class UserInterface {
    private:
        sf::Text m_title;
    public:
        explicit UserInterface(const sf::Font& font);
        void Draw(sf::RenderWindow& window) const;
    };

} // namespace mathplotter

#endif