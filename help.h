#ifndef help
#define help
#include <iostream>
#include <string>

const std::string help_page = ""
"Usage: sortener [OPTION]... [FILE/ARRAY]\n"
"Sortener is a program for visualizing the most commonly known sorting algorithms\n"
"\n"
"--sort-by ALGORITHM...\t\t""Select the sorting algorithms to use\n"
"--file FILE\t\t\t""Give a file to sort\n"
"--array ARRAY\t\t\t""Give an array to sort\n"
"--string\t\t\t""Sorts given file/array alphanumerically. By default only sorts numbers\n"
"--seperator\t\t\t""When reading given file, it seperates elements by given character. Default is new line '\\n' character\n"
"--visualize\t\t\t""Puts visual output of provided sortings for given file/array\n"
"--speed SPEED\t\t\t""Speeds up the visual output\n"
"--definition ALGORITHM...\t""Gives the definiton of the sorting algorithms\n"
"--save FILE\t\t\t""After sorting given array, saves the sorted version in a new file\n"
"--help\t\t\t\t""Shows help page\n";




#endif