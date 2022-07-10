#include <iostream>
#include "cgi.hpp"

int main() {
	if (cgi.isset("post","submit")) {
		cgi.put << "name: " << cgi.value("post", "name").String() << "\r\n";
		cgi.put << "number: " << cgi.value("post", "number").BigInt() << "\r\n";
	}
	
	cgi.put << "<!DOCTYPE html>\r\n";
	cgi.put << "<html lang=\"en\">\r\n";
	cgi.put << "<head>\r\n";
	cgi.put << "<meta charset=\"UTF-8\">\r\n";
	cgi.put << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\r\n";
	cgi.put << "<title>CGI From handling</title>\r\n";
	cgi.put << "</head>\r\n";
	cgi.put << "<body>\r\n";
	cgi.put << "<h4>POST CGI Form</h4>\r\n";
	cgi.put << "<form action=\"\" method=\"POST\">\r\n";
	cgi.put << "<input type=\"text\" name=\"name\" placeholder=\"Enter name\" />\r\n";
	cgi.put << "<input type=\"text\" name=\"number\" placeholder=\"Enter number\" />\r\n";
	cgi.put << "<input type=\"submit\" name=\"submit\" value=\"Submit\"/>\r\n";
	cgi.put << "</form>\r\n";
	cgi.put << "</body>\r\n";
	cgi.put << "</html>\r\n";
	return 0;
}