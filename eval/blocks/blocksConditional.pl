:- [golog_swi].

/*  Action Precondition Axioms  */
poss(move(X,Y),S) :- clear(X,S), clear(Y,S), not(X = Y).
poss(moveToTable(X),S) :- clear(X,S), not(ontable(X,S)).

/*  Successor State Axioms  */
clear(X,do(A,S)) :- (A = move(Y,Z) ; A = moveToTable(Y)),on(Y,X,S)
; clear(X,S), not(A = move(Y,X)).

on(X,Y,do(A,S)) :- A = move(X,Y) ;
                   on(X,Y,S), not(A = moveToTable(X)), not(A = move(X,Z)).
ontable(X,do(A,S)) :- A = moveToTable(X) ;
                      ontable(X,S), not(A = move(X,Y))	.

% Primitive control actions
primitive_action(move(N,M)). 
primitive_action(moveToTable(B)). 

proc(doMove, pi(n, pi(y, move(n,y) # moveToTable(n)))).

% Restore suppressed situation arguments.
restoreSitArg(clear(N),S,clear(N,S)).
restoreSitArg(on(N,M),S,on(N,M,S)).
restoreSitArg(ontable(M),S,ontable(M,S)).
       
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% added by Yves Lesperance

show_act_seq(s0).
show_act_seq(do(A,S)):- show_act_seq(S), write(A), nl.

run:- do(control,s0,S), show_act_seq(S).

% definition of executable (legal) situation

executable(s0).
executable(do(A,S)) :- poss(A,S), executable(S).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
:- use_module(library(statistics)).
:-include('fluents.pl').
:- current_prolog_flag(argv, Argv), concat_atom(Argv,' ', SingleArg), open(SingleArg,append,OS),
write(OS,'Running testcase...'),
nl(OS),
statistics(cputime, T0),                            
run,
statistics(cputime, T1),
T is T1-T0,
write(OS,T),nl(OS),close(OS).
:- halt.