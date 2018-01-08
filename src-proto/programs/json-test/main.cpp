
#include <iostream>
#include "irjson.h"

using namespace ircommon::json;

IRJsonObject * createJsonObject(){
	IRJsonObject * o;

	o = new IRJsonObject();

	o->set(std::string("name"), std::make_shared<IRJsonString>("test"));
	o->set(std::string("null"), std::make_shared<IRJsonNull>());
	o->set(std::string("integer"), std::make_shared<IRJsonInteger>(10));
	o->set(std::string("decimal"), std::make_shared<IRJsonDecimal>(10.1));

	std::shared_ptr<IRJsonObject> p2 = std::make_shared<IRJsonObject>();
	o->set(std::string("obj"), p2);

	p2->set(std::string("obj"), std::make_shared<IRJsonString>("str\xE2\x82\xAC\t"));
	o->set(std::string("zbool"), std::make_shared<IRJsonBoolean>(true));

	std::shared_ptr<IRJsonArray> a = std::make_shared<IRJsonArray>();
	a->append(std::make_shared<IRJsonBoolean>(true));
	o->set(std::string("array"), a);

	return o;
}


int main(){
	std::shared_ptr<IRJsonBase> obj;

	obj = std::shared_ptr<IRJsonBase>(createJsonObject());
	std::cout <<  obj->type() << "\n";

	std::string out;
	IRJsonSerializer s(true);
	s.serialize(*obj, out);

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
