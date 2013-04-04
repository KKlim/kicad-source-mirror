/*
 * This program source code file is part of KICAD, a free EDA CAD application.
 *
 * Copyright (C) 2010 Virtenio GmbH, Torsten Hueter, torsten.hueter <at> virtenio.de
 * Copyright (C) 2012 SoftPLC Corporation, Dick Hollenbeck <dick@softplc.com>
 * Copyright (C) 2012 Kicad Developers, see change_log.txt for contributors.
 * Copyright (C) 2013 Tomasz Wlostowski <tomasz.wlostowski@cern.ch>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <climits>
#include <iostream>
#include <sstream>

#include <math/math_util.h>

#ifdef WX_COMPATIBILITY
        #include <wx/gdicmn.h>
#endif

/**
 * Class VECTOR2_TRAITS
 * traits class for VECTOR2.
 */
template <class T>
struct VECTOR2_TRAITS
{
    ///> extended range/precision types used by operations involving multiple
    ///> multiplications to prevent overflow.
    typedef T extended_type;
};

template <>
struct VECTOR2_TRAITS<int>
{
    typedef int64_t extended_type;
};

// Forward declarations for template friends
template <class T>
class VECTOR2;
template <class T>
std::ostream& operator<<( std::ostream& stream, const VECTOR2<T>& vector );

/**
 * Class VECTOR2
 * defines a general 2D-vector/point.
 *
 * This class uses templates to be universal. Several operators are provided to help easy implementing
 * of linear algebra equations.
 *
 */
template <class T = int>
class VECTOR2 : public VECTOR2_TRAITS<T>
{
public:
    typedef typename VECTOR2_TRAITS<T>::extended_type extended_type;
    typedef T coord_type;

    T x, y;

    // Constructors

    /// Construct a 2D-vector with x, y = 0
    VECTOR2();

#ifdef WX_COMPATIBILITY
    /// Constructor with a wxPoint as argument
    VECTOR2( const wxPoint& aPoint );

    /// Constructor with a wxSize as argument
    VECTOR2( const wxSize& aSize );
#endif

    /// Construct a vector with given components x, y
    VECTOR2( T x, T y );

    /// Initializes a vector from another specialization. Beware of rouding
    /// issues.
    template <typename CastingType>
    VECTOR2( const VECTOR2<CastingType>& aVec )
    {
        x   = (T) aVec.x;
        y   = (T) aVec.y;
    }

    /// Casts a vector to another specialized subclass. Beware of rouding
    /// issues.
    template <typename CastedType>
    VECTOR2<CastedType> operator()() const
    {
        return VECTOR2<CastedType>( (CastedType) x, (CastedType) y );
    }

    /// Destructor
    // virtual ~VECTOR2();

    /**
     * Function Euclidean Norm
     * computes the Euclidean norm of the vector, which is defined as sqrt(x ** 2 + y ** 2).
     * It is used to calculate the length of the vector.
     * @return Scalar, the euclidean norm
     */
    T                   EuclideanNorm() const;

    /**
     * Function Perpendicular
     * computes the perpendicular vector
     * @return Perpendicular vector
     */
    VECTOR2<T>             Perpendicular() const;

    /**
     * Function LineProjection
     * computes the perpendicular projection point of self on a line
     * going through aA and aB points.
     * @return Projected point
     */
    VECTOR2<T>             LineProjection( const VECTOR2<T>& aA, const VECTOR2<T>& aB ) const;

    /**
     * Function LineSide
     * determines on which side of directed line passing via points aEnd
     * and a start aStart we are.
     * @return: < 0: left, 0 : on the line, > 0 : right
     */
    int                 LineSide( const VECTOR2<T>& aStart, const VECTOR2<T>& aEnd ) const;

    /**
     * Function LineDistance
     * returns the closest Euclidean distance to a line defined by points
     * aStart and aEnd.
     * @param aDetermineSide: when true, the sign of the returned value indicates
     * the side of the line at which we are (negative = left)
     * @return the distance
     */
    T                   LineDistance( const VECTOR2<T>& aStart, const VECTOR2<T>& aEnd, bool aDetermineSide = false ) const;

