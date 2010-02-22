fib(0, 0).
fib(1, 1).
fib(N, F) :-
	N1 is N - 1,
	N2 is N - 2,
	fib(N1, F1),
	fib(N2, F2),
	F is F1 + F2.

f(N, F) :-
	AN is abs(N),
	fib(AN, FP),
	F is FP * (sign(N) ** (N + 1)).

fib_print(N) :-
	write(N),
	write('th Fibonacci number is '), f(N, X), write(X), nl.

main :-
	current_prolog_flag(argv, A), length(A, AL),
	AL =:= 5, last(A, M), catch(atom_number(M, N), _, fail), fib_print(N);
	write('Usage: fibonacci <n>\n').
