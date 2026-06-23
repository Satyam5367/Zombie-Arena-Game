#include<cmath>
#include "Player3.h"
Player:: Player(){
   m_Speed = START_SPEED;
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
      
float Player::getRotation()
{
	return m_sprite.getRotation();
}      
      
      
 void Player::moveLeft()
{
	m_LeftPressed = true;
}

void Player::moveRight()
{
	m_RightPressed = true;
}

void Player::moveUp()
{
	m_UpPressed = true;
}

void Player::moveDown()
{
	m_DownPressed = true;
}

void Player::stopLeft()
{
	m_LeftPressed = false;
}

void Player::stopRight()
{
	m_RightPressed = false;
}

void Player::stopUp()
{
	m_UpPressed = false;
}

void Player::stopDown()
{
	m_DownPressed = false;
}


void Player::update(float elapsedTime, Vector2i mousePosition){

if (m_UpPressed)
	{
		m_Position.y -= m_Speed * elapsedTime;
	}

	if (m_DownPressed)
	{
		m_Position.y += m_Speed * elapsedTime;
	}

	if (m_RightPressed)
	{
		m_Position.x += m_Speed * elapsedTime;
	}

	if (m_LeftPressed)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}


 
 m_sprite.setPosition(m_Position);
 
 // Calculate the angle the player is facing
	float angle = (atan2(mousePosition.y - m_Resolution.y / 2, mousePosition.x - m_Resolution.x / 2)* 180) / 3.141;

	m_sprite.setRotation(angle);    
	
	} 
     
       