    /**
     * Function ClosestSegmentPoint
     * returns the closest point on a line segment defined by aStart and aEnd.
     * @return: our point
     */
    VECTOR2<T>             ClosestSegmentPoint( const VECTOR2<T>& aStart, const VECTOR2<T>& aEnd ) const;

    /**
     * Function Resize
     * returns a vector of the same direction, but length specified in aNewLength
     * @param aNewLength: length of the rescaled vector
     * @return rescaled vector
     */
    VECTOR2<T>             Resize( T aNewLength ) const;

    /**
     * Function Angle
     * computes the angle of the vector
     * @return vector angle, in radians
     */
    double              Angle() const;

    /**
     * Function Rotate
     * rotates the vector by a given angle
     * @param aAngle rotation angle in radians
     * @return rotated vector
     */
    VECTOR2<T>             Rotate( double aAngle ) const;

    /**
     * Function Format
     * returns the vector formatted as a string
     * @return the formatted string
     */
    const std::string   Format() const;

    /**
     * Function Cross()
     * computes cross product of self with aVector
     */
    extended_type       Cross( const VECTOR2<T>& aVector ) const;

    /**
     * Function Dot()
     * computes dot product of self with aVector
     */
    extended_type       Dot( const VECTOR2<T>& aVector ) const;


    // Operators

    /// Assignment operator
    VECTOR2<T>&            operator=( const VECTOR2<T>& aVector );

    /// Vector addition operator
    VECTOR2<T>             operator+( const VECTOR2<T>& aVector ) const;

    /// Compound assignment operator
    VECTOR2<T>&            operator+=( const VECTOR2<T>& aVector );

    /// Vector subtraction operator
    VECTOR2<T>             operator-( const VECTOR2<T>& aVector ) const;

    /// Compound assignment operator
    VECTOR2<T>&            operator-=( const VECTOR2<T>& aVector );

    /// Negate Vector operator
    VECTOR2<T>             operator-();

    /// Scalar product operator
    extended_type       operator*( const VECTOR2<T>& aVector ) const;

    /// Multiplication with a factor
    VECTOR2<T>             operator*( const T& aFactor ) const;

    /// Division with a factor
    VECTOR2<T>             operator/( const T& aFactor ) const;
    
    /// Equality operator
    const bool          operator==( const VECTOR2<T>& aVector ) const;

    /// Not equality operator
    const bool          operator!=( const VECTOR2<T>& aVector ) const;

    /// Smaller than operator
    bool                operator<( const VECTOR2<T>& aVector ) const;
    bool                operator<=( const VECTOR2<T>& aVector ) const;

    /// Greater than operator
    bool                operator>( const VECTOR2<T>& aVector ) const;
    bool                operator>=( const VECTOR2<T>& aVector ) const;

    friend std::ostream & operator<< <T> ( std::ostream & stream, const VECTOR2<T> &vector );
};


// ----------------------
// --- Implementation ---
// ----------------------

template <class T>
VECTOR2<T>::VECTOR2()
{
    x = y = 0.0;
}


#ifdef WX_COMPATIBILITY
template <class T>
VECTOR2<T>::VECTOR2( wxPoint const& aPoint )
{
    x   = T( aPoint.x );
    y   = T( aPoint.y );
}


template <class T>
VECTOR2<T>::VECTOR2( wxSize const& aSize )
{
    x   = T( aSize.x );
    y   = T( aSize.y );
}
#endif

template <class T>
VECTOR2<T>::VECTOR2( T aX, T aY )
{
    x   = aX;
    y   = aY;
}


template <class T>
T VECTOR2<T>::EuclideanNorm() const
{
    return sqrt( (extended_type) x * x + (extended_type) y * y );
}


template <class T>
double VECTOR2<T>::Angle() const
{
    return atan2( y, x );
}


template <class T>
VECTOR2<T> VECTOR2<T>::Perpendicular() const
{
    VECTOR2<T> perpendicular( -y, x );
    return perpendicular;
}


template <class T>
VECTOR2<T>& VECTOR2<T>::operator=( const VECTOR2<T>& aVector )
{
    x   = aVector.x;
    y   = aVector.y;
    return *this;
}


template <class T>
VECTOR2<T>& VECTOR2<T>::operator+=( const VECTOR2<T>& aVector )
{
    x   += aVector.x;
    y   += aVector.y;
    return *this;
}


