#include "Application.hpp"
#include "ShaderCompiler.hpp"

#include <fstream>
#include <iterator>
#include <iostream>
#include <memory>
#include <GL/glew.h>
#include "Primitive.hpp"

Application::Application()
{
    _window = nullptr;
}

bool Application::Init()
{
    if (!_initWindow())
        return false;

    if (!_initGlew())
        return false;

	_initPrimitiveTypes();

	_renderer.init(SCREEN_WIDTH, SCREEN_HEIGHT);

    return true;
}

bool Application::_initWindow()
{
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL Failed to initialize!\n";
        return false;
    }

    _window = SDL_CreateWindow("Shadow Volumes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(_window == nullptr)
    {
        std::cerr << "Failed to create SDL window!\n";
        return false;
    }

    //Set OpenGL version to 4.5, core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
#ifdef _DEBUG
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

    //Dpouble buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    //Create OpenGL context
    _glContext = SDL_GL_CreateContext(_window);

    //VSync
    SDL_GL_SetSwapInterval(1);

    return true;
}


bool Application::_initGlew()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "GLEW failed to initialize!\n";
        return false;
    }

    return true;
}

void Application::_initPrimitiveTypes()
{
	_primitiveDescriptors.resize(PrimitiveType::NUM_PRIMITIVE_TYPES);

	_primitiveDescriptors[PrimitiveType::LINE] = _getLineTokenDescriptor();
	_primitiveDescriptors[PrimitiveType::PLANE] = _getPlaneTokenDescriptor();
	_primitiveDescriptors[PrimitiveType::CUBE] = _getCubeTokenDescriptor();
	_primitiveDescriptors[PrimitiveType::TRIANGLE] = _getTriangleTokenDescriptor();
	_primitiveDescriptors[PrimitiveType::ORIGIN] = _getOriginTokenDescriptor();
}

PrimitiveTokenDescriptor Application::_getLineTokenDescriptor()
{
	PrimitiveTokenDescriptor lineDesc;
	lineDesc.primitiveName = "line";
	lineDesc.primitiveType = PrimitiveType::LINE;

	//starting point
	lineDesc.parameters.push_back(TokenTypes::FLOAT);
	lineDesc.parameters.push_back(TokenTypes::FLOAT);
	lineDesc.parameters.push_back(TokenTypes::FLOAT);

	//end point
	lineDesc.parameters.push_back(TokenTypes::FLOAT);
	lineDesc.parameters.push_back(TokenTypes::FLOAT);
	lineDesc.parameters.push_back(TokenTypes::FLOAT);

	//color
	lineDesc.parameters.push_back(TokenTypes::FLOAT);
	lineDesc.parameters.push_back(TokenTypes::FLOAT);
	lineDesc.parameters.push_back(TokenTypes::FLOAT);

	//thickness
	lineDesc.parameters.push_back(TokenTypes::FLOAT);

	return lineDesc;
}

PrimitiveTokenDescriptor Application::_getPlaneTokenDescriptor()
{
	PrimitiveTokenDescriptor planeDesc;
	planeDesc.primitiveName = "plane";
	planeDesc.primitiveType = PrimitiveType::PLANE;

	//plane equation
	planeDesc.parameters.push_back(TokenTypes::FLOAT);
	planeDesc.parameters.push_back(TokenTypes::FLOAT);
	planeDesc.parameters.push_back(TokenTypes::FLOAT);
	planeDesc.parameters.push_back(TokenTypes::FLOAT);

	//color
	planeDesc.parameters.push_back(TokenTypes::FLOAT);
	planeDesc.parameters.push_back(TokenTypes::FLOAT);
	planeDesc.parameters.push_back(TokenTypes::FLOAT);

	return planeDesc;
}

PrimitiveTokenDescriptor Application::_getCubeTokenDescriptor()
{
	PrimitiveTokenDescriptor cubeDesc;
	cubeDesc.primitiveName = "cube";
	cubeDesc.primitiveType = PrimitiveType::CUBE;

	//center point
	cubeDesc.parameters.push_back(TokenTypes::FLOAT);
	cubeDesc.parameters.push_back(TokenTypes::FLOAT);
	cubeDesc.parameters.push_back(TokenTypes::FLOAT);

	//extents
	cubeDesc.parameters.push_back(TokenTypes::FLOAT);
	cubeDesc.parameters.push_back(TokenTypes::FLOAT);
	cubeDesc.parameters.push_back(TokenTypes::FLOAT);

	//color
	cubeDesc.parameters.push_back(TokenTypes::FLOAT);
	cubeDesc.parameters.push_back(TokenTypes::FLOAT);
	cubeDesc.parameters.push_back(TokenTypes::FLOAT);

	//wireframe or solid ('w' or 's')
	cubeDesc.parameters.push_back(TokenTypes::CHAR);

	return cubeDesc;
}

