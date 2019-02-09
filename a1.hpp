// File: a1.hpp
// Pratik
// Agarwal
// I AFFIRM THAT WHEN WORKING ON THIS ASSIGNMENT
// I WILL FOLLOW UB STUDENT CODE OF CONDUCT, AND
// I WILL NOT VIOLATE ACADEMIC INTEGRITY RULES

#ifndef A1_HPP
#define A1_HPP

using namespace std;
#include <vector>
#include <mpi.h>
#include<cmath>
#include<bits/stdc++.h>
#include<iostream>
#include<random>
#include<functional>

// IMPLEMENT ME!
template <typename T, typename Pred>
void mpi_extract_if(MPI_Comm comm, const std::vector<T>& in, std::vector<T>& out, Pred pred) {

  vector<T> vtemp;
  int sz=in.size();
  bool flag[sz];
  int i=0;
  int rank,size,ccount = 0;
  MPI_Comm_size(comm, &size);
  //cout<<"processor"<<size<<"\n";
  MPI_Comm_rank(comm, &rank);
  //cout<<"rank"<<rank<<"\n";
  for (int j=0;j<sz;j++)
  {
      if (pred(in[j]))
      {
          flag[i]=true;
          i++;
      }
      else
      {
          flag[i++]=false;
      }
  }
  for (i=0;i<sz;i++)
  {
      if (flag[i])
      {
          vtemp.push_back(in[i]);
      }
  }
  ccount = vtemp.size();
  
  //Generate Random number and save them in a buffer
  int random_num[ccount];
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> distr(0,size-1);
  for(int i=0;i<ccount;i++)
  {
    int tem = distr(rng);
    random_num[i]=tem;
  }

  // Creating a vector of pairs and sorting it 
  vector< pair <T,int> > vect;
  for (int i=0; i<ccount; i++)
  {
    int tem = random_num[i];
    vect.push_back(make_pair(vtemp[i],tem));
  }
  sort (vect.begin(), vect.end(),
  [](const std::pair<T, int>& lhs, const std::pair<T, int>& rhs) { return lhs.second < rhs.second; });
  int countsum[size], allcount[size];
  for(int i=0;i<size;i++)
  {
    //cout<<"Count of Random: "<<i<<count(random_num,random_num+ccount,i);
    countsum[i]=count(random_num,random_num+ccount,i);
    MPI_Allreduce(&countsum[i], &allcount[i], 1, MPI_INT, MPI_SUM,comm);
  }
  out.resize(allcount[rank]);
  int soffset[size];
  int roffset[size];

  //calculate send offset
  soffset[0]=0;
  for(int i=1;i<size;i++)
  {
      soffset[i]=soffset[i-1]+countsum[i-1];
  }

  /*Broadcast to all processors
  for(int i=0; i<size;i++)
  {
    MPI_Bcast(&count[0], 1, MPI_INT, rank, comm)
  }*/

  //Each processor knows which processor would it receive the elements from
  int recbuf[size];
  MPI_Alltoall(&countsum[0], 1, MPI_INT, &recbuf[0], 1, MPI_INT, comm);
 
  //calculate receive offset
  roffset[0]=0;
  for(int i=1;i<size;i++)
  {
      roffset[i]=roffset[i-1]+recbuf[i-1];
  }

  //AlltoallV to make the transfer to every processor
  MPI_Alltoallv(&vtemp[0], &countsum[0], &soffset[0], MPI_INT, &out[0], &recbuf[0], &roffset[0], MPI_INT, comm);

} // mpi_extract_if
#endif // A1_HPP
