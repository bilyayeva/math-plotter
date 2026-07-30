#include <mathplotter/gridRenderer.hpp>

#include <stdexcept>

namespace mathplotter {

    GridRenderer::GridRenderer(float majorGridStep)
        : m_majorGridStep(majorGridStep),
          m_minorGridStep(majorGridStep / 4.f) {
        if (majorGridStep <= 0.f) {
            throw std::invalid_argument("GridRenderer: Invalid value.");
        }
    }

} // namespace mathplotter