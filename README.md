# Simulated-Annealing-for-an-Optimization-Problem

## Problem's Description
A new residence hall is finally ready, it consists of 50 4-person suites, and has chosen 200 students to move in. Because the resident hall is single-sex, any of our 200 students can share a room with anyone else. 
Students were given a questionnaire in which they were asked whether they are early risers or prefer to sleep in, whether they prefer a lot of social engagement or prefer their quiet time, how important it is for their area to be neat and tidy all of the time, and so on. Each student's compatibility as a roommate with each other student has been graded. This is a symmetric connection; given two students A and B, Compatibility(A, B) = Compatibility (B, A). Take note that this is done in pairs, and we're putting four people in a room.
A roommate assignment's fitness is determined by the sum of the pairwise compatibility scores; there are six such scores (AB, AC, AD, BC, BD, CD). As a result, the total fitness score for a room assignment ranges from 0-600. Lower totals indicate better compatibility. Choose a starting value for the 'temperature' parameter T that accepts most changes, including those that result in lower fitness; if in doubt, choose a higher value for T. Every 2000 accepted changes or 20,000 attempted changes, use proportional reduction for T (that is, T = 0.9T or 0.95 T, etc.). Repeat until you have 20,000 iterations with no successful modifications detected.

The task is how to assigne people to rooms such that compatibility is as good as possible.



## Input Description
Assume that the students are numbered 0-199, and that each row represents one student's evaluations (students have a rating of 0 with themselves). So the rating at location [a][b] represents the compatibility of students a and b. The metric in this problem changes in the total compatibility across the randomly chosen 2 rooms.


## Solution
The problem has been solved using simulated annealing. It starts with an arbitrary assignment -the first 4 students in the first room, and so on-. And using simluated annealing we will change the students according to their compatibility. 
The results are saved in the output.txt file with the following paremeters: Initial Temperature, Reduction, Best Compatibility, Worst Compatibility, and the Average Compatibility. And then followed by 50 lines, each of which describes the room number n and IDs of Each student, and concluded by the fitness score.


