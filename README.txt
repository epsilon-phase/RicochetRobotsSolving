HOMEWORK 6: RICOCHET ROBOT RECURSION


NAME:  < insert name >



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Norbert Szmit

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 20



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

i & j = dimensions of the board
    r = number of robots on the board
    w = number of interior walls
    m = maximum total number of moves allowed

moveRobot: O(i+j+w+r)
findPath:O(r*(i+j+w+r)*m)
findAccessibility(


SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
Most puzzles are solved in relatively short times, usually less than one second, however, the program does not find the shortest path available to it, and therefore fails the tests.
Also, I need


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


