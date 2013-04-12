#include "precomp.h"
#include "LSystemController.h"
#include "LSystemMeshCreator.h"
#include "LSystem.h"
#include "Mesh.h"
#include "Renderer.h"

LSystemController::LSystemController(std::unique_ptr<LSystem> pSystem, Renderer& renderer) : m_pSystem(std::move(pSystem)), m_pMeshCreator(new LSystemMeshCreator()), m_renderer(renderer)
{
}

void LSystemController::onUpdate()
{
	m_pSystem->applyRules();
	//std::unique_ptr<std::vector<std::unique_ptr<Mesh>>> pMeshList = m_pMeshCreator->createMesh(m_pSystem->getCurrentValue());
	//for (std::vector<std::unique_ptr<Mesh>>::iterator mesh = pMeshList->begin(); mesh != pMeshList->end(); mesh++)
	//{
	//	m_renderer.addDrawable(std::move(*mesh));
	//}
}
