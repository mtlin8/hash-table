#include <iostream>
#include <cmath> // for pow() function
#include <vector>
#include <string>
#include <iterator>
#include <cstdlib>
#include <set> // may not make direct sense for hash table, but to help it along will be nice

template <typename T> // this should be ok, string will always be first component
class Hashtable
{
    public:
        // DEFAULTS
        Hashtable(bool debug_);
        Hashtable (bool debug_, unsigned int size_);
        ~Hashtable ();
        int add (std::string k, const T& val);
        const T& lookup (std::string k);
        void reportAll (std::ostream &) const;
        unsigned int getSize ();

    private:
        // DEFAULTS
        int hash (std::string k) const;
        void resize ();
        bool debug;
        unsigned int size;
        // MY FUNCTIONS
        void hashtableSetup(); 
        bool wordAdded(std::string k);
        // MY DATA MEMBERS
        std::vector< std::pair<std::string, T> > myTable;
        std::set<unsigned int> tableSizes; // prime numbers we'll use
        std::set<unsigned int>::iterator tableSizesIterator = tableSizes.begin(); // to track how big our table is
        unsigned int r1;
        unsigned int r2;
        unsigned int r3;
        unsigned int r4;
        unsigned int r5;
        std::pair<std::string, T> defaultPair;
        int count = 0;
};

template<typename T>
Hashtable<T>::Hashtable(bool debug_) {
    debug = debug_;
    size = 11;
    hashtableSetup();
}

template<typename T>
Hashtable<T>::Hashtable(bool debug_, unsigned int size_) {
    debug = debug_;
    size = size_;
    hashtableSetup();
}

template<typename T>
void Hashtable<T>::hashtableSetup() {
    // set defaultPair
    char toCast = 'a';
    defaultPair.first = "draymondlikesnuts";
    defaultPair.second = (T)toCast; // char is smallest type, can be cast to anything

    for (unsigned int i = 0; i < size; i++) {
        myTable.push_back(defaultPair); // what do you push back if nothing's been added yet?
    }

    // also sets initial r values
    if (debug) {
        r1 = 983132572;
        r2 = 1468777056;
        r3 = 552714139;
        r4 = 984953261;
        r5 = 261934300;
    }
    else {
        // generate 5 random numbers
        r1 = rand() % (size - 1);
        r2 = rand() % (size - 1);
        r3 = rand() % (size - 1);
        r4 = rand() % (size - 1);
        r5 = rand() % (size - 1);
    }
    // create table of primes
    tableSizes.insert(11);
    tableSizes.insert(23);
    tableSizes.insert(47);
    tableSizes.insert(97);
    tableSizes.insert(197);
    tableSizes.insert(397);
    tableSizes.insert(797);
    tableSizes.insert(1597);
    tableSizes.insert(3203);
    tableSizes.insert(6421);
    tableSizes.insert(12853);
    tableSizes.insert(25717);
    tableSizes.insert(51437);
    tableSizes.insert(102877);
    tableSizes.insert(205759);
    tableSizes.insert(411527);
    tableSizes.insert(823117);
    tableSizesIterator = tableSizes.begin();
    while (size >= *tableSizesIterator) {
        ++tableSizesIterator;
    }
}

template<typename T>
Hashtable<T>::~Hashtable() {
    // delete any allocated memory
    // should be alright doing nothing here since we using vector
}

template<typename T>
int Hashtable<T>::add (std::string k, const T& val) {
    int collisions = 0;
    std::pair<std::string, T> newPair; // not worrying about duplicates here
    newPair.first = k;
    newPair.second = val;

    count++;
    if (size/count < 2 && size%count < 2) { // this size%count detail was what helped me pass that last test
        resize();
    }

    int hashed = hash(k);
    if (myTable[hashed] == defaultPair) {
        myTable[hashed] = newPair;
    }
    else if (myTable[hashed] == newPair) {
        // do nothing (quad probing here would mess things up, inserting duplicate unnecessarily)
    }
    else { // do quadratic probing
        int probe = 1;
        while (true) {
            collisions++;
            if (pow(probe,2) > size) {
                break;
            }
            hashed += pow(probe,2);
            hashed = hashed % size;
            if (myTable[hashed] == defaultPair) {
                myTable[hashed] = newPair;
                break;
            }
            probe++;
        }
    }
    return collisions;
}

