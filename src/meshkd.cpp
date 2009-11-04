#include <fstream>
#include <iostream>
#include <set>
#include "boost/lexical_cast.hpp"
#include "boost/regex.hpp"
#include "meshkd.hpp"
#include <stack>

BOOST_CLASS_EXPORT(MeshKDNode)

void MeshKDNode::addMeshKDTriangle ( MeshKDTriangle* t )
{
	if ( autoBBox )
	{
		bbox.addVector3 ( t->p0 );
		bbox.addVector3 ( t->p1 );
		bbox.addVector3 ( t->p2 );
	}
	MeshKDTriangleVector.push_back ( t );
}


void MeshKDNode::build ( SplitAxis axis )
{
	std::cout << "." <<std::flush;
	if ( getSize() > 50 )
	{
		this->axis = axis;
		double costForSplit;
		//std::cout << "looking for splitting plane " << std::flush;
		double split = findSplittingPlane ( axis, costForSplit );
// 		std::cout << "I contain " << MeshKDTriangleVector.size() << "MeshKDTriangles costing " << cost() << " split costs " << costForSplit<< std::endl;
		if ( cost() < costForSplit+0.01 ){
	//	std::cout << "Not splitting node with " << MeshKDTriangleVector.size() << " MeshKDTriangles. Cost for keep is " << cost() <<
	//			" best split is " << costForSplit << std::endl;
			return;
		}
		else {
	//		std::cout <<"Split accepted"<< std::endl;
		}
		BBox boxLeft (
		    Vector3 (
		        bbox.lowerBound.x,
		        bbox.lowerBound.y,
		        bbox.lowerBound.z ),
		    Vector3 (
		        ( axis == AXIS_X ) ? split : bbox.upperBound.x,
		        ( axis == AXIS_Y ) ? split : bbox.upperBound.y,
		        ( axis == AXIS_Z ) ? split : bbox.upperBound.z ) );
		BBox boxRight (
		    Vector3 (
		        ( axis == AXIS_X ) ? split : bbox.lowerBound.x,
		        ( axis == AXIS_Y ) ? split : bbox.lowerBound.y,
		        ( axis == AXIS_Z ) ? split : bbox.lowerBound.z ),
		    Vector3 (
		        bbox.upperBound.x,
		        bbox.upperBound.y,
		        bbox.upperBound.z ) );
		right = new MeshKDNode ( boxRight );
		left = new MeshKDNode ( boxLeft );
		ResultPosition res;
		while ( MeshKDTriangleVector.size() )
		{
			MeshKDTriangle* t = MeshKDTriangleVector[MeshKDTriangleVector.size()-1];
			MeshKDTriangleVector.pop_back();
			res = findMeshKDTrianglePosition ( t, split, axis );
			if ( res == LEFT ) left->addMeshKDTriangle ( t );
			if ( res == RIGHT ) right->addMeshKDTriangle ( t );
			if ( res == BOTH ) {left->addMeshKDTriangle ( t ); right->addMeshKDTriangle ( t );}

		}
#pragma omp parallel sections num_threads(2)
		{
#pragma omp section
			{
				if ( left ) left->build ( getNextAxis ( axis ) );
			}
#pragma omp section
			{
				if ( right ) right->build ( getNextAxis ( axis ) );
			}
		}
	}
}

BBox MeshKDNode::getBBox() const
{
	return bbox;
}
/*
bool MeshKDNode::intersect ( const Ray &ray, Intersection* intersection )
{
	if ( !left || !right )  //we are a leaf
	{
		bool foundSomething = false;
		for ( std::vector<MeshKDTriangle*>::iterator it = MeshKDTriangleVector.begin();
		        it != MeshKDTriangleVector.end();
		        ++it )
		{
			foundSomething = ( *it )->intersect ( ray, intersection ) || foundSomething;
		}
		return foundSomething;
	}
	else
	{
		//	Intersection tmpIntersection;
		double lefta=0, leftb=0, righta=0, rightb=0;
		bool hitLeft = left->bbox.intersect ( ray, lefta, leftb );
		bool hitRight = right->bbox.intersect ( ray, righta, rightb );
		if ( righta <= lefta )
		{
			if ( hitRight && right->intersect ( ray, intersection ) )
			{
				return true;
			}
			if ( hitLeft && left->intersect ( ray, intersection ) )
			{
				return true;
			}
		}
		else
		{
			if ( hitLeft && left->intersect ( ray, intersection ) )
			{
				return true;
			}
			if ( hitRight && right->intersect ( ray, intersection ) )
			{
				return true;
			}
		}
	}
	return false;

}
*/

