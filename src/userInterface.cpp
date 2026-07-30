#include <mathplotter/userInterface.hpp>

#include <SFML/Graphics/Font.hpp>

namespace mathplotter {

    UserInterface::UserInterface(const sf::Font& font)
        : m_title(font, "Math Plotter++") {
    }

} // namespace mathplotter