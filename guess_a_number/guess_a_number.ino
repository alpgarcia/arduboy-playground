#include <Arduboy2.h>
Arduboy2 arduboy;
int playerwin;
int attempts;
int guessednumber;
int randomnumber;
int lastguess;


void setup() {
  arduboy.begin();
  arduboy.clear();
  arduboy.initRandomSeed();
  playerwin = 0;
  attempts = 0;
  guessednumber = 0;
  randomnumber = random(1, 101);

}

void loop() {
  arduboy.clear();
  arduboy.pollButtons();
  if (playerwin == 0) {
    //Ask the player for a number and play the game
    if (attempts == 7) {
      //Game Over screen
      game_over();
    } else {
      //Player has more attempts
      if (arduboy.justPressed(UP_BUTTON)) {
        guessednumber = guessednumber + 1;
      }
      if (arduboy.justPressed(DOWN_BUTTON)) {
        guessednumber = guessednumber - 1;
      }
      if (arduboy.justPressed(LEFT_BUTTON)) {
        guessednumber = guessednumber - 5;
      }
      if (arduboy.justPressed(RIGHT_BUTTON)) {
        guessednumber = guessednumber + 5;
      }
      if (arduboy.justPressed(A_BUTTON)) {
        if (guessednumber == randomnumber) {
          playerwin = 1;
        } else {
          attempts = attempts + 1;
          lastguess = guessednumber;
        }
      }
      arduboy.setCursor(0, 0);
      arduboy.print("Attempt: ");
      arduboy.print(attempts);
      arduboy.print("\n");
      arduboy.print("Number to guess: ");
      arduboy.print(guessednumber);
      arduboy.print("\n");
      if (attempts == 0) {
        arduboy.print("Good luck!");
      } else {
        arduboy.print(lastguess);
        if (lastguess > randomnumber) {
          arduboy.print(" is too high!");
        }
        if( lastguess < randomnumber ) {
          arduboy.print(" is too low!");
        }
      }
    }
  } else {
    //Tell the player that they won!
    win();
  }
  arduboy.display();
}

void win() {
  arduboy.setCursor(0, 0);
  arduboy.print("You won!");
  arduboy.print("\n");
  arduboy.print("Correct Number: ");
  arduboy.print(randomnumber);

  start_again();  
}

void game_over() {
  arduboy.setCursor(0, 0);
  arduboy.print("You lost!");
  arduboy.print("\n");
  arduboy.print("Correct Number: ");
  arduboy.print(randomnumber);
  start_again();
}

void start_again() {
  if (arduboy.justPressed(A_BUTTON)) {
    randomnumber = random(1, 101);
    attempts = 0;
    playerwin = 0;
  }
}