bool MeshKDNode::intersect ( const Ray &ray, Intersection* intersection )
{
//	std::cout << "_____"<< std::endl;
	std::stack<MeshKDNode*> stack;
	
	MeshKDNode* current;
	stack.push(this);
	while(!stack.empty()){
		current = stack.top();
		stack.pop();
	/*	std::cout << current << std::endl;
		std::cout << current->left << current->right << std::endl;
		std::cout << current->MeshKDTriangleVector.size() << std::endl;
*/
		if(!current->left || !current->right){
			for ( std::vector<MeshKDTriangle*>::iterator it = current->MeshKDTriangleVector.begin();
			        it != current->MeshKDTriangleVector.end();
			        ++it )
			{
					( *it )->intersect ( ray, intersection );
			}
		}
		else{
			double lefta=0, leftb=0, righta=0, rightb=0;
			bool hitLeft = current->left->bbox.intersect ( ray, lefta, leftb );
			bool hitRight = current->right->bbox.intersect ( ray, righta, rightb );
			if(lefta > righta){
				if(hitLeft)stack.push(current->left);
				if(hitRight)stack.push(current->right);			
			}
			else{
				if(hitRight)stack.push(current->right);			
				if(hitLeft)stack.push(current->left);
			}
		}
	}

	if(intersection->distance != INFINITY)
		return true;
	return false;

}


