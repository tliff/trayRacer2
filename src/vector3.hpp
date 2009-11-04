#ifndef __VECTOR3_H
#define __VECTOR3_H
#include "definitions.hpp"
#include <math.h>
#include <iostream>
#include <string>
#include <sstream>
#include <boost/tokenizer.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/lexical_cast.hpp>

#include "outputable.hpp"

typedef double vecType;

class Vector3 : public Outputable
{
	public:
		vecType x,y,z;

		Vector3() : x ( 0 ), y ( 0 ), z ( 0 ) {};
		Vector3 ( vecType _x, vecType _y, vecType _z )
		{
			x=_x; y=_y; z=_z;
		}

		void normalize()
		{
			vecType length=getLength();
			x/=length;
			y/=length;
			z/=length;
		}
		
		

		bool operator== ( const Vector3& b ) const
		{
			if ( fabs ( b.x - x ) < EPSILON && fabs ( b.y - y ) < EPSILON && fabs ( b.z - z ) < EPSILON )
				return true;
			return false;
		}

		vecType getLength() const
		{
			return sqrt ( x*x+y*y+z*z );
		}

		Vector3 operator+ ( const Vector3& other ) const
		{
			return Vector3 ( x+other.x,y+other.y,z+other.z );
		}

		Vector3 operator- ( const Vector3& b ) const
		{
			return Vector3 ( x-b.x,y-b.y,z-b.z );
		}

		Vector3 operator* ( const vecType& b ) const
		{
			return Vector3 ( b*x,b*y,b*z );
		}

		Vector3 operator/ ( const vecType& b ) const
		{
			return Vector3 ( x/b,y/b,z/b );
		}


		Vector3 operator+= ( const Vector3& other )
		{
			x+=other.x;
			y+=other.y;
			z+=other.z;
			return *this;
		}

		Vector3 operator-= ( const Vector3& b )
		{
			x-=b.x;
			y-=b.y;
			z-=b.z;
			return *this;
		}

		Vector3 operator*= ( const vecType& b )
		{
			x*=b;
			y*=b;
			z*=b;
			return *this;
		}

		Vector3 operator/= ( const vecType& b )
		{
			x/=b;
			y/=b;
			z/=b;
			return *this;
		}
		Vector3 cross ( const Vector3& b ) const
		{
			return Vector3 (	y * b.z - b.y * z,
			                 z * b.x - b.z * x,
			                 x * b.y - b.x * y );
		}

		vecType dot ( const Vector3& b ) const
		{
			return ( x * b.x ) + ( y * b.y ) + ( z * b.z );
		}

		static Vector3 fromString(std::string s){
			boost::char_separator<char> sep(" ");
			boost::tokenizer<boost::char_separator<char> > tokens(s, sep);
			boost::tokenizer<boost::char_separator<char> >::iterator it  =tokens.begin();
			vecType a =  boost::lexical_cast<vecType>(*(it++)); 
			vecType b =  boost::lexical_cast<vecType>(*(it++)); 
			vecType c =  boost::lexical_cast<vecType>(*(it++)); 

			return Vector3(a,b,c);
		}

		Vector3 getPolar() const{
			float r, phi, theta;
			r = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
			phi = atan2(y,x);
			theta = atan2(sqrt(pow(x,2)+pow(y,2)),z);
			return Vector3(r, phi, theta);
		}
		
		void setPolar(Vector3 polar){
			float r = polar.x;
			float phi = polar.y;
			float theta = polar.z;

			x = r * sin(theta) * cos(phi);
			y = r * sin(phi) * sin(theta);
			z = r * cos(theta);
		}

		std::string  str() const
		{
			std::stringstream ss;
			ss << "(" << ( fabs ( x ) < EPSILON ? 0 : x ) << ";" << ( fabs ( y ) < EPSILON ? 0 : y ) << ";" << ( fabs ( z ) < EPSILON ? 0 : z ) << ")";
			return ss.str();
		}
		template<class Archive>
		void serialize (Archive & ar,  const unsigned int version )
		{
			ar & x;
			ar & y;
			ar & z;
		}
};

#endif
