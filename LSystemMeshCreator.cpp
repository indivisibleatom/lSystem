#include "precomp.h"
#include "LSystemMeshCreator.h"
#include "Mesh.h"
#include "utils.h"

std::unique_ptr<Mesh> LSystemMeshCreator::createMesh(const std::string& lSysString)
{
	m_turtle.reset();
	std::unique_ptr<Mesh> pMesh(new Mesh);
	
	for (std::string::const_iterator character = lSysString.cbegin(); character != lSysString.cend(); character++)
	{
		switch (*character)
		{
		//case 'F': Mesh* pCreatedMesh = createCylinderBlock(turtlePos);
		}
	}
	return pMesh;
}

std::unique_ptr<Mesh> LSystemMeshCreator::createCylinderBlock()
{
    std::unique_ptr<Mesh> pMesh(new Mesh);
	float cylRadius = 10;
	int cylResolution = 6;
	int cylLength = 5;

	Vector3 currentHeading = m_turtle.heading();
	Vector3 curLeft = m_turtle.left();
	Point3Df curPosition = m_turtle.position();
	Point3Df pointBorder(m_turtle.position(), cylRadius, curLeft);
	
	Vector3 centerToBorner(curPosition, pointBorder); 
	for (int i = 0; i < cylResolution; i++)
	{
		
	}

	m_turtle.translate(cylLength);
	return pMesh;
}


