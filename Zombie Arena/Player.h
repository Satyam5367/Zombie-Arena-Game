#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;
class Player{
    Vector2f m_Position;
    Sprite m_sprite;
    Texture m_Texture;
    Vector2f m_Resolution;
    IntRect m_Arena;
    int m_Tilesize;
    
   public:
       Player();
       FloatRect getPosition();
       Vector2f getCenter();
       Sprite getSprite();
       void spawn(IntRect arena, Vector2f resolution, int tilesize);
      };
    

