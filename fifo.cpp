#include "policies.h"
/* Three cases:
1. Page is in FIFO cache/page table
2. Page is not in FIFO and FIFO is not full
3. Page is not in FIFO and FIFO is full 
Solutions:
1. Update write if ‘W’ encountered
2. Add new page to back of FIFO
3. Eject the front of FIFO and add new page to back 
Reference: https://www.geeksforgeeks.org/program-page-replacement-algorithms-set-2-fifo/ */

void printFIFO(int totalReads, int totalWrites) {
	cout << "Total disk reads: " << totalReads << endl;
	cout << "Total disk writes: " << totalWrites << endl;
}

void FIFO(vector<unsigned int> traceArray, vector<char> rwArray, int frames) {
    int totalReads = 0;
    int totalWrites = 0;
    vector<int> tempArray;
    unordered_map<int, char> PageToChar;
    unordered_set<int> setPage;
    
    for (int i = 0; i < traceArray.size(); i++) {
        // page is not in FIFO and FIFO is not full
        if (setPage.size() < frames) {
            if (setPage.find(traceArray[i]) == setPage.end()) {
                setPage.insert(traceArray[i]);
                PageToChar[traceArray[i]] = rwArray[i];
                totalReads++;
                tempArray.push_back(traceArray[i]); 
            }
        }
        // page is in FIFO table
        else if (setPage.find(traceArray[i]) != setPage.end()) {
            auto p = setPage.find(traceArray[i]);
            if (rwArray[i] == 'W') {
                PageToChar[traceArray[i]] = 'W';
            }
        }
        // page is not in FIFO and FIFO is full
        else {
            if (setPage.find(traceArray[i]) == setPage.end()) {
                int frontArray = tempArray.front();
                tempArray.erase(tempArray.begin());
                if (PageToChar[frontArray] == 'W') {
                    totalWrites++;
                }
                PageToChar.erase(frontArray);
                PageToChar.insert({traceArray[i], rwArray[i]});
                setPage.erase(frontArray);
                setPage.insert(traceArray[i]);
                tempArray.push_back(traceArray[i]);
                totalReads++;
            }  
        }
    }
    printFIFO(totalReads, totalWrites);
}
