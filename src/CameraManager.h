#pragma once
#ifndef __CameraManager__
#define __CameraManager__

#include "raylib.h"

class CameraManager
{
public:
    static CameraManager* Instance(void)
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new CameraManager();
		}
		return s_pInstance;
	}

    void beginCameraMode() { BeginMode2D(m_camera); }
    void endCameraMode() { EndMode2D(); }

    void setCameraTarget(Vector2 pos);

private:
    CameraManager(void);
    ~CameraManager(void) {};

    static CameraManager* s_pInstance;

    Camera2D m_camera;
};

typedef CameraManager TheCameraManager;

#endif /* defined(__CameraManager__) */