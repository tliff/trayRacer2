
#include <boost/archive/binary_oarchive.hpp>

#include <iostream>
#include <fstream>
#include <boost/serialization/export.hpp>
#include "../meshkd.hpp"

int main ( int argc, char *argv[] )
{
	if ( argc != 3 )
	{
		std::cout << "Usage: " << argv[0] << " input.obj output.trkd" << std::endl;
		exit ( 0 );
	}
	MeshKD mesh;
	mesh.loadObjFromFile(argv[1]);
	mesh.writeTRKD(argv[2]);
}
