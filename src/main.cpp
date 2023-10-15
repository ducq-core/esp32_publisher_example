#include "Program.hpp"

Program *program = nullptr;

void setup() {
	program = new Program();
}

void loop() {
  program->loop();
}