fluent f[{"a","b","c","d","e","f","g","h","i","j"}];

action testActionFormula1()
precondition:
  not({<"a">, <"b">} - {<"a">} <= {<"b">} + {<"a">} - {<"a">});
effect:
  f += {<"a">};
end action

action testActionFormula2()
precondition:
  not({<"a">} + {<"b">} != {<"b">} + {<"a">});
effect:
  f += {<"b">};
end action

action testActionFormula3()
precondition:
  not("a" != "b");
effect:
  f += {<"c">};
end action

action testActionFormula4()
precondition:
  not("b" == "b");
effect:
  f += {<"d">};
end action

action testActionFormula5()
precondition:
  not("a" < "b");
effect:
  f += {<"e">};
end action

action testActionFormula6()
precondition:
  not("a" > "a");
effect:
  f += {<"f">};
end action

action testActionFormula7()
precondition:
  not("a" == "b");
effect:
  f += {<"g">};
end action

action testActionFormula8()
precondition:
  not(true);
effect:
  f += {<"h">};
end action

action testActionFormula9()
precondition:
  not(false);
effect:
  f += {<"i">};
end action

action testActionFormula10()
precondition:
  not({<"a">, <"b">} == {<"a">});
effect:
  f += {<"j">};
end action

testActionFormula1();
testActionFormula2();
testActionFormula3();
testActionFormula4();
testActionFormula5();
testActionFormula6();
testActionFormula7();
testActionFormula8();
testActionFormula9();
testActionFormula10();