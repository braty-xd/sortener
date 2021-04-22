// #include <stdio.h>  /* for printf */
// #include <stdlib.h> /* for exit */
#include <getopt.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <string>
#include <stdio.h>
#include <stdlib.h>
//#include <sstream>
#include "sorting_algorithms.h"
#include "definitions.h"
#include "help.h"

void copyNumbers();

int c;
int digit_optind = 0;
std::fstream my_file,new_file;
//std::fstream new_file;
// std::string file_name;
// std::string optarg_file_name;
// std::string new_file_name;
std::string before_file_init = "./",file_name,optarg_file_name,new_file_name,temp_string;
// template <typename T>
// std::vector<T> numbers;
// template <typename T>
// std::vector<T> temp_numbers;
std::vector<float> numbers,temp_numbers;
std::vector<std::string> strings,temp_strings;
//std::vector<float> temp_numbers;
//std::string temp_string;
//std::string opt_array;
char* opt_array;
char seperator = '\n';
float *my_list;
std::string *my_string_list;
std::vector<std::string> sorting_methods,sorting_definitons;
char *token,*arr_token;
bool save = false,is_file = false,is_definiton = false,is_arrayy=false, is_string = false,is_visualize = false,is_help = false;
double beg_time,extra_beg_time,extra_end_time;
int current_x,current_y;
std::string total_time_passed="";

enum SortingMethods
{
     InvalidMethod,
     Selection,
     Bubble,
     Insertion,
     Merge,
     Quick,
     Heap,
     Bucket,
     Shell,
};

SortingMethods resolveMethod(std::string input)
{
     if(input == "selection") return Selection;
     if(input == "bubble") return Bubble;
     if(input == "insertion") return Insertion;
     if(input == "quick") return Quick;
     if(input == "heap") return Heap;
     if(input == "merge") return Merge;
     if(input == "bucket") return Bucket;
     if(input == "shell") return Shell;
     return InvalidMethod;
}

int defSorting(std::string method)
{
     transform(method.begin(), method.end(), method.begin(), ::toupper);
     std::cout << method << " SORT\n\n";
     transform(method.begin(), method.end(), method.begin(), ::tolower);
     switch (resolveMethod(method))
     {
     case Selection:
          std::cout << selection_definiton;
          break;
     case Insertion:
          std::cout << insertion_definiton;
          break;
     case Bubble:
          std::cout << bubble_definiton;
          break;
     case Shell:
          std::cout << shell_definiton;
          break;
     case Heap:
          std::cout << heap_definiton;
          break;
     case Merge:
          std::cout << merge_definiton;
          break;
     case Quick:
          std::cout << quick_definiton;
          break;
     
     case InvalidMethod:
               std::cout << "invalid sorting argument: " << method << "\n";
               exit(EXIT_SUCCESS);
               return 1;          
     }

     return 0;
}

