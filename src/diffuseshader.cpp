#include "diffuseshader.hpp"

DiffuseShader::~DiffuseShader()
{
}


Color DiffuseShader::getRadiance ( Scene* scene, Intersection *i )
{
	float lighting = 0;
	for ( std::vector<Light*>::iterator it = scene->lightList.begin();
	        it != scene->lightList.end();
	        it++ )
	{
		if ( scene->canSee ( i->point, ( *it )->getPosition() ) )
		{
			lighting+= ( i->point- ( *it )->getPosition() ).dot ( ( i->normal*-1 ) );
		}
	}
	lighting = lighting < 0 ? 0: lighting;
	return Color ( lighting,lighting,lighting );
}
