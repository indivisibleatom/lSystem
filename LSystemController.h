#ifndef _LSYTEMDRAWER_H_
#define _LSYTEMDRAWER_H_

#include "LSystemMeshCreator.h"

class LSystem;
class LSystemMeshCreator;
class Renderer;
class Mesh;

class LSystemController
{
private:
	std::unique_ptr<LSystem> m_pSystem;
	std::unique_ptr<LSystemMeshCreator> m_pMeshCreator;
	std::unique_ptr<Mesh> m_pMesh;

public:
	LSystemController(std::unique_ptr<LSystem> pSystem);
	void onUpdate();
	void onDraw();
};

#endif//_LSYTEMDRAWER_H_