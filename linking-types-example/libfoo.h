/* We want to ensure that this header file is not included more than
   once. If we did include it more than once, we would get errors
   about redeclaring functions that already exist. The following line
   of code tells the compiler to ensure that this header is included
   at most one time in any C file.
*/
#pragma once

/* Note: An older, commonly-used alternative to the pragma line above
 * are called header guards.
 *
 * See: https://en.Wikipedia.org/wiki/Include_guard
 */



/* Declare the functions in our library */
int one(void);
void two(void);
