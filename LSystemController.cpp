#include "precomp.h"
#include "LSystemController.h"
#include "LSystemMeshCreator.h"
#include "LSystem.h"
#include "Mesh.h"

LSystemController::LSystemController(std::unique_ptr<LSystem> pSystem) : m_pSystem(std::move(pSystem)), m_pMeshCreator(new LSystemMeshCreator())
{
}

void LSystemController::onDraw()
{
	m_pMesh->draw();
}

void LSystemController::onUpdate()
{
	m_pSystem->applyRules();
	m_pMesh = m_pMeshCreator->createMesh(m_pSystem->getCurrentValue());
}