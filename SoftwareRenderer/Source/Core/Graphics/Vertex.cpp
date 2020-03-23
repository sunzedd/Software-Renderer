#include "Vertex.h"

namespace core {

Vertex& Vertex::operator += ( const Vertex& rhs )
{
    pos += rhs.pos;
    n += rhs.n;
    uv += rhs.uv;
    color += rhs.color;

    return *this;
}

Vertex& Vertex::operator -= ( const Vertex& rhs )
{
    pos -= rhs.pos;
    n -= rhs.n;
    uv -= rhs.uv;
    color -= rhs.color;

    return *this;
}

Vertex& Vertex::operator *= ( float val ) 
{
    pos *= val;
    n *= val;
    uv *= val;
    color *= val;

    return *this;
}

Vertex& Vertex::operator /= ( float val ) 
{
    pos /= val;
    n /= val;
    uv /= val;
    color /= val;

    return *this;
}

Vertex operator + ( const Vertex& lhs, const Vertex& rhs )
{				    
    Vertex out(lhs);

    out.pos += rhs.pos;
    out.n += rhs.n;
    out.uv += rhs.uv;
    out.color += rhs.color;

    return out;
}				    
                    
Vertex operator - ( const Vertex & lhs, const Vertex & rhs )
{
    Vertex out(lhs);

    out.pos -= rhs.pos;
    out.n -= rhs.n;
    out.uv -= rhs.uv;
    out.color -= rhs.color;

    return out;
}

Vertex operator * ( const Vertex& v, float val ) 
{				    						   
    Vertex out(v);

    out.pos *= val;
    out.n *= val;
    out.uv *= val;
    out.color *= val;

    return out;
}	

Vertex operator / ( const Vertex& v, float val ) 
{
    Vertex out(v);

    out.pos /= val;
    out.n /= val;
    out.uv /= val;
    out.color /= val;

    return out;
}

} // namespace core
