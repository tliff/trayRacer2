#include "renderer_default.hpp"
#include "sampler.hpp"

#define BUCKETWIDTH 16
#define BUCKETHEIGHT 16
#define SAMPLES 1024

void RendererDefault::render ( Scene* scene, Camera* camera, RenderSurface* surface )
{
	setObserverSurface ( surface );
	reportStart();
	//for every point on the surface shoot a ray
	this->scene = scene;
	this->camera = camera;
	this->surface = surface;
	int width = surface->getWidth();
	int height = surface->getHeight();
	raysEstimated = width * height * SAMPLES*2;
	
	const int xBuckets = width / BUCKETWIDTH + ((width % BUCKETWIDTH) ? 1 : 0);
	const int yBuckets = height / BUCKETHEIGHT + ((height % BUCKETHEIGHT) ? 1 : 0);


	std::cout << (xBuckets*yBuckets) << " buckets to render"<<std::endl;
	#pragma omp parallel num_threads(2)
	{
		#pragma omp for
		for(int i = 0; i < yBuckets * xBuckets; i++){
				renderBucket(i%yBuckets, i/yBuckets);
				#pragma omp critical
				reportProgress((i%yBuckets)*BUCKETWIDTH, (i/yBuckets)*BUCKETHEIGHT,BUCKETWIDTH,BUCKETHEIGHT);
		}
	}
	
	reportEnd();
}

void RendererDefault::renderBucket(int bx, int by){
	for(int x = bx*BUCKETWIDTH; x < std::min(bx*BUCKETWIDTH+BUCKETWIDTH, surface->getWidth()); x++){
		for(int y = by*BUCKETHEIGHT; y < std::min(by*BUCKETHEIGHT+BUCKETHEIGHT, surface->getHeight()); y++){
			Color c;
			for(int i = 0; i < SAMPLES; i++){
				c = c + samplePixel(x,y);
			}
			surface->setPixel(x,y, c);
		}
	}
}

inline Color RendererDefault::samplePixel(float x, float y){
	//std::cout << std::endl <<"est:" << raysEstimated << "  done:"<<raysDone << std::flush;
	x +=(((float)rand())/RAND_MAX)-0.5;
	y +=(((float)rand())/RAND_MAX)-0.5;
	float fx = ( float ) x/ ( float ) surface->getWidth();
	float fy = ( float ) y/ ( float ) surface->getHeight();
	Ray viewRay = camera->constructViewRay ( fx, fy );
	return sampleDirection(viewRay);
}

inline Color RendererDefault::sampleDirection(const Ray& r, int depth){
	//std::cout << "." << std::flush;
	//std::cout << std::endl << std::endl;
	//std::cout << std::endl << "|" << std::flush;
	if(depth > 50)
		return Color(0,0,10);
	Intersection tmp;
	Intersection* i = &tmp;

	Ray newRay = r;
	float cost = 1;
	int iterations =0;
	//std::cout <<"-----------"<< std::endl;
	while(true){
		raysDone += 1;
		i->distance = INFINITY;
		//std::cout << "." << std::flush
		//std::cout << newRay << std::endl;
		
		if(iterations == 100){
			std::cout << "CHECKMECHECKMECHECKME" << std::endl;
			return Color(1000,1000,0);

		}
		if(iterations++ > 50)
			return Color(0,0,0);
		//std::cout << newRay << std::endl;
		scene->getIntersection (newRay, i );
		if ( i->distance != INFINITY && i->shape != NULL )
		{
			//std::cout << "hit" << std::endl;
			cost *= newRay.direction.dot(i->normal*-1);	
		}
		else{
			return scene->getBackground(newRay.direction)*cost;
		}	
		//std::cout << i->point << "+" << (i->normal*0.01) << std::endl;
		newRay = Ray(i->point+(i->normal*0.0001), Sampler::randomHemisphere(i->normal));
	}
}


TRAYRACER_PLUGIN_EXPORT ( "renderer", "default", RendererDefault );
