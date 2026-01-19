/*PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 *You don't need to change anything in the driver code/main function except the part(s) where instructed.
 *You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 *The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 *Load the images into the textures objects from img directory.
 *Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 *SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 *TIP: You can study SFML for drawing scenes, sprites and window.
 **/
#include <SFML/Graphics.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
using namespace sf;
int
main ()
{
  srand (time (0));

  RenderWindow window (VideoMode (500, 480), title);	//320,480

  Texture obj1, obj2, obj3, obj4, obj5, obj6;
  obj1.loadFromFile ("img/tiles.png");
  obj2.loadFromFile ("img/background.png");
  obj3.loadFromFile ("img/frame.png");
  obj4.loadFromFile ("img/tiles.png");
  obj5.loadFromFile ("img/tiles.png");
  obj6.loadFromFile ("img/backgroundedit.png");

  /*
     Load "frames.png","tiles.png" and "background.png" for Texture objects
   */
  Sprite sprite (obj1), background (obj2), frame (obj3), spritebomb (obj4),
    spriteshadow (obj5), pausesprite (obj6);
  int delta_x = 0, colorNum = 1, score = 0, destroy_count = 0, colorshadow =
    13, level = 1, colorbomb = 1;
  float timer = 0, delay = 0.3, timer22 = 0;
  bool rotate = 0, fall = 0, pause = 0, terminate = 0, shrink =
    0, start_gate = 1, over_button = 0, bomb_iteration = 1;
  Clock clock;
  std::string strscore, strlevel, strtime;

  Font open_sans;
  open_sans.loadFromFile ("img/OpenSans-Medium.ttf");

  //display text
  Text my_text;
  my_text.setFont (open_sans);
  my_text.setCharacterSize (20);
  my_text.setString ("SCORE: \nLEVEL: \nTime: ");
  my_text.setPosition (325, 100);

  //display score, level, time
  Text my_score;
  Text my_level;
  Text my_time;
  Text endgame;
  Text unpause;
  Text restart;
  Text game_overtxt;

  my_score.setFont (open_sans);
  my_score.setCharacterSize (20);
  my_score.setPosition (400, 100);

  my_level.setFont (open_sans);
  my_level.setCharacterSize (20);
  my_level.setPosition (400, 127);

  my_time.setFont (open_sans);
  my_time.setCharacterSize (20);
  my_time.setPosition (400, 155);

  endgame.setFont (open_sans);
  endgame.setCharacterSize (20);
  endgame.setPosition (150, 300);
  endgame.setString ("END GAME - Press Q ");

  unpause.setFont (open_sans);
  unpause.setCharacterSize (20);
  unpause.setPosition (150, 250);
  unpause.setString ("UNPAUSE - PRESS L");

  restart.setFont (open_sans);
  restart.setCharacterSize (20);
  restart.setPosition (150, 200);
  restart.setString ("RESTART - PRESS R");

  game_overtxt.setFont (open_sans);
  game_overtxt.setCharacterSize (30);
  game_overtxt.setPosition (200, 200);
  game_overtxt.setString ("GAME OVER");


  float total_timer = 0;



  Music music;
  music.openFromFile ("Tetris.ogg");
  music.play ();
  bool change_music = 1;
  bool change_music2 = 0;


  while (window.isOpen ())
    {
      if (pause)
	{
	  window.clear (Color::Black);
	  window.draw (pausesprite);
	  window.draw (endgame);
	  window.draw (unpause);
	  window.draw (restart);
	  window.display ();
	  if (change_music)
	    {
	      music.openFromFile ("pause_music.ogg");
	      music.play ();
	      change_music2 = 1;
	    }
	  change_music = 0;
	}

      if (pause == 0 && change_music2 == 1)
	{
	  change_music2 = 0;
	  change_music = 1;
	  music.openFromFile ("Tetris.ogg");
	  music.play ();
	}


      strscore = std::to_string (score);
      my_score.setString (strscore);

      strlevel = std::to_string (level);
      my_level.setString (strlevel);

      strtime = std::to_string (total_timer);
      my_time.setString (strtime);


      float time = clock.getElapsedTime ().asSeconds ();
      total_timer += clock.getElapsedTime ().asSeconds ();
      clock.restart ();
      timer += time;
      delta_x = 0;
      fall = 0;
      rotate = 0;
      destroy_count = 0;

      if (score == 100)
	level = 2;

      if (level == 1)
	delay = 0.3;
      else if (level == 2)
	delay = 0.15;

      //---Event Listening Part---//
      Event e;
      while (window.pollEvent (e))
	{
	  //Event is occurring - until the game is in running state
	  if (e.type == Event::Closed)	//If cross/close is clicked/pressed
	    window.close ();	//Opened window disposes
	  if (e.type == Event::KeyPressed)
	    {
	      //If any other key (not cross) is pressed
	      if (e.key.code == Keyboard::Up)	//Check if the other key pressed is UP key
		rotate = true;	//Rotation gets on
	      else if (e.key.code == Keyboard::Left)	//Check if the other key pressed is LEFT key
		delta_x = -1;	//Change in X-Axis - Negative
	      else if (e.key.code == Keyboard::Right)	//Check if the other key pressed is RIGHT key
		delta_x = 1;	//Change in X-Axis - Positive
	      else if (e.key.code == Keyboard::Space)	//If Space key is pressed fall==1
		fall = 1;
	      else if (e.key.code == Keyboard::H)	//If H key is pressed pause == 1
		pause = 1;
	      else if (e.key.code == Keyboard::L)	//If L key is pressed pause == 0
		pause = 0;
	    }
	}

      if (Keyboard::isKeyPressed (Keyboard::Down))	
	delay = 0.05;		
      if (Keyboard::isKeyPressed (Keyboard::Q))
	over_button = 1;
      if (Keyboard::isKeyPressed (Keyboard::Z))
	grid_clear ();
      




      if (Keyboard::isKeyPressed (Keyboard::R))
	{
	  //Just another way to detect key presses without event listener
	  for (int i = 0; i < M; i++)
	    {
	      for (int j = 0; j < N; j++)
		{
		  gameGrid[i][j] = 0;
		}
	    }
	  score = 0;
	  pause = 0;
	  total_timer = 0;
	  for (int i = 0; i < 4; i++)
	    {
	      point_1[i][0] = BLOCKS[7][i] % 2;
	      point_1[i][1] = BLOCKS[7][i] / 2;
	    }
	}

      ///////////////////////////////////////////////
      ///***START CALLING YOUR FUNCTIONS HERE ***///



      if (pause == 0)		// run all functions if pause == 0
	{


	  fallingPiece (timer, delay, colorNum, shrink);
	  grid_shrink (total_timer, shrink);
	  bomb (timer, delay, colorbomb, score, total_timer, shrink);
	  delta_xmovement (delta_x);
	  destroy (score, destroy_count, shrink);

	  if (fall)
	    block_fall ();

	  if (rotate)
	    rotate_block ();

	  if (game_over (shrink) || over_button)
	    {
	      clock.restart ();
	      timer22 = 0;
	      while (timer22 < 10000)
		{

		  timer22 += clock.getElapsedTime ().asSeconds ();
		  window.clear (Color::Black);
		  window.draw (game_overtxt);
		  window.display ();
		}
	      return -1;
	    }
	}

      ///***YOUR CALLING STATEMENTS END HERE ***///
      //////////////////////////////////////////////

      if (pause == 0)
	{
	  window.clear (Color::Black);
	  window.draw (background);
	  for (int i = 0; i < M; i++)
	    {
	      for (int j = 0; j < N; j++)
		{
		  if (gameGrid[i][j] == 0)
		    continue;
		  sprite.
		    setTextureRect (IntRect (gameGrid[i][j] * 18, 0, 18, 18));
		  sprite.setPosition (j * 18, i * 18);
		  sprite.move (28, 31);	//offset
		  window.draw (sprite);
		}
	    }

	  for (int i = 0; i < 4; i++)
	    {
	      sprite.setTextureRect (IntRect (colorNum * 18, 0, 18, 18));
	      sprite.setPosition (point_1[i][0] * 18, point_1[i][1] * 18);
	      sprite.move (28, 31);
	      window.draw (sprite);
	    }

	  // sprite shadow

	  for (int i = 0; i < M; i++)
	    {
	      for (int j = 0; j < N; j++)
		{
		  if (gameGrid[i][j] == 0)
		    continue;
		  spriteshadow.
		    setTextureRect (IntRect (gameGrid[i][j] * 18, 0, 18, 18));
		  spriteshadow.setPosition (j * 18, i * 18);
		  spriteshadow.move (28, 31);	//offset
		  window.draw (spriteshadow);
		}
	    }

	  for (int i = 0; i < 4; i++)
	    {
	      spriteshadow.
		setTextureRect (IntRect (colorshadow * 18, 0, 18, 18));
	      spriteshadow.setPosition (point_shadow[i][0] * 18,
					point_shadow[i][1] * 18);
	      spriteshadow.move (28, 31);
	      window.draw (spriteshadow);
	    }


	  // sprite bomb

	  for (int i = 0; i < M; i++)
	    {
	      for (int j = 0; j < N; j++)
		{
		  if (gameGrid[i][j] == 0)
		    continue;
		  spritebomb.
		    setTextureRect (IntRect (gameGrid[i][j] * 18, 0, 18, 18));
		  spritebomb.setPosition (j * 18, i * 18);
		  spritebomb.move (28, 31);	//offset
		  window.draw (spritebomb);
		}
	    }

	  for (int i = 0; i < 4; i++)
	    {
	      spritebomb.setTextureRect (IntRect (colorbomb * 18, 0, 18, 18));
	      spritebomb.setPosition (point_bomb[i][0] * 18,
				      point_bomb[i][1] * 18);
	      spritebomb.move (28, 31);
	      window.draw (spritebomb);
	    }


	  //---The Final on Which Everything is Drawn Over is Loaded---//
	  window.draw (frame);
	  window.draw (my_text);
	  window.draw (my_score);
	  window.draw (my_level);
	  window.draw (my_time);
	  //---The Window that now Contains the Frame is Displayed---//
	  window.display ();
	}
    }

  return 0;

}

