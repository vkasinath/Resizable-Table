HOMEWORK 3: RESIZABLE TABLE


NAME:  Vishaal Kasinath


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

https://www.learncpp.com/cpp-tutorial/69-dynamic-memory-allocation-with-new-and-delete/
https://en.cppreference.com/w/cpp/language/pointer
https://www.tutorialspoint.com/cplusplus/cpp_templates.htm
https://en.cppreference.com/w/cpp/language/template_parameters
https://stackoverflow.com/questions/1768294/how-to-allocate-a-2d-array-of-pointers-in-c
https://stackoverflow.com/questions/7062853/c-pointer-assignment/7062888
http://valgrind.org/docs/manual/QuickStart.html
https://drmemory.org/docs/page_leaks.html
Andrew Koenig: Accelerated C++ Chapter 10

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20 hours


ORDER NOTATION:

Write each answer in terms of n = the number of rows and m = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get: O(1)

set: O(1)

numRows: O(col)

numColumns: O(row)

push_back_row: O(1)

push_back_column: O(1)

pop_back_row: O(1)

pop_back_column: O(row)

print: O(row*col)


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Table class design & implementation?

mosly used standard cout and print to determnine errors
tested with top, watched memory for multiple large runs

corner cases tested:
0 rows and 0 columns followed by push_back and pop_back
escape character in stringl
tested table delete and confirmed no memory leaks/access violations


EXTRA CREDIT: 
Indicate here if you implemented push_back for multiple rows or
multiple columns and/or rewrote your code using pointers instead of
subscripts for extra credit.  Also document the order notation for
your multi-row and multi-column push_back functions.

Implemented push_back for multiple rows and columns

multi-row push_back: O(n) where n = number of rows pushed
multi-column push_back: O(row*m) m = number columns pushed



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

