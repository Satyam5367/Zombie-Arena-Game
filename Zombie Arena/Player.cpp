#include "Player.h"
Player:: Player(){
   m_Texture.loadFromFile("graphics/player.png");
   m_sprite.setTexture(m_Texture);
   m_sprite.setOrigin(25, 25);
  }
  
void Player::spawn(IntRect arena, Vector2f resolution, int tilesize){
   m_Resolution.x = resolution.x;
   m_Resolution.y = resolution.y;
   
   m_Arena.left = arena.left;
   m_Arena.top = arena.top;
   m_Arena.height = arena.height;
   m_Arena.width = arena.width;
   
   m_Position.x = arena.width/2;
   m_Position.y = arena.height/2;
  }
FloatRect Player::getPosition(){
  return m_sprite.getGlobalBounds();
  }
     
 Vector2f Player::getCenter(){
      return  m_Position;
      }
 Sprite Player::getSprite(){
      return m_sprite;
      }
       
