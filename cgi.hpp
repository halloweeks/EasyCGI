#ifndef HTTP_LIB_MAIN
#define HTTP_LIB_MAIN

#include <vector>
#include <string.h>
#include "utilities/urldecode.hpp"
#include <sstream>
#include "utilities/randstr.hpp"

namespace cpp_cgi {
	class libhttp {
		private:
		std::vector<std::string> headers;
		std::vector<std::string> PostKeys;
		std::vector<std::string> PostValues;
		std::vector<std::string> GetKeys;
		std::vector<std::string> GetValues;
		std::vector<std::string> CookieKeys;
		std::vector<std::string> CookieValues;
		char* REQUEST_METHOD = std::getenv("REQUEST_METHOD");
		char* GET_QUERY_STRING = std::getenv("QUERY_STRING");
		char* CONTENT_TYPE = std::getenv("CONTENT_TYPE");
		char* HTTP_COOKIE = std::getenv("HTTP_COOKIE");
		std::string POST_QUERY_STRING;
		std::string tmp;
		std::string ReturnData;
		std::string COOKIE_KEY, COOKIE_VALUE;
		bool COOKIE_FIND_START = true, COOKIE_FIND_END = false;
		std::string POST_KEY, POST_VALUE;
		bool POST_START = true, POST_END = false;
		std::string GET_KEY, GET_VALUE;
		bool GET_START = true, GET_END = false;
		public:
		std::ostringstream put;
		libhttp();
		~libhttp();
		std::string method();
		bool isset(std::string, std::string);
		libhttp& value(std::string, std::string);
		void header(std::string);
		std::string upper(std::string);
		std::string lower(std::string);
		void SetCookie(std::string, std::string);
		void SetCookie(std::string, int);
		void SetCookie(std::string, long long);
		void SetCookie(std::string, float);
		void SetCookie(std::string, double);
		std::string String();
		int Int();
		long long LongLong();
		bool Bool();
		float Float();
		double Double();
	};
	
	
	libhttp::libhttp() {
		if (REQUEST_METHOD != NULL) {
			if (strcmp(REQUEST_METHOD, "POST") == 0) {
				while (std::cin >> tmp) {
					POST_QUERY_STRING += tmp;
				}
				if (POST_QUERY_STRING!= "") {
					for (int i = 0; i < POST_QUERY_STRING.size() +2; i++) {
						if (POST_START) {
							if (POST_QUERY_STRING[i] == '=')  {
								POST_START = false;
							} else {
								POST_KEY += POST_QUERY_STRING[i];
							}
						} else if (!POST_END) {
							if (POST_QUERY_STRING[i] == '&' || POST_QUERY_STRING[i] == '\0') {
								POST_END = true;
							} else {
								POST_VALUE += POST_QUERY_STRING[i];
							}
							if (POST_END) {
								PostKeys.push_back(urldecode(POST_KEY));
								PostValues.push_back(urldecode(POST_VALUE));
								POST_KEY = "";
								POST_VALUE = "";
								POST_START= true;
								POST_END = false;
							}
						}
					}
				}
			}
		}
	
		if (GET_QUERY_STRING != NULL) {
			for (int i = 0; i < strlen(GET_QUERY_STRING) +2; i++) {
				if (GET_START) {
					if (GET_QUERY_STRING[i] == '=')  {
						GET_START = false;
					} else {
						GET_KEY += GET_QUERY_STRING[i];
					}
				} else if (!GET_END) {
					if (GET_QUERY_STRING[i] == '&' || GET_QUERY_STRING[i] == '\0') {
						GET_END = true;
					} else {
						GET_VALUE += GET_QUERY_STRING[i];
					}
					if (GET_END) {
						GetKeys.push_back(urldecode(GET_KEY));
						GetValues.push_back(urldecode(GET_VALUE));
						GET_KEY = "";
						GET_VALUE = "";
						GET_START = true;
						GET_END = false;
					}
				}
			}
		}
		
		if (HTTP_COOKIE != NULL) {
			for (int i = 0; i < strlen(HTTP_COOKIE) +2; i++) {
				if (COOKIE_FIND_START) {
					if (HTTP_COOKIE[i] == '=')  {
						COOKIE_FIND_START = false;
					} else {
						COOKIE_KEY += HTTP_COOKIE[i];
					}
				} else if (!COOKIE_FIND_END) {
					if (HTTP_COOKIE[i] == ';' || HTTP_COOKIE[i] == '\0') {
						COOKIE_FIND_END = true;
					} else {
						COOKIE_VALUE += HTTP_COOKIE[i];
					}
					if (COOKIE_FIND_END) {
						CookieKeys.push_back(COOKIE_KEY);
						CookieValues.push_back(COOKIE_VALUE);
						COOKIE_KEY = "";
						COOKIE_VALUE = "";
						COOKIE_FIND_START = true;
						COOKIE_FIND_END = false;
					}
				}
			}
		}
		// session.CGI_SESSION_ID = value("cookie", "CGI_SESSION_ID").String();
	}
	
