% Author: Eva Ullán
% Date: 2004

/*
  BÚSQUEDA PRIMERO EN PROFUNDIDAD (sin tirar de Prolog)

  No se tira de Prolog para el backtracking, sino que cada vez que se procesa
  un nodo se generan todos los hijos, los cuales se almacenan en los pendientes
  de visitar en forma de ternas (nodo_hijo, nodo_padre, operador).
  Para ello, se utiliza una pila (abiertos) que es la estructura que marca el
  orden de exploración (LIFO).

  Camino/2 termina su ejecución cuando se llega a un estado objetivo y se ha
  encontrado un camino, o bien cuando no quedan nodos pendientes de visitar,
  en cuyo caso la búsqueda habrá fallado.

  El orden de generación de hijos se corresponde con la aplicación de los
  operadores en el orden textual en el que aparecen en la representación del
  problema (comportamiento de Prolog).

*/

% Descomentar para uso en SISCtus Prolog (en SWI-Prolog, no)
 :- use_module(library(lists)).       % permite usar member, length y append

% Predicado principal al que se llama para resolver el problema
%           resuelve(+EstadoInicial)

resuelve(Inicial) :-
                  write('BÚSQUEDA PRIMERO EN PROFUNDIDAD '),
                  write('(control de ciclos: camino actual)'), nl,
                  camino([(Inicial, nil, _)], []).

% Búsqueda de camino:
%          camino(+Pila, +ConjuntoVisitados)

% Termina sin encontrar solución si la pila se ha quedado vacía:
% no quedan nodos que visitar
camino(Abiertos, _) :-
                Abiertos = [], !,    % corte verde
                write('NO SE ENCONTRÓ NINGUNA SOLUCIÓN'), nl.

% Termina si se ha alcanzado un estado objetivo (dependiente del problema)
camino(Abiertos, Cerrados) :-
                Abiertos = [(Estado, Padre, Operador)|_],  % desapila nodo
                objetivo(Estado), !,  % si es estado objetivo
                write('SOLUCIÓN ENCONTRADA'),
                imprimeSolucion((Estado, Padre, Operador), Cerrados, 0), nl,
                write('Nodos expandidos: '), length(Cerrados, L), write(L), nl.

% Si el estado alcanzado no es un estado objetivo, se generan todos los
% sucesores del nodo y se apilan sólo los no expandidos ya ni pendientes de
% visitar, y se prosigue la búsqueda
camino(Abiertos, Cerrados) :-
                Abiertos = [(Estado, Padre, Operador)|Resto_Abiertos],
                % extrae nodo
                obten_hijos(Estado, Padre, Cerrados, Hijos),
                % expande nodo
                append(Hijos, Resto_Abiertos, N_Abiertos),
                % añade sus hijos a los pendientes de visitar (candidatos)
                pon_en_cjto((Estado, Padre, Operador), Cerrados, N_Cerrados),
                % marca estado del nodo como visitado
                camino(N_Abiertos, N_Cerrados).
                % prosigue la iteración


% Generación de todos los hijos de un nodo: expandir nodo
%            obten_hijos(+Estado, +Pila, +ConjuntoVisitados, -Hijos)

obten_hijos(Estado, Padre, Cerrados, Hijos) :-
                    findall(Hijo,
                           movimientos(Estado, Padre, Cerrados, Hijo),
                           Hijos).


% Generación de un hijo no pendiente de ezpandir ni expandido:
%            movimientos(+Estado, +Pila, +ConjuntoVisitados, -NodoHijo)

movimientos(Estado, Padre, Cerrados, (Siguiente, Estado, Operador)) :-
                    movimiento(Estado, Siguiente, _, Operador),
                    % Dependiente del problema: movimiento/4
                    \+(enCaminoActual(Siguiente, Padre, Cerrados)).
                    % Control de ciclos: no en camino actual


% Controla si un estado ha aparecido previamente en el camino actual:
%         enCaminoActual(+Estado, +Antecesor, +ConjuntoVisitados)

enCaminoActual(Estado, Estado, _).
enCaminoActual(Estado, Antecesor, Cerrados) :-
                        member((Antecesor, NAnt, _), Cerrados),
                        enCaminoActual(Estado, NAnt, Cerrados).


% Imprime la solución:
%         imprimeSolucion(+NodoObjetivo, +ConjuntoVisitados, +0)

imprimeSolucion((Estado, nil, _), _, Profundidad) :-
                         !, write(' A PROFUNDIDAD: '), write(Profundidad), nl,
                         write('Estado: '), write(Estado).

imprimeSolucion((Estado, Padre, Operador), Cerrados, Profundidad) :-
                         member((Padre, Abuelo, Op2), Cerrados),
                         P2 is Profundidad + 1,
                         imprimeSolucion((Padre, Abuelo, Op2), Cerrados, P2),
                         tab(3), write('Operador: '), write(Operador), nl,
                         write('Estado: '), write(Estado).

% Añadir a un conjunto (sólo si no está ya):
%        pon_en_cjto(+Elemento, +Conjunto, -NuevoConjunto)

pon_en_cjto(X, S, S) :- member(X, S), !.          % corte rojo
pon_en_cjto(X, S, [X|S]).


