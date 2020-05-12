toy(doll).
toy(train).
plays(ann,train).
likes(ann, X) :- toy(X), plays(ann, X). 
likes(john, Y) :- likes(ann, Y).