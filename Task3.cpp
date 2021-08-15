#include <iostream>
#include<string>
#include <thread>
#include "Summary.h"
#include <filesystem>
#include <vector>
#include <chrono> 


std::string get_extension(std::string path);

void ParseFiles(const std::filesystem::path& path, std::vector<std::string>& filevec)
{
	if (!exists(path)) std::cout << "Bad!";
	std::filesystem::directory_iterator end_iter;

	for (std::filesystem::directory_iterator iter(path); iter != end_iter; ++iter)
	{

		if (is_directory(iter->status()))
		{
			ParseFiles(iter->path(), filevec);
		}
		else
		{
			std::string extension = get_extension(iter->path().generic_string());
			if (extension == "h" || extension == "hpp" || extension == "c" || extension == "cpp")
				filevec.push_back(iter->path().string());

		}
	}
}

std::string get_extension(std::string path)
{
	size_t pos = path.rfind('.');
	return path.substr(pos + 1);
}


int main()
{
	static std::vector<std::string> filevec;
	std::vector<std::string>::iterator iter = filevec.begin();
	std::filesystem::path path= "C:\\Users\\Artem\\ClionProjects\\OOP";
	std::mutex mtx;
	clock_t start = clock();
	std::ofstream fout;
	
	fout.open("C:\\Users\\Artem\\VSProjects\\SoftServe\\Task3\\result.txt");
	ParseFiles(path, filevec);
	
	Summary s;
	while (!filevec.empty())
	{
		std::thread t1([&]() {
		mtx.lock();
		s.MakeSummary(filevec.back());
		filevec.pop_back();
		mtx.unlock();
		});
	
		std::thread t2([&]() {
			mtx.lock();
			s.MakeSummary(filevec.back());
			filevec.pop_back();
			mtx.unlock();
		});

		t1.join();
		t2.join();
	}

	
	
	std::cout <<"\n\tScanning folder "<<path << s;
	fout << "\n\tScanning folder " << path << s;
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	std::cout << "\n The time: " << seconds << std::endl;
	fout << "\n The time: " << seconds << std::endl;
	return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
