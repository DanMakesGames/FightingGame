#include "Game.h"
#include "Master.h"
#include "Actor.h"
#include "StaticModelComponent.h"
#include "PointLightComponent.h"
#include "DirLightComponent.h"
#include "FreeCam.h"
#include <ggponet.h>

Game::Game() : master(nullptr)
{
}

void Game::Initialize(Master* inMaster)
{
	master = inMaster;

}

void Game::MainLoop()
{
    DEBUG_PRINT("Main loop start");
	// Remeber that control of delta time needs to go here.
	// Broken up to facilitate future GGPO implementation


    Actor testActor3;
    testActor3.rotation = glm::quat(glm::yawPitchRoll(-1.0f, 0.4f, 0.0f));
    StaticModelComponent testStaticModel3(&testActor3);
    testActor3.position = vec3(0,0,300);
    testStaticModel3.SetModelSource("tvModel.fbx");
    testStaticModel3.materialFileNames.push_back("tvMat.mat");
    testStaticModel3.Initialize();

    Actor testActor4;
    //testActor4.rotation = glm::quat(glm::yawPitchRoll(-1.0f, 0.4f, 0.0f));
    StaticModelComponent testStaticModel4(&testActor4);
    testActor4.position = vec3(0, 0, -300);
    testStaticModel4.SetModelSource("tvModel.fbx");
    testStaticModel4.materialFileNames.push_back("tvMat.mat");
    testStaticModel4.Initialize();

    /*
    Actor testLight0;
    testLight0.position = glm::vec3(300, 100, 0);
    PointLightComponent light0(&testLight0);
    light0.base.color = glm::vec4(glm::vec3(0.5,0.5,0.5),0);
    */
    
    Actor testLight1;
    testLight1.position = glm::vec3(0,50,0);
    PointLightComponent light1(&testLight1);
    light1.base.color = glm::vec4(glm::vec3(0.6, 0.6, 0.6), 0);
    light1.base.ambientIntensity = 0.03f;
    light1.base.diffuseIntensity = 1.0f;
    
    
    /*
    Actor testLight2;
    
    DirLightComponent light2(&testLight2);
    light2.base.color = glm::vec4(glm::vec3(0.6, 0.6, 0.6), 0);
    light2.direction = glm::vec3(0,0,-1);
    light2.base.ambientIntensity = 0.03f;
    light2.base.diffuseIntensity = 1.0f;
    */

    Actor floor;
    floor.position = vec3(0, -100, 0);
    StaticModelComponent floorModel(&floor);
    floorModel.SetModelSource("floor.fbx");
    floorModel.Initialize();

    FreeCam freeCam;
    freeCam.position = glm::vec3(0, 0, 0);

    GLFWwindow* window = master->graphicsModule.GetWindow();
	while (!glfwWindowShouldClose(window))
	{
		// Gather Inuputs

		// Advance frame of game
        freeCam.Tick(1.0f);

		// Render Frame
		master->graphicsModule.RenderFrame(0);
	}
}

bool Game::AdvanceFrame(int flags, float deltaTime)
{
    // loop over actors, and their components, and tick
}