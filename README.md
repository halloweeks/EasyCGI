# EasyCGI
<p>Easy to make your website</p>

<b>Use cgi.put for print content don't use std::cout or printf</b>

```
cgi.put << "Hello";
```

<b>Write your first CGI program</b>
<p>You don't need to write content type 
default automatically add content-type: text/html</p>

```
#include <iostream>
#include "cgi.hpp"

int main() {
    cgi.put << "<p>Hello World!</p>";
    return 0;
}
```

<h3>CGI Form handling</h3>

<p>Make <b>index.html</b></p>

```
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>CGI From handling</title>
</head>
<body>
 <h4>My CGI Form</h4>
  <form action="main.cgi" method="POST">
   <input type="text" name="user" placeholder="Enter username" />
   <input type="text" name="pass" placeholder="Enter password" />
   <input type="submit" name="login" value="Login"/>
  </form>
</body>
</html>
```

<p>Make <b>main.cpp</b> and compile into <b>main.cgi</b></p>

```
#include <iostream>
#include "cgi.hpp"

int main() {
 if (cgi.isset("POST", "login")) {
  if (cgi.value("POST", "user") == "root") {
   if (cgi.value("POST", "pass") == "1234") {
     cgi.put << "<p style=\"color: green;\">Login successful</p>";
   } else {
     cgi.put << "<p style=\"color: red;\">Password incorrect</p>";
   }
  } else {
    cgi.put << "<p style=\"color: red;\">Username incorrect</p>";
  }
 }
 return 0;
}
```
