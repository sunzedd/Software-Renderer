#pragma once
#include "../Core/World/Entity.h"

namespace cr = Core;

namespace Demo
{
	class SceneObject : public cr::Entity
	{
	public:
		SceneObject(const std::string& name, std::shared_ptr<cr::Mesh> mesh, std::shared_ptr<cr::IShaderProgram> shader);
		
		void render(cr::RenderPipeline& renderer) override;
		void showVertexNormals(bool enabled);

	private:
		std::vector<cr::LineV3> m_vertexNormalIndicators;
		bool m_showVertexNormalsFlag;
	};
}