#ifndef OUTPUTABLE_HPP
#define OUTPUTABLE_HPP

#include <iostream>
#include <string>

class Outputable{
public:
	virtual std::string str()const=0;
	friend std::ostream &operator<<(std::ostream &out, const Outputable &o );
	virtual ~Outputable(){};
};

#endif

