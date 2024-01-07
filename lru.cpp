#include "policies.h"
/* Three cases:
1. Page is in LRU cache/page table
2. Page is not in LRU and LRU is not full
3. Page is not in LRU and LRU is full
Solutions:
1. Update write if ‘W’ encountered
2. Add new page to top of LRU
3. Eject the oldest page in LRU (bottom page) and add new page to top 
Reference: https://www.geeksforgeeks.org/program-for-least-recently-used-lru-page-replacement-algorithm/ */
void printLRU(int totalReads, int totalWrites) {
	cout << "Total disk reads: " << totalReads << endl;
	cout << "Total disk writes: " << totalWrites << endl;
}
void LRU(vector<unsigned int> traceArray, vector<char> rwArray, int frames) {
    unordered_map<int, int> elements;
    unordered_map<int, char> PageToChar;
    unordered_set<int> setPage;
    int totalReads = 0;
    int totalWrites = 0;
    for (int i = 0; i < traceArray.size(); i++)
    {   
        // page is in LRU table
        if (setPage.find(traceArray[i]) != setPage.end()) {
            auto p = setPage.find(traceArray[i]);
            if (rwArray[i] == 'W') {
                PageToChar[traceArray[i]] = 'W';
            }
        }
        // page is not in LRU and LRU is not full
        if (setPage.size() < frames) {
            if (setPage.find(traceArray[i]) == setPage.end()) {
                setPage.insert(traceArray[i]);
                PageToChar[traceArray[i]] = rwArray[i];
                totalReads++;
            }
            elements[traceArray[i]] = i;
        }
        // page is not in LRU and LRU is full
        else {
            if (setPage.find(traceArray[i]) == setPage.end()) {
                int lruPage = 1000000;
                int front;
                for (auto p = setPage.begin(); p != setPage.end(); p++) {
                    if (elements[*p] < lruPage) {
                        lruPage = elements[*p];
                        front = *p;
                    }  
                }
                if (PageToChar[front] == 'W') {
                    totalWrites++;
                }
                PageToChar.erase(front);
                PageToChar.insert({traceArray[i], rwArray[i]});
                setPage.erase(front);
                setPage.insert(traceArray[i]);
                totalReads++;
            }
            elements[traceArray[i]] = i;
        }
    }
    printLRU(totalReads, totalWrites);
}
