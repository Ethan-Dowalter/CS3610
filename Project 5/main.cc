/**
 *        @file: main.cpp
 *      @author: Ethan Dowalter
 *        @date: November 25, 2020
 *       @brief: Project 5 - Hopelessly mutilated Heap version of Single Source Shortest Path using graphs
 */


#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <sstream>
#include <cfloat>
#include <limits.h>
using namespace std;


struct Element{
	int dist;
	int index;
	/// Overloaded comparison operators for priority queue
	/// If I'm remembering correctly, I'm pretty sure it only uses < operator, but I did both just to be safe
	bool operator < (const Element& other) const { return dist < other.dist; }
	bool operator > (const Element& other) const { return dist > other.dist; }
};


int main(int argc, char** argv){

    ///Read user input
    int test_cases;                         //Number of test cases that the user is going to input
    vector <int> num_vertices;              //Total number of vertices in each network
    vector <vector <string>> vertices;      //2D matrix of vertices in each network
    vector <vector <vector <int>>> dist;    //3D matrix of distances between all vertices each network
    int temp;                               //Temporary int used to read in values
    string str;                             //Temporary string used to read in values

    cin >> test_cases;                      //read in number of test cases first
    for (int i = 0; i < test_cases; i++)    //loop for reading input
    {
        cin >> temp;                                            //read in the number of vertices with a temp int
        num_vertices.push_back(temp);                           //put the number of vertices into the matrix
        cin.ignore(numeric_limits<streamsize>::max(), '\n');    //makes sure to ignore new line char before getline function

        vertices.push_back(vector <string>());                  //create next row in 2D matrix for vertices
        for (int j = 0; j < num_vertices.at(i); j++)
        {
            getline(cin, str);                                  //read in each vertex with a temp string
            vertices[i].push_back(str);                         //put vertex in corresponding place in 2D matrix
        }
        
        dist.push_back(vector <vector <int>>());                //create next layer of 3D matrix
        for (int j = 0; j < num_vertices.at(i); j++)
        {
            dist[i].push_back(vector <int>());                  //create a row of distances for eavertex
            getline(cin, str);                                  //read in each line of ints with a temp string
            istringstream input_stream(str);                    //use the temp string to parse ints into matrix
            while (input_stream >> temp)                        //use temp int to read through string
            {
                dist[i][j].push_back(temp);                     //put distance in corresponding place in 3D matrix
            }
        }        
    }


    ///Perform shotest path algorithm
    deque <Element> min_heap;
    // vector <int> smallest_weight;                           //vector for tracking smallest distance from given vertex
    vector <string> predecessor;                            //vector for recording shortest path predecessors for given vertex
    vector <int> output_dist;                               //vector for recording the final shortest distance for each test case
    vector <string> output_path;                            //vector for recording the final shortest path for each test case
    vector <string> reverse_path;                           //vector for retracing the shortest path from final vertex
    for (int i = 0; i < test_cases; i++)                    //loop for shortest path algorithm
    {
        // for (int j = 0; j < num_vertices.at(i); j++)
        //     smallest_weight.push_back(dist[i][0][j]);       //initialize weights away from source

        Element temp_elem;
        for (int j = 1; j < num_vertices.at(i); j++)
        {
            if (dist[i][0][j] == 0)
                temp_elem.dist = 0;
            else
                temp_elem.dist = dist[i][0][j];

            temp_elem.index = j;
            min_heap.push_back(temp_elem);                  //initialize weights away from source
        }
        make_heap(min_heap.begin(), min_heap.end(), greater<>{});        //turns vector into min heap

        predecessor.push_back(vertices[i][0]);              //predecessor of first vertex is always itself
        for (int j = 1; j < num_vertices.at(i); j++)
        {
            if (dist[i][0][j] != 0)
                predecessor.push_back(vertices[i][0]);
            else
                predecessor.push_back("");                  //initialize rest of predecessor vector with empty strings 
        }
        
        bool *weight_found;                                 //array for knowing if the min distance is found for each vertex
        weight_found = new bool[num_vertices.at(i)];        //declare new array that matches size of total number of vertices

        weight_found[0] = true;                             //source vertex is first to be determined
        for (int j = 1; j < num_vertices.at(i); j++)
            weight_found[j] = false;                        //every other vertex is undetermined at first

        int v;
        double min_weight;
        for (int j = 0; j < num_vertices.at(i) - 1; j++)    //loop for determining the distance to one vertex
        {
            // min_weight = DBL_MAX;
            min_weight = min_heap[0].dist;

            // for (int k = 0; k < num_vertices.at(i); k++)    //linear search to find undetermined vertex with smallest distance
            // {
            //     if (!weight_found[k])
            //     {
            //         if (smallest_weight[k] < min_weight && smallest_weight[k] != 0)
            //         {
            //             v = k;
            //             min_weight = smallest_weight[v];
            //         }
            //     }
            // }

            v = min_heap[0].index;
            weight_found[v] = true;



            

            for (int k = 0; k < num_vertices.at(i); k++)
            {
                cout << weight_found[k] << ' ';
            }
            cout << endl;


            for (int k = 0; k < num_vertices.at(i); k++)
            {
                if (!weight_found[k])
                {
                cout << i << ' ' << v << ' ' << k << ':' << dist[i][v][k] << ' ' << min_weight << ' ' << min_heap[k].dist << endl;
                    if (dist[i][v][k] != 0 && (min_weight + dist[i][v][k] < min_heap[k].dist || min_heap[k].dist == 0))
                    {
                        min_heap[k].dist = min_weight + dist[i][v][k];        //update neighbors' distances if necessary
                        cout << min_heap[k].dist << ' ' << min_weight + dist[i][v][k] << endl;
                        predecessor.at(k) = vertices[i][v];
                    }
                }
            }

            

            // for (int k = 0; k < num_vertices.at(i); k++)
            // {
            //     if (!weight_found[k])
            //     {
            //     cout << i << ' ' << v << ' ' << k << ':' << dist[i][v][k] << ' ' << min_weight << ' ' << min_heap.top().dist << ' ' << smallest_weight[k] << endl;
            //         if (dist[i][v][k] != 0 && (min_weight + dist[i][v][k] < smallest_weight[k] || smallest_weight[k] == 0))
            //         {
            //             smallest_weight[k] = min_weight + dist[i][v][k];        //update neighbors' distances if necessary
            //             predecessor.at(k) = vertices[i][v];
            //         }
            //     }
            // }

            



            make_heap(min_heap.begin(), min_heap.end(), greater<>{});
            cout << min_heap[0].dist << endl << endl;
            min_heap.pop_front();
            make_heap(min_heap.begin(), min_heap.end(), greater<>{});
        }

        
        // while (!min_heap.empty())
        // {
        //     cout << min_heap[0].dist << ' ' << min_heap[0].index <<  endl;
        //     min_heap.pop_front();
        // }
        // cout << endl;
        // return 0;

        int temp = vertices[i].size() - 1;
        string str = vertices[i][temp];
        reverse_path.push_back(str);
        while (str != vertices[i][0])
        {
            str = predecessor.at(temp);
            for (size_t j = 0; j < vertices[i].size(); j++)
                if (vertices[i][j] == str)
                    temp = j;
            reverse_path.push_back(str);
        }

        // output_dist.push_back(smallest_weight.at(smallest_weight.size() - 1));

        str = "";
        for (int j = reverse_path.size() - 1; j >= 0; j--)
            str += reverse_path.at(j) + ' ';
        output_path.push_back(str);
        
        cout << endl << min_heap.size() << endl << endl;
        // while (smallest_weight.size() > 0)
        //     smallest_weight.pop_back();         //clear smallest_weight vector for next loop

        while (predecessor.size() > 0)
            predecessor.pop_back();             //clear predecessor vector for next loop

        while (reverse_path.size() > 0)
            reverse_path.pop_back();            //clear reverse_path vector for next loop
    }

    ///Display output
    for (int i = 0; i < test_cases; i++)
    {
        cout << output_path.at(i) << output_dist.at(i) << endl;
    }
    
    return 0;
}