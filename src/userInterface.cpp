#include <mathplotter/theme.hpp>
#include <mathplotter/userInterface.hpp>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <imgui.h>

namespace mathplotter {

    UserInterface::UserInterface(const sf::Font& font, const Theme& theme)
        : m_title(font, "Math Plotter++"),
          m_selectedThemeIndex(0) {
        ConfigureTitle(theme);
    }

    void UserInterface::ConfigureTitle(const Theme& theme) {
        m_title.setFillColor(theme.GetTitleFillColor());
        m_title.setOutlineColor(theme.GetTitleOutlineColor());
        m_title.setOutlineThickness(1.f);
        m_title.setCharacterSize(20u);
        const sf::FloatRect titleBounds{m_title.getLocalBounds()};
        m_title.setOrigin(titleBounds.position);
        m_title.setPosition({5.f, 5.f});
    }

    ImVec4 UserInterface::ToImGuiColor(const sf::Color& color) {
        return {
            color.r / 255.f,
            color.g / 255.f,
            color.b / 255.f,
            color.a / 255.f
        };
    }

    void UserInterface::SelectTheme([[maybe_unused]]Theme& theme) {
        const ImGuiViewport* viewport{ImGui::GetMainViewport()};
        const ImVec2 position{
            viewport->WorkPos.x + viewport->WorkSize.x - 10.f,
            viewport->WorkPos.y + 10.f
        };
        ImGui::SetNextWindowPos(
            position,
            ImGuiCond_Always,
            {1.f, 0.f}
        );
        const float comboWidth{
            ImGui::CalcTextSize("Light").x +
            ImGui::GetFrameHeight() +
            ImGui::GetStyle().FramePadding.x * 15.f
        };
        ImGui::SetNextItemWidth(comboWidth);
        constexpr ImGuiWindowFlags windowFlags{
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_AlwaysAutoResize
        };
        ImGuiStyle& style{ImGui::GetStyle()};
        ImGui::PushStyleVar(
            ImGuiStyleVar_WindowPadding,
            {0.f, 0.f}
        );
        ImGui::Begin("Theme", nullptr, windowFlags);
        ImGui::PopStyleVar();

        const char* themes[]{"Light", "Dark", "Matrix"};

        style.FrameBorderSize = 1.f;
        const ImVec4 background{
            ToImGuiColor(theme.GetBackgroundColor())
        };

        const ImVec4 foreground{
            ToImGuiColor(theme.GetAxisLabelColor())
        };

        ImVec4 hovered{foreground};
        hovered.w = 0.15f;

        ImVec4 active{foreground};
        active.w = 0.25f;

        style.Colors[ImGuiCol_WindowBg]         = background;
        style.Colors[ImGuiCol_PopupBg]          = background;
        style.Colors[ImGuiCol_FrameBg]          = background;
        style.Colors[ImGuiCol_Button]           = background;
        style.Colors[ImGuiCol_Border]           = foreground;
        style.Colors[ImGuiCol_Text]             = foreground;
        style.Colors[ImGuiCol_FrameBgHovered]   = hovered;
        style.Colors[ImGuiCol_FrameBgActive]    = active;
        style.Colors[ImGuiCol_ButtonHovered]    = hovered;
        style.Colors[ImGuiCol_ButtonActive]     = active;
        style.Colors[ImGuiCol_HeaderHovered]    = hovered;
        style.Colors[ImGuiCol_HeaderActive]     = active;
        style.Colors[ImGuiCol_TitleBg]          = background;
        style.Colors[ImGuiCol_TitleBgActive]    = background;
        style.Colors[ImGuiCol_TitleBgCollapsed] = background;
        style.Colors[ImGuiCol_Header]           = active;
        style.Colors[ImGuiCol_HeaderHovered]    = hovered;
        style.Colors[ImGuiCol_HeaderActive]     = active;
        if (
            ImGui::Combo(
            "##Theme",
            &m_selectedThemeIndex,
            themes,
            3)
        ) {
            switch (m_selectedThemeIndex) {
                case 0:
                    theme = Theme(ThemeType::Light);
                    break;
                case 1:
                    theme = Theme(ThemeType::Dark);
                    break;
                case 2:
                    theme = Theme(ThemeType::Matrix);
                    break;
            }

            ConfigureTitle(theme);
        }

        ImGui::End();
    }

    void UserInterface::Draw(sf::RenderWindow& window, Theme& theme) {
        SelectTheme(theme);
        window.draw(m_title);
    }

} // namespace mathplotter