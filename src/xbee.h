#ifndef XBEE_CPP
#define XBEE_CPP
#include <string>

extern char xbeechar;

void xbeesetup();
void xbeewriteloop(std::string data);
char xbeereadloop();
void serialToXbeeLoop();

#endif