int printSorting(std::string method)
{    
     copyNumbers();
     beg_time = clock();
     int numbers_size;
     if(is_string)
     {
          numbers_size = strings.size();
          switch (resolveMethod(method))
          {
          case Selection:
               selectionSort(my_string_list,numbers_size,is_visualize);
               break;
          case Bubble:
               bubbleSort(my_string_list,numbers_size,is_visualize);
               break;
          case Insertion:
               insertionSort(my_string_list,numbers_size,is_visualize);
               break;
          case Quick:
               quickSort(my_string_list,0,numbers_size-1,is_visualize);
               break;
          case Shell:
               shellSort(my_string_list,numbers_size,is_visualize);
               break;
          case Heap:
               heapSort(my_string_list,numbers_size,is_visualize);
               break;
          case Merge:
               mergeSort(my_string_list,0,numbers_size-1,is_visualize);
               break;
          // case Bucket:
          //      bucketSort(my_string_list,numbers_size);
          //      break;
          case InvalidMethod:
               std::cout << "invalid sorting argument: " << method << "\n";
               exit(EXIT_SUCCESS);
               return 1;
          }
     }
     else
     {
          numbers_size = numbers.size();
          switch (resolveMethod(method))
          {
          case Selection:
               selectionSort(my_list,numbers_size,is_visualize);
               break;
          case Bubble:
               bubbleSort(my_list,numbers_size,is_visualize);
               break;
          case Insertion:
               insertionSort(my_list,numbers_size,is_visualize);
               break;
          case Quick:
               quickSort(my_list,0,numbers_size-1,is_visualize);
               break;
          case Shell:
               shellSort(my_list,numbers_size,is_visualize);
               break;
          case Heap:
               heapSort(my_list,numbers_size,is_visualize);
               break;
          case Merge:
               mergeSort(my_list,0,numbers_size-1,is_visualize);
               break;
          // case Bucket:
          //      bucketSort(my_list,numbers_size);
          //      break;
          case InvalidMethod:
               std::cout << "invalid sorting argument: " << method << "\n";
               exit(EXIT_SUCCESS);
               return 1;
          }
     }
     
     getyx(stdscr,current_y,current_x);
     //move(0,0);
     //std::cout << "\r";
     //std::cout << "Total time elapsed for " << method << " sort: " << (double)(clock() - beg_time-(sleep_time*vis_wait_count))/CLOCKS_PER_SEC << " seconds \n";  -(sleep_time*vis_wait_count)
     total_time_passed += "Total time elapsed for " + method + " sort: " + std::to_string((double)(clock() - beg_time)/CLOCKS_PER_SEC) + " seconds \n";
     //std::cout << "Worst case performance: O(n2)\n";
     return 0;
}

void getNumbers()
{
     int i = 0;
     try
     {
          file_name = before_file_init.append(optarg_file_name);
          my_file.open(file_name, std::ios::in);
          if(!my_file)
          {
               std::cerr << "Cant read file " << optarg_file_name << " or it does not exist.\n";
               exit(EXIT_SUCCESS);
          }
          if(is_string)
          {
               while(getline(my_file,temp_string,seperator)){
               strings.push_back(temp_string);
               temp_strings.push_back(temp_string);
               }
               std::cout << "got strings\n";
               my_string_list = &temp_strings[0];
               std::cout << "got pointer assignment\n";
          }
          else
          {
               while(getline(my_file,temp_string,seperator)){
               numbers.push_back(std::stof(temp_string));
               temp_numbers.push_back(std::stof(temp_string));
               my_list = &temp_numbers[0];
          }
          }
          
          
          my_file.close();
     }
     catch(const char* msg)
     {
          std::cerr << "Cant read file " << optarg_file_name << " or it does not exist.\n";
          exit(EXIT_SUCCESS);
     }
     //std::cout << "got numbers\n";
}

void getArray()
{
     arr_token = strtok(opt_array,",");
     if(is_string)
     {
          while(arr_token != NULL){
          strings.push_back(arr_token);
          temp_strings.push_back(arr_token);
          arr_token = strtok(NULL, ",");
          }
          my_string_list = &temp_strings[0];
     }
     else
     {
          while(arr_token != NULL){
          numbers.push_back(std::stof(arr_token));
          temp_numbers.push_back(std::stof(arr_token));
          arr_token = strtok(NULL, ",");
          }
          my_list = &temp_numbers[0];
     }
     
}

void copyNumbers()
{
     int numbers_size;
     if(is_string)
     {
          for(int i = 0; i < strings.size(); i++)
          {
               temp_strings[i] = strings[i];
          }
     }
     else
     {
          for(int i = 0; i < numbers.size(); i++)
          {
               temp_numbers[i] = numbers[i];
          }
     }
     
}



