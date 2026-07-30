#ifndef MATHPLOTTER_USER_INTERFACE_HPP
#define MATHPLOTTER_USER_INTERFACE_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

namespace mathplotter {

    class UserInterface {
    private:
        sf::Text m_title;
    public:
        explicit UserInterface(const sf::Font& font);
    };

} // namespace mathplotter

#endif