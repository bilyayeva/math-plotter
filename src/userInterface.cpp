#include <mathplotter/userInterface.hpp>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace mathplotter {

    UserInterface::UserInterface(const sf::Font& font)
        : m_title(font, "Math Plotter++") {
    }

    void UserInterface::Draw(sf::RenderWindow& window) const {
        window.draw(m_title);
    }

} // namespace mathplotter