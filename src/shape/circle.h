#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include "../utils/point.h"

#include <memory>

namespace my
{

class Circle : public IShape
{
public:
    Circle(Point center, int radius)
        : m_center(center)
        , m_radius(radius)
    {
    }

    Circle(const Circle&) = default;
    Circle& operator=(const Circle&) = default;
    Circle(Circle&&) = default;
    Circle& operator=(Circle&&) = default;

    ~Circle() override = default;

    void render(Canvas& canvas) override
    {
        canvas << "Circle{ " << color() << ", " << m_center << ", " << m_radius << " }";
    }

    Ptr clone() override
    {
        return std::make_unique<Circle>(m_center, m_radius);
    }

private:
    Point m_center;
    int m_radius;
};

} // namespace my

#endif // CIRCLE_H