PrimitiveTokenDescriptor Application::_getTriangleTokenDescriptor()
{
	PrimitiveTokenDescriptor triangleDesc;
	triangleDesc.primitiveName = "triangle";
	triangleDesc.primitiveType = PrimitiveType::TRIANGLE;

	//v1
	triangleDesc.parameters.push_back(TokenTypes::FLOAT);
	triangleDesc.parameters.push_back(TokenTypes::FLOAT);
	triangleDesc.parameters.push_back(TokenTypes::FLOAT);

	//v2
	triangleDesc.parameters.push_back(TokenTypes::FLOAT);
	triangleDesc.parameters.push_back(TokenTypes::FLOAT);
	triangleDesc.parameters.push_back(TokenTypes::FLOAT);

	//v3
	triangleDesc.parameters.push_back(TokenTypes::FLOAT);
	triangleDesc.parameters.push_back(TokenTypes::FLOAT);
	triangleDesc.parameters.push_back(TokenTypes::FLOAT);

	//color
	triangleDesc.parameters.push_back(TokenTypes::FLOAT);
	triangleDesc.parameters.push_back(TokenTypes::FLOAT);
	triangleDesc.parameters.push_back(TokenTypes::FLOAT);

	//wireframe or solid ('w' or 's')
	triangleDesc.parameters.push_back(TokenTypes::CHAR);

	return triangleDesc;
}

PrimitiveTokenDescriptor Application::_getOriginTokenDescriptor()
{
	PrimitiveTokenDescriptor originDesc;
	originDesc.primitiveName = "origin";
	originDesc.primitiveType = PrimitiveType::ORIGIN;

	//scale
	originDesc.parameters.push_back(TokenTypes::FLOAT);

	return originDesc;
}

void Application::clearSDLWindow()
{
	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Application::Clear()
{
    //_renderer.clear();
     
	clearSDLWindow();
}

void Application::setupCamera(OrbitalCamera& camera)
{
    //Setup camera
    //Make the scene fit the camera's view frustum
    //Camera is static throughout the app, it will be the model that will rotate

    //Create hypothetical bounding sphere around scene's AABB, d - its radius
    //We will create camera's view frustum around this sphere
	float r = 50;
    float fovyDeg = 90;
    float fovyRad = glm::radians(fovyDeg);
    float aspectRatio = float(SCREEN_WIDTH) / float(SCREEN_HEIGHT);
    float nearZ = 0.1f;
    
    float fovXrad = 2 * glm::asin(aspectRatio * glm::sin(fovyRad/2.0f));

    //The sphere can touch the frustum either on left-right sides, or top-bottom
    //We choose, which distance is further away
    float d = r / glm::max(sin(fovyRad/2), sin(fovXrad/2));

    camera.setupCameraProjection(0.1f, 2*(d + r), aspectRatio, fovyDeg);
    camera.setupCameraView(d, glm::vec3(0, 0, 0), 0, 0);
    camera.update();
}

bool Application::Run(int argc, char* argv[])
{
    if(!Init())
        return false;

	if (!_processCmdArguments(argc, argv))
		return false;

    setupCamera(_camera);

    //Prepare rendering data
    //TODO

    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            switch (e.type)
            {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    quit = true;
                break;

            case SDL_KEYUP:
                break;

            case SDL_MOUSEMOTION:
                //Adjust camera only if left mouse button is pressed
                if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    _camera.adjustOrientation(float(e.motion.xrel), float(e.motion.yrel));
                }
                break;
            
            case SDL_MOUSEWHEEL:
                _camera.adjustZoom(e.wheel.y);
                break;

            default:
                break;
            }
        }

		if(_console.isLineAvailable())
		{
			
		}

        _camera.update();
        _renderer.onUpdate();

        _renderer.onWindowRedraw(_camera.getViewMatrix(), _camera.getProjectionMatrix());

        SDL_GL_SwapWindow(_window);
    }

    Clear();

    return true;
}

bool Application::_readWholeFile(const char* file, std::string& content)
{
	content.clear();

	std::ifstream stream(file);

	if (stream.fail())
		return false;

	content = std::string(std::istream_iterator<char>(stream >> std::noskipws), std::istream_iterator<char>());

	return true;
}

bool Application::_processCmdArguments(int argc, char* argv[])
{
	if (argc == 1)
		return true;

	if (argc > 2)
		return false;

	if(argc==2)
	{
		std::string fileContent;

		_readWholeFile(argv[1], fileContent);

		if (fileContent == "")
			return false;

		std::vector<std::string> lines;

		_splitStringToLines(fileContent, lines);

		for(const auto line : lines)
		{
			
		}
	}
}

void Application::_split(std::string str, std::string delimiters, std::vector<std::string>& results)
{
	_tokenizer.set(str, delimiters);
	results = _tokenizer.split();
}

void Application::_splitStringToLines(std::string str, std::vector<std::string>& lines)
{
	_split(str, "\n", lines);
}

void Application::_tokenizeLine(std::string line, std::vector<std::string>& tokens)
{
	_split(line, " \t", tokens);
}

bool Application::_getPrimitiveFromLine(const std::string& line, Primitive& primitive)
{
	Primitive p;

	p.primitiveType = PrimitiveType::UNKNOWN;

	std::vector<std::string> tokens;
	_tokenizeLine(line, tokens);

	if (!tokens.size())
		return false;

	for(const auto desc : _primitiveDescriptors)
	{
		if(tokens[0].compare(desc.primitiveName)==0)
		{
			p.primitiveType = desc.primitiveType;
			break;
		}
	}

	const auto desc = _primitiveDescriptors[p.primitiveType];

	if (p.primitiveType == PrimitiveType::UNKNOWN || tokens.size() != (1+desc.parameters.size()))
		return false;

	
	for(const auto param : desc.parameters)
	{
		
	}
}