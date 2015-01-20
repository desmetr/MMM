#include "CFG.h"
#include "CNF.h"

#include <iostream>

using namespace std;

int main(int argc,char* argv[]){
	CFG contextFree(argv[1]);
	CNF normalForm(&contextFree);

	cout << contextFree << endl;
	cout << endl << endl << endl;
	normalForm.run();
	cout << endl << endl << endl;
	cout << contextFree << endl;

	return 0;
}
