#include "precomp.h"
#include "LSystemController.h"
#include "LSystemInterpreter.h"
#include "LSystemMeshCreator.h"
#include "LSystem.h"
#include "Mesh.h"
#include "Renderer.h"

LSystemController::LSystemController(std::unique_ptr<LSystem> pSystem, Renderer& renderer) : m_pSystem(std::move(pSystem)), m_pInterpreter(new LSystemInterpreter()), m_renderer(renderer)
{
}

void LSystemController::onUpdate()
{
	m_pSystem->applyRules();
	m_renderer.addDrawable(m_pInterpreter->interpret(m_pSystem->getCurrentValue()));
	//for (std::vector<std::unique_ptr<Mesh>>::iterator mesh = pMeshList->begin(); mesh != pMeshList->end(); mesh++)
	//{
	//	m_renderer.addDrawable(std::move(*mesh));
	//}
}
