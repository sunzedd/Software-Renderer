#include "PointLightSource.h"

namespace Demo
{
	PointLightSource::PointLightSource(const vec4& indicatorColor)
		:
		Entity
		(
			Core::AssetLoader::loadMesh("Assets\\Meshes\\sphere.obj"),
			ShaderLibrary::instance().get("SC")
		)
	{
		std::dynamic_pointer_cast<SingleColorShader>(m_pShader)->bindColor(indicatorColor);
	}

	void PointLightSource::update(unsigned int dtime)
	{
	}

	void PointLightSource::render(Core::RenderPipeline& renderer)
	{
		if (m_isVisible)
		{
			if (m_isTransformed) recalcModelMatrix();
			
			renderer.bindShaderProgram(m_pShader);
			m_pShader->bindModelMatrix(m_modelMatrix);

			m_pMesh->render(renderer);
		}
	}
}