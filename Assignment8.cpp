//************************************************************************
// ASU CSE310 Assignment #8 Fall 2022
// ASU ID: 1223065376
// Name: Ian Carlson
// Description: this is the main program that reads input from keyboard,
// it then use disjoint set data structure to perform Kruskal MST algorithm
// on the graph. 
// 
//**************************************************************************

#include "Graph.h"

using namespace std;

void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& distance);
int searchCityArr(City* oneCityArray, int size, string oneCityName);

int main()
{
   int V, E, iv = 0, ie = 0 ,found, found1, distance;        //number of vertice and edges
   
   //cout << "Enter number of vertice and edges: " << endl;
   cin >> V >> E;
   cin.ignore(20, '\n');

   //a City array used to store all vertice (Cities) of the graph
   City* cityArray = new City[V];

   //an array used to store all edges of the graph
   Edge* edgeArray = new Edge[E];

   //----
   //----
   int i =0, j=0; //index for cityArray and edgeArray

   //local variables
   City* city1;
   City* city2;
   Edge* aNewEdge;

   string oneLine, oneArrCityInfo, arrCityName;

   //cout << "Enter one departure and its arrival city info." << endl;
   getline(cin, oneLine);

   while(oneLine.compare("End") != 0)
   {
      //get one line of the input, extract the first token
      //create a City if it does not exist in cityArray,
      //insert it inside the cityArray. This will be first point of the 'aNewEdge'
      string delimiter = ",";
      int pos=oneLine.find(delimiter);
      string token = oneLine.substr(0,pos);
      oneLine.erase(0, pos+delimiter.length());



      
      found = searchCityArr(cityArray, V, token);
      if(found == -1){
         cityArray[iv].cityName = token;
         found = iv;
         ++iv;
      }
     
      //extract the arrival city info. check whether it exists in
      //cityArray or not, if not, create a new City, add it inside.
      //This city will be the second point of the 'aNewEdge'
      pos = oneLine.find(delimiter);
      oneArrCityInfo = oneLine.substr(0,pos+1);
      oneLine.erase(0,pos+delimiter.length());

      while(oneArrCityInfo != "\n" && oneArrCityInfo != "" && oneArrCityInfo != " " && oneArrCityInfo != ","){


         getArrCityInfo( oneArrCityInfo,  arrCityName, distance);


         found1 = searchCityArr(cityArray, V, arrCityName);

         if(found1 == -1){
            cityArray[iv].cityName = arrCityName;
            found1 = iv;
            ++iv;
         }
         

         edgeArray[ie] = Edge(&cityArray[found], &cityArray[found1], distance);
         ++ie;


         pos = oneLine.find(delimiter);
         oneArrCityInfo = oneLine.substr(0,pos+1);
         oneLine.erase(0,pos+delimiter.length());
      }
      //by using the two cities we got above, create a new edge, add
      //it inside edgeArray
      
      //get next line
      getline(cin, oneLine);
   } //repeat until the 'End'

   //Create a Graph object by using cityArray and edgeArray
   Graph *g = new Graph(V, E, cityArray, edgeArray);


   //Run Kruskal MST algorithm on above graph
   g->MST_Kruskal();
   

}

//****************************************************************
//By giving a string, for example 'Y(1234)', this function
//extract the arrival city name 'Y' and distance '1234'
//Note: the delimiter is left and right parenthesis
//****************************************************************
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& distance)
{
   string delimiter1 = "(";
   string delimiter2 = ")";
   int pos=oneArrCityInfo.find(delimiter1);
   string token = oneArrCityInfo.substr(0,pos);
   arrCityName = token;
   oneArrCityInfo.erase(0, pos+delimiter1.length());

   pos=oneArrCityInfo.find(delimiter2);
   token = oneArrCityInfo.substr(0,pos);
   
   distance = stoi(token);
   oneArrCityInfo.erase(0, pos+delimiter2.length());

}

//*********************************************************************
//Given a city name, this function searches cityArray and it return the
//index of the City if it exists, otherwise it returns -1
//****************************************************************
int searchCityArr(City* oneCityArray, int size, string oneCityName)
{
   for(int i = 0; i < size; ++i){
         if(oneCityArray[i].cityName.compare(oneCityName) == 0){
            return i;
         }
   }
   return -1;
}