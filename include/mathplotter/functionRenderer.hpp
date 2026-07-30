#ifndef MATHPLOTTER_FUNCTION_RENDERER_HPP
#define MATHPLOTTER_FUNCTION_RENDERER_HPP

#include <string>

namespace mathplotter {

    class FunctionRenderer {
    private:
        std::string m_expression;
    public:
        explicit FunctionRenderer(std::string expression);
    };

} // namespace mathplotter

#endif