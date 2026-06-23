
//Setting up levels
//Moving the player with respect to mouse pointer
#include <SFML/Graphics.hpp>
#include "Player1.cpp"
#include<cmath>
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
 
 window.setView(mainView);
 Clock clock;
 
 
 
 Vector2f mouseWorldPosition;      //mouse in relation to world coordinates
 Vector2i mouseScreenPosition;     //mouse in relation to screen coordinates
 window.setMouseCursorVisible(true);
 
 Player player;   //instance of the Player class
 IntRect arena;   //boundaries of the arena
 
 
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
            
          if (state == State::PLAYING)
          {
            }  
       }  
  
     
     }      // End event polling
     
   // Handle the player quitting   
  if (Keyboard::isKeyPressed(Keyboard::Escape)){
       window.close();
    }

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
 
 
