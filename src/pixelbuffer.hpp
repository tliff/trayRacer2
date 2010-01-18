#ifndef _PIXELBUFFER_HPP_
#define _PIXELBUFFER_HPP_
#include <vector>

template <typename T> class PixelBuffer
{
public:
	PixelBuffer():
	    width(0),
	    height(0){}
	
	PixelBuffer (int _width, int _height) :
	    width(_width),
	    height(_height){
		buffer.resize(width*height);
	}
	virtual ~PixelBuffer (){
	}

	inline int getHeight() const
	{
		return height;
	}

	inline int getWidth() const
	{
		return width;
	}

	inline void resize(int _width, int _height){
		width = _width;
		height = _height;
		buffer.resize(width*height);
	}

	inline T getPixel(int x, int y) const
	{
		return(buffer[y*width+x]);
	}
	
	inline void setPixel(int x, int y, T c)
	{
		buffer[y*width+x] = c;
	}
	
	inline void setSample(){}; //FIXME

protected:
	int width, height;
  	std::vector<T> buffer;
};


#endif /* _PIXELBUFFER_HPP_ */
