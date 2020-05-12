:- module(hw5, [ catomic_number/2, ion/2, molecule/2]).
:- [catoms].

catomic_number(NAME, CATOMIC_NUMBER) :- catom(NAME,_,_,ARRAY),sum_list(ARRAY,CATOMIC_NUMBER).

ion(NAME, CHARGE) :- catom(NAME,_,_,ARRAY),last(ARRAY,TEMP), (TEMP > 4 -> CHARGE is TEMP-8; CHARGE is TEMP).

doesCompound(NAME1, NAME2) :- ion(NAME1, CHARGE1), ion(NAME2, CHARGE2), 0 is CHARGE1 + CHARGE2.


copyList(L,R) :- helper(L,R).
helper([],[]).
helper([H|T1],[H|T2]) :- helper(T1,T2).


sumCharges([],CHARGELIST) :- sum_list(CHARGELIST,TOTALCHARGE),!,(0 == TOTALCHARGE).
sumCharges([H|T],CHARGELIST) :- ion(H,CHARGE),!, insert(CHARGE,CHARGELIST,FINALCHARGELIST), !,sumCharges(T, FINALCHARGELIST).

sumAtomNum([],CHARGELIST,TOTALNUM) :- sum_list(CHARGELIST,TOTALCHARGE),!, TOTALNUM is TOTALCHARGE.
sumAtomNum([H|T],CHARGELIST,TOTALNUM) :- catomic_number(H,CHARGE),!, insert(CHARGE,CHARGELIST,FINALCHARGELIST), !,sumAtomNum(T, FINALCHARGELIST,TOTALNUM).

compoundNum(NAME1,NAME2,TOTAL) :-   doesCompound(NAME1, NAME2),
                                    catomic_number(NAME1,NUMBER1), catomic_number(NAME2,NUMBER2),
                                    TOTAL is NUMBER1 + NUMBER2.

test(LIST,TOTAL,TEMPLIST,RESULT) :- member(X,LIST), insert(X,TEMPLIST,RES), 
                                sumAtomNum(RES,[],ATOMNUM),(ATOMNUM == TOTAL -> (sumCharges(RES,[]), copyList(RES,RESULT)) ;
                                (ATOMNUM > TOTAL -> false,!;test(LIST,TOTAL,RES,RESULT))).



moleculeHelper(CATOM_LIST,TOTALNUM) :- findall(NAME, catomic_number(NAME, CATOMIC_NUMBER), RESULT),
                                test(RESULT,TOTALNUM,[],CATOM_LIST).

moleculeSort(CATOM_LIST,TOTALNUM) :- moleculeHelper(CATOMS,TOTALNUM), sort(0,@=<,CATOMS,CATOM_LIST).

molecule(CATOM_LIST,TOTALNUM) :- findall(CATOM_LIST2,moleculeSort(CATOM_LIST2,TOTALNUM),RESULT),!, list_to_set(RESULT,TEMP), member(CATOM_LIST,TEMP).


insert(X,R,[X|R]).
insert(X,[A|R],[A|L]) :- insert(X,R,L).
isSubset([],_).
isSubset([H | T], Y) :- member(H, Y), select(H, Y, Z), isSubset(T, Z).
equal(X, Y) :- isSubset(X, Y), isSubset(Y, X), !.