#pragma once
#include <memory>
#include <unordered_map>
#include "../../Core/Graphics/IShaderProgram.h"

namespace Demo
{
	class ShaderLibrary final
	{
	public:
		static ShaderLibrary& instance()
		{
			if (!m_instance)
				m_instance = new ShaderLibrary();
			
			return *m_instance;
		}

		void add(const std::string& name, std::shared_ptr<Core::IShaderProgram> shader) 
		{
			m_shaders.emplace(name, shader);
		}

		std::shared_ptr<Core::IShaderProgram> get(const std::string& name) 
		{
			auto shader = m_shaders[name];
			if (!shader)
				throw std::exception(("There is no such shader in shader library (" + name + ")").c_str());

			return m_shaders[name]; 
		}

	private:
		ShaderLibrary() 
		{
		}
		~ShaderLibrary()
		{
			delete m_instance;
		}

	private:
		std::unordered_map<std::string, std::shared_ptr<Core::IShaderProgram>> m_shaders;
		static ShaderLibrary* m_instance;
	};
}