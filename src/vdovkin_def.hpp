#ifndef VDOVKIN_DEF_HPP
#define VDOVKIN_DEF_HPP

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <istream>
#include <limits>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

inline void clearTerminal() {
#ifdef _WIN32
  system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix)
  system("clear");
#endif
}

inline bool UserInputInt(string input) {
  if (input.empty())
    return false;
  try {
    int number = stoi(input);
    if (number < 0)
      return false;
  } catch (...) {
    return false;
  }
  return true;
}

inline bool UserInputDouble(string input) {
  if (input.empty())
    return false;
  try {
    int number = stod(input);
    if (number < 0)
      return false;
  } catch (...) {
    return false;
  }
  return true;
}

inline bool UserInputBool(string input) {
  if (input.empty())
    return false;
  try {
    int number = stod(input);
    if (number < 0 || number > 1)
      return false;
  } catch (...) {
    return false;
  }
  return true;
}

inline bool UserInputString(string input) {
  if (input.empty())
    return false;
  return true;
}

function<void()> inline EnterInt(istream &is, int &varLink, string label) {
  return [&is, &varLink, label]() {
    string raw_input;
    cout << label;
    getline(is, raw_input);

    while (!UserInputInt(raw_input)) {
      cout << label;
      getline(is, raw_input);
    }
    varLink = stoi(raw_input);
  };
}

function<void()> inline EnterDouble(istream &is, double &varLink,
                                    string label) {
  return [&is, &varLink, label]() {
    string raw_input;
    cout << label;
    getline(is, raw_input);

    while (!UserInputDouble(raw_input)) {
      cout << label;
      getline(is, raw_input);
    }
    varLink = stod(raw_input);
  };
}

function<void()> inline EnterBool(istream &is, bool &varLink, string label) {
  return [&is, &varLink, label]() {
    string raw_input;
    cout << label;
    getline(is, raw_input);

    while (!UserInputBool(raw_input)) {
      cout << label;
      getline(is, raw_input);
    }
    varLink = stoi(raw_input);
  };
}

function<void()> inline EnterString(istream &is, string &varLink,
                                    string label) {
  return [&is, &varLink, label]() {
    cout << label;
    getline(cin, varLink);

    while (!UserInputString(varLink)) {
      cout << label;
      getline(is, varLink);
    }
  };
}

#endif // VDOVKIN_DEF_HPP