template <class T>
VECTOR2<T>& VECTOR2<T>::operator-=( const VECTOR2<T>& aVector )
{
    x   -= aVector.x;
    y   -= aVector.y;
    return *this;
}


template <class T>
int VECTOR2<T>::LineSide( const VECTOR2<T>& aStart, const VECTOR2<T>& aEnd ) const
{
    VECTOR2<T>         d   = aEnd - aStart;
    VECTOR2<T>         ap  = *this - aStart;

    extended_type   det = (extended_type) d.x * (extended_type) ap.y
                          - (extended_type) d.y * (extended_type) ap.x;

    return det < 0 ? -1 : (det > 0 ? 1 : 0);
}


template <class T>
VECTOR2<T> VECTOR2<T>::LineProjection( const VECTOR2<T>& aA, const VECTOR2<T>& aB ) const
{
    const VECTOR2<T>   d = aB - aA;
    extended_type   det     = (extended_type) d.x * d.x + d.y * (extended_type) d.y;
    extended_type   dxdy    = (extended_type) d.x * d.y;
    extended_type   qx      =
        ( (extended_type) aA.x * d.y * d.y + (extended_type) d.x * d.x * x - dxdy *
          (aA.y - y) ) / det;
    extended_type   qy =
        ( (extended_type) aA.y * d.x * d.x + (extended_type) d.y * d.y * y - dxdy *
          (aA.x - x) ) / det;

    return VECTOR2<T> ( (T) qx, (T) qy );
}


template <class T>
T VECTOR2<T>::LineDistance( const VECTOR2<T>& aStart, const VECTOR2<T>& aEnd, bool aDetermineSide ) const
{
    extended_type   a   = aStart.y - aEnd.y;
    extended_type   b   = aEnd.x - aStart.x;
    extended_type   c   = -a * aStart.x - b * aStart.y;

    T dist = ( a * x + b * y + c ) / sqrt( a * a + b * b );
    return aDetermineSide ? dist : abs(dist);
}


template <class T>
VECTOR2<T> VECTOR2<T>::ClosestSegmentPoint( const VECTOR2<T>& aStart, const VECTOR2<T>& aEnd ) const
{
    VECTOR2<T>         d = (aEnd - aStart);
    extended_type   l_squared = (extended_type) d.x * d.x + (extended_type) d.y * d.y;


    if( l_squared == 0 )
    {
        return aStart;
    }

    extended_type t =
        (extended_type) (x - aStart.x) * (extended_type) d.x +
        (extended_type) (y - aStart.y) * (extended_type) d.y;

    if( t < 0 )
    {
        return aStart;
    }
    else if( t > l_squared )
    {
        return aEnd;
    }

    double xp = (double) t * (double) d.x / (double) l_squared;
    double yp = (double) t * (double) d.y / (double) l_squared;

    /*VECTOR2<T> proj = aStart + VECTOR2<T> ( ( t * (extended_type) d.x / l_squared ),
                                              ( t * ( extended_type) d.y / l_squared ) );*/

    VECTOR2<T> proj = aStart + VECTOR2<T> ( (T)xp, (T) yp );

    return proj;
}


template <class T>
VECTOR2<T> VECTOR2<T>::Rotate( double aAngle ) const
{
    double  sa  = sin( aAngle );
    double  ca  = cos( aAngle );

    return VECTOR2<T> ( T( (double) x * ca - (double) y * sa ),
                     T( (double) x * sa + (double) y * ca ) );
}


template <class T>
VECTOR2<T> VECTOR2<T>::Resize( T aNewLength ) const
{
    if( x == 0 && y == 0 )
        return VECTOR2<T> ( 0, 0 );

    T l = this->EuclideanNorm();

    return VECTOR2<T> (
        rescale( aNewLength, x, l ),
        rescale( aNewLength, y, l ) );
}


template <class T>
const std::string VECTOR2<T>::Format() const
{
    std::stringstream ss;

    ss << "( xy " << x << " " << y << " )";

    return ss.str();
}


template <class T>
VECTOR2<T> VECTOR2<T>::operator+( const VECTOR2<T>& aVector ) const
{
    return VECTOR2<T> ( x + aVector.x, y + aVector.y );
}


