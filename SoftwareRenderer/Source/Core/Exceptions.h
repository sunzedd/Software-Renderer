#pragma once
#include <string>
#include <exception>

namespace core
{

class CoreException : public std::exception
{
public:
    CoreException()
        :
        exception("Core exception: unknown")
    {}
    
    CoreException(const std::string& message)
        :
        exception(("Core exception: " + message).c_str())
    {}
};

class ApplicationAlreadyCreatedException : public CoreException
{
public:
    ApplicationAlreadyCreatedException()
        :
        CoreException("Application already created")
    {}

    ApplicationAlreadyCreatedException(const std::string& message)
        :
        CoreException(("Core exception: " + message).c_str())
    {}
};


// AssetLoader exceptions
class CouldNotLoadAssetException : public CoreException
{
public:
    CouldNotLoadAssetException()
        :
        CoreException("Could not load asset")
    {}

    CouldNotLoadAssetException(const std::string& message)
        :
        CoreException(message)
    {}
};

class IncorrectOperationOrder : public CoreException
{
public:
    IncorrectOperationOrder()
        :
        CoreException("Incorrect operation order")
    {}

    IncorrectOperationOrder(const std::string& message)
        :
        CoreException(message)
    {}
};


// Renderer exceptions
class NoShaderBoundException : public CoreException
{
public:
    NoShaderBoundException()
        :
        CoreException("No shader bound")
    {}
    
    NoShaderBoundException(const std::string& message)
        :
        CoreException(message)
    {}
};

class RendererNotCreatedException : public CoreException
{
public:
    RendererNotCreatedException()
        :
        CoreException("Render pipeline not initialized.\n Note: you should call "
                      "Renderer::create(Window& window) before.")
    {}
};

}
