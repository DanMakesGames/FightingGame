#include "Game.h"
#include "Master.h"
#include "Actor.h"
#include "StaticModelComponent.h"
#include <ggponet.h>

Game::Game() : master(nullptr)
{
}

void Game::Initialize(Master* inMaster)
{
	master = inMaster;

}

bool Game::AdvanceFrame(int flags)
{
	// loop over actors, and their components, and tick
}

void Game::MainLoop()
{
    DEBUG_PRINT("Main loop start");
	// Remeber that control of delta time needs to go here.
	// Broken up to facilitate future GGPO implementation

    Actor testActor;
    testActor.position.x = 80;
    testActor.position.y = -50;
    testActor.rotation = glm::quat(glm::yawPitchRoll(0.8f, 0.0f ,0.0f));

    StaticModelComponent testStaticModel1(&testActor);
    testStaticModel1.localPosition.z = -300;
    testStaticModel1.localRotation = glm::quat(glm::yawPitchRoll(0.0f, 3.14f, 0.0f));
    testStaticModel1.SetModelSource("Cloud_KH1.obj");
    testStaticModel1.Initialize();

    Actor testActor2;
    StaticModelComponent testStaticModel2(&testActor2);
    testStaticModel2.SetModelSource("Cloud_KH1.obj");
    testStaticModel2.Initialize();
    
	while (!glfwWindowShouldClose(master->graphicsModule.window))
	{
		// Gather Inuputs

		// Advance frame of game

		// Render Frame
		master->graphicsModule.RenderFrame(0);
	}
}