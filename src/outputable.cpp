#include "outputable.hpp"

std::ostream& operator <<(std::ostream &os,const Outputable &obj)
{
      os<<obj.str();
      return os;
}
