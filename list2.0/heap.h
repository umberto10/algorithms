#pragma once
#include <algorithm>
#include <iostream>
#include "values.h"

template<typename tab, typename func>
void heapify(tab &res, int h_size, int i, func f);
 
template<typename tab, typename func> 
void heap_sort(tab &res, int h_size, func f) { 

  for (int i = h_size/2-1; i >= 0; i--) 
	heapify(res, h_size, i, f); 
  
  for (int i = h_size-1; i >= 0; i--) {
	if (::verbose)
	  std::cerr << "\033[31mswaping: " << res[0] << " with " << res[i] << "\033[0m" << std::endl;
	::swaps++;
	std::swap(res[0], res[i]); 
	heapify(res, i, 0, f); 
  } 
}

template<typename tab, typename func>
void heapify(tab &res, int h_size, int root, func f) { 
  int largest = root; 
  int left = 2*root + 1; 
  int right = 2*root + 2; 

  ::compares++;
  if (::verbose)
	std::cerr << "\033[31mcompareing: " << res[left] << " with " << res[largest] << "\033[0m" << std::endl;
  if (left < h_size && f(res[left],res[largest])) 
	largest = left; 

  ::compares++;
  if (::verbose)
	std::cerr << "\033[31mcompareing: " << res[right] << " with " << res[largest] << "\033[0m" << std::endl;
  if (right < h_size && f(res[right],res[largest])) 
	largest = right;
  
  ::compares++;
	  if (::verbose)
	  std::cerr << "\033[31mcompareing: " << res[largest] << " with " << res[root] << "\033[0m" << std::endl;
  if (largest != root) {
	if (::verbose)
	  std::cerr << "\033[31mswaping: " << res[root] << " with " << res[largest] << "\033[0m" << std::endl;
	::swaps++;
	std::swap(res[root], res[largest]); 
  
	heapify(res, h_size, largest, f); 
  } 
}
