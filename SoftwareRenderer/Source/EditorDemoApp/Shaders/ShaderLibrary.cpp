#include "ShaderLibrary.h"

Demo::ShaderLibrary* Demo::ShaderLibrary::m_instance = nullptr;

namespace Demo
{
	ShaderLibrary& ShaderLibrary::instance()
	{
		if (!m_instance)
			m_instance = new ShaderLibrary();

		return *m_instance;
	}

	void ShaderLibrary::add(const std::string& name, std::shared_ptr<Core::IShaderProgram> shader)
	{
		m_shaders.emplace(name, shader);
	}

	std::shared_ptr<Core::IShaderProgram> ShaderLibrary::get(const std::string& name)
	{
		auto shader = m_shaders[name];
		if (!shader)
			throw std::exception(("There is no such shader in shader library (" + name + ")").c_str());

		return m_shaders[name];
	}

	ShaderLibrary::~ShaderLibrary()
	{
		delete m_instance;
	}
}