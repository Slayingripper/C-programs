# G51PGA 2017 Coursework 1

## Introduction

This coursework focuses on writing two interesting programs using functions, variables, operators and conditionals. There are **two tasks** to complete, details of which are given below. You should complete **both tasks**. Links to external pages are provided in the details below which you will need to follow and read to complete each task.

## Assessment

This coursework is worth **10%** of your final course grade. The points awarded for each task are as follows:

|            | Compilation | Implementation | Execution | **Total** |
| ---------- | :---------: | :------------: | :-------: | :-------: |
| **Task 1** | 2           | 1              | 4         | **7**     |
| **Task 2** | 2           | 2              | 8         | **12**     |

For **Task 1**, you are awarded *two* points if your program compiles correctly: *one* point if it compiles without errors, and a further *one* point if it compiles without errors *and* warnings. If your program follows the implementation instructions given in [Task 1 Details](#details-1) below, you are awarded *one* point. If your program produces the correct output as described in [Task 1 Details](#details-1) below, you are awarded *four* points.

For **Task 2**, you are awarded *two* points if your program compiles correctly: *one* point if it compiles without errors, and a further *one* point if it compiles without errors *and* warnings. If your program follows the implementation instructions given in [Task 2 Details](#details-2) below, you are awarded a maximum of *two* points. If your program produces the correct output as described in [Task 2 Details](#details-2) below, you are awarded *eight* points.

The contribution towards your final course grade is calculated as follows:

```maths
	floor(10 * (task1_points_awarded + task2_points_awarded) / 19)
```

Your provisional score for each task can be viewed on GitLab after every push to `projects.cs.nott.ac.uk.`. Your final score will be based on the code in the last commit pushed to `projects.cs.nott.ac.uk.` *before* the coursework deadline. Commits pushed after the coursework deadline will be disregarded. After the coursework deadline, your code will undergo further review and, based on this review, your provisional score may go up or down. This further review will include checks for code plagiarism and for trivial implementations e.g. implementations just containing an empty main function or clearly not written following the task guidelines. Final scores will be published on the G51PGA moodle pages around a week after the coursework deadline.

Your repository contains a file called `.gitlab-ci.yml`. This file is used during the assessment process and *must not* be removed or edited in any way. Any tampering with this file will result in a score of zero for this coursework.

## Task 1

### Overview

The [Drake equation](https://en.wikipedia.org/wiki/Drake_equation) asserts to give an estimate of the number of intelligent civilisations, $`N`$, in our Milky Way galaxy. In its original form, the Drake equation calculates this estimate based on seven parameters. Your task is to write a program which calculates and prints $`N`$ for several different sets of parameters.

Your C source file for this task *must* be named `task1.c` and placed in the top-level directory of your git project for this coursework.

### Details

The original [Drake equation](https://en.wikipedia.org/wiki/Drake_equation) is:

```math
N = R_* \cdot f_p \cdot n_e \cdot f_l \cdot f_i \cdot f_c \cdot L
```

Where $`N`$ is the number of active, communicative extraterrestrial civilizations in the Milky Way galaxy, and the seven parameters are:

| Parameter | Description |
| :-----: | :--- |
| $`R_*`$ | the average rate of star formations in our galaxy |
| $`f_p`$ | the fraction of formed stars that have planets |
| $`n_e`$ | for stars that have planets, the average number of planets that can potentially support life |
| $`f_l`$ | the fraction of those planets that actually develop life |
| $`f_i`$ | the fraction of planets bearing life on which intelligent, civilized life, has developed |
| $`f_c`$ | the fraction of these civilizations that have developed communications |
| $`L`$   | the length of time over which such civilizations release detectable signals |

Your C source file should contain **two functions**: a `main` function and a function named `drake_equation`.

Your `drake_equation` function should calculate the Drake equation for a given set of parameters. The `drake_equation` function should take **seven arguments**, corresponding to the **seven parameters** in Drake's original equation, as described in the [Introduction](introduction-1) to this task. You should assume all arguments are double precision floating point numbers *except for* $`n_e`$ and $`L`$, which you should assume are non-negative integers. The `drake_equation` function should calculate and return the value of $`N`$ based on the values of the arguments passed to the function. $`N`$ should be returned as a non-negative integer.

Your `main` function should be defined correctly and should call the `drake_equation` function **four times** with the follow **four sets** of parameters:

|       | $`R_*`$ | $`f_p`$ | $`n_e`$ | $`f_l`$ | $`f_i`$ | $`f_c`$ | $`L`$ |
| :---: | :-----: | :-----: | :-----: | :-----: | :-----: | :-----: | :---: |
| Set 1 | 1.0     | 0.2     | 1       | 1.0     | 1.0     | 0.1     | 1000  |
| Set 2 | 1.0     | 0.5     | 5       | 1.0     | 1.0     | 0.2     | 1000000000  |
| Set 3 | 1.5     | 1.0     | 3       | 1.0     | 0.0001     | 0.001     | 304  |
| Set 4 | 3.0     | 1.0     | 5       | 1.0     | 1.0     | 0.1     | 10000000  |

*Set 1* and *Set 2* are Drake's original lower and upper estimates respectively for the parameters. *Set 3* and *Set 4* are possible lower and upper estimates respectively for the parameters based on current data.

After each call to `drake_equation`, your `main` function should print the value of $`N`$ calculated by the `drake_equation` function, along with the values of the seven parameters used in this calculation. You should print the results in the same order as above (*Set 1* first, then *Set 2*, then *Set 3*, then *Set 4*). Floating point numbers should be printed to **one decimal place**. Integers should be printed in standard (not scientific notation) form. The eight numbers should be printed together on a new line in the following format:

```
N=? R*=? fp=? ne=? fl=? fi=? fc=? L=?
```

where `?` is replaced by the values of each of the arguments the `drake_equation` function was called with and the value of $`N`$ calculated and returned by this function. So, the first output line of your program (*Set 1* above) will be:

```
N=20 R*=1.0 fp=0.2 ne=1 fl=1.0 fi=1.0 fc=0.1 L=1000
```

and so on for *Set 2*, *Set 3*, and *Set 4*.

## Task 2

### Overview

The [Gregorian calendar](https://en.wikipedia.org/wiki/Gregorian_calendar) is a widely used calendar. A number of different standardised date formats can be used to represent dates in the Gregorian calendar. Your task is to write a program which accepts a date input by a user and calculates and prints out the date in three of these standardised formats: calendar date format, ordinal date format, and ISO week date format.

Your C source file for this task *must* be named `task2.c` and placed in the top-level directory of your git project for this coursework.

### Details

Dates can be specified and represented using different calendars and formats. In this task we will focus on dates specified in the [Gregorian calendar](https://en.wikipedia.org/wiki/Gregorian_calendar). When representing dates in the Gregorian calendar, different formats can be used. [International Standard ISO 8601](https://www.iso.org/standard/40874.html) attempts to standardise the way Gregorian dates are represented (see [here](https://www.cl.cam.ac.uk/~mgk25/iso-time.html) for a useful summary).

The following definitions are given in ISO 8601:

* A [calendar date](https://en.wikipedia.org/wiki/Calendar_date) is a date in the format `YYYY-MM-DD`, where `YYYY` is the calendar year, `MM` is the calendar month, and `DD` is the calendar day of the month.

* An [ordinal date](https://en.wikipedia.org/wiki/Ordinal_date) is a date in the format `YYYY-DDD`, where `YYYY` is the calendar year and `DDD` is the calendar day of the year (ordinal day).

* A [week date](https://en.wikipedia.org/wiki/ISO_week_date) is a date in the format `YYYY-Www-D`, where `YYYY` is the calendar year to which the week belongs (ISO year), `ww` is the calendar week (ISO week), and `D` is the day of the week (ISO weekday number).

* The **ISO weekday number** assigns a number to each day of the week, with `Monday=1, Tuesday=2, ..., Sunday=7'.

Your task is to write a program which accepts the Gregorian day, month and year input (in that order) by the user and calculates and outputs the *correctly formatted* (as in the definitions above) **calendar date**, **ordinal date**, and **week date**.

Your program can use whichever method you choose to calculate the ordinal and week dates. However, you are **not allowed** to use library functions (C standard library or otherwise) in your program other than `printf`.

Your program should output **three** lines corresponding to the ISO 8601 extended format calendar date, ordinal date and week date respectively. For example, if the user enters the three numbers "4", "6", and "1945" (the date Monday 4th June 1945), your program should output:

```
1945-06-04
1945-155
1945-W23-1
```

You program will be tested by running it with a series of randomly generated dates between the years 1900 and 2100. For this task, you can assume all dates input by the user will be valid (this is not generally a good assumption for a program though!).

Since we have not covered keyboard input yet in lectures, a function to read a number from the keyboard is provided. This function is called `get_integer()` and is provided in the `get_integer.h` header file. To use this function, include the header file at the top of your program and call the function three times to read in the day, month and year respectively from the keyboard:

```c
#include "get_integer.h"

...

	day = get_integer();
	month = get_integer();
	year = get_integer();

...
```

One approach which you could use (although you are free to use any approach you like) is to break the problem down into smaller steps and procedure calls (viz. *procedural decomposition*) to first calculate the ordinal date from the calendar date, and then use the ordinal date to calculate the week date. Some hints for how to do this are given below. If you take the approach suggested below, you will quite likely end up with *nine* functions (not listed in any particular order):

1. a main function
2. a function which calculates the ISO week year
3. a function which calculates the ISO week number
4. a function which calculates the weeks in a year
5. a function which calculates the ISO weekday number
6. a function which calculates the day of the week for 1st January
7. a function which calculates the ordinal day
8. a function which calculates if a year is a leap year or not
9. a function which rounds down a decimal to an integer

In your `main` function, aside from getting the user input and printing the results as described above, you can call function ` to calculate the ordinal day, and functions 5, 3 and 2 to calculate the ISO week date. All the other functions are called from these four functions to help in their calculations.

The first step in the suggest approach is to calculate the ordinal date. The following pseudocode calculates and returns the ordinal day from a calendar date (see [here](https://en.wikipedia.org/wiki/Ordinal_date) for more details):

```python
def calculate_ordinal_day(day, month, year):
	if month is January:
		return day
	if month is February:
		return day + 31
	ordinal_day = floor(30.6 * month - 91.4) + day
	if year is leap year:
		return ordinal_day + 60
	return ordinal_day + 59
```

Where the `floor` function returns the largest integer not greater than an given value (you will need to write your own `floor` function rather than use the one in the C standard library). Do *not* call your function `floor` though, otherwise it will clash with the standard library function. You will also need to write a function which determines if a year is a leap year. [Leap years in the Gregorian calendar](https://en.wikipedia.org/wiki/Leap_year#Gregorian_calendar) are defined as:

> Every year that is exactly divisible by four is a leap year, except for years that are exactly divisible by 100, but these centurial years are leap years if they are exactly divisible by 400. For example, the years 1700, 1800, and 1900 were not leap years, but the years 1600 and 2000 were.

Once you have the ordinal day, you can use the ordinal day along with the day of the week to calculate the ISO week. So, first we need to calculate the day of the week for our particular date.

[Gauss' algorithm](https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Gauss.27s_algorithm) is once approach to calculate the day of the week. Gauss' algorithm calculates the day of the week of 1st January for a particular year, and we can then use some straightforward modulo 7 arithmetic on the ordinal day to calculate the day of the week for our specific calendar date. Gauss' algorithm to calculate the day of the week `d` of 1st January is:

```maths
d = mod(1 + 5 * mod(Y-1, 4) + 4 * mod(Y-1, 100) + 6 * mod(Y-1, 400), 7)
```

Where `Y` is the calendar year, and `mod(X, Y)` returns X modulo Y. Note that Gauss' algorithm returns `d=0` for Sunday, `d=1` for Monday, ..., `d=6` for Saturday, whereas ISO weekday numbers are `Monday=1, Tuesday=2, ..., Sunday=7`. Now we have the day of the week of 1st January for our year, we can use this and the ordinal day we calculated to work out the ISO week day for our particular date using modulo 7 arithmetic.

Going back to calculating the ISO week, we can now do this using the ordinal day and ISO week day for any calendar date. The algorithm for doing this is (more details [here](https://en.wikipedia.org/wiki/ISO_week_date#Calculating_the_week_number_of_a_given_date)):

```python
def calculate_week(ordinal_day, week_day, year):
	week = floor((ordinal_day - week_day + 10) / 7)
	if week is 0:
		week = weeks_in_year(year - 1)
	if week > weeks_in_year(year):
		if week_day before Thursday:
			week = 1
```

Where the `weeks_in_year` function returns the number of weeks in a given calendar year. The number of weeks in a year can be calculated using the following pseudocode (see [here](https://en.wikipedia.org/wiki/ISO_week_date#Weeks_per_year) for details):

```python
def p(year):
	p = mod(year + year / 4 - year / 100 + year / 400, 7)

def calculate_weeks_in_year(year):
	if p(year) is 4 or p(year - 1) is 3:
		weeks_in_year = 53
	else:
		weeks_in_year = 52
```

The ISO year is straightforward to work out for the ISO week returned by this algorithm. If the calendar month is December and the ISO week returned is 1, then the ISO year is the year following the calendar year. If the calendar month is January and ISO week returned is 52 or 53 then the ISO year is the previous calendar year.
