#include <cstdlib>
#include <iostream>

#include <pps.h>
#include <ppsAttr.h>

int main(int argc, char *argv[]) {

	PPSPublisher pps("pps_object");
	PPSAttr attr = pps.addAttr("attr1");

	// Update en mode direct
	pps.updateAttr("attr1", "value");
	pps.updateAttr("attr1", "value2");

	// En passant par PPSAttr
	attr.update("value3");

	return EXIT_SUCCESS;
}
