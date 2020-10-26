
#include <Arduboy2.h>
Arduboy2 arduboy;

int counter;

void setup() {
  arduboy.begin();
  arduboy.clear();
  counter = 0;

}

void loop() {
  arduboy.clear();
  arduboy.setCursor(0, 0);
  counter = counter + 1;
  arduboy.print(counter);
  arduboy.display();
}