SplitAxis MeshKDNode::getNextAxis ( SplitAxis s ) const
{
	switch ( s )
	{
		case AXIS_X: return AXIS_Y;
		case AXIS_Y: return AXIS_Z;
		case AXIS_Z: return AXIS_X;
		default:
		case AXIS_NONE: return AXIS_X;
	}
}
double MeshKDNode::findSplittingPlane ( SplitAxis a, double &costForSplit )
{
//	std::cout << "double MeshKDNode::findSplittingPlane ( SplitAxis a, double &costForSplit ) for "<< MeshKDTriangleVector.size() << std::endl;
	double bestSplitValue = 0;
	double bestCost = INFINITY;
//	std::cout << "BBox:" << bbox << std::endl;
	float ctraversal = 0;
	float cintersect = 1;
	std::set<float> splitPositions;

	for ( std::vector<MeshKDTriangle*>::iterator it = MeshKDTriangleVector.begin();
	        it != MeshKDTriangleVector.end();
	        ++it )
	{
		switch ( a )
		{
			case AXIS_X:
				if((*it)->p0.x > bbox.lowerBound.x && ((*it)->p0.x < bbox.upperBound.x))
					splitPositions.insert((*it)->p0.x);
				if((*it)->p1.x > bbox.lowerBound.x && ((*it)->p1.x < bbox.upperBound.x))
					splitPositions.insert((*it)->p1.x);
				if((*it)->p2.x > bbox.lowerBound.x && ((*it)->p2.x < bbox.upperBound.x))
					splitPositions.insert((*it)->p2.x);

				break;
			case AXIS_Y:
				if((*it)->p0.y > bbox.lowerBound.y && ((*it)->p0.y < bbox.upperBound.y))
					splitPositions.insert((*it)->p0.y);
				if((*it)->p1.y > bbox.lowerBound.y && ((*it)->p1.y < bbox.upperBound.y))
					splitPositions.insert((*it)->p1.y);
				if((*it)->p2.y > bbox.lowerBound.y && ((*it)->p2.y < bbox.upperBound.y))
					splitPositions.insert((*it)->p2.y);
				break;
			case AXIS_Z:
				if((*it)->p0.z > bbox.lowerBound.z && ((*it)->p0.z < bbox.upperBound.z))
					splitPositions.insert((*it)->p0.z);
				if((*it)->p1.z > bbox.lowerBound.z && ((*it)->p1.z < bbox.upperBound.z))
					splitPositions.insert((*it)->p1.z);
				if((*it)->p2.z > bbox.lowerBound.z && ((*it)->p2.z < bbox.upperBound.z))
					splitPositions.insert((*it)->p2.z);
				break;
			case AXIS_NONE:
				break;
		}
	}

//	std::cout << "Checking " << splitPositions.size() << " possible split positions )" << std::endl;
	long i = 0;
	for (std::set<float>::iterator it = splitPositions.begin();
		it != splitPositions.end();
		++it)
	{
		if(rand()%(int)splitPositions.size() > 5000)
			continue;
		//std::cout << "."<<std::flush;
		double splitValue=*it;

		double leftArea = fabs (
		                      ( ( ( a == AXIS_X ) ? splitValue: bbox.upperBound.x ) -  bbox.lowerBound.x ) *
		                      ( ( ( a == AXIS_Y ) ? splitValue: bbox.upperBound.y ) -  bbox.lowerBound.y ) *
		                      ( ( ( a == AXIS_Z ) ? splitValue: bbox.upperBound.z ) -  bbox.lowerBound.z ) );

		double rightArea = fabs (
		                       ( bbox.upperBound.x - ( ( a==AXIS_X ) ? splitValue : bbox.lowerBound.x ) ) *
		                       ( bbox.upperBound.y - ( ( a==AXIS_Y ) ? splitValue : bbox.lowerBound.y ) ) *
		                       ( bbox.upperBound.z - ( ( a==AXIS_Z ) ? splitValue : bbox.lowerBound.z ) ) );

		int countLeft = 0;
		int countRight = 0;
		/*
		for ( std::vector<MeshKDTriangle*>::iterator it = MeshKDTriangleVector.begin();
		        it != MeshKDTriangleVector.end();
		        ++it )
		{
			MeshKDTriangle* t = *it;
			ResultPosition res = findMeshKDTrianglePosition ( t, splitValue, axis );
			if ( res == LEFT ) countLeft++;
			if ( res == RIGHT ) countRight++;
			if ( res == BOTH ) {countLeft++; countRight++;}
		}
		*/
		int limit = std::min((int)MeshKDTriangleVector.size(), 3000);
		double factor = MeshKDTriangleVector.size() /(double)limit;
		//std::cout << "estimating with " << limit<< " factor:" << factor<<std::endl;
		for(int j = 0; j < limit; j++){
			//std::cout <<":"<<std::flush;
			int size = MeshKDTriangleVector.size();
			int index = rand()%size;
			MeshKDTriangle* t = MeshKDTriangleVector[index];
			ResultPosition res = findMeshKDTrianglePosition ( t, splitValue, axis );
			if ( res == LEFT ) countLeft++;
			if ( res == RIGHT ) countRight++;
			if ( res == BOTH ) {countLeft++; countRight++;}
		}
		//std::cout << countLeft << "/" << countRight << std::endl;
		countLeft *= factor;
		countRight *=factor;
		//std::cout << countLeft << "/" << countRight << std::endl;
		float cost = ctraversal + leftArea * countLeft * cintersect +
		             ctraversal + rightArea * countRight * cintersect;
			//	std::cout << bestCost << ":" <<cost << std::endl;
		if ( cost < bestCost )
		{
		//	std::cout << "FOUND SOMETHING" << std::endl;
		//	std::cout << "COST right: " << rightArea <<"*" <<countRight << "   left: " << leftArea<<"*"<<countLeft<<std::endl;
			bestCost = cost;
			bestSplitValue = splitValue;
		}
		if((i%2000)==0)
			;//std::cout << i <<"  checked" <<std::endl;
		else
			;//std::cout << "x" <<std::flush;
		i++;
	}
/*	std::cout << "Proposing split on ";
	switch ( a )
	{
		case AXIS_X:
			std::cout << "x:";
			break;
		case AXIS_Y:
			std::cout << "y:";
			break;
		case AXIS_Z:
			std::cout << "z:";
			break;
	}
	std::cout << bestSplitValue << " for " << bbox <<std::endl;*/
	costForSplit = bestCost;
	//std::cout << "ENDENDEDNEDNEND" << std::endl;
	return bestSplitValue;
}

ResultPosition MeshKDNode::findMeshKDTrianglePosition (
    MeshKDTriangle* t,
    double split,
    SplitAxis splitAxis ) const
{
	bool inLeft = false, inRight = false;
	switch ( splitAxis )
	{
		case AXIS_X:
			inLeft = ( t->p0.x <= split ) || ( t->p1.x <= split ) || ( t->p2.x <= split );
			break;
		case AXIS_Y:
			inLeft = ( t->p0.y <= split ) || ( t->p1.y <= split ) || ( t->p2.y <= split );
			break;
		case AXIS_Z:
			inLeft = ( t->p0.z <= split ) || ( t->p1.z <= split ) || ( t->p2.z <= split );
			break;
		case AXIS_NONE:
			break;

	}
	switch ( splitAxis )
	{
		case AXIS_X:
			inRight = ( t->p0.x > split ) || ( t->p1.x > split ) || ( t->p2.x > split );
			break;
		case AXIS_Y:
			inRight = ( t->p0.y > split ) || ( t->p1.y > split ) || ( t->p2.y > split );
			break;
		case AXIS_Z:
			inRight = ( t->p0.z > split ) || ( t->p1.z > split ) || ( t->p2.z > split );
			break;
		case AXIS_NONE:
			break;

	}
	if ( inLeft && inRight ) return BOTH;
	if ( inLeft ) return LEFT;
	if ( inRight ) return RIGHT;
	else return NONE;
}

