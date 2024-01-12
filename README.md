# NCHU VLSI/CAD Lab
## Grid-based Two-layer Channel Routing
* Each pin is labeled with a number from 0 to 1000
* Problem: \
  Given the label of each upper and lower pins, write a program to find the channel routing with the minimum cost.
* Cost: 
  * Number of tracks
  * Overall wire length
  * Number of vias
* Benchmarks
  * bench1.txt to bench8.txt
* Method: Constrained (considering vertical constraints) left-hand algorithm
  1. After finish reading the given pins, record the vertical constraint of each pin with a vertical contraint graph, namely the array vcg in the code.
  2. Sort the given pins by their pin-label number.
  3. Greedily, pick the unconstrained pin to route until finished.       
* Usage: 
```
g++  main.cpp -omain && ./main.exe  bench4.txt   
```
* Sample output: 
```
Sorted intervals of nets:
  I1[1, 3]
  I2[1, 5]
  I5[2, 6]
  I3[6, 8]
  I6[7, 9]
  I4[10, 11]

Vertical constraint:
  I1->I2
  I1->I5
  I2->I5
  I5->I3
  I6->I3

track_1:
  head(s): I1, I4, I6,
  route I1[1, 3]: watermark = 3;
  route I6[7, 9]: watermark = 9;
  route I4[10, 11]: watermark = 11;

track_2:
  head(s): I2,
  route I2[1, 5]: watermark = 5;

track_3:
  head(s): I5,
  route I5[2, 6]: watermark = 6;

track_4:
  head(s): I3,
  route I3[6, 8]: watermark = 8;

The resulting routing graph:
col:  1    2    3    4    5    6    7    8    9   10   11
pin:  1    1    1    2    2    5    6    3    0    4    0
    -------------------------------------------------------
      ^----^----^    ^    ^    ^    ^----^---->    ^---->
      >-------------------<    |         |    |         |
      |    >-------------------<         |    |         |
      v    v         v    v    v----v----<    v         v
    -------------------------------------------------------
      2    5    0    5    5    3    3    0    6    0    4
Number of tracks: 4
Overall wire length: 50
Number of vias: 17
```
