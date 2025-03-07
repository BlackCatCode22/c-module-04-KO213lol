#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

// Base class
class Animal {
protected:
    string name;
    int age;
    string species;
public:
    Animal(string n, int a, string s) : name(n), age(a), species(s) {}
    virtual ~Animal() {}
    virtual void display() const {
        cout << species << ": " << name << ", Age: " << age << endl;
    }
    string getSpecies() const { return species; }
    string getName() const { return name; }
    int getAge() const { return age; }
};

// Subclasses
class Hyena : public Animal {
public:
    Hyena(string n, int a) : Animal(n, a, "Hyena") {}
};

class Lion : public Animal {
public:
    Lion(string n, int a) : Animal(n, a, "Lion") {}
};

class Tiger : public Animal {
public:
    Tiger(string n, int a) : Animal(n, a, "Tiger") {}
};

class Bear : public Animal {
public:
    Bear(string n, int a) : Animal(n, a, "Bear") {}
};

// Function to process the file and store data
void processAnimals(vector<Animal*>& animals, map<string, int>& speciesCount) {
    ifstream inputFile("arrivingAnimals.txt");
    if (!inputFile) {
        cerr << "Error opening input file!" << endl;
        return;
    }
    
    string name, species;
    int age;
    while (inputFile >> species >> name >> age) {
        Animal* animal = nullptr;
        if (species == "Hyena")
            animal = new Hyena(name, age);
        else if (species == "Lion")
            animal = new Lion(name, age);
        else if (species == "Tiger")
            animal = new Tiger(name, age);
        else if (species == "Bear")
            animal = new Bear(name, age);
        
        if (animal) {
            animals.push_back(animal);
            speciesCount[species]++;
        }
    }
    inputFile.close();
}

// Function to generate the report
void generateReport(const vector<Animal*>& animals, const map<string, int>& speciesCount) {
    ofstream outputFile("newAnimals.txt");
    if (!outputFile) {
        cerr << "Error opening output file!" << endl;
        return;
    }
    
    for (const auto& entry : speciesCount) {
        outputFile << entry.first << " Count: " << entry.second << endl;
        for (const auto& animal : animals) {
            if (animal->getSpecies() == entry.first) {
                outputFile << "  " << animal->getName() << " (Age: " << animal->getAge() << ")" << endl;
            }
        }
    }
    outputFile.close();
}

int main() {
    vector<Animal*> animals;
    map<string, int> speciesCount;
    
    processAnimals(animals, speciesCount);
    generateReport(animals, speciesCount);
    
    for (auto animal : animals) {
        delete animal;
    }
    return 0;
}
