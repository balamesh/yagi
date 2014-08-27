fluent actionTest[{"a"}];

action testAction()
precondition:
  true;
effect:
  actionTest = {<"a">};
end action

action testActionWithParams($first, $second)
precondition:
  true;
effect:
  actionTest = {<"a">}; 
end action

action testSettingAction($first, $second) external ($setting1, $setting2)
precondition:
  true;
effect:
  actionTest = {<"a">};
end action