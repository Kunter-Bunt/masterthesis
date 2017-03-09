#include <iostream> //stdout
#include <fstream>	//file operations
#include <string>
#include <unistd.h>	//sleep
#include <thread>
using namespace std;

bool working = true;

void monitor(string file) {
	string dataPoint;
	ifstream tsharkInput(file);

	if (tsharkInput.is_open()){
		while (working){
			if (getline(tsharkInput, dataPoint)) {
				cout << dataPoint << '\n';
			}
			else {
				sleep(1);
				tsharkInput.clear();
			}
		}
		tsharkInput.close();
	}
	else cout << "Cannot open file " << file << endl;
}

int main(int argc, char** argv) {
	cout << "Starting..." << endl;
	
	//set up workers
	string file[argc-1];
	thread worker[argc-1];
	for (int i = 0; i < argc-1; i++) {
		cout << "Monitoring " << argv[i+1] << endl;
		file[i] = string(argv[i+1]);
		worker[i] = thread(monitor, file[i]);
	}
	
	//Cleaning up
	for (int i = 0; i < argc-1; i++) {
		worker[i].join();
	}
	return 0;
}


