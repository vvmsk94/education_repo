#ifndef SEGMENT_H
#define SEGMENT_H

#include "shape.h"
#include "../utils/point.h"
#include "../render/renderable.h"

#include <memory>

namespace my
{

class Segment : public IShape
{
public:

    Segment(Point point1, Point point2)
        : m_point1(point1)
        , m_point2(point2)
    {
    }

    Segment(const Segment&) = default;
    Segment& operator=(const Segment&) = default;
    Segment(Segment&&) = default;
    Segment& operator=(Segment&&) = default;

    ~Segment() override = default;

    void render(Canvas& canvas) override
    {
        canvas << "Segment{ " << color() << ", " << m_point1 << ", " << m_point2 << " }";
    }

    Ptr clone() override
    {
        return std::make_unique<Segment>(m_point1, m_point2);
    }

private:
    Point m_point1, m_point2;
};

} // namespace my

#endif // SEGMENT_H
