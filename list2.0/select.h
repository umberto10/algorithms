#pragma once
#include <iostream>
#include <algorithm>
#include "values.h"

template<typename tab, typename func>
void select_sort(tab &res, func f) {
  for (size_t i = 0; i < res.size(); i++) { //sort loop
	int tmp = res[i];
	int cnt = i;
	for (size_t j=i; j < res.size(); j++) { //find min/max
	  if (verbose)
		std::cerr << "\033[31mcompareing: " << res[i] << " with " << res[cnt] << "\033[0m" << std::endl;
	  compares++;
	  if (f(res[j], tmp)) {
		tmp = res[j];
		cnt = j;
	  }
	}
	if (verbose)
	  std::cerr << "\033[31mswaping: " << res[i] << " with " << res[cnt] << "\033[0m" << std::endl; 

	std::swap(res[i], res[cnt]); //put min/max elem to next idx
	swaps++;
  }
}
