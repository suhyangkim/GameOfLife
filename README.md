# GameOfLife
Stanford University Summer 2018 Assignment #1

Assignment by Marty Stepp and Victoria Kirst, based on previous version by Julie Zelenski, with other revisions by Jerry Cain, Keith Schwarz, Cynthia Lee, Ashley Taylor, etc.

This problem is about C++ functions, strings, reading files, using libraries, and decomposing a large problem.

Program Description:
The Game of Life (Wikipedia) is a simulation by British mathematician J. H. Conway in 1970. The game models the life cycle of bacteria using a two-dimensional grid of cells. Given an initial pattern, the game simulates the birth and death of future generations of cells using a set of simple rules.

This assignment implements a simplified version of Conway's simulation and a basic user interface for watching the bacteria grow over time.

This Game of Life program begins by prompting the user for a file name and using that file's contents to set the initial state of your bacterial colony grid. Then it will allow the user to advance the colony through generations of growth. The user can type t (or just press Enter) to "tick" forward the bacteria simulation by one generation, or a to begin an animation loop that ticks forward the simulation by several generations, once every 100 milliseconds; or q to quit. The menu is case-insensitive; for example, an uppercase or lowercase A, T, or Q should work.

When the user quits, it prompts the user Y/N to load another file or exit the program. If the user types any string that begins with the letter Y, case-insensitive, it prompts the user to load another file. If the user types any string that begins with the letter N, case-insensitive, the program ends and prints "Have a nice Life!". If the user types a string that does not begin with either Y or N, it re-prompts them with the message, "Please type a word that starts with 'Y' or 'N'.". The provided library function getYesOrNo from "simpio.h" (documentation) is used to to help out with this.
