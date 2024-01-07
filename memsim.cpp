#include <iostream>
#include "policies.h"
using namespace std;

int main(int argc, const char* argv[]) {
    unsigned int addr;
    char rw;
    int traces = 0;
    int frames = atoi(argv[2]);
    int p = atoi(argv[4]);
    const char* process = argv[4];
    vector<unsigned int> traceArray;
    vector<char> rwArray;
    FILE* tracefile = fopen(argv[1], "r");

    if (argc < 5) {
        cout << "You entered less than 5 arguments. Try again." << endl;
        exit(1);
    }

    while (fscanf(tracefile, "%x %c", &addr, &rw) != EOF) {
        int addrDivide = addr / 4096; // divide trace address by 4096
        traceArray.push_back(addrDivide);
        rwArray.push_back(rw);
        traces++;
    }
    fclose(tracefile);

    cout << "Total memory frames: " << argv[2] << endl;
    cout << "Events in trace: " << traces << endl;

    if (strcmp(argv[3], "fifo") == 0) {
        FIFO(traceArray, rwArray, frames);
        if ((strcmp(process, "debug") == 0)) {
            cout << "FIFO was called!" << endl;
        }
    }
    else if (strcmp(argv[3], "lru") == 0) {
        LRU(traceArray, rwArray, frames);
        if ((strcmp(process, "debug") == 0)) {
            cout << "LRU was called!" << endl;
        }
    }
    else if (strcmp(argv[3],"vms") == 0) {
        VMS(traceArray, rwArray, frames, p);
    }
    else {
        cout << "wrong parameter. try again" << endl;
        exit(1);
    }
    return 0;
}