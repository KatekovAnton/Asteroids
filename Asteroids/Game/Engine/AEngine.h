//
//  AEngine.h
//  MAX
//
//  Created by Anton Katekov on 25.12.12.
//  Copyright (c) 2012 AntonKatekov. All rights reserved.
//

#ifndef __MAX__AEngine__
#define __MAX__AEngine__

#include <iostream>
#include "miniPrefix.h"

using namespace Utils;
using namespace std;

class EngineMesh;
class Framebuffer;
class PivotObject;
class RenderSystem;
class Shader;
class SceneSystem;
class MAXCamera;
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
    shared_ptr<EngineMesh> _mapQuadMesh;
    
    
    
public:
    

    
    AEngineDelegate   *_delegate;
 
    float displayw,displayh;

    
    MAXCamera               *_camera;
    
    AEngine();
    ~AEngine();
    
    void Init();
    
        
    double ElapsedTime() const {return _elapsedTime;};
    double FullTime() const {return _fullTime;};
    void RunLoop(double delta);
    
	
    void SetZoom(float zoom);
    float CameraZoom();
    
    void Update();
	void DrawStart();
    void Draw();
    void EndFrame();
    
    void FinishLoading();
    
    Shader * GetShader();


   
    
    Vector2 ScreenToWorldCoordinates(const Vector2 &screen);
    Vector2 ScreenToWorldCell(const Vector2 &screen);
    Vector2 WorldCoordinatesToScreen(const Vector2 &screen);
    Vector2 WorldCoordinatesToScreenInterface(const Vector2 &world);
    Vector2 WorldCoordinatesToScreenInterfaceV(const Vector2 &world);
    Rect ScreenToWorldRect();
    
};


extern AEngine *  engine;

#endif /* defined(__MAX__AEngine__) */
