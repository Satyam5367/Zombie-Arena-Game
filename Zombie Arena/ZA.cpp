
#include "Player.cpp"
using namespace sf;
int main()
{
 Vector2f resolution; 
 resolution.x = VideoMode::getDesktopMode().width;
 resolution.y = VideoMode::getDesktopMode().height;
 RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);
 View mainView(FloatRect(0, 0, resolution.x, resolution.y));
 
 Player player;
 IntRect arena;
 
 while (window.isOpen())
{
  Event event;
  while (window.pollEvent(event)){
     if(event.type == event.Closed){
         window.close();
       }  
      }
  if (Keyboard::isKeyPressed(Keyboard::Escape)){
       window.close();
}

   arena.left =0;
   arena.top = 0;
   arena.height =500;
   arena.width = 500;
   int tilesize = 50;
   player.spawn(arena,resolution, tilesize);
   mainView.setCenter(player.getCenter());
   window.clear();
   window.setView(mainView);
   window.draw(player.getSprite());
   window.display();
   }
   return 0;
}
 
 
