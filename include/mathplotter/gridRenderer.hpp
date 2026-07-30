#ifndef MATHPLOTTER_GRID_RENDERER_HPP
#define MATHPLOTTER_GRID_RENDERER_HPP

namespace mathplotter {

    class GridRenderer {
    private:
        float m_majorGridStep;
        float m_minorGridStep;
    public:
        explicit GridRenderer(float majorGridStep); 
    };

} // namespace mathplotter

#endif