template <class T>
VECTOR2<T> VECTOR2<T>::operator-( const VECTOR2<T>& aVector ) const
{
    return VECTOR2<T> ( x - aVector.x, y - aVector.y );
}


template <class T>
VECTOR2<T> VECTOR2<T>::operator-()
{
    return VECTOR2<T> ( -x, -y );
}


template <class T>
typename VECTOR2<T>::extended_type VECTOR2<T>::operator*( const VECTOR2<T>& aVector ) const
{
    return aVector.x * x + aVector.y * y;
}


template <class T>
VECTOR2<T> VECTOR2<T>::operator*( const T& aFactor ) const
{
    VECTOR2<T> vector( x * aFactor, y * aFactor );
    return vector;
}


template <class T>
VECTOR2<T> VECTOR2<T>::operator/( const T& aFactor ) const
{
    VECTOR2<T> vector( x / aFactor, y / aFactor );
    return vector;
}


template <class T>
VECTOR2<T> operator*( const T& aFactor, const VECTOR2<T>& aVector )
{
    VECTOR2<T> vector( aVector.x * aFactor, aVector.y * aFactor );
    return vector;
}


template <class T>
typename VECTOR2<T>::extended_type VECTOR2<T>::Cross( const VECTOR2<T>& aVector ) const
{
    return (extended_type) x * (extended_type) aVector.y - 
           (extended_type) y * (extended_type) aVector.x;
}


template <class T>
typename VECTOR2<T>::extended_type VECTOR2<T>::Dot( const VECTOR2<T>& aVector ) const
{
    return (extended_type) x * (extended_type) aVector.x + 
           (extended_type) y * (extended_type) aVector.y;
}


template <class T>
bool VECTOR2<T>::operator<( const VECTOR2<T>& aVector ) const
{
    return ( *this * *this ) < ( aVector * aVector );
}


template <class T>
bool VECTOR2<T>::operator<=( const VECTOR2<T>& aVector ) const
{
    return ( *this * *this ) <= ( aVector * aVector );
}


template <class T>
bool VECTOR2<T>::operator>( const VECTOR2<T>& aVector ) const
{
    return ( *this * *this ) > ( aVector * aVector );
}


template <class T>
bool VECTOR2<T>::operator>=( const VECTOR2<T>& aVector ) const
{
    return ( *this * *this ) >= ( aVector * aVector );
}


template <class T>
bool const VECTOR2<T>::operator==( VECTOR2<T> const& aVector ) const
{
    return ( aVector.x == x ) && ( aVector.y == y );
}


template <class T>
bool const VECTOR2<T>::operator!=( VECTOR2<T> const& aVector ) const
{
    return ( aVector.x != x ) || ( aVector.y != y );
}


template <class T>
const VECTOR2<T> LexicographicalMax( const VECTOR2<T>& aA, const VECTOR2<T>& aB )
{
    if( aA.x > aB.x )
        return aA;
    else if( aA.x == aB.x && aA.y > aB.y )
        return aA;

    return aB;
}


template <class T>
const VECTOR2<T> LexicographicalMin( const VECTOR2<T>& aA, const VECTOR2<T>& aB )
{
    if( aA.x < aB.x )
        return aA;
    else if( aA.x == aB.x && aA.y < aB.y )
        return aA;

    return aB;
}


template <class T>
const int LexicographicalCompare( const VECTOR2<T>& aA, const VECTOR2<T>& aB )
{
    if( aA.x < aB.x )
        return -1;
    else if( aA.x > aB.x )
        return 1;
    else    // aA.x == aB.x
    {
        if( aA.y < aB.y )
            return -1;
        else if( aA.y > aB.y )
            return 1;
        else
            return 0;
    }
}


template <class T>
std::ostream& operator<<( std::ostream& aStream, const VECTOR2<T>& aVector )
{
    aStream << "[ " << aVector.x << " | " << aVector.y << " ]";
    return aStream;
}

/* Default specializations */
typedef VECTOR2<double>   VECTOR2D;
typedef VECTOR2<int>      VECTOR2I;

/* Compatibility typedefs */
// FIXME should be removed to avoid multiple typedefs for the same type
typedef VECTOR2<double>   DPOINT;
typedef DPOINT            DSIZE;

#endif    // VECTOR2D_H_