#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
using namespace std;

bool working = true;

int main(int argc, char** argv) {
	cout << "Starting..." << endl;
	
	string inputs[argc];
	for (int i = 0; i < argc; i++) {
		cout << "Monitoring " << argv[i] << endl;
		inputs[i] = argv[i];
	}


	string dataPoint;
	ifstream tsharkInput(inputs[1].c_str());
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
	else cout << "Cannot open file" << endl;
	return 0;
}


