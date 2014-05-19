#include <fstream>
using namespace std;

int main(int argc, char* argv[]){
	ifstream in(argv[1]);
	string line;
	ofstream out("goOutput2");

	if(in){
		while(getline(in, line)){
			out << line << endl;
		}
	}	
}