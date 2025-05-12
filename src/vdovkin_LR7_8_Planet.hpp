#ifndef VDOVKIN_LR7_8_PLANET_H
#define VDOVKIN_LR7_8_PLANET_H

#include "vdovkin_def.hpp"

template <typename MassType, typename RadiusType> class PlanetBase {
protected:
  string name;
  MassType mass;
  RadiusType radius;
  vector<int> explorationYears;

public:
  // конструктор по умолчанию
  PlanetBase() : name("Unknown"), mass(0), radius(0) {}

  PlanetBase(const string &n, MassType m, RadiusType r,
             const vector<int> &years)
      : name(n), mass(m), radius(r), explorationYears(years) {
    if (m < 0)
      throw invalid_argument("Mass cannot be negative");
    if (r < 0)
      throw invalid_argument("Radius cannot be negative");
    for (int year : years) {
      if (year < 1957)
        throw invalid_argument("Exploration year cannot be before 1957");
    }
  }

  template <typename U, typename V>
  PlanetBase(const PlanetBase<U, V> &other)
      : name(other.name), mass(static_cast<MassType>(other.mass)),
        radius(static_cast<RadiusType>(other.radius)),
        explorationYears(other.explorationYears) {}

  PlanetBase(const PlanetBase &other)
      : name(other.name), mass(other.mass), radius(other.radius),
        explorationYears(other.explorationYears) {}

  PlanetBase(PlanetBase &&other) noexcept
      : name(std::move(other.name)), mass(move(other.mass)),
        radius(move(other.radius)),
        explorationYears(std::move(other.explorationYears)) {}

  // конструктор копирования
  PlanetBase &operator=(const PlanetBase &other) {
    if (this != &other) {
      name = other.name;
      mass = other.mass;
      radius = other.radius;
      explorationYears = other.explorationYears;
    }
    return *this;
  }

  PlanetBase &operator=(PlanetBase &&other) noexcept {
    if (this != &other) {
      name = std::move(other.name);
      mass = move(other.mass);
      radius = move(other.radius);
      explorationYears = std::move(other.explorationYears);
    }
    return *this;
  }

  virtual ~PlanetBase() = default;

  // методы
  virtual void addExplorationYear(int year) {
    if (year < 1957)
      throw invalid_argument("Exploration year cannot be before 1957");
    explorationYears.push_back(year);
  }

  virtual void printInfo() const {
    cout << "Planet: " << name << "\nMass: " << mass
         << " kg\nRadius: " << radius << " m\nExploration Years: ";
    for (int year : explorationYears) {
      cout << year << " ";
    }
    cout << endl;
  }

  virtual double calculateGravity() const {
    if (radius == 0)
      throw runtime_error("Cannot calculate gravity: radius is zero");
    const double G = 6.67430e-11; // Gravitational constant in m^3 kg^-1 s^-2
    return G * mass / (radius * radius);
  }

  bool isExplored() const { return !explorationYears.empty(); }

  int getFirstExplorationYear() const {
    if (!isExplored())
      throw logic_error("Planet has not been explored");
    return *min_element(explorationYears.begin(), explorationYears.end());
  }

  // геттеры и сеттеры
  string getName() const { return name; }
  void setName(const string &n) { name = n; }
  MassType getMass() const { return mass; }
  void setMass(MassType m) {
    if (m < 0)
      throw invalid_argument("Mass cannot be negative");
    mass = m;
  }
  RadiusType getRadius() const { return radius; }
  void setRadius(RadiusType r) {
    if (r < 0)
      throw invalid_argument("Radius cannot be negative");
    radius = r;
  }
  const vector<int> &getExplorationYears() const { return explorationYears; }

  // перегрузка
  PlanetBase operator+(const PlanetBase &other) const {
    PlanetBase result = *this;
    result.explorationYears.insert(result.explorationYears.end(),
                                   other.explorationYears.begin(),
                                   other.explorationYears.end());
    sort(result.explorationYears.begin(), result.explorationYears.end());
    auto last =
        unique(result.explorationYears.begin(), result.explorationYears.end());
    result.explorationYears.erase(last, result.explorationYears.end());
    return result;
  }

  PlanetBase &operator+=(int year) {
    addExplorationYear(year);
    return *this;
  }

  PlanetBase &operator++() { // преф инкр
    mass += 1;
    return *this;
  }

  PlanetBase operator++(int) { // постф инкр
    PlanetBase temp = *this;
    mass += 1;
    return temp;
  }

  PlanetBase &operator--() { // преф декр
    if (mass <= 0)
      throw logic_error("Mass cannot be negative");
    mass -= 1;
    return *this;
  }

  PlanetBase operator--(int) { // постф декр
    if (mass <= 0)
      throw logic_error("Mass cannot be negative");
    PlanetBase temp = *this;
    mass -= 1;
    return temp;
  }

  bool operator<(const PlanetBase &other) const { return mass < other.mass; }
  bool operator>(const PlanetBase &other) const { return mass > other.mass; }
  bool operator==(const PlanetBase &other) const {
    return mass == other.mass && name == other.name && radius == other.radius &&
           explorationYears == other.explorationYears;
  }

  // вирт методы
  virtual bool hasAtmosphere() const {
    throw logic_error("Not applicable for this planet type");
  }
  virtual string getComposition() const {
    throw logic_error("Not applicable for this planet type");
  }
  virtual int getMoonCount() const {
    throw logic_error("Not applicable for this planet type");
  }
  virtual double getCoreTemperature() const {
    throw logic_error("Not applicable for this planet type");
  }

  // перегрузка операторов ввода-вывода
  friend ostream &operator<<(ostream &os, const PlanetBase &planet) {
    os << planet.name << " " << planet.mass << " " << planet.radius << " ";
    for (int year : planet.explorationYears) {
      os << year << " ";
    }
    return os;
  }

  friend istream &operator>>(istream &is, PlanetBase &planet) {
    is >> planet.name >> planet.mass >> planet.radius;
    planet.explorationYears.clear();
    int year;
    while (is >> year) {
      planet.addExplorationYear(year);
    }
    is.clear();
    return is;
  }
};

