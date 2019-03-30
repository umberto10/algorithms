#pragma once
#include <algorithm>
#include <iostream>
#include "values.h"

template<typename tab, typename func>
void insert_sort(tab &res, size_t start, size_t end, func f) {
  int tmp, j; 
  for(size_t i = start+1; i < end; i++) {
	tmp = res[i];
	bool first = true;
	
	if (::verbose)
	  std::cerr << "\033[31mcompareing: " << res[i-1] << " with " << tmp << "\033[0m" << std::endl;
	::compares++;
	for(j = i - 1; j >= 0 && f(res[j],tmp); j--) {
	  if (verbose && !first)
		std::cerr << "\033[31mcompareing: " << res[j] << " with " << tmp << "\033[0m" << std::endl;
	  ::compares++;
	  first = false;
	  res[j+1] = res[j];
	  ::swaps++;
	}
	if (::verbose)
	  std::cerr << "\033[31mswaping: " << res[i] << " with " << tmp << "\033[0m" << std::endl;
	res[j+1] = tmp;
	::swaps++;
  } 
}
