#pragma once
#include <unordered_map>
#include <memory>

namespace Demo
{
	/*
		Singleton template class for libraries (shader lib, texture lib, ... ect.)
	*/
	template <typename T>
	class Library
	{
	public:
		static Library<T>& instance()
		{
			if (!m_instance)
				m_instance = new Library<T>();

			return *m_instance;
		}

		void add(const std::string& name, std::shared_ptr<T> item)
		{
			m_container.emplace(name, item);
		}

		std::shared_ptr<T> get(const std::string& name)
		{
			auto item = m_container[name];
			if (!item)
				throw std::exception(("There is no such item in library (" + name + ")").c_str());

			return item;
		}

	private:
		Library() { }
		~Library() { delete m_instance; }

	private:
		std::unordered_map<std::string, std::shared_ptr<T>> m_container;
		static Library<T>* m_instance;
	};

	template <typename T>
	Library<T>* Library<T>::m_instance = nullptr;
}