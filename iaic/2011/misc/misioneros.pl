/*
 Representación general de problemas según el paradigma del espacio de estados
 El código ejemplo se corresponde con:
*/

%    EL PROBLEMA DE LOS MISIONEROS Y LOS CANÍBALES

/* ESTADOS:
 Fijar la representación de los estados y representarlos en Prolog mediante
 una estructura construida con un functor estado/n,
 cuya aridad dependerá del problema
           estado(...)
*/

%   estado(NumeroMisioneros, NumeroCanibales, Bote)
%   donde NumeroMisioneros es un entero entre 0 y 3
%         NumeroCanibales es un entero entre 0 y 3
%         Bote es entero entre 0 y 1
%   Asumimos que representamos la situación en la orilla de partida (izquierda)
%   y que la información de la orilla de la derecha está implícita.

/*
 ESTADO INICIAL:
 Explicitar cuál es el estado inicial mediante un predicado inicial/1
            inicial(Estado).
*/

inicial(estado(3, 3, 1)).   % Todos en la orilla izquierda

/*
 ESTADO OBJETIVO:
 Explicitar cuáles son los estados objetivos mediante un predicado objetivo/1
            objetivo(Estado).
*/

objetivo(estado(0, 0, 0)).   % Todos en la orilla derecha

/*
 CONDICIÓN DE PELIGROSIDAD (si procede):
 Explicitar qué estados están en situación de peligro mediante un predicado
 peligro/1
            peligro(Estado) :- Condición.
 Esta comprobación a veces aparece en los algoritmos de búsqueda, y otras
 en la especificación de los operadores. Nosotros la especificaremos aparte,
 pero la añadiremos a los operadores para evitar generar estados de peligro.
 Así la búsqueda no llegará a generar el estado de peligro para desecharlo
 después (cosa que haría si incluyésemos la comprobación en el algoritmo de
 búsqueda). De evitar los ciclos, en cambio, sólo puede encargarse la búsqueda.
*/

peligro(estado(NM, NC, _)) :-
                   (NM < NC, NM =\= 0)           % orilla izquierda
                   ;
                   (NM > NC, NM =\= 3).          % orilla derecha

/* OPERADORES:
 Explicitar las transformaciones de estados mediante un predicado
 movimiento/4:
      movimiento(Estado, EstadoSiguiente, CosteOperador, Operador)
                         :- Especificación
*/

movimiento(estado(NM, NC, B), estado(NNM, NC, NB), 1, 'M') :-
                      ((NM > 0, B = 1)    % orilla izda.
                       ;
                       (NM < 3, B = 0)),   % orilla dcha.
                      opuesta(B, NB),
                      ((B = 1) -> (NNM is NM - 1) ; (NNM is NM + 1)),
                      \+(peligro(estado(NNM, NC, NB))).
                      
movimiento(estado(NM, NC, B), estado(NNM, NC, NB), 1, 'MM') :-
                      ((NM > 1, B = 1)    % orilla izda.
                       ;
                       (NM < 2, B = 0)),   % orilla dcha.
                      opuesta(B, NB),
                      ((B = 1) -> (NNM is NM - 2) ; (NNM is NM + 2)),
                      \+(peligro(estado(NNM, NC, NB))).

movimiento(estado(NM, NC, B), estado(NM, NNC, NB), 1, 'C') :-
                      ((NC > 0, B = 1)    % orilla izda.
                       ;
                       (NC < 3, B = 0)),   % orilla dcha.
                      opuesta(B, NB),
                      ((B = 1) -> (NNC is NC - 1) ; (NNC is NC + 1)),
                      \+(peligro(estado(NM, NNC, NB))).
                      
movimiento(estado(NM, NC, B), estado(NM, NNC, NB), 1, 'CC') :-
                      ((NC > 1, B = 1)    % orilla izda.
                       ;
                       (NC < 2, B = 0)),   % orilla dcha.
                      opuesta(B, NB),
                      ((B = 1) -> (NNC is NC - 2) ; (NNC is NC + 2)),
                      \+(peligro(estado(NM, NNC, NB))).

movimiento(estado(NM, NC, B), estado(NNM, NNC, NB), 1, 'MC') :-
                      ((NM > 0, NC > 0, B = 1)    % orilla izda.
                       ;
                       (NM < 3, NC < 3, B = 0)),   % orilla dcha.
                      opuesta(B, NB),
                      ((B = 1) -> (NNM is NM - 1, NNC is NC - 1)
                          ; (NNM is NM + 1, NNC is NC + 1)),
                      \+(peligro(estado(NNM, NNC, NB))).
                      
/*
 PREDICADOS AUXILIARES
 Tantos como se considere adecuado para obtener el código más claro y legible
 posible
*/

