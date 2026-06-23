//using the bullets
//Putting the crosshair in place of mousePointer
//Putting the Zombies
//Putting the arena
//Putting the WASD  keys
//Setting up levels
//Moving the player with respect to mouse pointer
#include <SFML/Graphics.hpp>
#include "Player3.cpp"
#include"zombie.cpp"
#include "arena1.cpp"
#include"bullet.cpp"
#include<cmath>

int createBackground(VertexArray& rVA, IntRect arena);
Zombie* createHorde(int numZombies,IntRect arena);
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
 RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);
//********************************************************
 
 View mainView(FloatRect(0, 0, resolution.x, resolution.y)); // SFML View for the main action
 
 window.setView(mainView);
 

// Create a view for the HUD
View hudView(sf::FloatRect(0, 0, resolution.x, resolution.y));
 

// Load the font***************************************
Font font;
font.loadFromFile("fonts/zombiecontrol.ttf");

// Paused***state*********************************************
Text pausedText;
pausedText.setFont(font);
pausedText.setCharacterSize(155);
pausedText.setFillColor(Color::White);
pausedText.setPosition(400, 400);
pausedText.setString("Press Enter to continue");
//------------------------------------------------------------------- 
 
 
 //********************************************
 int numZombies;
     int numZombiesAlive;
     Zombie *zombies=nullptr;
 //*********************************************  
 
//******BULLETS*************
 Bullet bullets[100];
int currentBullet = 0;
int bulletsSpare = 24;
int bulletsInClip = 6;
int clipSize = 6;
float fireRate = 1;
//**************************************** 

Time lastPressed;  
 Clock clock;
 
Time gameTimeTotal; 
 
 Vector2f mouseWorldPosition;      //mouse in relation to world coordinates
 Vector2i mouseScreenPosition;     //mouse in relation to screen coordinates
 window.setMouseCursorVisible(false);
 
//******putting ********the cross hair********************** 
 Texture textureCrosshair;
 textureCrosshair.loadFromFile("graphics/crosshair.png");
 Sprite spriteCrosshair;
 spriteCrosshair.setTexture(textureCrosshair);
 spriteCrosshair.setOrigin(25, 25);
//***********************************************************
 
 Player player;   //instance of the Player class
 IntRect arena;   //boundaries of the arena
 
 
 // Create the background
 VertexArray background;
 // Load the texture for our background vertex array
 Texture textureBackground;
 textureBackground.loadFromFile("graphics/background_sheet.png");
 
 
 // About the game
 int score = 0;
 int hiScore = 0;
 while (window.isOpen())
{
  Event event;
  while (window.pollEvent(event)) //START OF EVENT POLLING
  
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
             
             //***********************************Bullet
            // currentBullet = 0;
	     //bulletsSpare = 24;
	     //bulletsInClip = 6;
	     //clipSize = 6;
	     //fireRate = 1;
            //******************************** 
            }
            
          if (state == State::PLAYING){
          
                }
          }
                } // END EVENT POLLING
     
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
			
			
	     //--------------------- Fire a bullet----------------------------------------------------------
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		   {

			if (gameTimeTotal.asMilliseconds()- lastPressed.asMilliseconds() > 1000 / fireRate && bulletsInClip > 0)
			       {
                                  // Pass the centre of the player 
				   // and the centre of the cross-hair
				   // to the shoot function
				    bullets[currentBullet].shoot(player.getCenter().x, player.getCenter().y,	mouseWorldPosition.x, mouseWorldPosition.y);
                                      currentBullet++;
					if (currentBullet > 99)
					{
						currentBullet = 0;
					}
					lastPressed = gameTimeTotal;

					bulletsInClip--;
				}

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
   
   //************************Zombies**************
   numZombies=wave*3;
   delete[]zombies;
	zombies=createHorde(numZombies,arena);
 //*****************************************************	
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
   
   gameTimeTotal += dt;
  
   float dtAsSeconds= dt.asSeconds();
   
  
   mouseScreenPosition = Mouse::getPosition();
   
   // Convert mouse position to world coordinates of mainView
   mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);
   
 // Set the crosshair to the mouse world location
   spriteCrosshair.setPosition(mouseWorldPosition);
   
   //update the player
   player.update(dtAsSeconds, Mouse::getPosition());
   
   
   Vector2f playerPosition(player.getCenter());
   
   mainView.setCenter(player.getCenter());
   
   //**************Zombies****************************
   for(int i=0;i<numZombies;i++){
	zombies[i].update(dtAsSeconds,playerPosition);
		}
   //*********************************************
   
   
   // Update any bullets that are in-flight
	for (int i = 0; i < 100; i++)
	  {
	      if (bullets[i].isInFlight())
		   {
		      bullets[i].update(dtAsSeconds);
				}
			}
   //Collision Detection
      for (int i = 0; i < 100; i++)
	  {
	      for (int j = 0; j < numZombies; j++)
		  {
		     if (bullets[i].isInFlight() &&
			  zombies[j].isAlive())
			     {
				 if (bullets[i].getPosition().intersects(zombies[j].getPosition()))
					{
					   // Stop the bullet
					     bullets[i].stop();
					     
					     // Register the hit and see if it was a kill
							if (zombies[j].hit()) {
								// Not just a hit but a kill too
								numZombiesAlive--;

								// When all the zombies are dead (again)
								if (numZombiesAlive == 0) {
									state = State::LEVELING_UP;
								}
							}

						}
					}

				}
        }// End zombie being shot
   
   }  // End updating the scene
   
   
   /*******************
     Draw the scene
     ********************/

  if(state == State::PLAYING)
   {

  window.clear();
  window.setView(mainView);
   
   window.draw(background, &textureBackground);
   
   window.draw(player.getSprite());
   
   //**Draw the Bullet*********
   for (int i = 0; i < 100; i++)
	{
	    if (bullets[i].isInFlight())
		  {
		      window.draw(bullets[i].getShape());
			}
		}
//****************************************************		
		
   
   //******************Zombies*********************
   for(int i=0; i<numZombies;i++){
	window.draw(zombies[i].getSprite());
			}
   //*******************************************		
   
   //Draw the crosshair
    window.draw(spriteCrosshair); 			
   
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
		
  if (state == State::PAUSED)
	{
	    window.draw(pausedText);
	    }		
		
   window.display();
   
 }   // End game loop
   return 0;
}


Zombie* createHorde(int numZombies,IntRect arena){
	Zombie* zombies=new Zombie[numZombies];
	int maxX=arena.width-20;
	int minX=arena.left+20;
	int maxY=arena.height-20;
	int minY=arena.top+20;
	
	for(int i=0;i<numZombies;i++){
		srand((int)time(0)*i);
		int side=(rand()%4);
		float x,y;
		switch(side){
			case 0:
				x=minX;
				y=(rand()%maxY)+minY;
				break;
			case 1:
				x=maxX;
				y=(rand()%maxY)+minY;
				break;
			case 2:
				y=minY;
				x=(rand()%maxX)+minX;
				break;
			case 3:
				y=maxY;
				x=(rand()%maxX)+minX;
				break;
		
		}
		srand((int)time(0)*i*2);
		int type=(rand()%3);
		zombies[i].spawn(x,y,type,i);
	
	}
	return zombies;
}



