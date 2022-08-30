Mitchell Lin
5766363703
mtlin@usc.edu

1. BIRTHDAY PARADOX
    - For this test, what I did was create a bool function that would quit and return false if a collision occurred within the first 23 and return true otherwise. If that was true, I incremented my lessThan23 variable by 1 to see in how many runs saw 23 elements inserted without collision. 
    - Depending on the sizing of how many elements I try to add, the range of percentage of runs that see 23 elements inserted without collision is 0.49 to 0.515, which falls right within our expected number.

2. PROBE RATE
    - After running probes on a hashtable of fixed size, I found that we had about 2n/3 collisions, n being 1000, and the number of collisions being between 590 - 690.

# hash-table
