#ifndef __MESHKD_HPP__
#define __MESHKD_HPP__
#include <iostream>
#include <fstream>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/serialization.hpp>

#include <boost/serialization/tracking.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/export.hpp>

#include <set> //FIXME: debug only

#include "vector3.hpp"
#include "shape.hpp"
#include "string"

#define KD_TRY_COUNT 50

enum SplitAxis
{
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
	AXIS_NONE,
};

enum ResultPosition
{
	LEFT,
	RIGHT,
	BOTH,
	NONE //this should never happen
};


class MeshKDTriangle{
		friend class boost::serialization::access;
public:
  Vector3 p0, p1, p2;
  Vector3 normal;
	MeshKDTriangle(){};
  MeshKDTriangle(Vector3 _p0, Vector3 _p1, Vector3 _p2) : p0(_p0),
						    p1(_p1),
						    p2(_p2){
    normal = (p2-p1).cross(p0-p1);
    normal.normalize();
  };
  std::string str() const;
inline bool intersect(const Ray &ray,
				Intersection* intersection){
  Vector3 tvec, pvec, qvec;
  double det,inv_det;
  double t, u, v, w;

  // find vectors for two edges sharing vert0 
  const Vector3 edge1 = p1 - p0;
  const Vector3 edge2 = p2 - p0;

  // begin calculating determinant - also used to calculate U parameter
  pvec = ray.direction.cross(edge2);

  // if determinant is near zero, ray lies in plane of MeshKDTriangle
  det = edge1.dot(pvec);

 /* if (det > -EPSILON && det < EPSILON)
    return false;*/
  inv_det = 1.0 / det;

  // calculate distance from vert0 to ray origin
  tvec = ray.origin - p0;

  // calculate U parameter and test bounds

  u = tvec.dot(pvec) * inv_det;
  if (u < 0.0 || u > (1.0 + EPSILON))
    return false;

  // prepare to test V parameter
  qvec = tvec.cross(edge1);

  // calculate V parameter and test bounds
  v = ray.direction.dot(qvec) * inv_det;
  if (v < 0.0 || u + v > (1.0+EPSILON))
    return false;

  w = (1.0 +EPSILON) - ( u + v);

  // calculate t, ray intersects MeshKDTriangle
  t = edge2.dot(qvec) * inv_det;
  if(t < 0) 
	  return false;
  //std::cout << "Tri intersected" << std::endl;
  if(t > intersection->distance)
	  return false;
  if(intersection == NULL)
    return true;


  if(normal.dot(ray.direction) > 0)
	normal = normal * -1;

  intersection->point = ray.origin + ray.direction*t;
  intersection->distance = t;
  intersection->normal = normal;

return true;
};

		template<class Archive>
		void serialize (Archive & ar,  const unsigned int version )
		{
			ar & p0;
			ar & p1;
			ar & p2;
			ar & normal;
		}

};

class MeshKDNode
{
		friend class boost::serialization::access;
	protected:
		BBox bbox;

		MeshKDNode *left, *right;
		SplitAxis axis;
		bool autoBBox;
		std::vector<MeshKDTriangle*> MeshKDTriangleVector;
		SplitAxis getNextAxis ( SplitAxis s ) const;
		double findSplittingPlane ( SplitAxis a, double &costForSplit  );
		ResultPosition findMeshKDTrianglePosition ( MeshKDTriangle* t, double splitValue, SplitAxis splitAxis ) const;
		template<class Archive>
		void serialize ( Archive & ar,  const unsigned int version )
		{
			ar & bbox;
			ar & autoBBox;
			ar & left;
			ar & right;
			ar & axis;
			ar & MeshKDTriangleVector;
		}
	public:
		MeshKDNode() :
				bbox ( BBox ( Vector3 ( INFINITY,INFINITY,INFINITY ),
				              Vector3 ( NEGINFINITY,NEGINFINITY,NEGINFINITY ) ) ),
				left ( NULL ),
				right ( NULL ),
				axis ( AXIS_NONE ),
				autoBBox ( true )
		{
		};

		MeshKDNode ( BBox b ) :
				bbox ( b ),
				left ( NULL ),
				right ( NULL ),
				axis ( AXIS_NONE ),
				autoBBox ( false )
		{
		};

		float cost()
		{
 			return area() * MeshKDTriangleVector.size();
		}
		
