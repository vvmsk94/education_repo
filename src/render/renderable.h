#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <ostream>

namespace my
{

using Canvas = std::ostream;

class IRenderable
{
public:
    virtual void render(Canvas& canvas) = 0;
    virtual ~IRenderable() = default;
};

} // namespace my

#endif // RENDERABLE_H
