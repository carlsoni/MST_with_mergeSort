//include necessary header file here
//----
#include "Edge.h"
using namespace std;

class Graph
{
   private:
      int V, E;             //number of vertice and edges in the graph
      City* setOfCities;    //an array of cities
      Edge* setOfEdges;     //an array of edges

   public:
      Graph(int numOfCities, int numOfEdges, City* cityArray, Edge* edgeArray);
      ~Graph();
      void make_set(City* aCity);
      City* find_set(City* aCity);
      void link(City* aCity, City* bCity);
      void Union(City* aCity, City* bCity);
      void SortEdges();
      void MST_Kruskal();
      void mergeSort(int begin, int end);
      void merge( int left, int mid, int right);
      //add any auxillary functions in case you need them
};

//finish each function according to above definition

// Constructor
Graph::Graph(int numOfCities, int numOfEdges, City* cityArray, Edge* edgeArray){
   V = numOfCities;
   E = numOfEdges;
   setOfCities = cityArray;
   setOfEdges = edgeArray;
}

Graph::~Graph(){

}

// makes each city its own set initialized as its own
// parent with a rank of 0
void Graph::make_set(City* aCity){
   aCity->parent = aCity;
   aCity->rank = 0;
}

// will return infinitly until it grabs its super parent being the parent of itself
City* Graph::find_set(City* aCity){
   if(aCity == aCity->parent){
      return aCity;
   }
   else{
     return find_set(aCity->parent);
   }
}

// links 2 sets together 
void Graph::link(City* aCity, City* bCity){
   if(aCity->rank > bCity->rank){
      bCity->parent = aCity;
   }
   else{
      aCity->parent = bCity;
      if(aCity->rank == bCity->rank){
         bCity->rank = bCity->rank + 1;
      }
   }
}
// calls the link function between the parents of supersets
void Graph::Union(City* aCity, City* bCity){
   link(find_set(aCity), find_set(bCity));
}

// calls a mergesort algorithmn
void Graph::SortEdges(){
   mergeSort(0, E - 1);
}

// merge sort algorithim according to pseudocode
void Graph::mergeSort(int begin, int end){
   if (begin >= end)
        return; // Returns recursively
 
    int mid = begin + (end - begin) / 2;
    mergeSort( begin, mid);
    mergeSort(mid + 1, end);
    merge(begin, mid, end);
}

// merge function from merge
void Graph::merge( int left, int mid, int right){
      int subArrayOne = mid - left + 1;
      int subArrayTwo = right - mid;
 
      // makes 2 sub array's of the super array
      Edge *leftArray = new Edge[subArrayOne];
      Edge *rightArray = new Edge[subArrayTwo];
 
    // populates the left and right sub array's 
    for (int i = 0; i < subArrayOne; i++){
      leftArray[i] = setOfEdges[left + i];
    }   
    for (int j = 0; j < subArrayTwo; j++){
      rightArray[j] = setOfEdges[mid + 1 + j];
    }

   //index of first and second sub array's
    int indexOfSubArrayOne = 0; 
    int indexOfSubArrayTwo = 0; 

    // index of merged array
    int indexOfMergedArray = left; 
 
    // Merge the temp arrays back into array
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne].getDistance() <= rightArray[indexOfSubArrayTwo].getDistance()) {
            setOfEdges[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            setOfEdges[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of left sub array
    while (indexOfSubArrayOne < subArrayOne) {
        setOfEdges[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of right sub array
    while (indexOfSubArrayTwo < subArrayTwo) {
        setOfEdges[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}


//*******************************************************************
//This function performs the Kruskal algorithm on the graph
void Graph::MST_Kruskal()
{
   cout << "MST Kruskal Algorithm Result\n" << endl;
   int totalDistance = 0;

   bool found = false;
   Edge * a = new Edge[V-1];
   int s = 0;

   // calls the sorting algorithmn of sorting edges by the distance in acsending order
   SortEdges();

   // makes a set for each city
   for(int i = 0; i < V; i++){
      make_set(&setOfCities[i]);
   }
   
   // loops through all the edges in the graph 
   for(int i = 0; i < E; i++){
      // checks if 2 cities on a given edge are in the same set
      if(find_set(setOfEdges[i].getCity1()) != find_set(setOfEdges[i].getCity2())){
         // if theyre not in the same set
         // they chack to see if both cities are already in the mst
         // this is to avoid cycles
         found = false;
         for(int j = 0; j < s; j++){
            if((a[j].getCity1() == setOfEdges[i].getCity1() && 
            a[j].getCity2() == setOfEdges[i].getCity2()) || 
            a[j].getCity2() == setOfEdges[i].getCity1() && 
            a[j].getCity1() == setOfEdges[i].getCity2()){
               found = true;
            }
         }

         // if not, the edge is added
         if(!found){
            a[s] = setOfEdges[i];
            ++s;
         }
         
         // joins the two sets together
         Union(setOfEdges[i].getCity1(), setOfEdges[i].getCity2());
      }
   }
   for(int i = 0; i < s; i++){
      a[i].printEdge();
      totalDistance += a[i].getDistance();
   }

   cout << "=================================================" << endl;
   cout << "Total  Distance: " << totalDistance << endl;
}