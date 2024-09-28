#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "../render/renderable.h"
#include "../shape/shape.h"
#include "../shape/circle.h"
#include "../shape/rectangle.h"
#include "../shape/segment.h"

#include <unordered_set>
#include <cassert>

namespace my
{

class Document : public IRenderable
{
public:
    using Ptr = std::unique_ptr<Document>;

    Document() = default;
    virtual ~Document() = default;

    void render(Canvas& canvas) override
    {
        for (const IShape::Ptr& shape : m_shapes)
        {
            shape->render(canvas);
            canvas << std::endl;
        }
    }

    const IShape::Ptr& add_circle(Point center, int radius)
    {
        auto [it, b_inserted] = m_shapes.emplace(std::make_unique<Circle>(center, radius));
        assert(b_inserted);
        return *it;
    }

    const IShape::Ptr& add_rectangle(Point corner, int width, int height)
    {
        auto [it, b_inserted] = m_shapes.emplace(std::make_unique<Rectangle>(corner, width, height));
        assert(b_inserted);
        return *it;
    }

    const IShape::Ptr& add_segment(Point point1, Point point2)
    {
        auto [it, b_inserted] = m_shapes.emplace(std::make_unique<Segment>(point1, point2));
        assert(b_inserted);
        return *it;
    }

    bool remove_shape(const IShape::Ptr& shape)
    {
        std::size_t removed = m_shapes.erase(shape);
        if (removed == 0)
            return false;
        return true;
    }

private:
    std::unordered_set<IShape::Ptr> m_shapes;
};

} // namespace my

#endif // DOCUMENT_H
