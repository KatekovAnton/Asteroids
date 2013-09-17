//
//  AEngine.cpp
//  Asteroids
//
//  Created by Anton Katekov on 25.12.12.
//  Copyright (c) 2012 AntonKatekov. All rights reserved.
//

#include "AEngine.h"
#include <time.h>
#include <math.h>
#include "FileManger.h"
#include "MAXAnimationManager.h"

#include "miniPrefix.h"
#include "EngineMesh.h"
#include "Framebuffer.h"
#include "RenderSystem.h"
#include "Shader.h"
#include "Display.h"
#include "Math.h"
#include "SceneSystem.h"
#include "ACamera.h"
#include "RenderObject.h"
#include "MAXDrawPrimitives.h"

AEngine globalEngine;
AEngine * engine = &globalEngine;

AEngine::AEngine()
	:_delegate(NULL)
{
    _renderSystem = new RenderSystem();
    _first = true;
}

AEngine::~AEngine()
{
    delete _renderSystem;

	delete _camera;
    delete _animationManager;
    delete _shaderObjects;
    delete _shaderInterface;
}

void AEngine::Init() {
    

	_freezeAnimationManager = false;
    _renderSystem->InitOpenGL();
    
    MRect _screenRect = RectMake(0, 0, _renderSystem->GetDisplay()->GetDisplayWidth()/_renderSystem->GetDisplay()->GetDisplayScale(), _renderSystem->GetDisplay()->GetDisplayHeight()/_renderSystem->GetDisplay()->GetDisplayScale());
    _camera = new ACamera(_screenRect,1.0);
    
   
   
    MAXDrawPrimitives::SharedDrawPrimitives();

    GCCHECK_GL_ERROR_DEBUG(); 

        
       
    //float scale = _renderSystem->GetDisplay()->GetDisplayScale();
    //_renderSystem->GetDisplay()->setDesignResolutionSize(_renderSystem->GetDisplay()->GetDisplayWidth()/scale, _renderSystem->GetDisplay()->GetDisplayHeight()/scale, kResolutionNoBorder);
    _animationManager = new MAXAnimationManager();
    
	
	_scene = NULL;
    
}

void AEngine::GetAllObjectsInArea(BoundingBox bb, USimpleContainer<PivotObject*> *buffer)
{
    _scene->GetAllObjectsInArea(bb, (USimpleContainer<PivotObject*>*)buffer);
}

void AEngine::RunLoop(double delta)
{
    displayw = Display::currentDisplay()->GetDisplayWidth()/Display::currentDisplay()->GetDisplayScale();
    displayh = Display::currentDisplay()->GetDisplayHeight()/Display::currentDisplay()->GetDisplayScale();
    
    _elapsedTime = delta;
    _fullTime += _elapsedTime;
    
    
    this->Update();
    if (_delegate) 
        _delegate->onFrame();
    
    this->Draw();
    
    
    this->EndFrame();
}

void AEngine::FinishLoading()
{
	_freezeAnimationManager = true;
	Update();
	_freezeAnimationManager = false;
}

void AEngine::Update()
{	
	if (!_scene)
	{
		if (!_freezeAnimationManager)
			_animationManager->Update();
		return;
	}
    _scene->BeginFrame();
    _scene->Frame(_elapsedTime);
    
    _scene->EndFrame();
    _scene->UpdateScene();
    if (_first) {
        _camera->Move(0, 0);
        _first = false;
    }
    _camera->Update();
	
	if (!_freezeAnimationManager)
		_animationManager->Update();
	if (!_scene)
		return;


    _scene->AfterUpdate();
    _scene->CalculateVisbleObject();
    
   
    _scene->LastUpdate(false);
}

void AEngine::DrawStart()
{
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void AEngine::Draw()
{
	DrawStart();
	if (_scene)
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
    
		GLint prog;
		glGetIntegerv(GL_CURRENT_PROGRAM, &prog);
	
		
		glUseProgram(prog);
    }
}

void AEngine::EndFrame()
{
    _renderSystem->EndFrame();
}

#pragma mark - Camera

void AEngine::SetCameraCenter(const Vector2 &position)
{    
    _camera->SetPosition(Vector3Make(position.x, position.y, 0));
}

void AEngine::SetZoom(float zoom)
{
    _camera->Scale(_camera->scale/ zoom);
}

float AEngine::CameraZoom()
{
    return _camera->scale;
}

void AEngine::ScaleCamera(float deltaScale)
{
    _camera->Scale(deltaScale);
}

void AEngine::MoveCamera(float deltax, float deltay)
{
    _camera->Move(deltax, deltay);
}

