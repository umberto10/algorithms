#pragma once
#include <algorithm>
#include <iostream>
#include "values.h"

template<typename tab, typename func>
void QuickSort(tab &res, int left, int right, func f) {
  int i = left;
  int j = right;
  int x = res[(left + right) / 2];
    
  do {
	::compares++;
	if (::verbose)
	  std::cerr << "\033[31mcompareing: " << res[i] << " with " << x << "\033[0m" << std::endl;
	while (f(res[i],x)) {
	  i++;
	  ::compares++;
	}

	::compares++;
	if (::verbose)
	  std::cerr << "\033[31mcompareing: " << res[j] << " with " << x << "\033[0m" << std::endl;
	while (!f(res[j], x) && res[j] != x) {
	  j--;
	  ::compares++;
	}
  
	if (i <= j) {
	  ::swaps++;
	  if (::verbose)
		std::cerr << "\033[31mswapig: " << res[i] << " with " << res[j] << "\033[0m" << std::endl;
	  std::swap(res[i], res[j]);
	  i++;
	  j--;
	}
  } while(i <= j);
 
  if(left < j)
	QuickSort(res, left, j, f);
  
  if(right > i)
	QuickSort(res, i, right, f);
}

