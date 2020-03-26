#include "Game.h"
#include "Master.h"
#include "Actor.h"
#include "StaticModelComponent.h"
#include "PointLightComponent.h"
#include "DirLightComponent.h"
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

    /*
    Actor testActor;
    testActor.position.x = 80;
    testActor.position.y = -50;
    testActor.rotation = glm::quat(glm::yawPitchRoll(0.8f, 0.0f ,0.0f));
    
    StaticModelComponent testStaticModel1(&testActor);

    testStaticModel1.localPosition.z = -300;
    testStaticModel1.localRotation = glm::quat(glm::yawPitchRoll(0.0f, 3.14f, 0.0f));
    testStaticModel1.SetModelSource("Cloud_KH1.obj");
    testStaticModel1.Initialize();
    */
    
    Actor testActor2;
    testActor2.position.z = 50;
    testActor2.position.y = -50;
    testActor2.position.x = 0;
    StaticModelComponent testStaticModel2(&testActor2);
    
    /*
    testStaticModel2.textureFileNames.push_back("texture000.png");
    testStaticModel2.textureFileNames.push_back("texture001.png");
    
    //sword tip
    testStaticModel2.textureFileNames.push_back("texture004.png");
    
    testStaticModel2.textureFileNames.push_back("texture007.png");
    
    testStaticModel2.textureFileNames.push_back("texture006.png");
    
    // hair?
    testStaticModel2.textureFileNames.push_back("texture001.png");
    
    // face
    testStaticModel2.textureFileNames.push_back("texture000.png");
    
    // lowersword
    testStaticModel2.textureFileNames.push_back("texture003.png");
    // more hair
    testStaticModel2.textureFileNames.push_back("texture002.png");
    
    testStaticModel2.textureFileNames.push_back("texture014.png");
    
    testStaticModel2.textureFileNames.push_back("texture012.png");
    
    testStaticModel2.textureFileNames.push_back("texture013.png");
    
    testStaticModel2.textureFileNames.push_back("texture009.png");
    
    testStaticModel2.textureFileNames.push_back("texture008.png");
    
    testStaticModel2.textureFileNames.push_back("texture010.png");
    
    testStaticModel2.textureFileNames.push_back("texture011.png");
    
    
    testStaticModel2.SetModelSource("Cloud_KH1.obj");
    testStaticModel2.Initialize();
    */

    Actor testActor3;
    StaticModelComponent testStaticModel1(&testActor3);
    
    testStaticModel1.SetModelSource("tvModel.fbx");
    testStaticModel1.materialFileNames.push_back("tvMat.mat");
    testStaticModel1.Initialize();



    Actor testLight0;
    testLight0.position = glm::vec3(300, 100, 0);
    PointLightComponent light0(&testLight0);
    light0.base.color = glm::vec4(glm::vec3(1,0,0),0);
    
    Actor testLight1;
    testLight1.position = glm::vec3(500,800,1000);
    PointLightComponent light1(&testLight1);
    light1.base.color = glm::vec4(glm::vec3(0, 0.4, 0), 0);

    Actor testLight2;
    DirLightComponent light2(&testLight2);
    light2.base.color = glm::vec4(glm::vec3(0, 0, 0.2), 0);
    light2.direction = glm::vec3(0,1,0);
    
	while (!glfwWindowShouldClose(master->graphicsModule.window))
	{
		// Gather Inuputs

		// Advance frame of game

		// Render Frame
		master->graphicsModule.RenderFrame(0);
	}
}