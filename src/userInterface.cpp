#include <mathplotter/theme.hpp>
#include <mathplotter/userInterface.hpp>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace mathplotter {

    UserInterface::UserInterface(const sf::Font& font, const Theme& theme)
        : m_title(font, "Math Plotter++") {
        m_title.setFillColor(theme.GetTitleFillColor());
        m_title.setOutlineColor(theme.GetTitleOutlineColor());
        m_title.setOutlineThickness(1.f);
    }

    void UserInterface::Draw(sf::RenderWindow& window) const {
        window.draw(m_title);
    }

} // namespace mathplotter