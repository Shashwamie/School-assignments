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
    getline(cin, inputFileName);
    cout << endl;

    // Open file that we are reading and open file to write too
    ifstream inFile(inputFileName);
    ofstream outFile("OutputData.dat");
    string teeFileName = "";
    ofstream teeOutFile;

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
                cout << "Brackets applied\n" << endl;
            }
            if(tolower(decorationType.at(0)) == 'n'|| decorationType == "2"){
                // adding the number decorator to the stream
                outputStream = new NumberedOutput<string>(outputStream);
                cout << "Numbers applied\n" << endl;
            }
            if(tolower(decorationType.at(0)) == 't'|| decorationType == "3"){
                // check if files already created
                if (teeFileName == "")
                {
                    cout << "Please provide a file name to write to (with file extension): " << endl;
                    getline(std::cin, teeFileName);
                    cout << endl;

                    teeOutFile.open(teeFileName);
                    if (teeOutFile.is_open())
                    {
                        // adding the Tee decorator to the stream
                        outputStream = new TeeOutput<string>(outputStream, teeOutFile);
                        cout << "Created tee file named: " << teeFileName << endl;
                        cout << endl;
                    }
                }
                else{
                    // when file is already made
                    cout << "Already created Tee file named: " << teeFileName << endl;
                    cout << endl;
                }      
            }
            if(tolower(decorationType.at(0)) == 'f'|| decorationType == "4"){
                string selection = "";

                cout << "What filter do you want? (enter number)" << endl;
                cout << "1. Line contains digit" << endl;
                cout << "2. Line contains asperand (@)" << endl;
                cout << "3. Line contains octothorpe (#)" << endl;
                cout << "4. Line contains less than 50 characters" << endl;
                cout << "5. Line references the word \"python\"" << endl;
                getline(cin, selection);
                cout << endl;

                if (selection == "1" || selection == "2" || selection == "3" || selection == "4" || selection == "5")
                {
                    // adding the Filter decorator to the stream
                    outputStream = new FilterOutput<string>(outputStream, selection);
                    cout << "Filter Applied\n" << endl;
                }
                else{
                    cout << "Invalid selection" << endl;
                }
            }

            // keeps looping to add more decorators until exit
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
        teeOutFile.close();
    }
    else{
        cout << "Can not open file!" << endl;
    }
    return 0;
}
