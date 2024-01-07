# Project 2 Operating Systems Description
This project evaluate how real applications respond to a variety of page replacement algorithms. We created a memory simulator and evaluate memory performance using provided traces from real applications. Memory traces include: bzip.trace and sixpack.trace. The page replacement algorithms that were apart of this memory simulator include: FIFO, LRU, and Segmented FIFO.
### Names
All coding and few parts of the report by Kamryn Suh
Report by Sophia Hostetler

## How to run the project
Necessary files to compile the program: memsim.cpp fifo.cpp lru.cpp vms.cpp policies.h bzip.trace sixpack.trace
memsim.cpp: main interface of the simulator
fifo.cpp: file that implements first-in first-out replacement policy 
lru.cpp: file that implements least recently used policy 
vms.cpp: file that implements segmented-fifo polciy 
policies.h: file that declares the policies to be used by the simulator

1. Make sure all required files are in correct directory
2. Compile the program using command "make" which creates memsim executable (or you can also try g++ memsim.cpp fifo.cpp lru.cpp vms.cpp -o memsim then follow #3 step)
3. To run the file: "memsim <tracefile> <frames> <lru|fifo|vms> <p> <debug|quiet>"

For reference above:
- policy: fifo, lru or vms 
- percentage: 1-100 
- tracefile: name of the tracefile 
- frames: number of frames to use 
- quiet/debug: quiet will just print the stats while debug will print every event that happens 
 