#include <iostream>

using namespace std;

//implementing function calculateWays

int calculateWays(int wordlen , int maxvowels) {
    //if max vowels = 0 calculating ways
    if(maxvowels==0) {
        int ways = 1;
        //loop for calculating ways
        for(int i=0 ; i<wordlen ; i++) {
            ways = ways*21;
        }

        return ways;
    } else {
        if(wordlen==1)//if word length is 1
        {
            int c = 1, v = 1;
            int ways = c*21 + v*5; //calculating ways
            return ways;
        }
        else // if max vowels and world length both are greater then 1
        {
            int ways = 0;
            //loop to calculating

            for(int i=0 ; i<wordlen ; i++) {
                int c = 1, v = 1;
                for(int j=0 ; j<wordlen-maxvowels ; j++) {
                    c = c*21;
                }
                for(int k=0 ; k<maxvowels ; k++) {
                    v = v*5;
                }
                ways = ways + (v*c); // calculating ways with vowels
            }
            
            int ways1 = 1;
            for(int i=0 ; i<wordlen ; i++) {
                ways1 = ways1*21; //calculating ways without vowels
            }
            
            return ways + ways1 ; //return total ways
        }
    }
}

int main() {

int wordlen , maxvowels;// declaring variables

cin>>wordlen>>maxvowels; // reading inputs from user

int ways = calculateWays(wordlen , maxvowels); //passing values to function calculateWays

cout<<ways; //printing ways

return 0;

}

