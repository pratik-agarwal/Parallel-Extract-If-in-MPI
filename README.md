# Problem

Your task in this assignment is to implement and benchmark efficient parallel MPI function mpi_extract_if . The function works as follows: 
Given a sequence of some objects of type T , and a predicate that returns true if object satisfies some condition, the function creates sequence Y with a copy of only thes objects in X for which the predicate is true. The order in which elements in Y appear can be arbitrary (as long as all objects that should be copied are copied however, Y should be evenly distributed between all processors. The input sequence has length n * p , and is evenly distributed between p processors (eac processor stores n elements). The type T is so called Plain Old Data (POD), and hence object of type T can be treated as an array of bytes. The input sequence is too large to aggregate it within main memory of a single processor. For example, it is realistic to expect that n=32000000000.


### Instructions:

Arguments of the mpi_extract_if are as follows:

1. T type of the elements in input/output sequence.
2. Pred unary predicate to test if given element of type T should be extracted. 
3. comm MPI communicator of processors participating in the function.
4. in vector storing n objects that are part of the input sequence.
5. out empty vector to store part of the output sequence.

When implementing mpi_extract_if you may assume that all arguments are correct, and there is no need to test for that. Moreover, you can assume tha mpi_extract_if is invoked with a correct communicator containing at least two ranks. Finally, the project backbone provides a simple Makefile . When invoked without arguments, Makefile must produce executable a1 from a1.cpp . 
