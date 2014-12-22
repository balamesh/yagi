#!/bin/sh

numberOfFloors=100
numberOfOn=100

numberOfRuns=10

while [ $numberOfRuns -gt 0 ]
do
  echo \numberOfRuns = $numberOfRuns

  echo "Generating random initial situation..."
  ./a.out $numberOfFloors $numberOfOn fluents $5
  
  echo "Running elevator 'no planning'"
  ./run_test.sh elevatorNoPlanning.y YAGIperfNoPlanning.txt #elevator.pl GologperfNoPlanning.txt

  echo "Running elevator 'no planning, conditional'"
  ./run_test.sh elevatorNoPlanningConditional.y YAGIperfNoPlanningCond.txt #elevatorConditional.pl GologperfNoPlanningCond.txt

  echo "Running elevator 'full planning'"
  ./run_test.sh elevatorPlanning.y YAGIperfPlanning.txt elevator.pl GologperfPlanning.txt

  echo "Running elevator 'full planning, conditional'"
  ./run_test.sh elevatorPlanningConditional.y YAGIperfPlanningCond.txt elevatorConditional.pl GologperfPlanningCond.txt

  numberOfRuns=$(( $numberOfRuns -1 ))
done