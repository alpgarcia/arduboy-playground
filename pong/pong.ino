#include <Arduboy2.h>
Arduboy2 arduboy;

int gamestate = 0;

// Ball
int ballx = 62;
int bally = 0;
int ballsize = 4;
int ballright = 1;
int balldown = 1;

// Paddles
int paddlewidth = 4;
int paddleheight = 9;
int playerx = 0;
int playery = 0;
int computery = 0;
int computerx = 127 - paddlewidth;


void setup() {
  arduboy.begin();
  
  //Seed the random number generator
  arduboy.initRandomSeed();
  
  //Set the game to 60 frames per second
  arduboy.setFrameRate(60);
  
  arduboy.clear();
}

void loop() {

  //Prevent the Arduboy from running too fast
  if (!arduboy.nextFrame()) {
    return;
  }
  
  arduboy.clear();
  arduboy.pollButtons();

  switch (gamestate) {

    case 0:
      //Title screen
      arduboy.setCursor(0, 0);
      arduboy.print("Title Screen");
      //Change the gamestate
      if (arduboy.justPressed(A_BUTTON)) {
        gamestate = 1;
      }
      break;

    case 1:
      //Gameplay screen
      arduboy.setCursor(0, 0);
      arduboy.print("Gameplay");
      //Draw the ball
      arduboy.fillRect(ballx, bally, ballsize, ballsize, WHITE);
      //Move the ball right
      if(ballright == 1) {
        ballx = ballx + 1;
      }
      //Move the ball left
      if(ballright == -1) {
        ballx = ballx - 1;
      }
      //Reflect the ball off of the left side of the screen
      if(ballx == 0) {
        ballright = 1;
      }
      //Reflect the ball off of the right side of the screen
      if(ballx + ballsize == 127) {
        ballright = -1;
      }
      //Move the ball down
      if(balldown == 1) {
        bally = bally + 1;
      }
      //Move the ball up
      if(balldown == -1) {
        bally = bally - 1;
      }
      //Reflect the ball off of the top of the screen
      if(bally == 0) {
        balldown = 1;
      }
      //Reflect the ball off of the bottom of the screen
      if(bally + ballsize == 63) {
        balldown = -1;
      }

      //Draw the player's paddle
      arduboy.fillRect(playerx, playery, paddlewidth, paddleheight, WHITE);
      //If the player presses Up and the paddle is not touching the top of the screen, move the paddle up
      if (arduboy.pressed(UP_BUTTON) && playery > 0) {
        playery = playery - 1;
      }
      //If the player presses down and the paddle is not touching the bottom of the screen, move the paddle down
      if (arduboy.pressed(DOWN_BUTTON) && playery + paddleheight < 63) {
        playery = playery + 1;
      }

      //Draw the computer's paddle
      arduboy.fillRect(computerx, computery, paddlewidth, paddleheight, WHITE);
      //If the ball is higher than the computer's paddle, move the computer's paddle up
      if(bally < computery) {
        computery = computery - 1;
      }
      //If the bottom of the ball is lower than the bottom of the computer's paddle, move the comptuer's paddle down
      if(bally + ballsize > computery + paddleheight) {
        computery = computery + 1;
      }
      
      //Change the gamestate
      if (arduboy.justPressed(A_BUTTON)) {
        gamestate = 2;
      }
      break;

    case 2:
      //Win screen
      arduboy.setCursor(0, 0);
      arduboy.print("Win Screen");
      //Change the gamestate
      if (arduboy.justPressed(A_BUTTON)) {
        gamestate = 3;
      }
      break;

    case 3:
      //Game over screen
      arduboy.setCursor(0, 0);
      arduboy.print("Game Over Screen");
      //Change the gamestate
      if (arduboy.justPressed(A_BUTTON)) {
        gamestate = 0;
      }
      break;
  }
  
  arduboy.display();
}
