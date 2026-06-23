//Putting the arena
//Putting the WASD  keys
//Setting up levels
//Moving the player with respect to mouse pointer
#include <SFML/Graphics.hpp>
#include "Player3.cpp"
#include<cmath>
int createBackground(VertexArray& rVA, IntRect arena);
using namespace sf;
int main()
{
  
  int wave = 0;

 enum class State{ PAUSED, LEVELING_UP, GAME_OVER, PLAYING}; //FOUR STATES OF THE GAME
 State state = State::GAME_OVER;
  
/*****************************************************
Get the screen resolution and create an SFML window
******************************************************/

 Vector2f resolution; 
 resolution.x = VideoMode::getDesktopMode().width;
 resolution.y = VideoMode::getDesktopMode().height;
 //resolution.x = 1920;
 //resolution.y = 1080;
 RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);
//********************************************************
 
 View mainView(FloatRect(0, 0, resolution.x, resolution.y)); // SFML View for the main action
 
 //window.setView(mainView);
 Clock clock;
 
 
 
 Vector2f mouseWorldPosition;      //mouse in relation to world coordinates
 Vector2i mouseScreenPosition;     //mouse in relation to screen coordinates
 window.setMouseCursorVisible(true);
 
 Player player;   //instance of the Player class
 IntRect arena;   //boundaries of the arena
 
 
 // Create the background
	VertexArray background;
	// Load the texture for our background vertex array
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/background_sheet.png");
 
 while (window.isOpen())
{
  Event event;
  while (window.pollEvent(event))
  
   {
         if(event.type == Event::KeyPressed)
        {
           // Pause a game while playing
          if(event.key.code == Keyboard:: Return && state == State::PLAYING)
          {     
              state = State::PAUSED;
             }
             
             // Restart while paused
           else if (event.key.code == Keyboard:: Return && state == State::PAUSED){
              state = State::PLAYING;
              clock.restart();
             } 
            // Start a new game while in GAME_OVER state 
            else if (event.key.code == Keyboard::Return && state == State::GAME_OVER)
              {
             state = State::LEVELING_UP;
            }
            
          if (state == State::PLAYING){
          
                }
          }
                } // End event polling
     
   // Handle the player quitting   
  if (Keyboard::isKeyPressed(Keyboard::Escape)){
       window.close();
    }
    
    
    // Handle WASD while playing*********************************
      
		if (state == State::PLAYING)
		{
			// Handle the pressing and releasing of the WASD keys
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player.moveDown();
			}
			else
			{
				player.stopDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				player.moveLeft();
			}
			else
			{
				player.stopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				player.moveRight();
			}
			else
			{
				player.stopRight();
			}
			

		}// End WASD while playing

      
    /*******************************************************/

 if (state == State::LEVELING_UP)
  {

 if (event.key.code == Keyboard::Num1){
    state = State::PLAYING;
    }
    
    
 if (event.key.code == Keyboard::Num2){
    state = State::PLAYING;
    } 
  if (event.key.code == Keyboard::Num3){
    state = State::PLAYING;
    }
    
  if (event.key.code == Keyboard::Num4){
    state = State::PLAYING;
    }
    
  if (event.key.code == Keyboard::Num5){
    state = State::PLAYING;
    }  
    
  if (event.key.code == Keyboard::Num6){
    state = State::PLAYING;
    }
    
 if(state == State::PLAYING) {          
   wave++;
   arena.left =0;
   arena.top = 0;
   arena.height = wave * 500;
   arena.width = wave * 500;
   int tilesize = 50;
   
   // Pass the vertex array by reference 
				// to the createBackground function
				int tileSize = createBackground(background, arena);
   
   player.spawn(arena,resolution, tilesize);
   clock.restart();
      }
  }
 //**************** End LEVELING up****************************************
 
   /************************************************
          UPDATE THE FRAME
    ************************************************/
  
  if (state == State::PLAYING)
{    
   
   Time dt= clock.restart();
  
   float dtAsSeconds= dt.asSeconds();
   
  
   mouseScreenPosition = Mouse::getPosition();
   
   // Convert mouse position to world coordinates of mainView
   mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);
   
   //update the player
   player.update(dtAsSeconds, Mouse::getPosition());
   
   
   Vector2f playerPosition(player.getCenter());
   
   mainView.setCenter(player.getCenter());
   
   }
   
   
   /*******************
     Draw the scene
     ********************/

  if(state == State::PLAYING)
   {

   window.clear();
   window.setView(mainView);
   
   window.draw(background, &textureBackground);
   
   window.draw(player.getSprite());
   
   }
 if (state == State::LEVELING_UP)
		{
		}

		if (state == State::PAUSED)
		{
		}

		if (state == State::GAME_OVER)
		{
		}
   window.display();
   
 }   // End game loop
   return 0;
}


int createBackground(VertexArray& rVA, IntRect arena)
{
	// Anything we do to rVA we are actually doing to background (in the main function)

	// How big is each tile/texture
	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int VERTS_IN_QUAD = 4;

	int worldWidth = arena.width / TILE_SIZE;
	int worldHeight = arena.height / TILE_SIZE;

	// What type of primitive are we using?
	rVA.setPrimitiveType(Quads);

	// Set the size of the vertex array
	rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

	// Start at the beginning of the vertex array
	int currentVertex = 0;
	for (int w = 0; w < worldWidth; w++){
		for (int h = 0; h < worldHeight; h++){
			// Position each vertex in the current quad
			rVA[currentVertex + 0].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 1].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 2].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
			rVA[currentVertex + 3].position = Vector2f((w * TILE_SIZE), (h * TILE_SIZE) + TILE_SIZE);

			// Define the position in the Texture to draw for current quad
			// Either mud, stone, grass or wall
			if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth - 1)
			{
				// Use the wall texture
				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + TILE_TYPES * TILE_SIZE); //(0, 150)
				rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + TILE_TYPES * TILE_SIZE); //(50, 150)
				rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPES * TILE_SIZE); //(50, 200)
				rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + TILE_TYPES * TILE_SIZE);//(0, 200)
			}
			else
			{
				// Use a random floor texture
				srand((int)time(0) + h * w - h);
				int mOrG = (rand() % TILE_TYPES);
				int verticalOffset = mOrG * TILE_SIZE;

				rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
				rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
				rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
				rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

			}

			// Position ready for the next for vertices
			currentVertex = currentVertex + VERTS_IN_QUAD;
		}
	}

	return TILE_SIZE;
}

 
 