bool MeshKD::loadObjFromFile ( std::string filename )
{
	std::vector<Vector3> vectorVector; // SCNR
	std::vector<Vector3> normalVector;
	std::cout << "reading " << filename << std::endl;
	std::ifstream file ( filename.c_str() );
	if ( !file.is_open() )
	{
		std::cerr << "Couldn't load mesh " << filename << std::endl;
		return false;
	}
	//build regexes
	boost::regex vexp ( "^v\\s+(.*?)\\s+(.*?)\\s+(.*?)$" );
	boost::regex fexp ( "^f\\s+(.*?)\\s+(.*?)\\s+(.*?)$" );

	boost::cmatch match;
	char line[1024];
	while ( !file.eof() )
	{
		file.getline ( line,1024 );
//		std::cout << line << std::endl;
		if ( boost::regex_match ( line, match, vexp ) )
		{
			Vector3 v = Vector3 ( boost::lexical_cast<double> ( match[1] ),
			                      boost::lexical_cast<double> ( match[2] ),
			                      boost::lexical_cast<double> ( match[3] ) );
			vectorVector.push_back ( v );

		}
		else if ( boost::regex_match ( line, match, fexp ) )
		{
			Vector3 a, b, c;
			int vectorSize = vectorVector.size();
			if ( boost::lexical_cast<int> ( match[1] ) < 0 )
				a = vectorVector[vectorSize + boost::lexical_cast<int> ( match[1] ) ];
			if ( boost::lexical_cast<int> ( match[1] ) > 0 )
				a = vectorVector[boost::lexical_cast<int> ( match[1] )-1];
			if ( boost::lexical_cast<int> ( match[2] ) < 0 )
				b = vectorVector[vectorSize + boost::lexical_cast<int> ( match[2] ) ];
			if ( boost::lexical_cast<int> ( match[2] ) > 0 )
				b = vectorVector[boost::lexical_cast<int> ( match[2] )-1];
			if ( boost::lexical_cast<int> ( match[3] ) < 0 )
				c = vectorVector[vectorSize + boost::lexical_cast<int> ( match[3] ) ];
			if ( boost::lexical_cast<int> ( match[3] ) > 0 )
				c = vectorVector[boost::lexical_cast<int> ( match[3] )-1];
			tree.addMeshKDTriangle ( new MeshKDTriangle ( a,b,c ) );
		}
	}
	/*
	std::cout << "Finished reading" << std::endl;
	std::cout << "Loaded " << ( unsigned int ) tris.size() << " faces" << std::endl;
	std::cout << "Building tree" << std::endl;
	std::cout << "Finished building tree" << std::endl;
	tris.dump();
	oa <<const_cast<const OctreeNode&> ( tris );*/
	this->boundingBoxComputed = true;
	std::cout << "Building tree" << std::endl;
	tree.build ( AXIS_X );
	std::cout << "Finished building tree" << std::endl;
	std::cout << "Tree countains " << tree.getMeshKDTriangleCount() << " tris" << std::endl;
	return true;

}

bool MeshKD::intersect ( const Ray &ray, Intersection* intersection )
{
	if ( !this->getBBox().intersect ( ray ) )
		return false;
	bool gotHit = tree.intersect ( ray,intersection );
	intersection->shape = this;
	return gotHit;
}

bool MeshKD::doesIntersect ( const Ray &ray )
{
	return intersect ( ray, NULL );
}


MeshKD::MeshKD ( std::string filename )
{
	//loadObjFromFile ( filename );
	loadTRKD(filename);
}


MeshKD::~MeshKD()
{
	for ( std::vector<MeshKDTriangle*>::iterator it = MeshKDTriangleVector.begin();
	        it != MeshKDTriangleVector.end();
	        ++it )
	{
		delete *it;
	}
}

std::string MeshKD::str() const
{
	return std::string ( "Mesh" );
}

