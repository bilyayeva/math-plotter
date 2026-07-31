#include <mathplotter/theme.hpp>
#include <mathplotter/colorPalette.hpp>

#include <stdexcept>

namespace mathplotter {

    Theme::Theme(ThemeType type) : m_type(type) {
        switch (type) {
            case ThemeType::Light:
                m_backgroundColor   = ColorPalette::kWhite;
                m_majorGridColor    = ColorPalette::kGreen;
                m_minorGridColor    = ColorPalette::kBlue;
                m_axisColor         = ColorPalette::kBlack;
                m_axisLabelColor    = ColorPalette::kBlack;
                m_titleFillColor    = ColorPalette::kWhite;
                m_titleOutlineColor = ColorPalette::kBlack;
                break;
            case ThemeType::Dark:
                m_backgroundColor   = ColorPalette::kBlack;
                m_majorGridColor    = ColorPalette::kRed;
                m_minorGridColor    = ColorPalette::kGreen;
                m_axisColor         = ColorPalette::kWhite;
                m_axisLabelColor    = ColorPalette::kWhite;
                m_titleFillColor    = ColorPalette::kBlack;
                m_titleOutlineColor = ColorPalette::kWhite;
                break;
            default:
                throw std::invalid_argument("Theme: Unsupported theme type.");
        }
    }

} // namespace mathplotter