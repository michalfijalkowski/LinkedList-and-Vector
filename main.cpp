#include <cstddef>
#include <cstdlib>
#include <string>
#include <cstdio>

#include "Vector.h"
#include "LinkedList.h"
#include <chrono>
#include <iostream>
namespace
{

    template <typename T>
    using Vector = aisdi::Vector<T>;
 
    template <typename T>
    using List = aisdi::LinkedList<T>;
 
 
    void perfomTest()
    {
        List<std::string> collection;
        collection.append("TODO");
    }
 
    void Test_append(int a)
    {
        List <int> collection_list;
 
 
        Vector <int> collection_vector;
        auto clock_b_vector = std::chrono::high_resolution_clock::now();
        for(int i=1;i<=a;i++)
        {
 
            collection_vector.append(std::rand());
 
        }
        auto clock_e_vector = std::chrono::high_resolution_clock::now();
        std::cout<<"Adding using append "<<a<<" elements for vector takes: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_e_vector-clock_b_vector).count()<<" nanoseconds \n";
 
		double vector_time = std::chrono::duration_cast<std::chrono::nanoseconds>(clock_e_vector-clock_b_vector).count();
		
        auto clock_b_list = std::chrono::high_resolution_clock::now();
        for(int i=1;i<+a;i++)
        {
            collection_list.append(std::rand());
        }
        auto clock_e_list = std::chrono::high_resolution_clock::now();
        std::cout<<"Adding using append "<<a<<" elements for list takes: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_e_list-clock_b_list).count()<<" nanoseconds \n";
		
		double list_time = std::chrono::duration_cast<std::chrono::nanoseconds>(clock_e_list-clock_b_list).count();
		
		if(vector_time/list_time>1) std::cout<<"List is "<< vector_time/list_time << " faster than Vector\n\n";
		else
		{
			std::cout<<"Vector is "<< list_time/vector_time << " faster than list\n\n";
		}
		
	 }
 
    void Test_prepend(int a)
    {
        List <int> collection_list;
        Vector <int> collection_vector;
 
        auto clock_b_vector = std::chrono::high_resolution_clock::now();
        for(int i=1;i<=a;i++)
        {
 
            collection_vector.prepend(std::rand());
 
        }
        auto clock_e_vector = std::chrono::high_resolution_clock::now();
        std::cout<<"Adding using prepend "<<a<<" elements for vector takes: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_e_vector-clock_b_vector).count()<<" nanoseconds \n";
		
		double vector_time = std::chrono::duration_cast<std::chrono::nanoseconds>(clock_e_vector-clock_b_vector).count();
 
        auto clock_b_list = std::chrono::high_resolution_clock::now();
        for(int i=1;i<+a;i++)
        {
            collection_list.prepend(std::rand());
        }
        auto clock_e_list = std::chrono::high_resolution_clock::now();
        std::cout<<"Adding using prepend "<<a<<" elements for list takes: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_e_list-clock_b_list).count()<<" nanoseconds \n";
		
		double list_time = std::chrono::duration_cast<std::chrono::nanoseconds>(clock_e_list-clock_b_list).count();
		
		if(vector_time/list_time>1) std::cout<<"List is "<< vector_time/list_time << " faster than Vector\n\n";
		else
		{
			std::cout<<"Vector is "<< list_time/vector_time << " faster than list\n\n";
		}
 
    }
    void Test_ErasingAllElements(int a)
    {
        List <int> collection_list;
        Vector <int> collection_vector;
        for(int i=1;i<a;i++)
        {
            collection_list.append(std::rand());
            collection_vector.append(std::rand());
        }
 
        auto clock_b_vector = std::chrono::high_resolution_clock::now();
        collection_vector.erase(collection_vector.begin(),collection_vector.end());
        auto clock_e_vector = std::chrono::high_resolution_clock::now();
        std::cout<<"Erasing all ("<<a<<") elements from vector takes:  "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_e_vector-clock_b_vector).count()<<" nanoseconds \n";
 
		double vector_time = std::chrono::duration_cast<std::chrono::nanoseconds>(clock_e_vector-clock_b_vector).count();
		
        auto clock_b_list = std::chrono::high_resolution_clock::now();
        collection_list.erase(collection_list.begin(),collection_list.end());
        auto clock_e_list = std::chrono::high_resolution_clock::now();
        std::cout<<"Erasing all ("<<a<<") elements from list takes: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_e_list-clock_b_list).count()<<" nanoseconds \n";
 
		double list_time = std::chrono::duration_cast<std::chrono::nanoseconds>(clock_e_list-clock_b_list).count();
		
		if(vector_time/list_time>1) std::cout<<"List is "<< vector_time/list_time << " faster than Vector\n\n";
		else
		{
			std::cout<<"Vector is "<< list_time/vector_time << " faster than list\n\n";
		}
 
 
    }
 
 
} // namespace
 
int main(int argc, char** argv)
{
    const std::size_t repeatCount = argc > 1 ? std::atoll(argv[1]) : 10000;
    for (std::size_t i = 0; i < repeatCount; ++i)
    {
        perfomTest();
    }
	Test_append(100);
	Test_append(1000);
    Test_append(10000);
    Test_prepend(100);
    Test_prepend(1000);
    Test_prepend(10000);
    Test_ErasingAllElements(100);
    Test_ErasingAllElements(1000);
    Test_ErasingAllElements(10000);
 
 
 
 
    return 0;
}
