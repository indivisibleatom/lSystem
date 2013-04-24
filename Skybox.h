#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "drawable.h"

class Skybox : public IDrawable
{
public:
	Skybox();
	void draw() const;
};

#endif//_SKYBOX_H_
