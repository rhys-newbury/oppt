///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 *  Contains code for homogeneous points.
 *  \file    IceHPoint.h
 *  \author    Pierre Terdiman
 *  \date    April, 4, 2000
 */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Include Guard
#pragma once

#ifndef ATTRIBUTE_MAY_ALIAS
  #if  defined _WIN32
    #define ATTRIBUTE_MAY_ALIAS
  #else
    #define ATTRIBUTE_MAY_ALIAS __attribute__((__may_alias__))
  #endif
#endif

  class ATTRIBUTE_MAY_ALIAS ICEMATHS_API  HPoint : public Point
  {
    public:

    //! Empty constructor
    inline_        HPoint()                                    {}
    //! Constructor from floats
    inline_        HPoint(float xx, float yy, float zz, float ww=0.0f) : Point(xx, yy, zz), w(ww)  {}
    //! Constructor from array
    inline_        HPoint(const float f[4]) : Point(f), w(f[3])                  {}
    //! Constructor from a Point
    inline_        HPoint(const Point& p, float ww=0.0f) : Point(p), w(ww)              {}
    //! Destructor
    inline_        ~HPoint()                                    {}

    //! Clear the point
    inline_  HPoint&    Zero()                      { x =      y =      z =      w = 0.0f;    return *this;  }

    //! Assignment from values
    inline_  HPoint&    Set(float xx, float yy, float zz, float ww )  { x  = xx;    y  = yy;  z  = zz;  w  = ww;    return *this;  }
    //! Assignment from array
    inline_  HPoint&    Set(const float f[4])              { x  = f[X];  y  = f[Y];  z  = f[Z];  w  = f[W];    return *this;  }
    //! Assignment from another h-point
    inline_  HPoint&    Set(const HPoint& src)              { x  = src.x;  y  = src.y;  z  = src.z;  w = src.w;    return *this;  }

    //! Add a vector
    inline_  HPoint&    Add(float xx, float yy, float zz, float ww )  { x += xx;    y += yy;  z += zz;  w += ww;    return *this;  }
    //! Add a vector
    inline_  HPoint&    Add(const float f[4])              { x += f[X];  y += f[Y];  z += f[Z];  w += f[W];    return *this;  }

    //! Subtract a vector
    inline_  HPoint&    Sub(float xx, float yy, float zz, float ww )  { x -= xx;    y -= yy;  z -= zz;  w -= ww;    return *this;  }
    //! Subtract a vector
    inline_  HPoint&    Sub(const float f[4])              { x -= f[X];  y -= f[Y];  z -= f[Z];  w -= f[W];    return *this;  }

    //! Multiplies by a scalar
    inline_  HPoint&    Mul(float s)                  { x *= s;    y *= s;    z *= s;    w *= s;      return *this;  }

    //! Returns MIN(x, y, z, w);
        float    Min()                const    { return MIN(x, MIN(y, MIN(z, w)));                    }
    //! Returns MAX(x, y, z, w);
        float    Max()                const    { return MAX(x, MAX(y, MAX(z, w)));                    }
    //! Sets each element to be componentwise minimum
        HPoint&    Min(const HPoint& p)              { x = MIN(x, p.x); y = MIN(y, p.y); z = MIN(z, p.z); w = MIN(w, p.w);  return *this;  }
    //! Sets each element to be componentwise maximum
        HPoint&    Max(const HPoint& p)              { x = MAX(x, p.x); y = MAX(y, p.y); z = MAX(z, p.z); w = MAX(w, p.w);  return *this;  }

    //! Computes square magnitude
    inline_  float    SquareMagnitude()          const    { return x*x + y*y + z*z + w*w;                      }
    //! Computes magnitude
    inline_  float    Magnitude()              const    { return sqrtf(x*x + y*y + z*z + w*w);                  }

    //! Normalize the vector
    inline_  HPoint&    Normalize()
              {
                float M = Magnitude();
                if(!_equal(M, 0.0))
                {
                  M = 1.0f / M;
                  x *= M;
                  y *= M;
                  z *= M;
                  w *= M;
                }
                return *this;
              }

    // Arithmetic operators
    //! Operator for HPoint Negate = - HPoint;
    inline_  HPoint    operator-()              const    { return HPoint(-x, -y, -z, -w);              }

    //! Operator for HPoint Plus  = HPoint + HPoint;
    inline_  HPoint    operator+(const HPoint& p)      const    { return HPoint(x + p.x, y + p.y, z + p.z, w + p.w);    }
    //! Operator for HPoint Minus = HPoint - HPoint;
    inline_  HPoint    operator-(const HPoint& p)      const    { return HPoint(x - p.x, y - p.y, z - p.z, w - p.w);    }

    //! Operator for HPoint Mul   = HPoint * HPoint;
    inline_  HPoint    operator*(const HPoint& p)      const    { return HPoint(x * p.x, y * p.y, z * p.z, w * p.w);    }
    //! Operator for HPoint Scale = HPoint * float;
    inline_  HPoint    operator*(float s)          const    { return HPoint(x * s, y * s, z * s, w * s);        }
    //! Operator for HPoint Scale = float * HPoint;
    inline_  friend  HPoint  operator*(float s, const HPoint& p)      { return HPoint(s * p.x, s * p.y, s * p.z, s * p.w);    }

    //! Operator for HPoint Div   = HPoint / HPoint;
    inline_  HPoint    operator/(const HPoint& p)      const    { return HPoint(x / p.x, y / p.y, z / p.z, w / p.w);    }
    //! Operator for HPoint Scale = HPoint / float;
    inline_  HPoint    operator/(float s)          const    { s = 1.0f / s; return HPoint(x * s, y * s, z * s, w * s);  }
    //! Operator for HPoint Scale = float / HPoint;
    inline_  friend  HPoint  operator/(float s, const HPoint& p)      { return HPoint(s / p.x, s / p.y, s / p.z, s / p.w);    }

    //! Operator for float DotProd = HPoint | HPoint;
    inline_  float    operator|(const HPoint& p)      const    { return x*p.x + y*p.y + z*p.z + w*p.w;            }
    // No cross-product in 4D

    //! Operator for HPoint += HPoint;
    inline_  HPoint&    operator+=(const HPoint& p)            { x += p.x; y += p.y; z += p.z; w += p.w;  return *this;  }
    //! Operator for HPoint += float;
    inline_  HPoint&    operator+=(float s)                { x += s;   y += s;   z += s;   w += s;    return *this;  }

    //! Operator for HPoint -= HPoint;
    inline_  HPoint&    operator-=(const HPoint& p)            { x -= p.x; y -= p.y; z -= p.z; w -= p.w;  return *this;  }
    //! Operator for HPoint -= float;
    inline_  HPoint&    operator-=(float s)                { x -= s;   y -= s;   z -= s;   w -= s;    return *this;  }

    //! Operator for HPoint *= HPoint;
    inline_  HPoint&    operator*=(const HPoint& p)            { x *= p.x; y *= p.y; z *= p.z; w *= p.w;  return *this;  }
    //! Operator for HPoint *= float;
    inline_  HPoint&    operator*=(float s)                { x*=s; y*=s; z*=s; w*=s;          return *this;  }

    //! Operator for HPoint /= HPoint;
    inline_  HPoint&    operator/=(const HPoint& p)            { x /= p.x; y /= p.y; z /= p.z; w /= p.w;  return *this;  }
    //! Operator for HPoint /= float;
    inline_  HPoint&    operator/=(float s)                { s = 1.0f / s; x*=s; y*=s; z*=s; w*=s;    return *this;  }

    // Arithmetic operators

    //! Operator for Point Mul = HPoint * Matrix3x3;
        Point    operator*(const Matrix3x3& mat)    const;
    //! Operator for HPoint Mul = HPoint * Matrix4x4;
        HPoint    operator*(const Matrix4x4& mat)    const;

    // HPoint *= Matrix3x3 doesn't exist, the matrix is first casted to a 4x4
    //! Operator for HPoint *= Matrix4x4
        HPoint&    operator*=(const Matrix4x4& mat);

    // Logical operators

    //! Operator for "if(HPoint==HPoint)"
    inline_  bool    operator==(const HPoint& p)      const    { return ( (_equal(x, p.x))&&(_equal(y, p.y))&&(_equal(z, p.z))&&(_equal(w, p.w)));      }
    //! Operator for "if(HPoint!=HPoint)"
    inline_  bool    operator!=(const HPoint& p)      const    { return ( (!_equal(x,p.x))||(!_equal(y, p.y))||(!_equal(z, p.z))||(!_equal(w, p.w)));      }

    // Cast operators

    //! Cast a HPoint to a Point. w is discarded.
#ifdef _MSC_VER
    inline_        operator  Point()          const    { return Point(x, y, z);                  }
    // gcc complains that conversion to a base class will never use a type conversion operator
#endif

    public:
        float    w;
   };

