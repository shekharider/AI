% Facts
parent(john, mary).
parent(john, tom).
parent(mary, alice).
parent(tom, bob).

% Rules
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).
