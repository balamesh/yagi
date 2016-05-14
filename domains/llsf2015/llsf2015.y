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

fluent skill_status[{"S_INACTIVE", "S_RUNNING", "S_FINAL", "S_FAILED"}];

fluent light_state[{"ON", "OFF", "BLINKING", "UNKNOWN"}]
                  [{"ON", "OFF", "BLINKING", "UNKNOWN"}]
                  [{"ON", "OFF", "BLINKING", "UNKNOWN"}];
light_state = {<"UNKNOWN","UNKNOWN","UNKNOWN">};

fluent light_state_of_machine[{"C-BS", "C-DS", "C-RS1", "C-RS2", "C-CS1", "C-CS2",
                          "M-BS", "M-DS", "M-RS1", "M-RS2", "M-CS1", "M-CS2"}]
                             [{"ON", "OFF", "BLINKING", "UNKNOWN"}]
                             [{"ON", "OFF", "BLINKING", "UNKNOWN"}]
                             [{"ON", "OFF", "BLINKING", "UNKNOWN"}];


// Fluent written by executing the skill "explore_zone"
fluent explore_state[{"UNKNOWN", "MAYBE", "NO", "YES"}]
                    [{"-1", "0", "65","1","17","33","177","66","2","18","34","178","161","97","113","129","145","162","98","114","130","146", "81", "82", "49", "50"}];
explore_state = {<"UNKNOWN","-1">};

// This fact is used to know whether the currently seen tag is on the side which we need for the light signal vision.
// We have to make sure to be on the correct side to watch the particular light side.
// Note that the delivery station actually only has one input side and has to be detected from that side.
fact mps_non_light_sides[{"1", "17", "33", "177", "65", "82", "97", "113", "129", "145", "161", "50"}];
// Simply add all available elements
mps_non_light_sides += {<_>};

// Current game state
fluent state[{"INIT", "WAIT_START", "RUNNING", "PAUSED"}];
state = {<"INIT">};

// Current game phase
fluent phase[{"PRE_GAME", "SETUP", "EXPLORATION", "PRODUCTION", "POST_GAME"}];
phase = {<"PRE_GAME">};

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

action blackboard_read($interface)
precondition:
  true;
signal:
  "bb-read " + $interface;
end action

action skill_status_query() external ($status)
precondition:
  true;
effect:
  skill_status = {<$status>};
signal:
  "bb-get SkillerInterface::Skiller";
end action

action log($level, $msg)
precondition:
  true;
signal:
  "log " + $level + " " + $msg;
end action

action wait($time_ms)
precondition:
  true;
signal:
  "sleep " + $time_ms;
end action

action read_light() external ($red, $yellow, $green)
precondition:
  true;
effect:
  light_state = {<$red, $yellow, $green>};
signal:
  "bb-get RobotinoLightInterface::/machine-signal/best";
end action

action read_explore_zone() external ($search_state, $tag_id)
precondition:
  true;
effect:
  explore_state = {<$search_state, $tag_id>};
signal:
  "bb-get ZoneInterface::/explore-zone/info";
end action

action move_to_output($tag_id) external ($mps_tag, $status)
precondition:
  <$tag_id> in mps_non_light_sides;
effect:
  skill_status = {<$status>};
signal:
  "skill-exec-wait relgoto{x=1.5, ori=math.pi}";
end action

exogenous-event game_state ($state, $phase)
  state = {<$state>};
  phase = {<$phase>};
end exogenous-event

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
