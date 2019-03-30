#include <iostream>
#include <getopt.h>
#include <vector>
#include <functional>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <chrono>
#include <unistd.h>
#include <cstdlib>
#include "insert.h"
#include "select.h"
#include "heap.h"
#include "quick.h"
#include "mquick.h"
#include "values.h"

void process(int argc, char** argv) {
  char* type;
  int desc = false;
  int asc = false;
  int len, data_only = 0;
  int k_times;
  char* doc;
  

  struct timespec before, after;
  
  const char* short_opts = "t:d:a:s:m:h:k";

  const option long_opts[] = {
							  {"type", required_argument, nullptr, 't'},
							  {"desc", no_argument, &desc, 1},
							  {"asc", no_argument, &asc, 1},
							  {"verbose", no_argument, &verbose, 1},
							  {"verbose_d", no_argument, &verbose_d, 1},
							  {"stat", required_argument, nullptr, 's'},
							  {"k", required_argument, nullptr, 'k'},
							  {"help", no_argument, nullptr, 'h'},
							  {nullptr, no_argument, nullptr, 0}
  };
  
  for (;;) {
	const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

	if (-1 == opt)
	  break;

	switch(opt) {
	case 't':
	  //std::cout << "type" << optarg << std::endl;
	  type = optarg;
	  break;
	case 's':
	  //std::cout << "stat" << optarg  << std::endl;
	  data_only = 1;
	  doc = optarg;
	  break;
	case 'h':
	  std::cout << "help!" << std::endl;
	  std::cout << "--type select|insert|quick|mquick|heap" << std::endl;
	  std::cout << "--asc|desc" << std::endl;
	  std::cout << "--stat _|file_name" << std::endl;
	  return;
	  break;
	case 'k' :
	  k_times = std::atoi(optarg);
	}
  }
  
  if (!data_only) {
	
	std::cout << "Length: ";
	std::cin >> len;

	std::vector<int> res;
	/*
	  int tmp;
	  for (int i = 0; i < len; i++) {
	  std::cin >> tmp;
	  res.push_back(tmp);
	  }
	  1	*/
	
	std::srand (std::time(nullptr));
	
    for (int i = 0; i < len; i++) {
	  res.emplace_back((rand()+1)%20000);
	}

	/* DEBUG */
	/*
	  std::cout << "before sort: ";
	  for(auto&& j : res)
	  std::cout << j << ' ';

	  std::cout << std::endl;
	*/
  
	switch(type[0]) {
	case 's':
	  clock_gettime(CLOCK_MONOTONIC, &before); 
	  asc ? select_sort<>(res, std::function<bool(int,int)>(std::less<>())) : select_sort<>(res, std::function<bool(int,int)>(std::greater<>()));
	  clock_gettime(CLOCK_MONOTONIC, &after);

	  std::cout << "Select sort with \033[35m" << compares << "\033[0m compares with: " << swaps << " swapas in:" << std::endl;
	  std::cout << "sec: \033[32m"  << after.tv_sec - before.tv_sec << "\033[0m nano_sec: \033[33m"<< after.tv_nsec - before.tv_nsec << "\033[0m" << std::endl;
	  break;
	case 'i':
	  clock_gettime(CLOCK_MONOTONIC, &before);
	  asc ? insert_sort<>(res, 0, res.size(), std::function<bool(int,int)>(std::greater<>())) : insert_sort<>(res, 0, res.size(), std::function<bool(int,int)>(std::less<>()));
	  clock_gettime(CLOCK_MONOTONIC, &after);

	  std::cout << "Insert sort with \033[35m" << compares << "\033[0m compares with: " << swaps << " swaps in:" << std::endl;
	  std::cout << "sec: \033[32m"  << after.tv_sec - before.tv_sec << "\033[0m nano_sec: \033[33m"<< after.tv_nsec - before.tv_nsec << "\033[0m" << std::endl;
	  break;
	case 'q':
	  clock_gettime(CLOCK_MONOTONIC, &before);
   	  asc ? QuickSort<>(res, 0, len-1, std::function<bool(int,int)>(std::less<>())) : QuickSort<>(res, 0, len-1, std::function<bool(int,int)>(std::greater<>()));
	  clock_gettime(CLOCK_MONOTONIC, &after);

	  std::cout << "Quick sort with \033[35m" << compares << "\033[0m compares with: " << swaps << " swaps in:" << std::endl;
	  std::cout << "sec: \033[32m"  << after.tv_sec - before.tv_sec << "\033[0m nano_sec: \033[33m"<< after.tv_nsec - before.tv_nsec << "\033[0m" << std::endl;
	  break;
	case 'h':
	  clock_gettime(CLOCK_MONOTONIC, &before);
	  asc ?  heap_sort<>(res, res.size(), std::function<bool(int,int)>(std::greater<>())) :heap_sort<>(res, len, std::function<bool(int,int)>(std::less<>()));
	  clock_gettime(CLOCK_MONOTONIC, &after);

	  std::cout << "Heap sort with \033[35m" << compares << "\033[0m compares with: " << swaps << " swaps in:" << std::endl;
	  std::cout << "sec: \033[32m"  << after.tv_sec - before.tv_sec << "\033[0m nano_sec: \033[33m"<< after.tv_nsec - before.tv_nsec << "\033[0m" << std::endl;
	  break;
	case 'm':
	  clock_gettime(CLOCK_MONOTONIC, &before);
	  asc ? mQuickSort<>(res, 0, len-1, std::function<bool(int,int)>(std::greater<>())) : mQuickSort<>(res, 0, len-1, std::function<bool(int,int)>(std::less<>()));
	  clock_gettime(CLOCK_MONOTONIC, &after);
	  
	  std::cout << "mQuick sort with \033[35m" << compares << "\033[0m compares with: " << swaps << " swaps in:" << std::endl;
	  std::cout << "sec: \033[32m"  << after.tv_sec - before.tv_sec << "\033[0m nano_sec: \033[33m"<< after.tv_nsec - before.tv_nsec << "\033[0m" << std::endl;	 
	  break;
	}
  
	//std::cout << std::endl;
	// DEBUG
	/*
	  std::cout << "afer sort: ";
	  for(auto&& j : res)
	  std::cout << j << ' ';
	*/
  } else {
	if (doc[0] == '_') {
	  std::ofstream fs ("select.txt");
	  std::ofstream fi ("insert.txt");
	  std::ofstream fh ("heap.txt");
	  std::ofstream fq ("quick.txt");
	  std::ofstream fm ("mquick.txt");
	  std::cout << "all" << std::endl;
	  std::vector<int> i, s, q, m, h;
	  std::uintmax_t i_com, s_com, q_com, m_com, h_com;
	  std::uintmax_t i_sw, s_sw, q_sw, m_sw, h_sw;
	  long double i_t, s_t, q_t, m_t, h_t;
	  std::srand(std::time(nullptr));
	  
	  auto before = std::chrono::steady_clock::now();	  
	  for (int n = 100; n <= 10000; n += 100) {
		i_com = 0; s_com = 0; q_com = 0; m_com = 0; h_com = 0;
		i_sw = 0; s_sw = 0; q_sw = 0; m_sw = 0; h_sw = 0;
		i_t = 0; s_t = 0; q_t = 0; m_t = 0; h_t = 0;
		
		for (int k = 1; k <= k_times; k++) {
		  i.clear();
		  s.clear();
		  q.clear();
		  m.clear();
		  h.clear();     
		  
		  std::srand(std::time(nullptr));
		  for (int j = 0; j < n; j++) {
			int tmp = std::rand()+1 % 2*n;
			i.emplace_back(tmp);
			s.emplace_back(tmp);
			q.emplace_back(tmp);
			m.emplace_back(tmp);
			h.emplace_back(tmp);
		  }
		  		  
		  ::compares = 0;
		  ::swaps = 0;
		  auto beforeS = std::chrono::steady_clock::now();
		  select_sort<>(s, std::function<bool(int,int)>(std::less<>()));
		  auto afterS = std::chrono::steady_clock::now();

		  if (::verbose_d)
			std::cout << "select done! k: " << k << " n: " << n << " in : \033[32m"<< std::chrono::duration_cast<std::chrono::milliseconds>(afterS-beforeS).count() << " swaps: " << ::swaps << " compares: " << ::compares << "\033[0m" << std::endl;
		  s_com += ::compares;
		  s_sw += ::swaps;
		  s_t += std::chrono::duration_cast<std::chrono::milliseconds>(afterS-beforeS).count();
		  

		  ::compares = 0;
		  ::swaps = 0;
		  beforeS = std::chrono::steady_clock::now();
		  insert_sort<>(i, 0,i.size(), std::function<bool(int,int)>(std::greater<>()));		 
		  afterS = std::chrono::steady_clock::now();

		  if (::verbose_d)
			std::cout << "insert done! k: " << k << " n: " << n << " in : \033[32m" << std::chrono::duration_cast<std::chrono::milliseconds>(afterS-beforeS).count() << " swaps: " << ::swaps << " compares: " << ::compares << "\033[0m" << std::endl;
		  i_com += ::compares;
		  i_sw += ::swaps;
		  i_t += std::chrono::duration_cast<std::chrono::milliseconds>(afterS-beforeS).count();

		  ::compares = 0;
		  ::swaps = 0;
		  beforeS = std::chrono::steady_clock::now();
		  heap_sort<>(h, h.size(), std::function<bool(int,int)>(std::greater<>()));
		  afterS = std::chrono::steady_clock::now();
		  
		  if (::verbose)
			std::cout << "heap done! k: " << k << " n: " << n << " in : \033[32m"<< std::chrono::duration_cast<std::chrono::milliseconds>(afterS-beforeS).count() << " swaps: " << ::swaps << " compares: " << ::compares << "\033[0m" << std::endl;
		  h_com += ::compares;
		  h_sw += ::swaps;
		  h_t += std::chrono::duration_cast<std::chrono::milliseconds>(afterS-beforeS).count();
		  
		  ::compares = 0;
		  ::swaps = 0;
		  beforeS = std::chrono::steady_clock::now();
		  QuickSort<>(q, 0, q.size()-1, std::function<bool(int,int)>(std::less<>()));
		  afterS = std::chrono::steady_clock::now();

		  if (::verbose_d)
			std::cout << "quick done! k: " << k << " n: " << n << " in : \033[32m" << std::chrono::duration_cast<std::chrono::milliseconds>(afterS-beforeS).count() << " swaps: " << ::swaps << " compares: " << ::compares << "\033[0m" << std::endl;
		  q_com += ::compares;
		  q_sw += ::swaps;
		  q_t += std::chrono::duration_cast<std::chrono::milliseconds>(afterS-beforeS).count();																		    
		  ::compares = 0;
		  ::swaps = 0;
		  beforeS = std::chrono::steady_clock::now();
		  mQuickSort<>(m, 0, m.size()-1, std::function<bool(int,int)>(std::greater<>()));		  
		  afterS = std::chrono::steady_clock::now();
		  if (::verbose_d)
			std::cout << "mquick done! k: " << k << " n: " << n << " in : \033[32m"<< std::chrono::duration_cast<std::chrono::milliseconds>(afterS-beforeS).count() << " swaps: " << ::swaps << " compares: " << ::compares << "\033[0m" <<  std::endl;
		  m_com += ::compares;
		  m_sw += ::swaps;
		  m_t += std::chrono::duration_cast<std::chrono::milliseconds>(afterS-beforeS).count();
		  
		}
		fs << k_times << " " << n << " " << s_com/k_times << " " << s_sw/k_times << " " << s_t/k_times << std::endl;
		fi << k_times << " " << n << " " << i_com/k_times << " " << i_sw/k_times << " " << i_t/k_times << std::endl;
		fh << k_times << " " << n << " " << h_com/k_times << " " << h_sw/k_times << " " << h_t/k_times << std::endl;
		fq << k_times << " " << n << " " << q_com/k_times << " " << q_sw/k_times << " " << q_t/k_times << std::endl;
		fm << k_times << " " << n << " " << m_com/k_times << " " << m_sw/k_times << " " << m_t/k_times << std::endl;
	  }
	  auto after = std::chrono::steady_clock::now();
	  std::cout << "all sorts with \033[35m in: " << "sec: \033[32m"  << std::chrono::duration_cast<std::chrono::seconds>(after - before).count() << "\033[0m" << std::endl;
	  fs.close();
	  fi.close();
	  fh.close();
	  fq.close();
	  fm.close();
	  
	} else {
	  std::cout << "one : " << doc << std::endl;
	  std::ofstream f (doc);
	}
	
  }
}

int main(int argc, char** argv) {
  process(argc, argv);
  return EXIT_SUCCESS;
}
