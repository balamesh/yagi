fluent g2[{"a","b"}][{"x","y"}];
g2 = {<"a","x">, <"b","y">};

fluent h2[{"a","b"}][{"x","y"}];
fluent flu2[{"i","j", "k"}];

if (true) then
  h2 = {<"a","x">};
end if

if (false) then
  flu2 = {<"i">};
else
  flu2 = {<"j">};
end if