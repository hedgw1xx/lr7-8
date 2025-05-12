#include "vdovkin_LR7_8_Methods.hpp"
#include "vdovkin_def.hpp"

int main() {
  PlanetVector planets;

  struct MenuItem {
    string title;
    function<void()> action;
  };

  map<int, MenuItem> menu = {
      {1,
       {"Create Terrestrial Planet",
        [&planets]() { createTerrestrialPlanet(planets); }}},
      {2,
       {"Create Gas Giant Planet",
        [&planets]() { createGasGiantPlanet(planets); }}},
      {3, {"Display All Planets", [&planets]() { displayPlanets(planets); }}},
      {4,
       {"Calculate Gravity for a Planet",
        [&planets]() { calculateGravityForPlanet(planets); }}},
      {5,
       {"Add Exploration Year to a Planet",
        [&planets]() { addExplorationYearToPlanet(planets); }}},
      {6,
       {"Sort Planets by Mass", [&planets]() { sortPlanetsByMass(planets); }}},
      {7,
       {"Find Planets Explored in a Specific Year",
        [&planets]() { findPlanetsExploredInYearMenu(planets); }}},
      {8,
       {"Use Adapter for a Planet's Exploration Years",
        [&planets]() { useAdapterForPlanet(planets); }}},
      {0, {"Exit", []() { cout << "Exiting...\n"; }}}};

  int choice = 0;

  while (true) {

    cout << "Menu:" << endl;
    for (const auto &item : menu) {
      cout << item.first << ". " << item.second.title << endl;
    }
    cout << "0. Exit" << endl;

    EnterInt(cin, choice, "Enter your choice: ")();

    if (choice == 0) {
      cout << "© 2025 Eugene Vdovkin" << endl;
      break;
    }

    cout << endl;

    if (menu.find(choice) != menu.end()) {
      clearTerminal();
      menu[choice].action();
    } else {
      clearTerminal();
      cout << "Invalid choice" << endl;
    }

    cout << endl << endl;
  }

  return 0;
}
