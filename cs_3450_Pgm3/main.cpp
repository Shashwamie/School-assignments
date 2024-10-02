#include "StreamOutput.h"
#include "BracketOutput.h"
#include "DecoratorBase.h"
#include "NumberedOutput.h"
#include "TeeOutput.h"
#include "FilterOutput.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;
int main()
{
    /* Single decorator test
    ofstream outStream("OutputData.dat");
    Output<ofstream> *streamOutput = new StreamOutput<ofstream>(outStream);

    string name = "Tom";
    streamOutput = new FilterOutput<ofstream>(streamOutput);
    streamOutput->writeString(name);
    */

    string inputFileName;
    string outputFileName;

    // Get the file we will be reading;
    cout << "Please enter the name of a file you would like to decorate: " << endl;
    //getline(cin, inputFileName);
    inputFileName = "decorator.dat";
    cout << endl;

    // Open file that we are reading and open file to write too
    ifstream inFile(inputFileName);
    ofstream outFile("OutputData.dat");
    ofstream teeFile("teeOutputData.dat");

    if (inFile.is_open())
    {
        // Create a stream output object that takes in strings and writes to outFile
        Output<string> *outputStream = new StreamOutput<string>(outFile);


        // Asking user what type of decoration they want to apply
        string decorationType = "none";
        while(decorationType != "exit"){
            cout << "What type of decoration do you want to add?" << endl;
            cout << "1. Bracket Output" << endl;
            cout << "2. Numbered Output" << endl;
            cout << "3. Tee Output" << endl;
            cout << "4. Filter Output" << endl;
            cout << "5. Exit\n" << endl;

            getline(cin, decorationType);
            cout << endl;

            // slecting the decoration to apply;
            if(tolower(decorationType.at(0)) == 'b'|| decorationType == "1"){
                // adding the bracket decorator to the stream
                outputStream = new BracketOutput<string>(outputStream);
            }
            if(tolower(decorationType.at(0)) == 'n'|| decorationType == "2"){
                // adding the number decorator to the stream
                outputStream = new NumberedOutput<string>(outputStream);
            }
            if(tolower(decorationType.at(0)) == 't'|| decorationType == "3"){
                // adding the Tee decorator to the stream
                outputStream = new TeeOutput<string>(outputStream, teeFile);
            }
            if(tolower(decorationType.at(0)) == 'f'|| decorationType == "4"){
                // adding the Filter decorator to the stream
                outputStream = new FilterOutput<string>(outputStream);
            }
            if(tolower(decorationType.at(0)) == 'e'|| decorationType == "5"){
                // assigning to exit
                decorationType = "exit";
            }
        }

        // reading in file and applying decorators at the same time
        string line;
        while (getline(inFile, line))
        {
            outputStream->write(line);
        }

        inFile.close();
        outFile.close();
    }
    else{
        cout << "Can not open file!" << endl;
    }
    return 0;
}
