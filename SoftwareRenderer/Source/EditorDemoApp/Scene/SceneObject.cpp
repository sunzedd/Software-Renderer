#include "SceneObject.h"

namespace Demo
{
	SceneObject::SceneObject(std::shared_ptr<cr::Mesh> mesh, std::shared_ptr<cr::IShaderProgram> shader)
		:
		Entity(mesh, shader),
		m_showVertexNormalsFlag(false)
	{
		m_vertexNormalIndicators = m_pMesh->buildNormalIndicatorLinesList(0.2f);
	}

	void SceneObject::render(cr::RenderPipeline& renderer)
	{
		if (m_isActive)
		{
			if (m_isTransformed)
			{
				recalcModelMatrix();
			}

			renderer.bindShaderProgram(m_pShader);
			m_pShader->bindModelMatrix(m_modelMatrix);

			m_pMesh->render(renderer);

			if (m_showVertexNormalsFlag)
			{
				renderer.runLines(m_vertexNormalIndicators, cr::Vec4(1.0f, 0.5f, 0.0f, 1.0f));
			}
		}
	}

	void SceneObject::showVertexNormals(bool enabled)
	{
		m_showVertexNormalsFlag = enabled;
	}
}