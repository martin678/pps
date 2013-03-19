#include <cstdlib>
#include <iostream>

#include <stringUtils.h>

#include "PID.h"
#include <unistd.h>

int gVerbosity;

int main(int argc, char *argv[]) {

	PID	pid;

	// Defaults
//	gPollInterval_ms = 500;
	gVerbosity = 0;

	int opt = 0;
	// Traiter les autres options
	while ((opt = getopt(argc, argv, "p:i:d:f:c:o:vV?")) != -1) {
		switch (opt) {
		case 'p':
			pid.setP(strtod(optarg, NULL));
			break;
		case 'i':
			pid.setI(strtod(optarg, NULL));
			break;
		case 'd':
			pid.setD(strtod(optarg, NULL));
			break;
		case 'f': // TODO: fréquence d'opération
			break;
		case 'c':	// TODO: CurrentValue read path
			break;
		case 'o':	// TODO: Output path (commande)
			break;
		case 'v':
			gVerbosity++;
			break;
		case 'V':
//			cout << "dev-LCR2: v" << version << endl;
			exit(0);
			break;
		case '?':
//			cout << "dev-LCR2 [options]" << endl;
//			cout << "Options:" << endl;
//			cout << "-f: Facteur utilisé par le LCR2 pour représenter les volumes en entiers (1, 10 ou 100) [dynamic]" << endl;
//			cout << "    Utiliser cette option seulement si le facteur ne peut être lu du registre." << endl;
//			cout << "-i: ID du registre" << endl;
//			cout << "    Attribue le nom du resmgr: /dev/Registrei" << endl;
//			cout << "-n: Nom du resmgr" << endl;
//			cout << "    Ecrase le nom attribue par -i" << endl;
//			cout << "-p: Port serie a utiliser" << endl;
//			cout << "-t: Temps entre les polls au registre (500ms)" << endl;
//			cout << "-V: Affiche le numero de version et quitte" << endl;
//			cout << "-?: Affiche ce message" << endl;
			exit(0);
			break;
		}
	}

// TODO: PID.setVerbosity(gVerbosity);


}
