load('/usr/share/javascript/fulljslint.js');
 
var body = arguments[0];
var result = JSLINT(body);

if (! result) {
  print(JSLINT.report());
}
