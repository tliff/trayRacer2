#include "sceneloader_sffile.hpp"
#include <fstream>
#include <iostream>

#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/loops.hpp>
#include <boost/spirit/iterator/file_iterator.hpp>
#include <boost/spirit/core.hpp>
#include <boost/spirit/utility/confix.hpp>
#include <boost/spirit/tree/parse_tree.hpp>
#include <boost/spirit/tree/tree_to_xml.hpp>
#include <boost/spirit/tree/ast.hpp>

#include <boost/spirit/utility/chset.hpp>

using namespace std;
using namespace boost;
using namespace boost::spirit;



Scene *s;

const std::string whiteSpaces ( " \f\n\r\t\v" );

void trimRight ( std::string& str,
                 const std::string& trimChars = whiteSpaces )
{
	std::string::size_type pos = str.find_last_not_of ( trimChars );
	str.erase ( pos + 1 );

}

void trimLeft ( std::string& str,
                const std::string& trimChars = whiteSpaces )
{
	std::string::size_type pos = str.find_first_not_of ( trimChars );
	str.erase ( 0, pos );

}

void trim ( std::string& str, const std::string& trimChars = whiteSpaces )
{
	trimRight ( str, trimChars );
	trimLeft ( str, trimChars );
}

void newArgument ( const file_iterator<char> first, const file_iterator<char> last )
{
     std::string str ( first, last );
     s->sceneBuilderNewArgument(str);
}

void newArgumentValue ( const file_iterator<char> first, const file_iterator<char> last )
{
     std::string str ( first, last );
     trim(str);
     s->sceneBuilderNewArgumentValue(str);
}

void newBlock ( const file_iterator<char> first, const file_iterator<char> last )
{
     std::string str ( first, last );
     s->sceneBuilderNewBlock(str);
}


struct sffile : public grammar<sffile>
{
	template <typename ScannerT>
	struct definition
	{

		definition ( sffile const& /*self*/ )
		{
			e_sffile
			=   * ( e_block| eol_p );

			e_block
			=  e_identifier[&newBlock] >> *space_p >> ch_p ( '{' ) >> e_blockbody >> ch_p ( '}' ) ;

			e_identifier
			= + ( alnum_p | ch_p ( '-' ) );

			e_blockbody
			=   * ( e_blockbodyline|eol_p );

			e_blockbodyline
			= 	*space_p >> e_argid[&newArgument] >> e_argvalue[&newArgumentValue];

			e_argid
			=	+ ( alnum_p | ch_p ( '-' ) );

			e_argvalue
			=   * ( anychar_p - eol_p ) >> eol_p;
		}
		
		rule<ScannerT>
		e_sffile, e_block, e_identifier, e_blockbody, e_argid, e_argvalue, e_blockbodyline
		;


		rule<ScannerT> const&
		start() const { return e_sffile; }
	};
};


bool SceneLoaderSFFile::loadSceneFromFile ( Scene* scene, std::string filename )
{

	s = scene;
	std::map<std::string, std::map<std::string, boost::any> > parsedTree;
	std::ifstream file ( filename.c_str() );
	if ( !file.is_open() )
	{
		std::cerr << "Couldn't load file " << filename << std::endl;
		return false;
	}

	file_iterator<char> start ( filename.c_str() );
	file_iterator<char> end = start.make_end();

	sffile g;
	boost::spirit::parse ( start, end,g ).full;
	scene->create();
	//std::cout <<"PARSERRESULT: "<< ( success ? "success" : "failure" ) << std::endl;

	return true;
}

TRAYRACER_PLUGIN_EXPORT ( "sceneloader", "sffile", SceneLoaderSFFile );
