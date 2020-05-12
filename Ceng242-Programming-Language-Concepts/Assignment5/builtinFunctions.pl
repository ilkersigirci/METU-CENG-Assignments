?- sort(0,@<,[4,4,1,5,3],SORTED).
SORTED = [1, 3, 4, 5].

?- delete([1,3,3,5,6],3,RESULT).
RESULT = [1, 5, 6].

?- select(4,[1,4,2,4],RESULT).
RESULT = [1, 2, 4] .

?- append([1,2,5],[2,5,6],RESULT).
RESULT = [1, 2, 5, 2, 5, 6].

?- compare(<,1,2).
true.

?- nth0(1,[1,2,3],RESULT).
RESULT = 2.

?- nth0(1,RESULT,5,[1,2,3]).
RESULT = [1, 5, 2, 3].

?- last([1,2,3],LAST).
LAST = 3.

?- length([1,2,3,4],LENGTH).
LENGTH = 4.

?- reverse([1,2,3],RESULT).
RESULT = [3, 2, 1].

?- max_member(MAX, [1,2,4,3]).
MAX = 4.

?- numlist(1,5,RESULT).
RESULT = [1, 2, 3, 4, 5].

?- is_set([1,2,2]).
false.

?- list_to_set([1,2,2],SET).
SET = [1, 2].

?- intersection([1,2,3],[2,3,4],RESULT).
RESULT = [2, 3].

?- union([1,2,3],[2,3,4],RESULT).
RESULT = [1, 2, 3, 4].

?- subset([2,3], [1,2,3]).
true.
