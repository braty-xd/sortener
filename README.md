# Sortener

Sortener is a versatile terminal program for visualizing and comparing sorting algorithms.

To install it, you should have g++ and make programs.

# Installation

run ```
git clone https://github.com/braty-xd/sortener.git```
and ```
sudo make install```

After installing it using makefile, you can use to --help to get:

Usage: sortener [OPTION]... [FILE/ARRAY]\
Sortener is a program for visualizing the most commonly known sorting algorithms

--sort-by ALGORITHM...          Select the sorting algorithms to use\
--file FILE                     Give a file to sort\
--array ARRAY                   Give an array to sort\
--string                        Sorts given file/array alphanumerically. By default only sorts numbers\
--seperator                     When reading given file, it seperates elements by given character. Default is new line '\n' character\
--visualize                     Puts visual output of provided sortings for given file/array\
--speed SPEED                   Speeds up the visual output\
--definition ALGORITHM...       Gives the definiton of the sorting algorithms\
--save FILE                     After sorting given array, saves the sorted version in a new file\
--help                          Shows help page\
--compare                       Compares sorting times\
--example EXAMPLE               Uses pre data sets for sorting.

--sort-by and --definiton options takes available sorting algorithms as argument.

Available sorting algortihms:

Bubble\
Selection\
Insertion\
Quick\
Merge\
Heap\
Shell

# Usage Examples

A basic use of definition

```sortener --definition merge```

Sorting given array by given algorithm

```sortener --sort-by bubble --array 20,60,40,80,10,70,30,50 --visualize```

Sorting given array with given speed

```sortener --sort-by quick --array 20,60,40,80,10,70,30,50 --visualize --speed 0.5```

Sorting given file

```sortener --sort-by selection --file trys/number_newline.txt --visualize```

Seperating given file with given argument and sorting it

```sortener --sort-by insertion --file trys/number_space.txt --visualize --seperator ' '```

Sorting alphanumerically

```sortener --sort-by bubble --file trys/word_newline.txt --string --visualize```

Sorting dataset 1 and comparing the sorting times

```sortener --sort-by selection,insertion,bubble,merge,quick,heap,shell --example 1 --compare```

Saving the sorted array

```sortener --sort-by bubble --array 20,60,40,80,10,70,30,50  --save a1```


These are the basic demonstration of how to use current options and their arguments. You can combine them way more different and get the result to your heart's content
