#include <mathplotter/theme.hpp>
#include <mathplotter/userInterface.hpp>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string>

namespace mathplotter {

    UserInterface::UserInterface(const sf::Font& font, const Theme& theme)
        : m_title(font, "Math Plotter++"),
          m_selectedThemeIndex(0),
          m_functionRows(1) {
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

    sf::Color UserInterface::ToSfmlColor(const ImVec4& color) {
        return {
            static_cast<std::uint8_t>(color.x * 255.f),
            static_cast<std::uint8_t>(color.y * 255.f),
            static_cast<std::uint8_t>(color.z * 255.f),
            static_cast<std::uint8_t>(color.w * 255.f)
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

    void UserInterface::SetFunctionError(
        std::size_t rowIndex,
        bool hasError
    ) {
        if (rowIndex < m_functionRows.size()) {
            m_functionRows[rowIndex].hasError = hasError;
        }
    }

    std::optional<FunctionSubmission> UserInterface::DrawFunctionPanel(
        const Theme& theme
    ) {
        std::optional<FunctionSubmission> submission;

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

        ImGui::PushStyleColor(ImGuiCol_WindowBg, background);
        ImGui::PushStyleColor(ImGuiCol_PopupBg, background);
        ImGui::PushStyleColor(ImGuiCol_Text, foreground);
        ImGui::PushStyleColor(ImGuiCol_Border, foreground);
        ImGui::PushStyleColor(ImGuiCol_TableBorderStrong, foreground);
        ImGui::PushStyleColor(ImGuiCol_TableBorderLight, foreground);
        ImGui::PushStyleColor(ImGuiCol_Button, background);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hovered);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, active);

        constexpr ImGuiWindowFlags windowFlags{
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_AlwaysAutoResize
        };

        ImGui::SetNextWindowPos(
            {10.f, 10.f},
            ImGuiCond_Always
        );

        const ImGuiViewport* viewport{ImGui::GetMainViewport()};

        const float maxHeight{
            viewport->WorkSize.y - 20.f
        };

        ImGui::SetNextWindowSizeConstraints(
            {230.f, 0.f},
            {230.f, maxHeight}
        );

        ImGui::PushStyleVar(
            ImGuiStyleVar_WindowPadding,
            {0.f, 0.f}
        );

        ImGui::Begin("Functions", nullptr, windowFlags);

        ImGui::PopStyleVar();

        constexpr std::size_t maxFunctions{15};

        constexpr float headerHeight{40.f};
        constexpr float numberColumnWidth{30.f};

        constexpr ImGuiTableFlags headerFlags{
            ImGuiTableFlags_BordersOuterV |
            ImGuiTableFlags_BordersInnerV |
            ImGuiTableFlags_NoSavedSettings
        };

        ImGui::PushStyleVar(
            ImGuiStyleVar_CellPadding,
            {0.f, 0.f}
        );

        ImGui::PushStyleVar(
            ImGuiStyleVar_ItemSpacing,
            {
                ImGui::GetStyle().ItemSpacing.x,
                0.f
            }
        );

        if (ImGui::BeginTable("FunctionHeader", 2, headerFlags)) {
            ImGui::TableSetupColumn(
                "Add",
                ImGuiTableColumnFlags_WidthFixed,
                numberColumnWidth
            );

            ImGui::TableSetupColumn(
                "Title",
                ImGuiTableColumnFlags_WidthStretch
            );

            ImGui::TableNextRow(
                ImGuiTableRowFlags_None,
                headerHeight
            );

            ImGui::TableSetColumnIndex(0);

            ImGui::PushStyleVar(
                ImGuiStyleVar_FrameBorderSize,
                0.f
            );

            if (
                ImGui::Button(
                    "+",
                    {
                        ImGui::GetContentRegionAvail().x,
                        headerHeight
                    }
                ) &&
                m_functionRows.size() < maxFunctions
            ) {
                m_functionRows.emplace_back();
            }

            ImGui::PopStyleVar();

            ImGui::TableSetColumnIndex(1);

            const ImVec2 titleSize{
                ImGui::CalcTextSize("Function")
            };

            ImGui::SetCursorPosX(
                ImGui::GetCursorPosX() +
                (ImGui::GetContentRegionAvail().x - titleSize.x) / 2.f
            );

            ImGui::SetCursorPosY(
                ImGui::GetCursorPosY() +
                (headerHeight - titleSize.y) / 2.f
            );

            ImGui::TextUnformatted("Function");

            ImGui::EndTable();
        }

        ImGui::PopStyleVar(2);

        bool addNewRow{false};

        constexpr ImGuiTableFlags tableFlags{
            ImGuiTableFlags_BordersOuter |
            ImGuiTableFlags_BordersInnerH |
            ImGuiTableFlags_NoSavedSettings
        };

        ImGui::PushStyleVar(
            ImGuiStyleVar_CellPadding,
            {0.f, 0.f}
        );

        if (ImGui::BeginTable("FunctionTable", 3, tableFlags)) {
            ImGui::TableSetupColumn(
                "Number",
                ImGuiTableColumnFlags_WidthFixed,
                numberColumnWidth
            );

            ImGui::TableSetupColumn(
                "Color",
                ImGuiTableColumnFlags_WidthFixed,
                30.f
            );

            ImGui::TableSetupColumn(
                "Expression",
                ImGuiTableColumnFlags_WidthStretch
            );

            constexpr ImVec4 transparent{0.f, 0.f, 0.f, 0.f};

            ImGui::PushStyleColor(ImGuiCol_FrameBg, transparent);
            ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, transparent);
            ImGui::PushStyleColor(ImGuiCol_FrameBgActive, transparent);

            ImGui::PushStyleVar(
                ImGuiStyleVar_FrameBorderSize,
                0.f
            );

            constexpr float rowHeight{30.f};
            const ImVec2 tableStart{
                ImGui::GetCursorScreenPos()
            };

            for (std::size_t i{0}; i < m_functionRows.size(); ++i) {
                ImGui::PushID(static_cast<int>(i));

                ImGui::TableNextRow(
                    ImGuiTableRowFlags_None,
                    rowHeight
                );

                ImGui::TableSetColumnIndex(0);
                const std::string number{
                    std::to_string(i + 1)
                };

                const ImVec2 numberSize{
                    ImGui::CalcTextSize(number.c_str())
                };

                ImGui::SetCursorPosX(
                    ImGui::GetCursorPosX() +
                    (ImGui::GetContentRegionAvail().x - numberSize.x) / 2.f
                );

                ImGui::SetCursorPosY(
                    ImGui::GetCursorPosY() +
                    (rowHeight - numberSize.y) / 2.f
                );

                ImGui::TextUnformatted(number.c_str());

                ImGui::TableSetColumnIndex(1);

                if (m_functionRows[i].isSubmitted) {        
                    constexpr float colorSize{16.f};

                    const float horizontalOffset{
                        (ImGui::GetContentRegionAvail().x - colorSize) / 2.f
                    };

                    ImGui::SetCursorPosX(
                        ImGui::GetCursorPosX() + horizontalOffset
                    );

                    ImGui::SetCursorPosY(
                        ImGui::GetCursorPosY() +
                        (rowHeight - colorSize) / 2.f
                    );

                    ImGui::PushStyleVar(
                        ImGuiStyleVar_FrameBorderSize,
                        1.f
                    );

                    if (m_functionRows[i].hasError) {
                        const ImVec2 errorSize{
                            ImGui::CalcTextSize("!")
                        };

                        ImGui::SetCursorPosX(
                            ImGui::GetCursorPosX() +
                            (colorSize - errorSize.x) / 2.f
                        );

                        ImGui::SetCursorPosY(
                            ImGui::GetCursorPosY() +
                            (colorSize - errorSize.y) / 2.f
                        );

                        ImGui::TextUnformatted("!");
                    } else {

                        if (
                            ImGui::ColorButton(
                                "##FunctionColor",
                                m_functionRows[i].color,
                                ImGuiColorEditFlags_NoTooltip,
                                {colorSize, colorSize}
                            )
                        ) {
                            ImGui::OpenPopup("FunctionColorPicker");
                        }

                        const ImVec2 colorButtonMax{ImGui::GetItemRectMax()};
                        const ImVec2 colorButtonMin{ImGui::GetItemRectMin()};

                        ImGui::SetNextWindowPos(
                            {
                                colorButtonMax.x + 5.f,
                                colorButtonMin.y
                            },
                            ImGuiCond_Appearing
                        );

                        if (
                            ImGui::BeginPopup(
                                "FunctionColorPicker",
                                ImGuiWindowFlags_NoMove
                            )
                        ) {
                            constexpr ImGuiColorEditFlags colorPickerFlags{
                                ImGuiColorEditFlags_NoAlpha |
                                ImGuiColorEditFlags_NoInputs |
                                ImGuiColorEditFlags_NoSidePreview |
                                ImGuiColorEditFlags_NoSmallPreview
                            };

                            ImGui::SetNextItemWidth(160.f);

                            if (
                                ImGui::ColorPicker4(
                                    "##ColorPicker",
                                    &m_functionRows[i].color.x,
                                    colorPickerFlags
                                )
                            ) {
                                submission = FunctionSubmission{
                                    i,
                                    m_functionRows[i].expression,
                                    ToSfmlColor(m_functionRows[i].color)
                                };
                            }

                            ImGui::EndPopup();
                        }
                    }

                    ImGui::PopStyleVar();
                }

                ImGui::TableSetColumnIndex(2);

                ImGui::SetCursorPosY(
                    ImGui::GetCursorPosY() +
                    (rowHeight - ImGui::GetFrameHeight()) / 2.f
                );      

                ImGui::SetNextItemWidth(-1.f);

                const bool expressionSubmitted{
                    ImGui::InputText(
                        "##FunctionExpression",
                        &m_functionRows[i].expression,
                        ImGuiInputTextFlags_EnterReturnsTrue
                    )
                };

                if (ImGui::IsItemEdited()) {
                    m_functionRows[i].isSubmitted = false;
                }

                if (
                    expressionSubmitted &&
                    !m_functionRows[i].expression.empty()
                ) {
                    m_functionRows[i].isSubmitted = true;

                    submission = FunctionSubmission{
                        i,
                        m_functionRows[i].expression,
                        ToSfmlColor(m_functionRows[i].color)
                    };

                    if (i == m_functionRows.size() - 1) {
                        addNewRow = true;
                    }
                }

                ImGui::PopID();
            }
            ImGui::PopStyleVar();
            ImGui::PopStyleColor(3);

            ImGui::EndTable();
            const float separatorX{
                tableStart.x + numberColumnWidth + 1.f
            };

            const float tableBottom{
                tableStart.y +
                rowHeight * static_cast<float>(m_functionRows.size())
            };

            ImGui::GetWindowDrawList()->AddLine(
                {separatorX, tableStart.y},
                {separatorX, tableBottom},
                ImGui::GetColorU32(ImGuiCol_TableBorderStrong)
            );
        }
        ImGui::PopStyleVar();
        
        if (
            addNewRow &&
            m_functionRows.size() < maxFunctions
        ) {
            m_functionRows.emplace_back();
        }

        ImGui::End();
        ImGui::PopStyleColor(9);

        return submission;
    }

    std::optional<FunctionSubmission> UserInterface::Draw(
        [[maybe_unused]]sf::RenderWindow& window,
        Theme& theme
    ) {
        const auto submission{DrawFunctionPanel(theme)};

        SelectTheme(theme);

        return submission;
    }

} // namespace mathplotter