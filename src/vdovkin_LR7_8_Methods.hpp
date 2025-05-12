#ifndef VDOVKIN_LR7_8_METHODS_H
#define VDOVKIN_LR7_8_METHODS_H

#include "vdovkin_LR7_8_Planet.hpp"
#include "vdovkin_def.hpp"

using Planet = PlanetBase<double, double>;
using Terrestrial = TerrestrialPlanet<double, double>;
using GasGiant = GasGiantPlanet<double, double>;
using PlanetPtr = unique_ptr<Planet>;
using PlanetVector = vector<PlanetPtr>;

// создать планету земной группы
void createTerrestrialPlanet(PlanetVector &planets) {
  string name;
  double mass, radius;
  int numYears;
  vector<int> years;

  EnterString(cin, name, "Enter planet name: ")();
  EnterDouble(cin, mass, "Enter mass (kg): ")();
  EnterDouble(cin, radius, "Enter radius (m): ")();
  EnterInt(cin, numYears, "Enter number of exploration years: ")();
  for (int i = 0; i < numYears; ++i) {
    int year;
    EnterInt(cin, year, "Enter exploration year: ")();
    years.push_back(year);
  }

  try {
    planets.push_back(make_unique<Terrestrial>(name, mass, radius, years));
    cout << "Terrestrial planet created successfully.\n";
  } catch (const exception &e) {
    cerr << "Error creating planet: " << e.what() << endl;
  }
}

// Создать планету газовой группы
void createGasGiantPlanet(PlanetVector &planets) {
  string name;
  double mass, radius;
  int numYears;
  vector<int> years;

  EnterString(cin, name, "Enter planet name: ")();
  EnterDouble(cin, mass, "Enter mass (kg): ")();
  EnterDouble(cin, radius, "Enter radius (m): ")();
  EnterInt(cin, numYears, "Enter number of exploration years: ")();
  for (int i = 0; i < numYears; ++i) {
    int year;
    EnterInt(cin, year, "Enter exploration year: ")();
    years.push_back(year);
  }

  try {
    planets.push_back(make_unique<GasGiant>(name, mass, radius, years));
    cout << "Gas giant planet created successfully.\n";
  } catch (const exception &e) {
    cerr << "Error creating planet: " << e.what() << endl;
  }
}

// ыывести все планеты
void displayPlanets(const PlanetVector &planets) {
  if (planets.empty()) {
    cout << "No planets to display.\n";
    return;
  }
  for (const auto &planet : planets) {
    planet->printInfo();
    try {
      cout << "Gravity: " << planet->calculateGravity() << " m/s²\n";
      if (auto *terrestrial = dynamic_cast<Terrestrial *>(planet.get())) {
        cout << "Has atmosphere: "
             << (terrestrial->hasAtmosphere() ? "Yes" : "No") << "\n";
        cout << "Composition: " << terrestrial->getComposition() << "\n";
      } else if (auto *gasGiant = dynamic_cast<GasGiant *>(planet.get())) {
        cout << "Moon count: " << gasGiant->getMoonCount() << "\n";
        cout << "Core temperature: " << gasGiant->getCoreTemperature()
             << " K\n";
      }
    } catch (const exception &e) {
      cerr << "Error: " << e.what() << "\n";
    }
    cout << "\n";
  }
}

// выбрать планету по индексу
Planet *selectPlanet(const PlanetVector &planets) {
  if (planets.empty()) {
    cout << "No planets available.\n";
    return nullptr;
  }
  int index;
  EnterInt(cin, index,
           "Enter planet index (1 to " + to_string(planets.size()) + "): ")();
  if (index < 1 || index > static_cast<int>(planets.size())) {
    cout << "Invalid index.\n";
    return nullptr;
  }
  return planets[index - 1].get();
}

// вычислить гравитацию для планеты
void calculateGravityForPlanet(const PlanetVector &planets) {
  Planet *planet = selectPlanet(planets);
  if (planet) {
    try {
      cout << "Gravity: " << planet->calculateGravity() << " m/s²\n";
    } catch (const exception &e) {
      cerr << "Error: " << e.what() << "\n";
    }
  }
}

// добавить год исследований к планете
void addExplorationYearToPlanet(PlanetVector &planets) {
  Planet *planet = selectPlanet(planets);
  if (planet) {
    int year;
    EnterInt(cin, year, "Enter exploration year: ")();
    try {
      planet->addExplorationYear(year);
      cout << "Year added successfully.\n";
    } catch (const exception &e) {
      cerr << "Error: " << e.what() << "\n";
    }
  }
}

// сортировать планеты по массе
void sortPlanetsByMass(PlanetVector &planets) {
  try {
    if (planets.empty())
      throw invalid_argument("Cannot sort empty list");
    sort(planets.begin(), planets.end(),
         [](const PlanetPtr &a, const PlanetPtr &b) {
           return a->getMass() < b->getMass();
         });
    cout << "Planets sorted by mass.\n";
  } catch (const exception &e) {
    cerr << "Error: " << e.what() << "\n";
  }
}

// найти планеты в году
void findPlanetsExploredInYearMenu(const PlanetVector &planets) {
  int year;
  EnterInt(cin, year, "Enter year: ")();
  try {
    PlanetVector result;
    for (const auto &planet : planets) {
      const auto &years = planet->getExplorationYears();
      if (find(years.begin(), years.end(), year) != years.end()) {
        result.push_back(make_unique<Planet>(*planet));
      }
    }
    if (result.empty())
      throw runtime_error("No planets explored in the given year");
    cout << "Planets explored in " << year << ":\n";
    for (const auto &planet : result) {
      cout << planet->getName() << "\n";
    }
  } catch (const exception &e) {
    cerr << "Error: " << e.what() << "\n";
  }
}

// адаптеры
void useAdapterVector(const Planet &planet) {
  PlanetAdapter<vector, int> adapter(planet);
  cout << "Exploration years as vector: ";
  adapter.print();
  cout << "Unique years: " << adapter.countUnique() << "\n";
}

void useAdapterSet(const Planet &planet) {
  PlanetAdapter<set, int> adapter(planet);
  cout << "Exploration years as set: ";
  adapter.print();
  cout << "Unique years: " << adapter.countUnique() << "\n";
}

void useAdapterForPlanet(const PlanetVector &planets) {
  Planet *planet = selectPlanet(planets);
  if (planet) {
    int choice;
    cout << "Choose container: 1. Vector 2. Set\n";
    EnterInt(cin, choice, "Enter choice: ")();
    if (choice == 1) {
      useAdapterVector(*planet);
    } else if (choice == 2) {
      useAdapterSet(*planet);
    } else {
      cout << "Invalid choice.\n";
    }
  }
}

#endif // VDOVKIN_LR7_8_METHODS_H
