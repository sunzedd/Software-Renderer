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


// RenderPipeline exceptions
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

class RenderPipelineNotCreatedException : public CoreException
{
public:
    RenderPipelineNotCreatedException()
        :
        CoreException("Render pipeline not initialized.\n Note: you should call "
                      "RenderPipeline::create(Window& window) before.")
    {}
};

}