		float area()
		{
			return ( bbox.upperBound.x - bbox.lowerBound.x ) *
			       ( bbox.upperBound.y - bbox.lowerBound.y ) *
				( bbox.upperBound.z - bbox.lowerBound.z );
		}

		long getMeshKDTriangleCount()
		{
			long count = this->getSize();
			if ( left ) count += left->getMeshKDTriangleCount();
			if ( right ) count += right->getMeshKDTriangleCount();
			return count;
		}

		void addMeshKDTriangle ( MeshKDTriangle* t );
		void build ( SplitAxis axis );

		long getSize() { return MeshKDTriangleVector.size();}

		virtual bool intersect ( const Ray &ray, Intersection* intersection );

		void collectMeshKDTriangles(std::vector<MeshKDTriangle*> &ov){
	//		std::cout <<"size:" <<  ov.size() << std::endl;
			if(MeshKDTriangleVector.size() >0){
				for(std::vector<MeshKDTriangle*>::iterator it = MeshKDTriangleVector.begin();
				it != MeshKDTriangleVector.end();
				++it
				){
				//	std::cout <<".";
					ov.push_back(*it);
				}
			}
			else{
				if(left)left->collectMeshKDTriangles(ov);
				if(right)right->collectMeshKDTriangles(ov);
			}
		}

		void dump(int depth = 0){
/*			//std::cout << "<node>" << std::endl;
			if(MeshKDTriangleVector.size() >0){
				std::cout << MeshKDTriangleVector.size() << std::endl;
				for(std::vector<MeshKDTriangle*>::iterator it = MeshKDTriangleVector.begin();
				it != MeshKDTriangleVector.end();
				++it
					)
					std::cout << **it << std::endl;
			}
			else{
				if(left)left->dump(depth+1);
				if(right)right->dump(depth+1);
			}
			//std::cout << "</node>" << std::endl;*/
		}

		virtual BBox getBBox() const;

		virtual ~MeshKDNode() {}

		friend class MeshKD;
};

class MeshKD : public Shape
{
		friend class boost::serialization::access;
	protected:
/*		template<class Archive>
		void serialize ( Archive & ar,  const unsigned int version )
		{
			ar & boost::serialization::base_object<Shape> ( *this );
			ar & tree;
		}*/
		std::vector<MeshKDTriangle*> MeshKDTriangleVector;
		MeshKDNode tree;
	public:
		MeshKD ( std::string );

		MeshKD() {};

		~MeshKD();

		bool loadObjFromFile ( std::string filename );
		
		bool writeTRKD(std::string filename){
			std::ofstream ofs (filename.c_str() );
			boost::archive::binary_oarchive oa ( ofs );
			oa << tree;
			ofs.close();
			return true;
		}
		
		bool loadTRKD(std::string filename){
			std::ifstream ifs (filename.c_str() );
			boost::archive::binary_iarchive ia ( ifs );
			ia >> tree;
		//	dump();
			ifs.close();
			std::cout << getBBox() << std::endl;
			return true;
		}

		virtual bool intersect ( const Ray &ray,
		                         Intersection* intersection );
		virtual bool doesIntersect ( const Ray &ray );

		virtual void computeBoundingBox() {};

		virtual std::string str() const;


		void setUp(std::multimap<std::string,std::string> m){
			std::multimap<std::string,std::string>::iterator result;
			result = m.find("file");
			if(result != m.end())
				loadTRKD(result->second);
		}
		
		void dump(){
			std::cout << std::endl;
			std::vector<MeshKDTriangle*> tris;
			tree.collectMeshKDTriangles(tris);
			int v = -2;
			for(std::vector<MeshKDTriangle*>::iterator it = tris.begin();
				it != tris.end();
				++it){
				std::cout << "MARKv " << (*it)->p0.x << " "<< (*it)->p0.y << " "<< (*it)->p0.z << v++ << std::endl;
				std::cout << "MARKv " << (*it)->p1.x << " "<< (*it)->p1.y << " "<< (*it)->p1.z << v++ << std::endl;
				std::cout << "MARKv " << (*it)->p2.x << " "<< (*it)->p2.y << " "<< (*it)->p2.z << v++ << std::endl;
				std::cout << "MARKf " << v << " " << (v+2)<< " " << (v+1) << std::endl;
				//v+=3;
			}
		}

		virtual BBox& getBBox()
		{
			return tree.bbox;
		}

};

//BOOST_CLASS_TRACKING ( MeshKD , 0 )
BOOST_CLASS_TRACKING ( MeshKDNode , 0 )

#endif
