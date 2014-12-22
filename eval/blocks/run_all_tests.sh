#!/bin/sh

numberOfBlocks=10
numberOfStacks=5

numberOfRuns=10

while [ $numberOfRuns -gt 0 ]
do
  echo \numberOfRuns = $numberOfRuns
  
  echo "Generating random initial situation..."
  ./a.out $numberOfBlocks $numberOfStacks fluents
  
  echo "Running blocks 'no planning'"
  ./run_test.sh blocksNoPlanning.y YAGIperfNoPlanning.txt

  echo "Running blocks 'no planning, conditional'"
  ./run_test.sh blocksNoPlanningConditional.y YAGIperfNoPlanningCond.txt

  echo "Running blocks 'full planning'"
  ./run_test.sh blocksPlanning.y YAGIperfPlanning.txt blocks.pl GologperfPlanning.txt

  echo "Running blocks 'full planning, conditional'"
  ./run_test.sh blocksPlanningConditional.y YAGIperfPlanningCond.txt blocksConditional.pl GologperfPlanningCond.txt

  numberOfRuns=$(( $numberOfRuns -1 ))
done