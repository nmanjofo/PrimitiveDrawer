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

#include "Tokenizer.hpp"
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
		PrimitiveTokenDescriptor _getOriginTokenDescriptor();

	bool _processCmdArguments(int argc, char* argv[]);

	bool _readWholeFile(const char* file, std::string& content);

	void _tokenizeLine(std::string line, std::vector<std::string>& tokens);
	void _splitStringToLines(std::string str, std::vector<std::string>& lines);
	void _split(std::string str, std::string delimiters, std::vector<std::string>& results);
		bool _getPrimitiveFromLine(const std::string& line, Primitive& primitive);

    //SDL window and OpenGL context
    SDL_Window*          _window;
    SDL_GLContext        _glContext;

    //Camera
    OrbitalCamera        _camera;

	Tokenizer			 _tokenizer;
	Console				 _console;

	//Renderer
	PrimitiveRenderer	_renderer;
	std::vector<PrimitiveTokenDescriptor> _primitiveDescriptors;
};
