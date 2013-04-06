#ifndef _LSYSTEMMESHCREATOR_H_
#define _LSYSTEMMESHCREATOR_H_

#include "Turtle.h"
#include "Mesh.h"

class LSystemMeshCreator
{
private:
	Turtle m_turtle; 
public:
	LSystemMeshCreator(){}

	std::unique_ptr<Mesh> createMesh(const std::string& lSysString);
	std::unique_ptr<Mesh> createCylinderBlock();
};

#endif//_LSYSTEMMESHCREATOR_H_