#ifndef _RENDERER_H_
#define _RENDERER_H_

class IDrawable;

class Renderer
{
private:
	int m_bpp;
	std::tuple<int, int> m_screenSize;
public:
	Renderer(int screenX, int screenY, int bpp);
	bool init();
	bool draw(const IDrawable& drawable);
    //void applyTransFormation(const Matrix4& matrix)
};

#endif//_RENDERER_H_