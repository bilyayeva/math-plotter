#ifndef MATHPLOTTER_USER_INTERFACE_HPP
#define MATHPLOTTER_USER_INTERFACE_HPP

#include <mathplotter/theme.hpp>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <imgui.h>

#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace mathplotter {

    struct FunctionSubmission {
        std::size_t rowIndex;
        std::string expression;
        sf::Color color;
    };

    class UserInterface {
    private:
        struct FunctionRow {
            std::string expression;
            ImVec4 color{1.f, 0.f, 0.f, 1.f};
            bool isSubmitted{false};
            bool hasError{false};
        };

        sf::Text m_title;
        int m_selectedThemeIndex{0};
        std::vector<FunctionRow> m_functionRows;

        std::optional<FunctionSubmission> DrawFunctionPanel(
            const Theme& theme
        );
        void ConfigureTitle(const Theme& theme);
        void SelectTheme(Theme& theme);
        ImVec4 ToImGuiColor(const sf::Color& color);
        sf::Color ToSfmlColor(const ImVec4& color);
    public:
        UserInterface(const sf::Font& font, const Theme& theme);
        std::optional<FunctionSubmission> Draw(
            sf::RenderWindow& window,
            Theme& theme
        );
        void SetFunctionError(
            std::size_t rowIndex,
            bool hasError
        );
    };

} // namespace mathplotter

#endif