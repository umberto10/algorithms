#pragma once
#include <algorithm>
#include <iostream>
#include "insert.h"
#include "values.h"

int medium(int a, int b, int c);

template<typename tab, typename func>
void mQuickSort(tab &res, int left, int right, func f) {
  int i = left;
  int j = right;
  int x; 
  (res.size()%2 == 0) ? (x = medium(res[left], res[right], res[(left + right)/2])) : (x = medium(res[left], res[right], res[(left + right - 1)/2]));
  
    do {
	::compares++;
	if (::verbose)
	  std::cerr << "\033[31mcompareing: " << res[i] << " with " << x << "\033[0m" << std::endl;
	while (!f(res[i],x) && res[i] != x) {
	  i++;
	  ::compares++;
	  if (::verbose)
		std::cerr << "\033[31mcompareing: " << res[i] << " with " << x << "\033[0m" << std::endl;
	}

	if (::verbose)
	  std::cerr << "\033[31mcompareing: " << res[j] << " with " << x << "\033[0m" << std::endl;
	::compares++;
	while (f(res[j], x)) {
	  j--;
	  ::compares++;
	  if (::verbose)
		std::cerr << "\033[31mcompareing: " << res[j] << " with " << x << "\033[0m" << std::endl;
	}
  
	if (i <= j) {
	  ::swaps++;
	  if (::verbose)
		std::cerr << "\033[31mswapping: " << res[i] << " with " << res[j] << "\033[0m" << std::endl;
	  std::swap(res[i], res[j]);
	  i++;
	  j--;
	}
	if (::verbose)
	  std::cerr << "\033[31mcompareing: " << i << " with " << j << "\033[0m" << std::endl;
  } while(i <= j);

  if(left < j) {
	//std::cout << "j - left = " << j - left << std::endl;
	if (j - left <= 16) {
	  insert_sort<>(res, left, j+1, f);
	  //std::cout << "calling insert" <<  std::endl;
	} else {
	  mQuickSort(res, left, j, f);
	}
  }
  
  if(right > i) {
	//std::cout << "right - i = " << right - i << std::endl;
	if (right - i <= 16) {
	  insert_sort<>(res, i, right+1, f);
	  //std::cout << "calling insert" << std::endl;
	} else {
	  mQuickSort(res, i, right, f);
	}
  }
}

int medium(int a, int b, int c) {
  int res[3] = {a, b, c};

  ::compares++;
  for (int i =0; i < 2; i++) {
	::compares++;	
	if (res[i] > res[i+1]) {
	  std::swap(res[i], res[i+1]);
	  ::swaps++;
	}
  }
  if (::verbose)
	std::cout << "\033[31mmed: " << res[1] << "\033[0m"<< std::endl;
  
  return res[1];
}




