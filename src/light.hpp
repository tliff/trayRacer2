#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_
class Light
{
public:
	Light(){
		
	}
	Light (Vector3 _position) : position(_position)
	{
		
	};
	 ~Light ();

	Vector3 getPosition() const 
	{
		return position;
	}
	
	void setUp(std::multimap<std::string,std::string> m){
		std::multimap<std::string,std::string>::iterator result;
		result = m.find("position");
		if(result != m.end())
			position = Vector3::fromString(result->second);
	}
	

private:
	Vector3 position;
};


#endif /* _LIGHT_HPP_ */
