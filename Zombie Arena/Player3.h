#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class Player{
    const float START_SPEED = 200;
   float m_Speed;
    Vector2f m_Position;
    Sprite m_sprite;
    Texture m_Texture;
    Vector2f m_Resolution;
    IntRect m_Arena;
    int m_Tilesize;
    // Which directions is the player currently moving in
	bool m_UpPressed;
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;
    
   public:
       Player();
       FloatRect getPosition();
       Vector2f getCenter();
       Sprite getSprite();
       void spawn(IntRect arena, Vector2f resolution, int tilesize);
       void update(float elapsedTime, Vector2i mousePosition);
       float getRotation();
        void moveLeft();
        void moveRight();
       void moveUp();
      void moveDown();
    
      void stopLeft();
     void stopRight();
      void stopUp();
       void stopDown();
       
      };
    

