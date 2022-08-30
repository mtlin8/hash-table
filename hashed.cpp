#include "Hashtable.h"
#include <random>
#include <ctime>

using namespace std;

bool birthdayParadox (Hashtable<int>& table);
string randomString();

int main(int argc, char* argv[]) 
{
    // you decide how you run each test, put that in README.md. Check to make sure this is the case.

    srand(time(0));

    // BIRTHDAY PROBLEM
    int lessThan23 = 0;
    int bday = 100000;
    for (int i = 0; i < bday; i++) {
        Hashtable<int> table(false, 365);
        if (birthdayParadox(table)) lessThan23++;
    }
    double result = (double) lessThan23/bday;
    cout << result << endl;

    // SECOND TEST (STILL DECIDING)
    int elementsToAdd = 1000;

    // AVERAGE PROBES
    Hashtable<int> probe(false, 1597);
    int totalProbes = 0;
    for (int i = 0; i < elementsToAdd; i++) {
        int collisions = probe.add(randomString(), i);
        totalProbes += collisions;
    }
    cout << totalProbes << endl;

    return 0;
}

bool birthdayParadox (Hashtable<int>& table) {
    int numElements = 0;
    while (numElements < 23) {
        int collisions = table.add(randomString(), numElements);
        if (collisions != 0) {
            return false; 
        }
        numElements++;
    }
    return true;
}

string randomString() {
    string str = "";
    for (int i = 0; i < 26; i++) {
        int toCast = rand() % 26;
        str += toCast + 'a';
    }
    return str;
}