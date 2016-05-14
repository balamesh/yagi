/***************************************************************************
 *  llsf2015.y - LLSF2015 game
 *
 *  Created: Fri Feb 20 09:32:21 2015
 *  Copyright  2015  Tim Niemueller [www.niemueller.de]
 *             2016  Nicolas Limpert
 ****************************************************************************/

/* Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
fluent blackboard_connected[{"true", "false"}];
blackboard_connected = {<"false">};

fluent expl_zones[{"Z1","Z2","Z3","Z4","Z5","Z6","Z7","Z8","Z9","Z10","Z11","Z12", "Z13",
                      "Z14", "Z15", "Z16", "Z17", "Z18", "Z19", "Z20", "Z21", "Z22", "Z23", "Z24"}];

fluent current_machine[{"C-BS", "C-DS", "C-RS1", "C-RS2", "C-CS1", "C-CS2",
                 "M-BS", "M-DS", "M-RS1", "M-RS2", "M-CS1", "M-CS2"}];

// Not used - might be useful in order to map certain stations to their respective zones.
// Probably useful for the Production Phase.
fluent machines_in_zones[{"C-BS", "C-DS", "C-RS1", "C-RS2", "C-CS1", "C-CS2",
                          "M-BS", "M-DS", "M-RS1", "M-RS2", "M-CS1", "M-CS2"}]
                        [{"Z1","Z2","Z3","Z4","Z5","Z6","Z7","Z8","Z9","Z10","Z11","Z12", "Z13",
                          "Z14", "Z15", "Z16", "Z17", "Z18", "Z19", "Z20", "Z21", "Z22", "Z23", "Z24"}];

// Mappings of mps tags to names.
// This fluent is used to map tag_ids to their according MPS-name.
// We only want to know the mps-name according to the tag, regardless of output or input side.
// This is gathered from the rulebook available at "http://www.robocup-logistics.org/rules"
fluent tags_of_machines[{"C-BS", "C-DS", "C-RS1", "C-RS2", "C-CS1", "C-CS2",
                          "M-BS", "M-DS", "M-RS1", "M-RS2", "M-CS1", "M-CS2"}]
                       [{"1","17","33","177","65","81","97","113","129","145","161","49","2","18","34","178","66","82","98","114","130","146","162","50"}];

tags_of_machines += {<"C-CS1","1">};
tags_of_machines += {<"C-CS1","2">};
tags_of_machines += {<"C-CS2","17">};
tags_of_machines += {<"C-CS2","18">};
tags_of_machines += {<"C-RS1","33">};
tags_of_machines += {<"C-RS1","34">};
tags_of_machines += {<"C-RS2","177">};
tags_of_machines += {<"C-RS2","178">};
tags_of_machines += {<"C-BS","65">};
tags_of_machines += {<"C-BS","66">};
tags_of_machines += {<"C-DS","81">};
tags_of_machines += {<"C-DS","82">};
tags_of_machines += {<"M-CS1","97">};
tags_of_machines += {<"M-CS1","98">};
tags_of_machines += {<"M-CS2","113">};
tags_of_machines += {<"M-CS2","114">};
tags_of_machines += {<"M-RS1","129">};
tags_of_machines += {<"M-RS1","130">};
tags_of_machines += {<"M-RS2","145">};
tags_of_machines += {<"M-RS2","146">};
tags_of_machines += {<"M-BS","161">};
tags_of_machines += {<"M-BS","162">};
tags_of_machines += {<"M-DS","49">};
tags_of_machines += {<"M-DS","50">};

action blackboard_connect($host, $port)
precondition:
  blackboard_connected == {<"false">};
effect:
  blackboard_connected = {<"true">};
signal:
  "bb-connect " + $host + " " + $port;
end action

action blackboard_open_reading($type, $id)
precondition:
  blackboard_connected == {<"true">};
signal:
  "bb-open READ " + $type + " " + $id;
end action

exogenous-event exploration_zone ($zone)
  expl_zones += {<$zone>};
end exogenous-event

proc init()
  blackboard_connect("localhost", "1921");
  blackboard_open_reading("RobotinoLightInterface", "/machine-signal/best");
  blackboard_open_reading("ZoneInterface", "/explore-zone/info");
end proc

proc main()
  init();
end proc

main();
