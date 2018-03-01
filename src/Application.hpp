#pragma once

/*
 * File:   Application.hpp
 * Author: Jozef Kobrtek
 * Date:   24th August 2016
 */

//STL includes
#include <vector>


//OpenGL stuff
#include <SDL/SDL.h>
#undef main

//Project includes
#include "OrbitalCamera.hpp"	
#include "PrimitiveParser.hpp"
#include "PrimitiveRenderer.hpp"
#include "Console.hpp"
#include "TokenDescriptors.hpp"

//Project defines
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

struct Primitive;

class Application
{
public:
    Application();

    //Main application function
    bool Run(int argc, char* argv[]);

    //Initializes window and OpenGL
    //Calls initGL function
    bool Init();
	
    //Setup camera for scene
    void setupCamera(OrbitalCamera& orbitalCamera);

    //Clears all resources used by the application
    //Also calls clearGL
    void Clear();

    //Destroys window
    void clearSDLWindow();

private:

	bool _initWindow();
	bool _initGlew();
	void _initPrimitiveTypes();
		PrimitiveTokenDescriptor _getLineTokenDescriptor();
		PrimitiveTokenDescriptor _getPlaneTokenDescriptor();
		PrimitiveTokenDescriptor _getCubeTokenDescriptor();
		PrimitiveTokenDescriptor _getTriangleTokenDescriptor();

	void _loadPrimitivesFromCmdArguments(int argc, char* argv[], std::vector<Primitive>& primitives);

	bool _readWholeFile(const char* file, std::string& content);

    //SDL window and OpenGL context
    SDL_Window*          _window;
    SDL_GLContext        _glContext;

    //Camera
    OrbitalCamera        _camera;

	PrimitiveParser		 _primitiveParser;
	Console				 _console;

	//Renderer
	PrimitiveRenderer	_renderer;
	std::vector<PrimitiveTokenDescriptor> _primitiveDescriptors;
};
