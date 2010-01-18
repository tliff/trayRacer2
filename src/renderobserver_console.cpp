#include "renderobserver_console.hpp"

#include <iostream>
#include <iomanip>

RenderObserverConsole::RenderObserverConsole()
 : RenderObserver()
{
	std::cout <<"\033[s" << std::flush;	
}


void RenderObserverConsole::reportProgress(long raysDone, long raysEstimated,
						int x, int y, int w, int h){
	std::cout <<"\033[1K\033[0E" <<std::flush;
	std::cout << std::setiosflags(std::ios::right)<<  std::setw(4) << std::setprecision(3) <<
			((float)raysDone / raysEstimated) * 100 
			<< std::setiosflags(std::ios::left)<< "% done at " <<
			  (raysDone / (timer.elapsed()*1000)) << "KRays/sec"<< std::flush;
}

void RenderObserverConsole::reportEnd(){
	std::cout << std::endl;
}

RenderObserverConsole::~RenderObserverConsole()
{
}




//TRAYRACER_PLUGIN_EXPORT("renderobserver", "console", RenderObserverConsole);