//Vector2 AEngine::ScreenToWorldCoordinates(const Vector2 &screen)
//{
//    Vector2 camcentercell;
//    camcentercell.x = _map->mapW/2.0 - _camera->position.x;
//    camcentercell.y = _camera->position.y + _map->mapH/2.0;
//    
//    Vector2 camcenterCoords;
//    camcenterCoords.x = camcentercell.x * 64.0;
//    camcenterCoords.y = camcentercell.y * 64.0;
//    
//    Vector2 screenSize;
//    screenSize.x = displayw * _camera->scale;
//    screenSize.y = displayh * _camera->scale;
//    
//    Vector2 ltp;
//    ltp.x = camcenterCoords.x - screenSize.x;
//    ltp.y = camcenterCoords.y - screenSize.y;
//    
//    float dx = screen.x/displayw;
//    float dy = screen.y/displayh;
//    
//    Vector2 result;
//    result.x = ltp.x + screenSize.x * dx * 2;
//    result.y = ltp.y + screenSize.y * dy * 2;
//    
//    return result;
//}
//
//Vector2 AEngine::ScreenToWorldCell(const Vector2 &screen)
//{
//    Vector2 coords = ScreenToWorldCoordinates(screen);
//    return Vector2(coords.x/64.0, coords.y/64.0);
//}
//
//Vector2 AEngine::WorldCoordinatesToScreen(const Vector2 &world)
//{
//    Vector2 camcentercell;
//    camcentercell.x = _map->mapW/2.0 - _camera->position.x;
//    camcentercell.y = _camera->position.y + _map->mapH/2.0;
//    
//    Vector2 camcenterCoords;
//    camcenterCoords.x = camcentercell.x * 64.0;
//    camcenterCoords.y = camcentercell.y * 64.0;
//    
//    Vector2 screenSize;
//    screenSize.x = displayw * _camera->scale;
//    screenSize.y = displayh * _camera->scale;
//    
//    Vector2 result;
//    result.x = 0.5 * displayw * (world.x - camcenterCoords.x + screenSize.x)/screenSize.x;
//    result.y = 0.5 * displayh * (world.y - camcenterCoords.y + screenSize.y)/screenSize.y;
//    
//    return result;
//}
//
//Vector2 AEngine::WorldCoordinatesToScreenInterface(const Vector2 &world)
//{
//    Vector2 camcentercell;
//    camcentercell.x = _map->mapW/2.0 - _camera->position.x;
//    camcentercell.y = _camera->position.y + _map->mapH/2.0;
//    
//    Vector2 camcenterCoords;
//    camcenterCoords.x = camcentercell.x * 64.0;
//    camcenterCoords.y = camcentercell.y * 64.0;
//    
//    Vector2 screenSize;
//    screenSize.x = displayw * _camera->scale;
//    screenSize.y = displayh * _camera->scale;
//    
//    Vector2 result;
//    result.x = 0.5 * displayw * (world.x - camcenterCoords.x + screenSize.x)/screenSize.x;
//    result.y = displayh - 0.5 * displayh * (world.y - camcenterCoords.y + screenSize.y)/screenSize.y;
//    
//    return result;
//}
//
//GLKVector2 AEngine::WorldCoordinatesToScreenInterfaceV(const GLKVector2 &world)
//{
//    Vector2 camcentercell;
//    camcentercell.x = _map->mapW/2.0 - _camera->position.x;
//    camcentercell.y = _camera->position.y + _map->mapH/2.0;
//    
//    Vector2 camcenterCoords;
//    camcenterCoords.x = camcentercell.x * 64.0;
//    camcenterCoords.y = camcentercell.y * 64.0;
//    
//    Vector2 screenSize;
//    screenSize.x = displayw * _camera->scale;
//    screenSize.y = displayh * _camera->scale;
//    
//    GLKVector2 result;
//    result.x = 0.5 * displayw * (world.x - camcenterCoords.x + screenSize.x)/screenSize.x;
//    result.y = displayh - 0.5 * displayh * (world.y - camcenterCoords.y + screenSize.y)/screenSize.y;
//    
//    return result;
//}
//
MRect AEngine::ScreenToWorldRect()
{
    Vector2 camcentercell;
    camcentercell.x = _camera->position.x;
    camcentercell.y = _camera->position.y;
    
    Vector2 camcenterCoords;
    camcenterCoords.x = camcentercell.x * 64.0;
    camcenterCoords.y = camcentercell.y * 64.0;
    
    Vector2 screenSize;
    screenSize.x = displayw * _camera->scale;
    screenSize.y = displayh * _camera->scale;
    
    Vector2 ltp;
    ltp.x = camcenterCoords.x - screenSize.x;
    ltp.y = camcenterCoords.y - screenSize.y;
    
    MRect result;
    result.origin = ltp;
    result.size.width = screenSize.x * 2.0;
    result.size.height = screenSize.y * 2.0;
    
    return result;
}


