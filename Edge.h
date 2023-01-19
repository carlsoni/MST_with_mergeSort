#include <iomanip>
#include <string>
#include <iostream>
using namespace std;

//City represents one vertex of the graph
struct City
{
   string cityName;
   int rank;
   struct City* parent;

   //C++ don't provide a default constructor, need it here.
   City()
   {
        //----
        //----
   }

   //overloaded constructor
   City(string name)
   {
      //----
      //----
      cityName = name;
   }
};

//class Edge represents one edge of the graph which connects two City objects
class Edge
{
   private:
   struct City* city1;
   struct City* city2;
   int distance;

   public:
   Edge();  //default constructor
   Edge(City* city1, City* city2, int distance);
   ~Edge();
   City* getCity1();
   City* getCity2();
   int getDistance();
   void printEdge();
};

//finish each function according to above definition
//----
//----
Edge::Edge(){

}

Edge::Edge(City* city1, City* city2, int distance){
   this->city1 = city1;
   this->city2 = city2;
   this->distance = distance;
}

Edge::~Edge(){

}

City* Edge::getCity1(){
   return city1;
}

City* Edge::getCity2(){
   return city2;
}

int Edge::getDistance(){
   return distance;
}

void Edge::printEdge()
{
   cout << left;
   cout << setw(15) << city1->cityName
   << setw(8) << "<--->"
   << setw(15) << city2->cityName
   << setw(3) << " = "
   << setw(8) << right << getDistance()
   << endl;
}