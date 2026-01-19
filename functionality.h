/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */


#include <iostream>


 //---Piece Starts to Fall When Game Starts---//
 
void
fallingPiece (float &timer, float &delay, int &colorNum, bool shrink)
{
  if (timer > delay)
    {
      for (int i = 0; i < 4; i++)
	{
	  point_2[i][0] = point_1[i][0];
	  point_2[i][1] = point_1[i][1];
	  point_1[i][1] += 1;	//How much units downward
	  point_shadow[i][0] = point_1[i][0];
	  point_shadow[i][1] = point_1[i][1];
	}

      while (shadowanamoly ())	//Make shadow fall down 
	for (int i = 0; i < 4; i++)
	  point_shadow[i][1] += 1;
      for (int i = 0; i < 4; i++)	//bringing shadow 1 step up to compensate a iteration
	point_shadow[i][1] -= 1;

      if (!anamoly ())
	{			// if touches block touches blocks or walls
	  for (int i = 0; i < 4; i++)
	    gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
	  colorNum = 1 + rand () % 7;
	  int n = rand () % 7;	//shape variable

	  for (int i = 0; i < 4; i++)
	    {			//For creating main block                               
	      point_1[i][0] = BLOCKS[n][i] % 2;
	      point_1[i][1] = BLOCKS[n][i] / 2;
	      point_1[i][0] = point_1[i][0] + 4;

	    }


	  for (int i = 0; i < 4; i++)
	    {
	      point_shadow[i][0] = point_1[i][0];
	      point_shadow[i][1] = point_1[i][1];
	    }



	}


    }
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///

//-------------------------------------------------------  <              BOMB                  >--------------------------------------------------------------------
// This Function is responsible for the creation, movement and behavior of bomb
// We take score and time as input and decide when to make the bomb fall according to those circumstances
// This is executed subsequenly after falling block and actions happen to both simultaenously
void
bomb (float &timer, float &delay, int &colorbomb, int &score,
      float total_time, bool shrink)
{

  if (timer > delay)
    {
      int n = 7;
      int position = 1 + rand () % 8;

      if ((total_time > 40 && total_time < 41) || (score == 40))
	{

	  for (int i = 0; i < 4; i++)
	    {
	      point_bomb[i][0] = BLOCKS[n][i] % 2;
	      point_bomb[i][1] = BLOCKS[n][i] / 2;
	      point_bomb[i][0] = point_bomb[i][0] + position;
	      point_bomb[i][1] = point_bomb[i][1] + 1;

	    }

	}

      if ((total_time > 70 && total_time < 71) || (score == 80))
	{

	  for (int i = 0; i < 4; i++)
	    {
	      point_bomb[i][0] = BLOCKS[n][i] % 2;
	      point_bomb[i][1] = BLOCKS[n][i] / 2;
	      point_bomb[i][0] = point_bomb[i][0] + position;
	      point_bomb[i][1] = point_bomb[i][1] + 1;

	    }

	}


      if (point_bomb[0][1] >= 1 || point_bomb[1][1] >= 1
	  || point_bomb[2][1] >= 1 || point_bomb[3][1] >= 1)
	for (int i = 0; i < 4; i++)
	  {
	    point_tbomb[i][0] = point_bomb[i][0];
	    point_tbomb[i][1] = point_bomb[i][1];
	    point_bomb[i][1] += 1;	//How much units downward
	  }

      if (!bombanamoly ())
	{


	  if (point_bomb[0][1] >= M || point_bomb[1][1] >= M
	      || point_bomb[2][1] >= M || point_bomb[3][1] >= M)
	    int c = 0;

	  else
	    {
	      bool iteration = 1;

	      for (int i = 0; i < 4; i++)
		{

		  if (iteration)
		    gameGrid[point_tbomb[i][1]][point_tbomb[i][0]] =
		      colorbomb;

		  iteration = 0;


		  if (gameGrid[point_tbomb[i][1]][point_tbomb[i][0]] ==
		      gameGrid[point_tbomb[i][1] + 1][point_tbomb[i][0]])
		    {

		      for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			  gameGrid[i][j] = 0;
		    }

		  else if (gameGrid[point_tbomb[i][1]][point_tbomb[i][0]] !=
			   gameGrid[point_tbomb[i][1] + 1][point_tbomb[i][0]])
		    {
		      gameGrid[point_tbomb[i][1] + 1][point_tbomb[i][0]] = 0;
		      gameGrid[point_tbomb[i][1] + 2][point_tbomb[i][0]] = 0;
		      gameGrid[point_tbomb[i][1] + 1][point_tbomb[i][0] + 1] =
			0;
		      gameGrid[point_tbomb[i][1] + 2][point_tbomb[i][0] + 1] =
			0;

		    }
		}
	      for (int i = 0; i < 4; i++)
		gameGrid[point_tbomb[i][1]][point_tbomb[i][0]] = 0;
	    }

	  for (int i = 0; i < 4; i++)
	    {
	      point_bomb[i][0] = BLOCKS[n][i] % 2;
	      point_bomb[i][1] = BLOCKS[n][i] / 2;
	    }



	  colorbomb = 1 + rand () % 7;


	}
      timer = 0;
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

// -------------------------------------------------<                Moves the block Left Or Right                >    ----------------------------------------------






void
delta_xmovement (int delta_x)	// Delta X is the input given by left/right key - This Functions moves the block to left or right depending on input
{
  for (int i = 0; i < 4; i++)
    {				// All rows (all elements) move one by one (LOOP)
      point_2[i][0] = point_1[i][0];	// Remembering Values
      point_2[i][1] = point_1[i][1];
      point_1[i][0] = point_1[i][0] + delta_x;
    }


  if (!anamoly ())
    {				// If Object hits side walls reset the position to last remembered position (1 step backwards in x direction)
      for (int i = 0; i < 4; i++)
	{
	  point_1[i][0] = point_2[i][0];
	  point_1[i][1] = point_2[i][1];
	}
    }
  return;

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------<                  SpaceBar Function                    >------------------------------------------------
void
block_fall () // - This function makes the block fall, It increases Y axis value until it hits another block or wall
{
  while (anamoly ())
    {				//Till the object hits a wall or another object
      for (int i = 0; i < 4; i++)
	{			// Row counter
	  point_2[i][0] = point_1[i][0];	// Remebering old values in Point_2 - X Axis
	  point_2[i][1] = point_1[i][1];	// Remembering old values in Point_2 - Y Axis
	  point_1[i][1] = point_1[i][1] + 1;
	}			// Incrementing 1 in Y-Axis
    }

  for (int i = 0; i < 4; i++)
    {				// To Bring back the object 1 step up because it goes under the frame or overwrites.
      point_1[i][1] = point_1[i][1] - 1;
    }

  return;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------<         Function to destroy and replace last line when it is full             >----------------------------------------------
void
destroy (int &score, int &destroy_count, bool shrink)   //This function destroys a line when full then using recursion calculates score depending on how many
//lines are destroyed           // If shrink == 1 function ignore side columns and grid border.
{

  int remember_row = 0, count = 0;


  if (shrink == 0)
    {

      for (int i = M - 1; i > 0; i--)
	{
	  count = 0;

	  for (int j = 0; j < N; j++)
	    {
	      if (gameGrid[i][j] == 0)
		break;
	      else if (gameGrid[i][j] != 0)
		count += 1;
	    }

	  if (count == 10)
	    {
	      remember_row = i;
	      break;
	    }

	}

      if (count != 10)
	return;

      std::cout << "Remember row ==  " << remember_row;

      for (int j = 0; j < N; j++)
	{
	  gameGrid[remember_row][j] = 0;
	}



      for (int i = remember_row; i > 1; i--)
	{			
	  for (int j = 0; j < N; j++)
	    {			
	      gameGrid[i][j] = gameGrid[i - 1][j];	
	    }
	}
    }


  if (shrink == 1)
    {

      for (int i = M - 2; i > 0; i--)
	{
	  count = 0;

	  if (i == 0)
	    continue;

	  for (int j = 0; j < N; j++)
	    {
	      if (gameGrid[i][j] == 0)
		break;
	      else if (gameGrid[i][j] != 0)
		count += 1;
	    }



	  if (count == 10)
	    {
	      remember_row = i;
	      break;
	    }

	}

      if (count != 10)
	return;

      for (int j = 0; j < N; j++)
	{
	  gameGrid[remember_row][j] = 0;
	}



      for (int i = remember_row; i > 1; i--)
	{			// Control Rows
	  for (int j = 0; j < N; j++)
	    {			// Control Columns
	      gameGrid[i][j] = gameGrid[i - 1][j];	// Replace All rows with upper row ( Fill the destroyed row)
	    }
	}
    }






  destroy_count++;
  if (destroy_count == 1)
    score += 10;

  else if (destroy_count == 2)
    score += 20;

  else if (destroy_count == 3)
    score += 30;

  else if (destroy_count == 4)
    score += 40;


  destroy (score, destroy_count, shrink);



  return;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------------- <              Rotate Function                    > ---------------------------------------------------------

void
rotate_block ()  // THis function exchanges Y axis and X axis values and thus rotates piece, if object hits walls object reverts to previous state
{				//columns exchange




  for (int i = 0; i < 4; i++)
    {				// Row counter
      point_2[i][0] = point_1[i][0];	// Remebering old values in Point_2 - X Axis
      point_2[i][1] = point_1[i][1];
      point_1[i][0] = point_1[i][1];	// Remembering old values in Point_2 - Y Axis
      point_1[i][1] = point_2[i][0];
    }				// Incrementing 1 in Y-Axis


  if (!anamoly)
    {
      for (int i = 0; i < 4; i++)
	{
	  point_1[i][0] = point_2[i][0];
	  point_1[i][1] = point_2[i][1];
    }}
  return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------<                 Game Over Function                       >--------------------------------------------------------
bool
game_over (bool shrink)	// checks all columns of the top most row - if not 0 - game is over -  returns -1  
// Also accounts for shrink factor if grid is shrinked it recalculates top most row
{

  if (shrink == 0)
    {
      for (int i = 0; i < N; i++)
	{			// Checks whether full Top row is filled or not
	  if (gameGrid[0][i] != 0)	// if - Yes
	    return 1;		// Return to main.cpp
	}
    }

  if (shrink == 1)
    {

      for (int i = 1; i < N; i++)
	{			// Checks whether full Top row is filled or not

	  if (i == 9)
	    continue;

	  if (gameGrid[1][i] != 0)
	    return 1;
	}

    }
  return 0;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------  <                        BONUS                       >---------------------------------------------------------

void
grid_clear ()    // Press Z to clear Grid         loop to make all rows and columns 0
{
  for (int i = 0; i < M; i++)
    for (int j = 0; j < N; j++)
      gameGrid[i][j] = 0;
}



//------------------------------------------------------------------------------------------------------------------------------------------------------------------    
//--------------------------------------  <                    Grid shrink                   >---------------------------------------------------------
void
grid_shrink (float total_timer, bool & shrink)  //Takes time as input and then accordingly shortens grid when time is 50 seconds - Also activates shrink bool to 1
{
  if (total_timer > 50 && total_timer < 52)
    {

      for (int j = 0; j < N; j++)
	gameGrid[0][j] = 11;

      for (int j = 0; j < N; j++)
	gameGrid[M - 1][j] = 11;

      for (int i = 0; i < M; i++)
	gameGrid[i][0] = 11;

      for (int i = 0; i < M; i++)
	gameGrid[i][N - 1] = 11;

      shrink = 1;
    }




  return;
}


















///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////

