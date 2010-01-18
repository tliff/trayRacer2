#ifndef __RENDERER_DEFAULT__
#define __RENDERER_DEFAULT__

#include <string>
#include <renderer.hpp>

class RendererDefault : public Renderer {
	protected:
		Scene* scene;
		Camera* camera;
		RenderSurface* surface;
		inline Color sampleDirection(const Ray& r, int depth=0);
		inline Color samplePixel(float x, float y);
		inline void renderBucket(int bx, int by);
		int debug;
	public:
		void render(Scene*, Camera*, RenderSurface*);
};


#endif
