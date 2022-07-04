#include <iostream>
#include "cgi.hpp"

int main() {
	if (cgi.isset("post","submit")) {
		cgi.put << "name: " << cgi.value("post", "name").String() << "";
		cgi.put << "number: " << cgi.value("post", "number").LongLong() << "";
	}
	
	cgi.put << "<!DOCTYPE html>";
	cgi.put << "<html lang=\"en\">";
	cgi.put << "<head>";
	cgi.put << "<meta charset=\"utf-8\">";
	cgi.put << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
	cgi.put << "<title>CGI From handling</title>";
	cgi.put << "</head>";
	cgi.put << "<body>";
	cgi.put << "<h4>My CGI Form</h4>";
	cgi.put << "<form action=\"\" method=\"POST\">";
	cgi.put << "<input type=\"text\" name=\"name\" placeholder=\"Enter name\" />";
	cgi.put << "<input type=\"text\" name=\"number\" placeholder=\"Enter number\" />";
	cgi.put << "<input type=\"submit\" name=\"submit\" value=\"Submit\"/>";
	cgi.put << "</form>";
	cgi.put << "</body>";
	cgi.put << "</html>";
	return 0;
}