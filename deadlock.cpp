//Johnathan Hampton
//CST 221
//
//10/18/2020
//DeadLock Assignment

#include <iostream>
#include <string>
#include <fstream>


using namespace std;


// Number of processes
const int J = 5;


// Number of resources
const int H = 3;


ofstream txtFile;


// Function to find the need of each process
// To calculate the need, we take the max matrix and subtract the new matrix from it
void calculateNeed(int need[J][H], int max[J][H], int locat[J][H])
{
   // Calculating Need of each P
   for (int i = 0 ; i < J ; i++)
       for (int j = 0 ; j < H ; j++)


           // Need of instance = maxm instance - allocated instance
           need[i][j] = max[i][j] - locat[i][j];
}



//method to print string out into  readible state
void printMatrix(string msg, int array[J][H]) {
 cout << msg << endl;
 txtFile << msg << endl;
 for ( int x = 0; x < J; x ++ ) {
   cout << "[";
   txtFile << "[";
   for ( int y = 0; y < H; y++ ) {
       cout << array[x][y] << " ";
       txtFile << array[x][y] << " ";
   }
   txtFile << "]" << endl;
   cout << "]" << endl;
 }
}




// Function to find the system is in safe state or not
bool isSafe(int processes[], int avail[], int max[][H], int locat[][H])
{
   int need[J][H];


   // Function to calculate need matrix
   calculateNeed(need, max, locat);


   printMatrix("Needed Resources Matrix: ", need);





   bool finish[J] = {0};


   // To store safe sequence
   int safeSeq[J];


   // Make a copy of available resources
   int work[H];
   for (int i = 0; i < H ; i++)
       work[i] = avail[i];


   // While all processes are not finished
   // or system is not in safe state.
   int count = 0;
   while (count < J)
   {
       // Find a process which is not finish and
       // whose needs can be satisfied with current
       // work[] resources.
       bool found = false;
       for (int p = 0; p < J; p++)
       {
           // First check if a process is finished,

           if (finish[p] == 0)
           {
               //for loop for all resources
               int j;
               for (j = 0; j < H; j++)
                   if (need[p][j] > work[j])
                       break;


              //satisfied or not check
               if (j == H)
               {

                   for (int k = 0 ; k < H ; k++)
                       work[k] += locat[p][k];


                   // Add this process to safe sequence.
                   safeSeq[count++] = p;



                   finish[p] = 1;


                   found = true;
               }
           }
       }


       // not safe state
       if (found == false)
       {
           cout << "System is not in safe state";
           txtFile << "System is not in safe state";
           return false;
       }
   }


   // If system is in safe state then
   // safe state
   cout << "System is in a safe state.\nSafe sequence is: ";
   txtFile << "System is in a safe state.\nSafe sequence is: ";
   for (int i = 0; i < J ; i++) {
       cout << safeSeq[i] << " ";
       txtFile << safeSeq[i] << " ";
   }
   return true;
}


// Driver code
int main()
{
   txtFile.open("d-safe.txt");


   int processes[] = {0, 1, 2, 3, 4};


   // Available instances of resources
   int avail[] = {3, 3, 2};


   // Maximum H t
   // to processes
   int maxm[][H] = {{7, 5, 3},
                    {3, 2, 2},
                    {9, 0, 2},
                    {2, 2, 2},
                    {4, 3, 3}};
   printMatrix("Maximum Resource Matrix: ", maxm);


   int allot[][H] = {{0, 1, 0},
                     {2, 0, 0},
                     {3, 0, 2},
                     {2, 1, 1},
                     {0, 0, 2}};
   printMatrix("Allocated Resources Matrix: ", locat);


   // Check system is in safe state
   isSafe(processes, avail, max, locat);


   txtFile.close();


   return 0;
}
