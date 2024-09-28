#ifndef POINT_H
#define POINT_H

#include <ostream>

namespace my
{

struct Point
{
    int x;
    int y;
};

inline std::ostream& operator<<(std::ostream& stream, Point point)
{
    stream << "Point{ " << point.x << ", " << point.y << " }";
    return stream;
}

} // namespace my

#endif // POINT_H
