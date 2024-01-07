#include "policies.h"
/* Three cases FIFO:
1. Page is in FIFO cache/page table
2. Page is not in FIFO and FIFO is not full
3. Page is not in FIFO and FIFO is full 
Solutions:
1. Update write if ‘W’ encountered
2. Add new page to back of FIFO
3. Eject the front of FIFO and add new page to back */
/* Three cases LRU:
1. Page is in LRU cache/page table
2. Page is not in LRU and LRU is not full
3. Page is not in LRU and LRU is full
Solutions:
1. Update write if ‘W’ encountered
2. Add new page to top of LRU
3. Eject the oldest page in LRU (bottom page) and add new page to top */
/* Five Cases VMS:
1. Page is in FIFO cache/page table
2. Page is not in FIFO and FIFO is not full
3. Page is not in FIFO and FIFO is full, LRU is not full
4. Page is in LRU (FIFO full)
5. Page is not in FIFO and is not in LRU, both are full 
Edge Cases: 
• LRU size is 0, degenerates into a FIFO algorithm, should have the same output as your FIFO algo given the same input.
• FIFO size is 0, degenerates into an LRU algorithm
// when we increment write: we only do this during ejection from LRU*/
void printVMS(int totalReads, int totalWrites) {
	cout << "Total disk reads: " << totalReads << endl;
	cout << "Total disk writes: " << totalWrites << endl;
}
void VMS(vector<unsigned int> traceArray, vector<char> rwArray, int frames, int p) {
    int secondarySize = (frames * p) / 100;
    int primarySize = (frames - secondarySize);
    int totalReads = 0;
    int totalWrites = 0;
    vector<int> tempArray;
    unordered_map<int, char> PageToChar;
    unordered_set<int> setPage;
    unordered_set<int> setPageLRU;
    unordered_map<int, int> indexes;
    // EDGE CASES // 
    if (primarySize == 0) {
        LRU(traceArray, rwArray, frames);
        exit(1);
    }
    else if (secondarySize == 0) {
        FIFO(traceArray, rwArray, frames);
        exit(1);
    }
    // FIFO STRUCTURE //
    else {
        for (int i = 0; i < traceArray.size(); i++) {
            // case 1: page is in fifo cache page table
            if (setPage.find(traceArray[i]) != setPage.end()) {
                auto p = setPage.find(traceArray[i]);
                if (rwArray[i] == 'W') {
                    PageToChar[traceArray[i]] = 'W';
                }
            }
            // case 2: page is not in fifo and fifo is not full
            else if (setPage.size() < primarySize) {
                if (setPage.find(traceArray[i]) == setPage.end()) {
                    setPage.insert(traceArray[i]);
                    PageToChar[traceArray[i]] = rwArray[i];
                    totalReads++;
                    tempArray.push_back(traceArray[i]); 
                }
            }
            // case 3: page is not in fifo and fifo is full, LRU is not full
            else if ((setPage.find(traceArray[i]) == setPage.end())) {
                    int frontArray = tempArray.front();
                    tempArray.erase(tempArray.begin());
                    if (PageToChar[frontArray] == 'W') {
                        totalWrites++;
                    }
                    PageToChar.erase(frontArray);
                    PageToChar.insert({traceArray[i], rwArray[i]}); 
                    setPage.erase(frontArray);  // eject front of fifo and move into LRU
                    setPageLRU.insert(frontArray); // moves front of FIFO into LRU set
                    setPage.insert(traceArray[i]); 
                    tempArray.push_back(traceArray[i]);
            }
            // case 4: page is in lru
            else if (setPageLRU.find(traceArray[i]) != setPageLRU.end()) {
                int frontArray = tempArray.front();
                auto p = setPageLRU.find(traceArray[i]);
                if (rwArray[i] == 'W') {
                    PageToChar[traceArray[i]] = 'W';
                }
                setPage.insert(traceArray[i]); // move page back of fifo
                tempArray.push_back(traceArray[i]); // move page back of fifo
                setPageLRU.insert(frontArray); //move front of fifo to LRU 
            }
            // case 5
            else if (setPage.find(traceArray[i]) == setPage.end() && setPageLRU.find(traceArray[i]) == setPageLRU.end()) {
                int frontArray = tempArray.front();
                int lruPage = 1000000;
                int front;
                for (auto it = setPageLRU.begin(); it != setPageLRU.end(); it++) {
                    if (indexes[*it] < lruPage) {
                        lruPage = indexes[*it];
                        front = *it;
                    }  
                }
                if (PageToChar[front] == 'W') {
                    totalWrites++;
                }
                PageToChar.erase(front);
                PageToChar.insert({traceArray[i], rwArray[i]});
                setPageLRU.erase(front); // eject oldest LRU page
                setPageLRU.insert(frontArray); // insert front of FIFO to LRU
                setPage.insert(front); // add new page back of FIFO
                tempArray.push_back(front); // add new page back of FIFO
                totalReads++;
            }
            indexes[traceArray[i]] = i;
        }
    }
    printVMS(totalReads, totalWrites);
}