#ifndef MATHPLOTTER_USER_INTERFACE_HPP
#define MATHPLOTTER_USER_INTERFACE_HPP

#include <mathplotter/theme.hpp>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <imgui.h>

namespace mathplotter {

    class UserInterface {
    private:
        sf::Text m_title;
        int m_selectedThemeIndex{0};

        void ConfigureTitle(const Theme& theme);
        void SelectTheme(Theme& theme);
        ImVec4 ToImGuiColor(const sf::Color& color);
    public:
        UserInterface(const sf::Font& font, const Theme& theme);
        void Draw(sf::RenderWindow& window, Theme& theme);
    };

} // namespace mathplotter

#endif