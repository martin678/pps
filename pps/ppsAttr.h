#ifndef PPSATTR_H_
#define PPSATTR_H_

#include <string>
using namespace std;

class PPSAttr
{
	public:
		PPSAttr();
		PPSAttr(string objPath, string name);
		~PPSAttr();
		
		void update(string value);

	private:
		string _name;
		string _value;
		string _objPath;
};

#endif
