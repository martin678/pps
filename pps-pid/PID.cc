/*
 * PID.cc
 *
 *  Created on: 2012-11-10
 *      Author: martin.gagnon
 */

#include "PID.h"

PID::PID() {
	init();
}

PID::PID(double p, double i, double d) {
	init();
	init(p, i, d);
}

PID::~PID() {
}

void PID::init() {
	mP = 0.0;
	mI = 0.0;
	mD = 0.0;
	mSetPoint = 0.0;
	mCurrentValue = 0.0;
	mCommand = 0.0;
	mError = 0.0;
	mErrorPrev = 0.0;
	mErrorCumul = 0.0;
	mErrorDeriv = 0.0;
	mVerbosity = 0;
}

void PID::init(double p, double i, double d) {
	mP = p;
	mI = i;
	mD = d;
}

double PID::process(double cv) {
	// Valeur actuelle reçue en paramètre
	mCurrentValue = cv;

	// Calcule l'erreur
	// TODO: Conseil de FF: limiter l'erreur cumulée
	mErrorPrev = mError;
	mError = mSetPoint - mCurrentValue;
	mErrorCumul += mError;
	mErrorDeriv = mErrorPrev - mError;

	// valider le calcul précédent avec celui-ci, de dev-pid_pos
	//	PID.SumError += PID.Error;
	//	PID.dError = PID.LastError - PID.PrevError;
	//	PID.PrevError = PID.LastError;
	//	PID.LastError = PID.Error;

	// Calculer Sortie
	mCommand = mError * mI + mErrorCumul * mI + mErrorDeriv * mD;

	// Calcul de dev-pid_pos:
//	PID.Sortie = (int) (PID.Error * gPConst // Proportionnel
//			+ PID.SumError * gIConst // Integrale
//			+ PID.dError * gDConst // Derivee
//			+ 2048); // Offset

	// Limite la sortie: le client s'arrangera avec ca
//	PID.Sortie = PID.Sortie < 0 ? 0 : PID.Sortie;
//	PID.Sortie = PID.Sortie > 4095 ? 4095 : PID.Sortie;

	return mCommand;
}
