#ifndef MATHPLOTTER_USER_INTERFACE_HPP
#define MATHPLOTTER_USER_INTERFACE_HPP

#include <mathplotter/theme.hpp>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <imgui.h>

#include <string>
#include <vector>

namespace mathplotter {

    class UserInterface {
    private:
        struct FunctionRow {
            std::string expression;
            ImVec4 color{1.f, 0.f, 0.f, 1.f};
        };

        sf::Text m_title;
        int m_selectedThemeIndex{0};
        std::vector<FunctionRow> m_functionRows;

        void DrawFunctionPanel(const Theme& theme);
        void ConfigureTitle(const Theme& theme);
        void SelectTheme(Theme& theme);
        ImVec4 ToImGuiColor(const sf::Color& color);
    public:
        UserInterface(const sf::Font& font, const Theme& theme);
        void Draw(sf::RenderWindow& window, Theme& theme);
    };

} // namespace mathplotter

#endif