int main(int argc, char **argv)
{
     //parsing all the arguments
     while (1)
     {
          int this_option_optind = optind ? optind : 1;
          int option_index = 0;
          static struct option long_options[] = {
              {"verbose", no_argument, 0, 0},
              {"file", required_argument, 0, 2},
              {"array", required_argument, 0, 3},
              {"seperator", required_argument, 0, 4},
              {"sort-by", required_argument, 0, 5},
              {"save", required_argument, 0, 6},
              {"detail", no_argument, 0, 7},
              {"definition", no_argument, 0, 8},
              {"string", no_argument, 0, 9},
              {"visualize", no_argument, 0, 10},
              {"speed", required_argument, 0, 11},
              {"help", no_argument, 0, 12},
              {0, 0, 0, 0}};

          c = getopt_long_only(argc, argv, ":a:bc:d:012",
                               long_options, &option_index);
          if (c == -1)
               break;

          switch (c)
          {

          case 2:
               is_file = true;
               optarg_file_name = optarg;
               break;
          case 3:
               is_arrayy = true;
               opt_array = optarg;
               //seperator=',';
               
               break;
          case 4:
               seperator = optarg[0];
               if(optarg[0] == 'n')
               {
                    seperator = '\n';
               }
               break;
          case 5:
               token = strtok(optarg,",");
               while(token != NULL){
                    sorting_methods.push_back(token);
                    token = strtok(NULL, ",");
               }
               break;
          case 6:
               save = true;
               new_file_name = optarg;
               break;
          case 8:
               is_definiton = true;
               break;
          case 9:
               is_string= true;
               break;
          case 10:
               is_visualize = true;
               IS_VIS = true;
               break;
          case 11:
               sleep_time /= stof(optarg);
               break;
          case 12:
               is_help= true;
               break;
          case ':':
               std::cout << "option " << long_options[optind].name << " needs an argument\n";
               exit(EXIT_SUCCESS);
               break;

          case '?':
               std::cout << "option " << argv[optind - 1] << " is invalid\n";
               exit(EXIT_SUCCESS);
               break;

          default:
               printf("?? getopt returned character code 0%o ??\n", c);
          }
     }

     if (optind < argc)
     {
          printf("non-option ARGV-elements: ");
          while (optind < argc)
               printf("%s ", argv[optind++]);
          printf("\n");
     }

     if(argc == 1)
     {
          std::cout << "Usage: sortener [OPTION]... [FILE/ARRAY]\n";
          std::cout << "Sortener is a program for visualizing the most commonly known sorting algorithms\n\n";
          std::cout << "Use --help option to see options\n";
          exit(EXIT_SUCCESS);
     }

     if(is_help)
     {
          std::cout << help_page;
          exit(EXIT_SUCCESS);
     }

     if(is_file)
     {
          getNumbers();
     }
     else if(is_arrayy)
     {
          getArray();
     }

     if(is_definiton)
     {
          for(int i = 0; i< sorting_methods.size(); i++)
          {
               if(defSorting(sorting_methods[i])) break;
               std:: cout << "\n";
          }
          exit(EXIT_SUCCESS);
     }

     if(is_visualize)
     {
          startScreen();
     }

     for(int i = 0; i< sorting_methods.size(); i++)
     {
          vis_wait_count=0;
          if(printSorting(sorting_methods[i])) break;
          current_array="";
          visWait();

     }

     if(is_visualize)
     {
          //getch();
          endScreen();
     }
     std::cout << total_time_passed;
     //std::cout << "got print sorting\n";
     if(save)
     {
          std::cout << "in save\n";
          try
          {
               copyNumbers();
               if(is_string)
               {
                    std::cout << "in string\n";
                    my_string_list = &temp_strings[0];
                    quickSort(my_string_list,0,strings.size()-1,is_visualize);
                    new_file.open(new_file_name,std::ios::out);
                    for(int i = 0; i < strings.size(); i++)
                    {
                         new_file << temp_strings.at(i);
                         new_file << seperator;
                    }
               }
               else
               {
                    my_list = &temp_numbers[0];
                    quickSort(my_list,0,numbers.size()-1,is_visualize);
                    new_file.open(new_file_name,std::ios::out);
                    for(int i = 0; i < numbers.size(); i++)
                    {
                         new_file << temp_numbers.at(i);
                         new_file << seperator;
                    }
               }
               
               new_file.close();
          }
          catch(const char *msg)
          {
               std::cerr << "Cant open file " << new_file_name << "\n";
          }
     }
     //std::cout << "allooooo\n";
     // if(is_visualize)
     // {
     //      startScreen();
     //      printArrayVis();
     //      getch();
     //      endScreen();
     // }
     
     exit(EXIT_SUCCESS);
}
