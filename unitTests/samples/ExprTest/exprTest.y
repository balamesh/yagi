fluent f[{"a","b","c"}];
f = {<"a">};

fluent g[{"a","b"}][{"x","y"}];
g = {<"a","x">, <"b","y">};

fluent ass [{"p1","p2","p3"}][{"r1","r2","r3"}];
ass = {<"p2","r2">, <"p3","r3">, <"p1","r2">};

fluent f1[{"1","2","3"}];
f1 = {<"1">, <"2">};

fluent f2[{"1","2","3"}];
fluent f3[{"1","2","3"}];
f3 = {<"2">};	

action valExprTest($x)
signal:
  "the value of $x is " + $x + "!";
end action

valExprTest("42");

f2 = f + f;
f3 = f1 - f1;
g = {<"b","x">} + {<"a","y">};
f = f + {<"b">};

//associativity
ass = ass - {<"p2","r2">, <"p3","r3">} - {<"p3","r3">}; //x = a - b - c <=> x = (a - b) - c
