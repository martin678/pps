#include <ppsAttr.h>
#include <fileUtils.h>

PPSAttr::PPSAttr() {
	_name = "";
	_value = "";
}

PPSAttr::PPSAttr(string objPath, string name){
	_name = name;
	_objPath = objPath;
	_value = "";
	writeFile(_objPath, _name + "::");
}

PPSAttr::~PPSAttr() {}

void PPSAttr::update(string value){
	writeFile(_objPath, _name + "::" + value);
}
