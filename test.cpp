#include <iostream>
#include <string>

#include "cref.h"
#include "vref.h"

struct Ship {
  int fuel;

  Ship(int fuel_) : fuel(fuel_) {}
};

void printUsage(const char* exeName) {
	std::cerr << "Usage: " << exeName << " [testnum]" << std::endl;
	std::cerr << "  where testnum is between 0 and 3 inclusive." << std::endl;
	std::cerr << "Example: " << exeName << " 3" << std::endl;
	exit(1);
}

void test_crefs() {
	cowned<Ship> ship = make_cowned<Ship>(42);
  cref<Ship> shipRef = ship.ref();

  auto shipHandle = shipRef.open();
  assert(shipHandle->fuel == 42);
}

void test_cref_two_opens_fail() {
	cowned<Ship> ship = make_cowned<Ship>(42);
  cref<Ship> shipRef = ship.ref();

  auto shipHandle = shipRef.open();

  // Should fail
  auto shipHandle2 = shipRef.open();
}

cref<Ship> test_cref_existing_past_cowned_fails() {
	cowned<Ship> ship = make_cowned<Ship>(42);
  return ship.ref();
}

void test_vrefs() {
	vowned<Ship> ship = make_vowned<Ship>(42);
  vref<Ship> shipRef = ship.ref();

  auto shipHandle = shipRef.open();
  assert(shipHandle->fuel == 42);
}

void test_vref_two_opens_fail() {
	vowned<Ship> ship = make_vowned<Ship>(42);
  vref<Ship> shipRef = ship.ref();

  auto shipHandle = shipRef.open();

  // Should fail
  auto shipHandle2 = shipRef.open();
}


int main(int argc, char* argv[]) {
	if (argc < 2) {
		printUsage(argv[0]);
		return 1;
	}

	int testNum = 0;
	try {
		testNum = std::stoi(argv[1]);
	} catch (std::invalid_argument&) {
		printUsage(argv[0]);
		return 1;
	}

	switch (testNum) {
		case 0: test_crefs(); break;
		case 1: test_cref_two_opens_fail(); break;
		case 2: test_cref_existing_past_cowned_fails(); break;
		case 3: test_vrefs(); break;
		case 4: test_vref_two_opens_fail(); break;
	}

	return 0;
}
