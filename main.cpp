
#include <iostream>
#include <fstream>
#include "huffmanread.h"


using namespace std;

    

int main()
{
    
    cout<<"Do you want to Encode or Decode?" << endl;
    cout<<"Press 'E' for encoding and 'D' for Decoding" << endl;
    char input;
    cin>>input;
    input = (char)toupper(input);
    if(input == 'E')
    {
        encoding();
    }
    else if(input == 'D') {
                       
        decoding(ROOTNODE); 
    }else
    {
        cout<<"Illegal Input"<<endl;
    }
}