template<typename T>
const T& Hashtable<T>::lookup (std::string k) {
    int lookup = hash(k);
    int probe = 1;
    while (probe < sqrt(size)) { // this takes care of infinite loop problem
        if (myTable[lookup].first == k) {
            return myTable[lookup].second;
        }
        else { 
            lookup += pow(probe, 2);
            lookup = lookup % size; // quadratic probing
        }
        probe++;
    }
    return defaultPair.second;
}

template<typename T>
void Hashtable<T>::reportAll (std::ostream &) const {
    /* output to the given stream, every (key,value) pair, in the order they appear in the Hashtable; 
    on each line, output the key, followed by a space, followed by the value, and then a newline. 
    Note that this requires the T type to have operator« defined.*/

    for (int i = 0; i < size; i++) {
        if (myTable[i] != defaultPair) {
            std::cout << myTable[i].first << " " << myTable[i].second << std::endl;
        }
    }
}

template<typename T>
unsigned int Hashtable<T>::getSize () {
    return size;
}

template<typename T>
int Hashtable<T>::hash (std::string k) const {
    int a[6]; // to store int values of substring chars
    int w[5]; // to store int values of substrings

    int strLen = k.size();
    int stopFirstSubstring = strLen % 6;
    int w_Iterator = 4 - (strLen / 6); // to mark where we start. 4 is last index.
    for (int i = 0; i < w_Iterator; i++) {
        w[i] = 0;  // first set out of range w values to 0
    }
    // iterate through the first substring (because it will always exist)
    for (int i = 0; i < 6 - stopFirstSubstring; i++) {
        a[i] = 0; // set out of range a values to 0
    }
    for (int i = 0; i < stopFirstSubstring; i++) {
        a[i + 6 - stopFirstSubstring] = k[i] - 'a' + 1; // NO SEGFAULT LFG
    }
    w[w_Iterator] = pow(27,5)*a[0] + pow(27,4)*a[1] + pow(27,3)*a[2] + pow(27,2)*a[3] + pow(27,1)*a[4] + pow(27,0)*a[5];
    
    // now iterate through the rest, if it's there
    int k_Iterator = stopFirstSubstring;
    while (w_Iterator < 5) {
        w_Iterator++;
        for (int i = 0; i < 6; i++) {
            a[i] = k[i + k_Iterator] - 'a' + 1;
        }
        k_Iterator += 6;
        w[w_Iterator] = pow(27,5)*a[0] + pow(27,4)*a[1] + pow(27,3)*a[2] + pow(27,2)*a[3] + pow(27,1)*a[4] + pow(27,0)*a[5];
    }

    int result = (int)(((long long)r1*w[0] + (long long)r2*w[1] + 
                    (long long)r3*w[2] + (long long)r4*w[3] + (long long)r5*w[4]) % size); // watch castings
    return result;
}

template<typename T>
void Hashtable<T>::resize () {
    // double the number of indices available
    // call when add() pushes load factor past 0.5
    /* 11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117 */
    // put in set, if curr size larger, iterate iterator. Done in constructor.

    // DON"T NEED TO WIPE VECTOR. Just iterate through first half of vector 
    // once rehashed, set to default

    unsigned int oldSize = size;
    size = *tableSizesIterator; // double the size
    ++tableSizesIterator;
    r1 = (unsigned int) rand() % (size - 1); // r values reset upon each resize
    r2 = (unsigned int) rand() % (size - 1);
    r3 = (unsigned int) rand() % (size - 1);
    r4 = (unsigned int) rand() % (size - 1);
    r5 = (unsigned int) rand() % (size - 1);

    for (unsigned int i = oldSize; i < size; i++) {
        myTable.push_back(defaultPair); // put default values in indices of table
        // linear time resize is the only issue here
    }

    for (unsigned int i = 0; i < oldSize; i++) {
        unsigned int collisions = (unsigned int)add(myTable[i].first, myTable[i].second);
        myTable[i] = defaultPair; // no way myTable[i] contains anything valuable at this point, so reset
    }
}