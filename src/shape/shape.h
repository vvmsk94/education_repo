#ifndef SHAPE_H
#define SHAPE_H

#include "../render/renderable.h"
#include "../utils/color.h"

#include <memory>

namespace my
{

class IShape : public IRenderable
{
public:
    using Ptr = std::unique_ptr<IShape>;

    virtual ~IShape() = default;

    virtual Ptr clone() = 0;

    void color(Color color)
    {
        m_color = color;
    }

    Color color() const
    {
        return m_color;
    }

private:
    Color m_color;
};

} // namespace my

#endif // SHAPE_H
