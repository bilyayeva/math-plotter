#include <mathplotter/functionRenderer.hpp>

#include <string>

namespace mathplotter {

    FunctionRenderer::FunctionRenderer(std::string expression)
        : m_expression(expression) {
    }

} // namespace mathplotter