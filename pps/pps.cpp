#include <pps.h>
#include <fileUtils.h>

PPSPublisher::PPSPublisher(){
	_name = "";
}

PPSPublisher::PPSPublisher(string n){
	PPSPublisher();
	_name = n;
	_path = "/pps/" + _name;
	createFile(_path);
}

PPSPublisher::~PPSPublisher(){
	deleteFile(_path);

}

PPSAttr PPSPublisher::addAttr(string name){
//	writeFile(_path, name + "::");
	PPSAttr attr(_path, name);
	return attr;

}

void PPSPublisher::updateAttr(string name, string value){
	writeFile(_path, name + "::" + value);
}