	libhttp::~libhttp() {
		bool content_type = false;
		for (int i = 0; i < headers.size(); i++) {
			if (lower(headers[i].substr(0, 13)) == "content-type:") {
				content_type = true;
			}
			std::cout << headers[i];
		}
		
		if (!content_type) {
			std::cout << "content-type: text/html\r\n";
		}
		
		std::cout << "\r\n" << put.str();
	}
	
	std::string libhttp::method() {
		if (REQUEST_METHOD != NULL) {
			return REQUEST_METHOD;
		}
		return "";
	}
	
	bool libhttp::isset(std::string methods, std::string key) {
		if (upper(methods) == "GET") {
			for (int i = 0; i < GetKeys.size(); i++) {
				if (key == GetKeys[i]) {
					return true;
				}
			}
		} else if (upper(methods) == "POST") {
			for (int i = 0; i < PostKeys.size(); i++) {
				if (key == PostKeys[i]) {
					return true;
				}
			}
		} else if (upper(methods) == "COOKIE") {
			for (int i = 0; i < CookieKeys.size(); i++) {
				if (key == CookieKeys[i]) {
					return true;
				}
			}
		}
		return false;
	}
	
	libhttp& libhttp::value(std::string methods, std::string key) {
		if (upper(methods) == "GET") {
			for (int i = 0; i < this->GetValues.size(); i++) {
				if (key == GetKeys[i]) {
					this->ReturnData = GetValues[i];
					break;
				}
			}
		} else if (upper(methods) == "POST") {
			for (int i = 0; i < this->PostValues.size(); i++) {
				if (key == PostKeys[i]) {
					this->ReturnData = this->PostValues[i];
					break;
					// return PostValues[i];
				}
			}
		} else if (upper(methods) == "COOKIE") {
			for (int i = 0; i < CookieKeys.size(); i++) {
				if (key == CookieKeys[i]) {
					ReturnData = CookieValues[i];
					break;
					// return CookieValues[i];
				}
			}
		}
		return *this;
	}
	
	// headers
	void libhttp::header(std::string data) {
		headers.push_back(data + "\r\n");
	}
	
	// string upper case
	std::string libhttp::upper(std::string str) {
		std::string output;
		for (int i =0; i < str.size(); i++) {
			output += toupper(str[i]);
		}
		return output;
	}
	
	// string lower case
	std::string libhttp::lower(std::string str) {
		std::string output;
		for (int i = 0; i < str.size(); i++) {
			output += tolower(str[i]);
		}
		return output;
	}
	
	// set cookies
	void libhttp::SetCookie(std::string name, std::string value) {
		headers.push_back("set-cookie: " + name + "=" + value + "\r\n");
	}
	
	void libhttp::SetCookie(std::string name, int value) {
		headers.push_back("set-cookie: " + name + "=" + std::to_string(value) + "\r\n");
	}
	
	void libhttp::SetCookie(std::string name, long long value) {
		headers.push_back("set-cookie: " + name + "=" + std::to_string(value) + "\r\n");
	}
	
	void libhttp::SetCookie(std::string name, float value) {
		headers.push_back("set-cookie: " + name + "=" + std::to_string(value) + "\r\n");
	}
	
	void libhttp::SetCookie(std::string name, double value) {
		headers.push_back("set-cookie: " + name + "=" + std::to_string(value) + "\r\n");
	}
	
	
	std::string libhttp::String() {
		return this->ReturnData;
	}
	
	int libhttp::Int() {
		int numbers = 0;
		try {
			numbers = std::stoi(ReturnData);
		} catch (...){}
		return numbers;
	}
	
	long long libhttp::LongLong() {
		long long numbers = 0;
		try {
			numbers = std::stoll(ReturnData);
		} catch (...) {}
		return numbers;
	}
	
	float libhttp::Float() {
		float numbers = 0.0;
		try {
			numbers = std::stof(ReturnData);
		} catch (...) {}
		return numbers;
	}
	
	double libhttp::Double() {
		double numbers = 0.00;
		try {
			numbers = std::stod(ReturnData);
		} catch (...) {}
		return numbers;
	}
	
	bool libhttp::Bool() {
		if (ReturnData == "true" || ReturnData == "1") {
			return true;
		}
		return false;
	}
	
}


cpp_cgi::libhttp cgi;

#endif
