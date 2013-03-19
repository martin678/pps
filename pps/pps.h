#ifndef PPS_H_
#define PPS_H_

#include <ppsAttr.h>

#include <string>
#include <deque>
using namespace std;


class PPSPublisher
{
	public:
		PPSPublisher();
		PPSPublisher(string name);
		~PPSPublisher();

		PPSAttr addAttr(string name);
		void updateAttr(string name, string value);
	
	private:
		string _name;
		string _path;
//		deque<PPSAttr>	_attrs;
};

#endif


