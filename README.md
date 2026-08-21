# Data-Structures-and-Algorithms

## Project Overview

The projects in this course focused on designing a program that could load, organize, search, sort, and display course information for the Computer Science program. The program needed to read course data from a file, store each course with its title and prerequisites, display an individual course, and print the full course list in alphanumeric order. The larger problem was determining which data structure and algorithms would provide an effective and maintainable solution.

## My Approach

I approached the problem by first identifying the operations the program needed to perform. These operations included loading records, validating course information, searching for a particular course, and sorting the complete course list. I then compared vectors, hash tables, and binary search trees by considering their run-time and memory characteristics.

Understanding data structures is important because the structure used to store information affects how efficiently a program can access, insert, search, and sort that information. A vector provides a straightforward way to store and sort a collection of courses. A hash table can provide efficient average-case searches when the course number is used as a key. A binary search tree can preserve an ordered relationship among records, although its performance depends on the shape and balance of the tree. Comparing these options helped me understand that selecting a data structure should be based on the program's required operations rather than personal preference.

## Overcoming Roadblocks

One challenge was ensuring that the program could correctly parse the input file and preserve the relationships between courses and their prerequisites. I addressed this by separating the file-reading, validation, storage, searching, sorting, and display responsibilities into distinct steps. I also tested the program using different inputs, including invalid filenames and course records with and without prerequisites. Breaking the problem into smaller operations made errors easier to identify and correct.

Another challenge was making sure the course list appeared in the required alphanumeric order. I overcame this by checking the stored course numbers and verifying the sorting logic against the expected output. Testing individual components before running the complete program helped me confirm that the data was loaded and displayed correctly.

## Growth in Software Design

This project expanded my approach to software design by showing me the value of analyzing a program before writing its final implementation. Comparing the run-time and memory characteristics of multiple data structures encouraged me to consider how design choices affect performance, scalability, and usability. I learned to identify the most important operations first and then select an implementation that supports those operations effectively.

In future projects, I will continue using pseudocode, complexity analysis, modular design, and targeted testing before completing the final code. This process reduces unnecessary revisions because the program's structure and responsibilities are considered before implementation.

## Maintainability, Readability, and Adaptability

My work in this course also changed how I write maintainable and readable programs. I learned to use descriptive names, consistent formatting, focused functions, and comments that explain important decisions rather than repeating the code. Separating file loading, course lookup, sorting, and output into different functions makes the program easier to test and modify.

The program is more adaptable because its data-processing logic is not tied entirely to the user interface. Future changes, such as loading a different course catalog, adding additional course details, or changing the display format, could be implemented without rewriting the entire program. These practices make the code easier for another developer to understand and maintain.

## Repository Contents

- **Project One:** Analysis comparing the run-time and memory characteristics of vectors, hash tables, and binary search trees.
- **Project Two:** Working course-planning program that loads course information and prints the Computer Science course list in alphanumeric order.
