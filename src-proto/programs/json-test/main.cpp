
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

	std::shared_ptr<IRJsonObject> p2 = std::make_shared<IRJsonObject>();
	p = p2;
	o.set(std::string("obj"), p);

	std::string tmp = "str\xE2\x82\xAC\t";
	p = std::make_shared<IRJsonString>(tmp);
	p2->set(std::string("obj"), p);

	p = std::make_shared<IRJsonBoolean>(true);
	o.set(std::string("zbool"), p);

	std::string out;
	IRJsonSerializer s(true);
	s.serialize(o, out);

	std::cout << out << "\n";

	out = "/* oi */  \"\\\"\\u20ACFF \\/\" /* rerwerw \n";
	IRJsonTokenizer tokenizer(out);
	IRJsonTokenizer::TokenType token;
	do {
		token = tokenizer.next();
		std::cout <<  IRJsonTokenizer::tokenToName(token) << " " << tokenizer.value() <<"\n";
	} while (token != IRJsonTokenizer::INPUT_END);



	return 0;
}
