//Using SDL and standard IO
#include "CollisionSystem.h"
#include "ISDLImageLoader.h"
#include "InputManager.h"
#include "Dependencies.h"
#include "GameManager.h"
#include "ISDLWindow.h"
#include "GameObject.h"
#include "Grid.h"
#include "Spawner.h"
#include "Window.h"

//Screen dimension constants
constexpr int SCREEN_WIDTH = 1024;
constexpr int SCREEN_HEIGHT = 768;

int main(int argc, char* args[])
{
	ISDLWindow* sdlWindow = new ISDLWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
	ISDLImageLoader* imageLoader = new ISDLImageLoader(sdlWindow->get_Renderer());
	Window window = Window(sdlWindow, imageLoader);

	Dependencies::instance()->Spawner->InitializeGameState(imageLoader, sdlWindow);
	Dependencies::instance()->Grid->GenerateGrid();
	
	bool quit = false;
	Uint32 lastFrameTicks = 0;
	while (!quit)
	{
		const Uint32 ticks = SDL_GetTicks(); // can be used to see how much time in ms has passed since app start
		const float deltaTime = (ticks - lastFrameTicks) / 1000.0f;
		lastFrameTicks = ticks;

		// Update InputManager
		Dependencies::instance()->InputManager->Update();
		quit = Dependencies::instance()->InputManager->Quit;

		const JohnsArray<GameObject> gameObjects = Dependencies::instance()->GameManager->GameObjects;
		
		// Update Collision System
		CollisionSystem::Update(&gameObjects);
		
		// Run Update on all GameObjects
		for	(int i = 0; i < gameObjects.count; i++)
		{
			gameObjects.Array[i]->Update(deltaTime);
		}

		// clear the screen
		window.clear();

		// Render the Grid
		for (int x = 0; x < GridX; x++)
		{
			for (int y = 0; y < GridY; y++)
			{
				window.render(Dependencies::instance()->Grid->TheGrid[x][y]);
			}
		}
		
		// Render all GameObjects
		for (int layer = 0; layer < 4; layer++)	// Ooo ok I just had an idea, I need to order the rendering after the renderOrder on the images and I thought I would have to make a copy and quicksort it.
												// Instead listen here, I loop from 0-3 (our render layers basically) and just render the things on that layer. This is basically O(4n) (from 4 layers) which is O(n) because we dont keep constants. This is only better if the amount of things we need to render is more than 2 to the power of the amount of render layers we have, as quicksort is O(nlogn). In this case I am rendering 2 things... nah i just solved rendering man im good 
		{
			for	(int i = 0; i < gameObjects.count; i++)
			{
				if (gameObjects.Array[i]->Image->renderOrder == layer)
				{
					window.render(gameObjects.Array[i]);
				}
			}
		}
		// present screen (switch buffers)
		SDL_RenderPresent(sdlWindow->get_Renderer());

		SDL_Delay(0); // can be used to wait for a certain amount of ms
	}

	delete sdlWindow;
	delete imageLoader;

	return 0;
}
