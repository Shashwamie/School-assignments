#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <map>
#include <algorithm>

using namespace std;


class StockData {
public: 
    vector<string> snapshot;
    vector<map<string, string> > companySymbols;
    vector<map<string, vector<string> > > comapnyNums;
};

class Observer {
public:
    virtual void update(StockData data) = 0;
};

class AverageStockPriceObserver : public Observer {
public:
    void update(StockData data) {
        string fileName = "Average.dat";
        ofstream average(fileName);

        for (int i = 0; i < data.snapshot.size(); i++) {
            // finding average for snapshot
            double averagePrice = 0.0;
            map<string, vector<string> >::iterator it = data.comapnyNums.at(i).begin();
            while (it != data.comapnyNums.at(i).end()) {
                averagePrice = averagePrice + stod(it->second.at(6));
                ++it;
            }
            averagePrice = averagePrice / (double)(data.comapnyNums.size());

            average << data.snapshot.at(i) << " , Average Price: " << averagePrice << endl;
        }
        average.close();
    }
};

class HiLowObserver : public Observer {
public: 
    void update(StockData data) {
        string fileName = "HiLow.dat";
        ofstream hilow(fileName);

        for (int i = 0; i < data.snapshot.size(); i++) {
            // determine within 1% of high or low
            map<string, vector<string> >::iterator it = data.comapnyNums.at(i).begin();
            map<string, string>::iterator it2 = data.companySymbols.at(i).begin();
            hilow << data.snapshot.at(i) << endl;
            while (it != data.comapnyNums.at(i).end()) {
                if ((((stod(it->second.at(6))) >= (stod(it->second.at(2)) * 0.99)) && ((stod(it->second.at(6))) <= (stod(it->second.at(2)) * 1.01))) ||
                    (((stod(it->second.at(6))) >= (stod(it->second.at(1)) * 0.99)) && ((stod(it->second.at(6))) <= (stod(it->second.at(1)) * 1.01)))) {
                    hilow << it2->second << ": " << it->second.at(6) << ", " << it->second.at(2) << ", " << it->second.at(1) << endl;
                }
                ++it;
                ++it2;
            }
            hilow << endl;
        }

        hilow.close();
    }
};

class FieldsObserver : public Observer {
public:
    void update(StockData data) {
        string fileName = "Fields.dat";
        ofstream field(fileName);

        for (int i = 0; i < data.snapshot.size(); i++) {
            // list all fields for specific ticker symbol
            map<string, string>::iterator it = data.companySymbols.at(i).begin();
            map<string, vector<string> >::iterator it2 = data.comapnyNums.at(i).begin();
            field << data.snapshot.at(i) << endl;
            while (it != data.companySymbols.at(i).end()) {
                if (it->second == "ALL" || it->second == "BA" || it->second == "BC" || it->second == "GBEL" || it->second == "KFT" || it->second == "MCD" ||
                    it->second == "TR" || it->second == "WAG") {
                    field << it->first << " " << it->second << " ";
                    for (int i = 0; i < 7; i++) {
                        field << it2->second.at(i) << " ";
                    }
                    field << endl;
                }
                ++it;
                ++it2;
            }
            field << endl;
        }
        field.close();
    }
};


class LocalStocks {
    list<Observer*> observers;
    StockData data;
    const string fileName = "Ticker.dat";

public:
    void registerObserver(Observer* o) {
        observers.push_back(o);
    }

    void removeObserver(Observer* o) {
        observers.remove(o);
    }

    void notifyObservers() {
        for (Observer* observer : observers) {
            observer->update(data);
        }
    }


    void readTickerData() {
        ifstream infile;
        ofstream hiLow("HiLow.dat");
        ofstream allFields("Fields.dat");
        infile.open(fileName);
        vector<string> snapshots;
        string line;
        string startingLine;


        if (!infile.is_open()) {
            std::cout << "Can't open file: " << fileName << endl;
        }
        else {
            int loopCounter = 0;
            while (!infile.eof()) {
                map<string, string> companySymbols;
                map<string, vector<string> > companyNums;
                // Getting snapshot line and saving int in queue
                getline(infile, startingLine);
                snapshots.push_back(startingLine.substr(0, startingLine.size() - 3));


                // Reads file until end of snapshot
                queue<string> listQueue;
                while (getline(infile, line)) {
                    if (line.at(0) == 'Z') {
                        listQueue.push(line);
                        break;
                    }
                    listQueue.push(line);
                }


                // Looping through all data in snapshot
                int listSize = listQueue.size();
                for (int i = 0; i < listSize; i++) {
                    string currentLine = listQueue.front();
                    listQueue.pop();


                    // Looping through one line at a time
                    istringstream stringStream(currentLine);
                    string word;
                    stack<string> stack;
                    while (stringStream >> word) {
                        stack.push(word);
                    }


                    // puts current lines numbers into vector
                    // 0 is end of the numbers and 6 is the firs
                    vector<string> nums;
                    for (int j = 0; j < 7; j++) {
                        nums.push_back(stack.top());
                        stack.pop();
                    }

                    // saving current line symbol
                    string symbol = stack.top();
                    stack.pop();

                    // saving current lines company name
                    string companyName;
                    int stackSize = stack.size();
                    for (int j = 0; j < stackSize; j++) {
                        companyName = stack.top() + " " + companyName;
                        stack.pop();
                    }

                    // mapping companies to their data
                    companySymbols[companyName] = symbol;
                    companyNums[companyName] = nums;
                }
                // finding average for snapshot
                double averagePrice = 0.0;
                map<string, vector<string> >::iterator it = companyNums.begin();
                while (it != companyNums.end()) {
                    //std::cout << it->first << endl;
                    averagePrice = averagePrice + stod(it->second.at(6));
                    ++it;
                }
                averagePrice = averagePrice / (double)(companyNums.size());


                // making sure it exits
                if (averagePrice > 0) {

                    // writing to Average.dat
                    //average << snapshots.at(loopCounter) << " , Average Price: " << averagePrice << endl;
                    data.comapnyNums.push_back(companyNums);
                    data.companySymbols.push_back(companySymbols);
                    data.snapshot.push_back(snapshots.at(loopCounter));


                    // writing to HiLow.dat
                    //hiLow << snapshots.at(loopCounter) << endl;
                    //hiLow << companySymbols
                }


                // clearing empty line
                getline(infile, startingLine);
                loopCounter++;

                notifyObservers();
                cout << "observers notified" << endl;
            }
        }
        
    }
};





int main() {
	LocalStocks localStocks;

	AverageStockPriceObserver averageObserver;
    HiLowObserver hiLowObserver;
    FieldsObserver fieldObserver;

	// Register observers
	localStocks.registerObserver(&averageObserver);
	localStocks.registerObserver(&hiLowObserver);
	localStocks.registerObserver(&fieldObserver);

	// Simulate reading from ticker.dat
	localStocks.readTickerData();

	return 0;
}
