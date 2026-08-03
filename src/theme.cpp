#include <mathplotter/theme.hpp>
#include <mathplotter/colorPalette.hpp>

#include <SFML/Graphics/Color.hpp>

#include <stdexcept>

namespace mathplotter {

    Theme::Theme(ThemeType type) : m_type(type) {
        switch (type) {
            case ThemeType::Light:
                m_backgroundColor   = ColorPalette::kWhite;
                m_majorGridColor    = ColorPalette::kGrey;
                m_minorGridColor    = ColorPalette::kLightGrey;
                m_axisColor         = ColorPalette::kBlack;
                m_axisLabelColor    = ColorPalette::kBlack;
                m_titleFillColor    = ColorPalette::kWhite;
                m_titleOutlineColor = ColorPalette::kBlack;
                m_functionColor     = ColorPalette::kRed;
                break;
            case ThemeType::Dark:
                m_backgroundColor   = ColorPalette::kBlack;
                m_majorGridColor    = ColorPalette::kVeryDarkGrey;
                m_minorGridColor    = ColorPalette::kAlmostBlack;
                m_axisColor         = ColorPalette::kWhite;
                m_axisLabelColor    = ColorPalette::kWhite;
                m_titleFillColor    = ColorPalette::kBlack;
                m_titleOutlineColor = ColorPalette::kWhite;
                m_functionColor     = ColorPalette::kGreen;
                break;
            case ThemeType::Matrix:
                m_backgroundColor   = ColorPalette::kBlack;
                m_majorGridColor    = ColorPalette::kDarkGreen;
                m_minorGridColor    = ColorPalette::kVeryDarkGreen;
                m_axisColor         = ColorPalette::kMatrixGreen;
                m_axisLabelColor    = ColorPalette::kMatrixGreen;
                m_titleFillColor    = ColorPalette::kBlack;
                m_titleOutlineColor = ColorPalette::kMatrixGreen;
                m_functionColor     = ColorPalette::kGreen;
                break;
            default:
                throw std::invalid_argument("Theme: Unsupported theme type.");
        }
    }

    sf::Color Theme::GetBackgroundColor() const {
        return m_backgroundColor;
    }

    sf::Color Theme::GetMajorGridColor() const {
        return m_majorGridColor;
    }

    sf::Color Theme::GetMinorGridColor() const {
        return m_minorGridColor;
    }

    sf::Color Theme::GetAxisColor() const {
        return m_axisColor;
    }

    sf::Color Theme::GetAxisLabelColor() const {
        return m_axisLabelColor;
    }

    sf::Color Theme::GetTitleFillColor() const {
        return m_titleFillColor;
    }

    sf::Color Theme::GetTitleOutlineColor() const {
        return m_titleOutlineColor;
    }

    sf::Color Theme::GetFunctionColor() const {
        return m_functionColor;
    }

} // namespace mathplotter