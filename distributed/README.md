CSC569Project3
==============

This is the project 3 for CSC 569 Distributed Computing. It is to write a distributed vector add with MPI and CUDA.

To Compile:
   make

To Run on 4 Nodes:
   time mpirun -mca btl_tcp_if_include eth0 -n 4 --host 302x20,302x21,302x22,302x24 ./VectorAdd /home/clupo/vectoradd/400mil_binary.a /home/clupo/vectoradd/400mil_binary.b

To Run on 8 Nodes:
   time mpirun -mca btl_tcp_if_include eth0 -n 8 --host 302x20,302x21,302x22,302x24,302x25,302x26,302x27,302x28 ./VectorAdd /home/clupo/vectoradd/400mil_binary.a /home/clupo/vectoradd/400mil_binary.b
   
To Run on 16 Nodes:
   time mpirun -mca btl_tcp_if_include eth0 -n 16 --host 302x20,302x21,302x22,302x24,302x25,302x26,302x27,302x28,302x19,302x18,302x17,302x16,302x15,302x14,302x11,302x12 ./VectorAdd /home/clupo/vectoradd/400mil_binary.a /home/clupo/vectoradd/400mil_binary.b

Notes:
   - I developed my code starting from the CUDA MPI example and am currently 
     using a modified version of their Makefile
   - My Program will not run on clusters smaller than 4 nodes
   - On the first run of the program for any set of the nodes (ie 4, 8, 16) 
     would take anywhere from 1 minute to 4 minutes
      - I believe this is because of caching or mounting issues 