% El bote cruza el río

opuesta(0, 1).     % de izda a dcha
opuesta(1, 0).     % de dcha a izda

/*
Los algoritmos de búsqueda tendrán implementado el predicado resuelve/1,
que usaremos para resolver el problema seleccionando distintos tipos
de estrategias de búsqueda.

La búsqueda con profundidad limitada debe usar el predicado resuelve/2
para pasarle el límite.

Si usamos algoritmos de búsqueda informada en los que se usa información
heurística, la representación de los problemas necesita tener implementada
alguna heurística con el predicado heuristica/2:
       heuristica(Estado, Medida)
*/
/*
:- ensure_loaded('../Estrategias/profLimitadaProlog').

test(Limite) :-
             inicial(EstadoInicial),
             resuelve(EstadoInicial, Limite).
*/


:- ensure_loaded('../Estrategias/busquedaProlog').
%:- ensure_loaded('../Estrategias/profundidad').
%:- ensure_loaded('../Estrategias/anchura').

test :-
     inicial(EstadoInicial),
     resuelve(EstadoInicial).

/* PRUEBAS:

?- movimiento(estado(3,3,1), NuevoEstado, 1, Operador).

NuevoEstado = estado(3, 2, 0)
Operador = 'C' ;

NuevoEstado = estado(3, 1, 0)
Operador = 'CC' ;

NuevoEstado = estado(2, 2, 0)
Operador = 'MC' ;

No

?- test.
BÚSQUEDA PRIMERO EN PROFUNDIDAD (tirando de Prolog; control de ciclos en
                                 camino actual)
SOLUCIÓN ENCONTRADA A PROFUNDIDAD: 11
estado(3, 3, 1)
estado(3, 1, 0)
estado(3, 2, 1)
estado(3, 0, 0)
estado(3, 1, 1)
estado(1, 1, 0)
estado(2, 2, 1)
estado(0, 2, 0)
estado(0, 3, 1)
estado(0, 1, 0)
estado(1, 1, 1)
estado(0, 0, 0)
OPERADORES UTILIZADOS:
[CC, C, CC, C, MM, MC, MM, C, CC, M, MC]

Yes

?- test.
BÚSQUEDA PRIMERO EN PROFUNDIDAD (control de ciclos: camino actual)
SOLUCIÓN ENCONTRADA A PROFUNDIDAD: 11
Estado: estado(3, 3, 1)   Operador: CC
Estado: estado(3, 1, 0)   Operador: C
Estado: estado(3, 2, 1)   Operador: CC
Estado: estado(3, 0, 0)   Operador: C
Estado: estado(3, 1, 1)   Operador: MM
Estado: estado(1, 1, 0)   Operador: MC
Estado: estado(2, 2, 1)   Operador: MM
Estado: estado(0, 2, 0)   Operador: C
Estado: estado(0, 3, 1)   Operador: CC
Estado: estado(0, 1, 0)   Operador: M
Estado: estado(1, 1, 1)   Operador: MC
Estado: estado(0, 0, 0)
Nodos expandidos: 13

Yes

?- test.
BÚSQUEDA PRIMERO EN ANCHURA (controla expandidos y pendientes de visitar)
Expande el nodo estado(3, 3, 1)
Expande el nodo estado(3, 2, 0)
Expande el nodo estado(3, 1, 0)
Expande el nodo estado(2, 2, 0)
Expande el nodo estado(3, 2, 1)
Expande el nodo estado(3, 0, 0)
Expande el nodo estado(3, 1, 1)
Expande el nodo estado(1, 1, 0)
Expande el nodo estado(2, 2, 1)
Expande el nodo estado(0, 2, 0)
Expande el nodo estado(0, 3, 1)
Expande el nodo estado(0, 1, 0)
Expande el nodo estado(1, 1, 1)
Expande el nodo estado(0, 2, 1)
SOLUCIÓN ENCONTRADA A PROFUNDIDAD: 11   Nodos expandidos: 14
Estado: estado(3, 3, 1)   Operador: CC
Estado: estado(3, 1, 0)   Operador: C
Estado: estado(3, 2, 1)   Operador: CC
Estado: estado(3, 0, 0)   Operador: C
Estado: estado(3, 1, 1)   Operador: MM
Estado: estado(1, 1, 0)   Operador: MC
Estado: estado(2, 2, 1)   Operador: MM
Estado: estado(0, 2, 0)   Operador: C
Estado: estado(0, 3, 1)   Operador: CC
Estado: estado(0, 1, 0)   Operador: M
Estado: estado(1, 1, 1)   Operador: MC
Estado: estado(0, 0, 0)

Yes
*/


