action testAction()
precondition:
  {<"a">, <"b">} - {<"a">} == {<"b">} + {<"a">} - {<"a">};
effect:
  x = x;
end action