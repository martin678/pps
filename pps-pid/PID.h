/*
 * PID.h
 *
 *  Created on: 2012-11-10
 *      Author: martin.gagnon
 */

#ifndef PID_H_
#define PID_H_

class PID {
public:
	PID();
	PID(double p, double i, double d);
	virtual ~PID();
	void init();
	void init(double p, double i, double d);
	double process(double currentValue);	// retourne mCommand
	void setSetPoint(double sp) { mSetPoint = sp; }
	void setP(double p) { mP = p; }
	void setI(double i) { mI = i; }
	void setD(double d) { mD = d; }


private:
	double mP;
	double mI;
	double mD;
	double mSetPoint;
	double mCurrentValue;
	double mCommand;
	double mError;
	double mErrorPrev;
	double mErrorCumul;
	double mErrorDeriv;
	int mVerbosity;
};

#endif /* PID_H_ */