// специализация для планет земной группы
template <typename MassType, typename RadiusType>
class TerrestrialPlanet : public PlanetBase<MassType, RadiusType> {
public:
  using PlanetBase<MassType, RadiusType>::PlanetBase; // Inherit constructors

  bool hasAtmosphere() const override {
    return this->radius > 1000; // Example condition
  }

  string getComposition() const override {
    return "Rocky"; // Simplified example
  }
};

// специализация для газовых планет
template <typename MassType, typename RadiusType>
class GasGiantPlanet : public PlanetBase<MassType, RadiusType> {
public:
  using PlanetBase<MassType, RadiusType>::PlanetBase; // Inherit constructors

  int getMoonCount() const override {
    return 10; // Simplified example
  }

  double getCoreTemperature() const override {
    return 5000.0; // Simplified example in Kelvin
  }
};

// Шаблонный класс-адаптер
template <template <typename...> class Container, typename T>
class PlanetAdapter {
private:
  Container<T> data;

public:
  PlanetAdapter(const PlanetBase<double, double> &planet) {
    for (int year : planet.getExplorationYears()) {
      data.insert(data.end(), static_cast<T>(year));
    }
  }

  void print() const {
    for (const auto &item : data) {
      cout << item << " ";
    }
    cout << endl;
  }

  size_t countUnique() const {
    if constexpr (is_same_v<Container<T>, set<T>>) {
      return data.size();
    } else {
      set<T> uniqueData(data.begin(), data.end());
      return uniqueData.size();
    }
  }
};

#endif // VDOVKIN_LR7_8_PLANET_H
