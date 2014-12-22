#include "CFG.h"
#include "CNF.h"
#include "CYK.h"
#include "Formatter.h"
using namespace std;

int main(int argc,char* argv[]){
	CFG contextFree(argv[1]);
	CNF normalForm(&contextFree);
	normalForm.run();
	cout << contextFree << endl;
	CYK algo(contextFree);
	Formatter _autoFormat("<music><mdiv><score><scoreDef meter.count=\"4\" meter.unit=\"4\" key.sig=\"0\" key.mode=\"major\"><staffGrp><staffDef n=\"1\" xml:id=\"P1\" label=\"Piano\" lines=\"5\" clef.line=\"2\" clef.shape=\"G\"/></staffGrp></scoreDef><section><measure n=\"0\" xml:id=\"0\"><staff n=\"1\"><layer n=\"1\"><note xml:id=\"1\" pname=\"C\" oct=\"4\" dur=\"4\" stem.dir=\"up\"/><note xml:id=\"2\" pname=\"E\" oct=\"4\" dur=\"4\" stem.dir=\"up\"/><note xml:id=\"3\" pname=\"G\" oct=\"4\" dur=\"4\" stem.dir=\"up\"/><note xml:id=\"4\" pname=\"C\" oct=\"5\" dur=\"4\" stem.dir=\"down\"/></layer></staff></measure><measure n=\"1\" xml:id=\"5\" right=\"end\"><staff n=\"1\"><layer n=\"1\"><note xml:id=\"6\" pname=\"G\" oct=\"4\" dur=\"4\" stem.dir=\"up\"/><note xml:id=\"7\" pname=\"E\" oct=\"4\" dur=\"4\" stem.dir=\"up\"/><note xml:id=\"8\" pname=\"C\" oct=\"4\" dur=\"2\" stem.dir=\"up\"/></layer></staff></measure></section></score></mdiv></music>");
	string formatted =_autoFormat.getFormatedVersion();
	std::cout << algo.testString(formatted) << std::endl;
	cout << "succesful run" << endl;


}
