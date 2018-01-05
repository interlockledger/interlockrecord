
#include <iostream>
#include "irjson.h"

using namespace ircommon::json;

int main(){

	IRJsonObject o;

	std::shared_ptr<IRJsonBase> p = std::make_shared<IRJsonString>("test");
	o.set(std::string("name"), p);
	p = std::make_shared<IRJsonNull>();
	o.set(std::string("null"), p);

	p = std::make_shared<IRJsonInteger>(10);
	o.set(std::string("integer"), p);

	p = std::make_shared<IRJsonDecimal>(10.1);
	o.set(std::string("decimal"), p);

	std::string out;
	IRJsonSerializer s(false);
	s.serialize(out, o);

	std::cout << out << "\n";


	return 0;
}
