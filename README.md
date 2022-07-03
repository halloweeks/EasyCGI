# EasyCGI
<p>Easy to make your website</p>

<b>Required to cgi.put do not use std::cout or printf</b>
```
cgi.put << "Hello";
```

<b>Write your first</b>

```
#include <iostream>
#include "cgi.hpp"

int main() {
    cgi.put << "<p>Hello World!</p>";
    return 0;
}
```

<h3>Form handling</h3>

<p>index.html</p>

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
  </form>";
</body>
</html>
```

<p>main.cpp compile into main.cgi</p>

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
