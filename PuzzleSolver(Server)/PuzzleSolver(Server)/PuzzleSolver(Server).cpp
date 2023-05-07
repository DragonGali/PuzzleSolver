#include "Picture.h"



int main()
{
    
  
    ifstream InFile("C://Users//magshimim//Desktop//PuzzleSolver//puzzle-maker//ClientLink.txt"); // create an output file stream object
    string text;

    if (InFile.is_open()) { // check if the file is open
        getline(InFile, text);
        Picture picture(text);
        InFile.close(); // close the file
    }
    else {
        cout << "Unable to open file" << endl;
    }
    
   

  // Picture picture("C://Users//magshimim//Desktop//PuzzleSolver//puzzle-maker//Pictures//image i guess.jpg");
    

}
