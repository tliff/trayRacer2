#ifndef __MATH_MATRIX44_HPP
#define __MATH_MATRIX44_HPP

#include "../outputable.hpp"

class Matrix44 : public Outputable
 {
public:
    double m[16];	
    
    Matrix44(double f00, double f10, double f20, double f30,
	     double f01, double f11, double f21, double f31,
	     double f02, double f12, double f22, double f32,
	     double f03, double f13, double f23, double f33){
	m[0]=f00;  m[1]=f10;  m[2]=f20;  m[3]=f30;
	m[4]=f01;  m[5]=f11;  m[6]=f21;  m[7]=f31;
	m[8]=f02;  m[9]=f12;  m[10]=f22; m[11]=f32;
	m[12]=f03; m[13]=f13; m[14]=f23; m[15]=f33;
    }

/*    Matrix44(Vector4 &a, Vector4 &b, Vector4 &c, Vector4 &d){
	m[0]=a.x;  m[1]=b.x;  m[2]=c.x;  m[3]=d.x;
	m[4]=a.y;  m[5]=b.y;  m[6]=c.y;  m[7]=d.y;
	m[8]=a.z;  m[9]=b.z;  m[10]=c.z; m[11]=d.z;
	m[12]=a.w; m[13]=b.w; m[14]=c.w; m[15]=d.w;
    }*/
    
    Matrix44(){
    }
    
    Matrix44(const Matrix44& a){
	for(int i=0; i< 16; i++)
	    m[i] = a.m[i];
    }
   
/* 
    void setRow(int i, Vector4& v){
	m[i*4+0]=v.x;
	m[i*4+1]=v.y;
	m[i*4+2]=v.z;
	m[i*4+3]=v.w;
    }*/
    
    void operator=(const Matrix44& b){
	for(int i=0; i < 16; i++)
	    m[i] = b.m[i];
    }
    
/*
    Vector4 getRow(int i){
	return Vector4(m[i*4+0],m[i*4+1],m[i*4+2],m[i*4+3]);
    }*/
    
    bool operator==(const Matrix44 &b){
	for(int i=0; i<16; i++){
	    if(fabs(b.m[i] - m[i]) > EPSILON)
		return false;
	}
	return true;
    }
    
    Vector3 operator*(const Vector3 &v){
	double invW = 1/(v.x * m[12] + v.y * m[13] + v.z * m[14] + m[15]);
	return Vector3( (v.x * m[0] + v.y * m[1] + v.z * m[2] + m[3])*invW,
			(v.x * m[4] + v.y * m[5] + v.z * m[6] + m[7])*invW,
			(v.x * m[8] + v.y * m[9] + v.z * m[10] + m[11])*invW);
	
    }
    
    void operator*(const double d){
	for(int i=0; i < 16;i++)
	    m[i]*=d;
    }
    
    Matrix44 operator*(const Matrix44 &b){
	Matrix44 r;
	for(int k = 0; k < 4; k++){
	    for(int i = 0; i < 4; i++){
		double val = 0;
		for(int j = 0; j < 4; j++){
		    val+=m[i*4+j]*b.m[j*4+k];
		}
		r.m[i*4+k]=val;
	    }
	}
	return r;
    }
    
    double det(){
	return	m[0]*m[5]*m[10]*m[15]-
	    m[0]*m[5]*m[11]*m[14]+
	    m[0]*m[9]*m[14]*m[7]-
	    m[0]*m[9]*m[6]*m[15]+
	    m[0]*m[13]*m[6]*m[11]-
	    m[0]*m[13]*m[10]*m[7]-
	    m[4]*m[1]*m[10]*m[15]+
	    m[4]*m[1]*m[11]*m[14]-
	    m[4]*m[9]*m[14]*m[3]+
	    m[4]*m[9]*m[2]*m[15]-
	    m[4]*m[13]*m[2]*m[11]+
	    m[4]*m[13]*m[10]*m[3]+
	    m[8]*m[1]*m[6]*m[15]-
	    m[8]*m[1]*m[14]*m[7]+
	    m[8]*m[5]*m[14]*m[3]-
	    m[8]*m[5]*m[2]*m[15]+
	    m[8]*m[13]*m[2]*m[7]-
	    m[8]*m[13]*m[6]*m[3]-
	    m[12]*m[1]*m[6]*m[11]+
	    m[12]*m[1]*m[10]*m[7]-
	    m[12]*m[5]*m[10]*m[3]+
	    m[12]*m[5]*m[2]*m[11]-
	    m[12]*m[9]*m[2]*m[7]+
	    m[12]*m[9]*m[6]*m[3];
	
    }
    
    Matrix44 trans(){
	return Matrix44(m[0],m[4],m[8],m[12],
			m[1],m[5],m[9],m[13],
			m[2],m[6],m[10],m[14],
			m[3],m[7],m[11],m[15]);
    }
    
    double cofactor(int col, int row){
	double mm[9];
	int ri=0;
	for(int i=0; i < 16; i++)
	    if(i/4 != row && i%4 != col)
		mm[ri++]=m[i];
	
	double cf =(mm[0]*mm[4]*mm[8]+
		    mm[1]*mm[5]*mm[6]+
		    mm[2]*mm[3]*mm[7]-(
			mm[6]*mm[4]*mm[2]+
			mm[7]*mm[5]*mm[0]+
			mm[8]*mm[3]*mm[1]))*pow(-1.0,col+row);
	return cf;
    }
    
    Matrix44 adjoint(){
	Matrix44 a;
	for(int i=0; i<4; i++){
	    for(int j=0; j<4; j++){
		a.m[i+j*4]=cofactor(j,i);
	    }
	}
	return a;
    }
    
    void invert(){
	double d = this->det();
	*this = adjoint();
	this->operator *(1/d);
    }
    
    std::string str() const{
	std::stringstream ss;
	for(int i = 0; i < 4; i++){
	    ss << (float)m[4*i+0] << "   " << 
		(float)m[4*i+1] << "   " << 
		(float)m[4*i+2] << "   " << 
		(float)m[4*i+3] << std::endl;
	}
	return ss.str();
    }
    
		static Matrix44 translation(const double x, const double y, const double z){
			return Matrix44(
				1, 0, 0, -x,
				0, 1, 0, -y,
				0, 0, 1, -z,
				0, 0, 0, 1
			);
		}
		static Matrix44 translation(const Vector3 &v){
			return Matrix44(
				1, 0, 0, -(v.x),
				0, 1, 0, -(v.y),
				0, 0, 1, -(v.z),
				0, 0, 0, 1
			);
		}
		
		static Matrix44 rotation(const Vector3 &n){
			Vector3 a;
			float x;
			do{
				x = (float)(rand())/RAND_MAX;
				a = Vector3(x + 10, x-100, x);
			}while(a.dot(n) == 1);
			Vector3 u = n.cross(a);
			Vector3 v = n.cross(u);
			u.normalize();
			v.normalize();
			
			return Matrix44(
				u.x, v.x, n.x, 0,
				u.y, v.y, n.y, 0,
				u.z, v.z, n.z, 0,
				0, 0, 0, 1				
				);
		}

		//rotation
		//shearing?

		static Matrix44 lookAt(const Vector3 &pos, const Vector3 &at, const Vector3 &up){
// 			std::cout <<  pos << at << std::endl;
			Vector3 zaxis = pos - at;
// 			std::cout << "DIFFE " << zaxis << std::endl;
			zaxis.normalize();
// 			std::cout << "ZAXIS " << zaxis << std::endl;
			Vector3 xaxis = zaxis.cross(up);
			xaxis.normalize();
			Vector3 yaxis = xaxis.cross(zaxis);

	//		std::cout << "Coordinate axis(ZxX=Y):"<< zaxis << "x" << xaxis << "=" <<  yaxis << std::endl;

			return Matrix44(
					xaxis.x, yaxis.x, -zaxis.x, pos.x,
					xaxis.y, yaxis.y, -zaxis.y, pos.y,
					xaxis.z, yaxis.z, -zaxis.z, pos.z,
					0, 0, 0, 1
			    );	
		    }
		};

#endif

