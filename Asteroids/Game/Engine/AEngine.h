//
//  AEngine.h
//  Asteroids
//
//  Created by Anton Katekov on 25.12.12.
//  Copyright (c) 2012 AntonKatekov. All rights reserved.
//

#ifndef __MAX__AEngine__
#define __MAX__AEngine__

#include <iostream>
#include "miniPrefix.h"

using namespace std;

class EngineMesh;
class Framebuffer;
class PivotObject;
class RenderSystem;
class Shader;
class SceneSystem;
class ACamera;
class MAXAnimationManager;

class AEngineDelegate {
public:
    virtual void onFrame() = 0;
};

class AEngine {
    bool _first;
    
    RenderSystem        *_renderSystem;
    double                _elapsedTime;
    double                _fullTime;
    
    bool _freezeAnimationManager;
    MAXAnimationManager *_animationManager;
    SceneSystem         *_scene;
    
    Shader              *_shaderObjects;
    Shader              *_shaderInterface;
    
    
    
public:
    
    MAXAnimationManager *GetAnimationManager() {return _animationManager;}
    
    AEngineDelegate   *_delegate;
 
    float displayw,displayh;

    
    ACamera               *_camera;
    
    AEngine();
    ~AEngine();
    
    void Init();
    
        
    double ElapsedTime() const {return _elapsedTime;};
    double FullTime() const {return _fullTime;};
    void RunLoop(double delta);
    
    void AddUnit(PivotObject* newUnit);
    void RemoveUnit(PivotObject* newUnit);
    
    void Update();
	void DrawStart();
    void Draw();
    void EndFrame();
    
    void FinishLoading();
    
    Shader * GetShader();
    
    void GetAllObjectsInArea(BoundingBox bb, USimpleContainer<PivotObject*> *buffer);
    
#pragma mark - Camera
    
    void SetCameraCenter(const Vector2 &position);
    void SetZoom(float zoom);
    float CameraZoom();
    void ScaleCamera(float deltaScale);
    void MoveCamera(float deltax, float deltay);
    
    Vector2 ScreenToWorldCoordinates(const Vector2 &screen);
    Vector2 ScreenToWorldCell(const Vector2 &screen);
    Vector2 WorldCoordinatesToScreen(const Vector2 &screen);
    Vector2 WorldCoordinatesToScreenInterface(const Vector2 &world);
    Vector2 WorldCoordinatesToScreenInterfaceV(const Vector2 &world);
    MRect ScreenToWorldRect();
    
};


extern AEngine *  engine;

#endif /* defined(__MAX__AEngine__) */
