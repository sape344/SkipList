#include "skiplist.hpp"
#include <chrono>
#include <math.h>
#include <random>
#include <iostream>
#include <time.h>
#include <sys/time.h>
//#define SIZE 1'000'000
int main(int argc, char const *argv[])
{
    int SIZE=100;
    if(argc==2){

     SIZE=std::stoi(argv[1]);

    }

    auto start = std::chrono::high_resolution_clock::now();
    auto stop = std::chrono::high_resolution_clock::now();
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_int_distribution<> dist(0, SIZE);

    int* randNumbers= new int[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        randNumbers[i]=dist(e2);
    }
    std::cout<<"Size = "<<SIZE<<"\n";
    skiplist dene(5, 0.5);
    double meanInsert=0;
    double meanSearch=0;
    double meanDelete=0;
    int loop_size=1;
    for (size_t i = 0; i < loop_size; i++)
    {
        start = std::chrono::system_clock::now();
        for (int i = 0; i < SIZE; i++)
        {
            dene.Insert(randNumbers[i]);

        }
        dene.Print();
        stop = std::chrono::system_clock::now();
        meanInsert+=std::chrono::duration<double, std::micro>(stop-start).count();
        start = std::chrono::system_clock::now();
        for (int i = 0; i < SIZE; i++)
        {

            dene.Search(randNumbers[i]);
        }
        stop = std::chrono::system_clock::now();
        meanSearch+=std::chrono::duration<double, std::micro>(stop-start).count();
        start = std::chrono::system_clock::now();
        for (int i = 0; i < SIZE; i++)
        {

            dene.Delete(randNumbers[i]);
        }
        stop = std::chrono::system_clock::now();
        meanDelete+=std::chrono::duration<double, std::micro>(stop-start).count();
        dene.Print();

    }
    




    std::cout<<"Size :"<<SIZE<<" ,Insert Total time(micro): "<<(meanInsert/loop_size)<<",Mean time:"<<(meanInsert/(loop_size*SIZE))<<"\n";
    std::cout<<"Size :"<<SIZE<<" ,Search Total time(micro): "<<(meanSearch/loop_size)<<",Mean time:"<<(meanSearch/(loop_size*SIZE))<<"\n";
    std::cout<<"Size :"<<SIZE<<" ,Delete Total time(micro): "<<(meanDelete/loop_size)<<",Mean time:"<<(meanDelete/(loop_size*SIZE))<<"\n"; 

    //dene.Print();
    delete[] randNumbers;
}

