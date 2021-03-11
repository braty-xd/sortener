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
#include <sstream>
#include <ncurses.h>
#include "sorting_algorithms.h"

void copyNumbers();

int c;
int digit_optind = 0;
std::fstream my_file,new_file;
//std::fstream new_file;
// std::string file_name;
// std::string optarg_file_name;
// std::string new_file_name;
std::string before_file_init = "./",file_name,optarg_file_name,new_file_name,temp_string;
std::vector<float> numbers,temp_numbers;
//std::vector<float> temp_numbers;
//std::string temp_string;
char seperator = '\n';
float *my_list;
std::vector<std::string> sorting_methods,sorting_definitons;
char *token,*arr_token;
bool save = false,is_file = false,is_definiton = false,is_array=false;
double beg_time;

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

int printSorting(std::string method)
{
     copyNumbers();
     beg_time = clock();
     switch (resolveMethod(method))
     {
     case Selection:
          selectionSort(my_list,numbers.size());
          break;
     case Bubble:
          bubbleSort(my_list,numbers.size());
          break;
     case Insertion:
          insertionSort(my_list,numbers.size());
          break;
     case Quick:
          quickSort(my_list,0,numbers.size()-1);
          break;
     case Shell:
          shellSort(my_list,numbers.size());
          break;
     case Heap:
          heapSort(my_list,numbers.size());
          break;
     case Merge:
          mergeSort(my_list,0,numbers.size()-1);
          break;
     case Bucket:
          bucketSort(my_list,numbers.size());
          break;
     case InvalidMethod:
          std::cout << "invalid sorting argument: " << method << "\n";
          exit(EXIT_SUCCESS);
          return 1;
     }
     std::cout << "Total time elapsed for " << method << " sort: " << (double)(clock() - beg_time)/CLOCKS_PER_SEC << " seconds \n";
     return 0;
}

void getNumbers()
{
     try
     {
          file_name = before_file_init.append(optarg_file_name);
          my_file.open(file_name, std::ios::in);
          if(!my_file)
          {
               std::cerr << "Cant read file " << optarg_file_name << " or it does not exist.\n";
               exit(EXIT_SUCCESS);
          }
          while(getline(my_file,temp_string,seperator)){
               numbers.push_back(std::stof(temp_string));
               temp_numbers.push_back(std::stof(temp_string));
          }
          my_list = &temp_numbers[0];
          my_file.close();
     }
     catch(const char* msg)
     {
          std::cerr << "Cant read file " << optarg_file_name << " or it does not exist.\n";
          exit(EXIT_SUCCESS);
     }
}

void copyNumbers()
{
     for(int i = 0; i < numbers.size(); i++)
     {
          temp_numbers[i] = numbers[i];
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
              {"definiton", no_argument, 0, 8},
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
               is_array = true;
               arr_token = strtok(optarg,",");
               while(arr_token != NULL){
                    numbers.push_back(std::stof(arr_token));
                    arr_token = strtok(NULL, ",");
               }
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

     if(is_file)
     {
          getNumbers();
     }

     for(int i = 0; i< sorting_methods.size(); i++)
     {
          if(printSorting(sorting_methods[i])) break;
     }

     if(save)
     {
          try
          {
               my_list = &numbers[0];
               quickSort(my_list,0,numbers.size()-1);
               new_file.open(new_file_name,std::ios::out);
               for(int i = 0; i < numbers.size(); i++)
               {
                    new_file << numbers.at(i);
                    new_file << seperator;
               }
               new_file.close();
          }
          catch(const char *msg)
          {
               std::cerr << "Cant open file " << new_file_name << "\n";
          }
     }
     

     exit(EXIT_SUCCESS);
}
