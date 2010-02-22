
:- dynamic error/0, lazyDebug/0, function/2, rule/4, contLambda/1, contLambdaS/1, lazy/2, (@)/3.
:- op(600,xfx, @).
:- discontiguous (@)/3.
:- multifile (@)/3.
:- multifile function/2.
:- multifile lazy/2.

:- op(100,xfx , or).
:- op(120,xfx , and).
:- op(120,xfx , ?).

:- op(700,xfx, <-).
:- op(900,xfx , :).





expand(File):-
        retractall(rule(_,_,_,_)),
        retractall(function(_,_)),
        retractall(error),
        retractall(lazy(_,_)),
        retractall(@(_,_,_)),
        retractall(contLambda(_)), assert(contLambda(0)),
	retractall(contLambdaS(_)), assert(contLambdaS(0)),


        
        name(File,Str),
        append(Str,".plf",Str1),
        name(File1,Str1),
        open(File1,read,H),


        (getRules(H),!;close(H),fail),        
        close(H),
        (error,!,fail;true),
        !,
        
        append(Str,".pl",Str2),
        name(File2,Str2),
        open(File2,write,H2),

	writeFunsAndLazys(H2),
        translate(H2),
        close(H2),!,
        name(Output,Str), [Output].

expand(_):- nl, write('Parse stop').

memoFunction(F,N):-
        (
          function(F,M),!,
          (
            N==M
          ;
            assert(error), write('ERROR: function '), write(F),
            write(' with different arities '),write(N),write(' and '), write(M), nl
          )
        ;
          assert(function(F,N))
        ).
                


getRules(H) :-
        read_term(H,T,[]), !,
        (
          T== end_of_file,!
        ;
          functor(T,F,Ar),!,
          (
            F == (:-),!,
            (
              Ar==1,!,T=..[:-,G],
	     (
	      G=lazy(Fs),!,Fs=..[N|Args], checkLazyDecl(Args), assertz(lazy(N,Args))
              ;
	      G=include(File),
	      name(File,Str),append(Str,".plf",Str1),name(File1,Str1),open(File1,read,Hp),getRules(Hp)
	      ;
	      assertz(rule(pred,none,none,G))
              )
            ;
              T=..[:-,L,R], functor(L,F1,_),
              (
                F1== (=),!, L=..[_,Head,Body],
                functor(Head,N,ArP), memoFunction(N,ArP),
                assertz(rule(func,Head,Body,R))
              ;
                assertz(rule(pred,L,none,R))
              )
            )
          ;
            F = (=), !, T=..[_,Head,Body],
            functor(Head,N,ArP), memoFunction(N,ArP),
            assertz(rule(func,Head,Body,none))
          ;
            assertz(rule(pred,T,none,none))
          ),
          getRules(H)
        ).


writeFunsAndLazys(H):-
        write(H,':- style_check([-singleton,-discontiguous]).'), nl(H),
	findall((function(F,M),none),function(F,M),L),writeLstClauses(H,L),
        write(H,'function(@,2).'),nl(H),
        write(H,'function(quote,1).'),nl(H),
	findall((lazy(N,Args),none),lazy(N,Args),K),writeLstClauses(H,K).

translate(H):-
        rule(R,Head,Body,Conds),
        (
         R==func,!,
         makeLazyFunc((Head,Body,Conds),(Head1,Body1,Conds1)),
         (lazyDebug,!,current_output(H1),writeClause(H1,(Head1=Body1,Conds1));true),
         flatFunc((Head1,Body1,Conds1),Fs),
         writeLstClauses(H,Fs)
        ;
         makeLazyPred((Head,Conds),(Head1,Conds1)),
         (lazyDebug,!,current_output(H1),writeClause(H1,(Head1,Conds1));true),
         flatPred((Head1,Conds1),Ps),
         writeLstClauses(H,Ps)
        ),
        retract(rule(R,Head,Body,Conds)),
        !,
	translate(H).

translate(H):- 
	findall((F,Ar),function(F,Ar),Ls), genApplys(Ls,Aps), 
	append(Aps,[(@(eval(S),A,R), (!, eval(S,A,R))), (@(E,_,E),none)],Aps1),
	writeLstClauses(H,Aps1).


checkLazyDecl([]).
checkLazyDecl([X|Xs]) :- (var(X);X==on;X=on(shareOff)),!,checkLazyDecl(Xs).
checkLazyDecl([X|_]) :- write('Invalid lazy declaration '), write(X), fail.






makeLazyFunc((Head,Body,Conds),(LHead,LBody,LConds)):-
        makeLazyPatLst([Head],[LHead],LVars,Appls),
        makeLazyExp(Body,LVars,LBody),
        makeLazyGoal(Conds,LVars,Conds1),
        appendTup(Appls,Conds1,LConds).

        
makeLazyPred((Head,Conds),(HeadL,CondsL)):-        
        makeLazyPatLst([Head],[HeadL],LVars,Appls),
        makeLazyGoal(Conds,LVars,Conds1),
        appendTup(Appls,Conds1,CondsL).
        

makeLazyPatLst([],[],[],none).
makeLazyPatLst([C|Rs],[C|Rs1],LVars,Preds):- var(C),!,makeLazyPatLst(Rs,Rs1,LVars,Preds).
makeLazyPatLst([C|Rs],[C1|Rs1],LVars,Preds):- 
        C=..[N|Args],
        makeLazyPatLst(Args,ArgsL,LVars1,Preds1),
        (
          lazy(N,L),!,zipLazys(L,ArgsL,ArgsF,LVars2,Preds2),
          C1=..[N|ArgsF],
          makeLazyPatLst(Rs,Rs1,LVars3,Preds3),
          appendTup(Preds2,Preds1,PredsA), appendTup(PredsA,Preds3,Preds),
          append(LVars1,LVars2,LVarsA), append(LVarsA,LVars3,LVars)
        ;           
          makeLazyPatLst(Rs,Rs1,LVars2,Preds2),
          C1=..[N|ArgsL],append(LVars1,LVars2,LVars),appendTup(Preds1,Preds2,Preds)
        ).
    

zipLazys([],[],[],[],none).
zipLazys([X|Xs],[Y|Ys],[Y|Ys1],LVars,Conds):- var(X),!,zipLazys(Xs,Ys,Ys1,LVars,Conds).
zipLazys([_On|Xs],[Y|Ys],[Y|Ys1],[Y|LVars],Conds):- var(Y),!,zipLazys(Xs,Ys,Ys1,LVars,Conds).
zipLazys([_On|Xs],[Y|Ys],[F|Ys1],LVars,Conds):-
        makeLazyPatLst([Y],[Yl],LVars1,Conds1),
        zipLazys(Xs,Ys,Ys1,LVars2,Conds2),
        append(LVars1,LVars2,LVars),
        appendTup((F@dummy=Yl),Conds1,Conds3),
        appendTup(Conds3,Conds2,Conds).

makeLazyExp(E,LVars,E1):- var(E),!,(memberVar(E,LVars),!,E1=E@dummy;E1=E).
makeLazyExp(ifThen(C,E),LVars,ifThen(C1,fun(_,E1))):- !,
	makeLazyExp(C,LVars,C1),makeLazyExp(E,LVars,E1).
makeLazyExp(ifThenElse(C,E,F),LVars,ifThenElse(C1,fun(_,E1),fun(_,F1))):- !,
	makeLazyExp(C,LVars,C1),makeLazyExp(E,LVars,E1),makeLazyExp(F,LVars,F1).
makeLazyExp(and(X,Y),LVars,A):- !, makeLazyExp(ifThenElse(X,Y,false),LVars,A).
makeLazyExp(or(X,Y),LVars,O):- !, makeLazyExp(ifThenElse(X,true,Y),LVars,O).
makeLazyExp(?(X,Y),LVars,?(fun(_,X1),fun(_,Y1))):- !,
        makeLazyExp(X,LVars,X1),makeLazyExp(Y,LVars,Y1).
makeLazyExp(quote(X),LVars,fun(_,Xl)):- !, makeLazyExp(X,LVars,Xl).


makeLazyExp(E,LVars,LE):-
        E=..[N|Args],
        makeLazyExpLst(Args,LVars,ArgsL),
        (          
          lazy(N,ArgsOn),!,buildLazyCons(ArgsOn,ArgsL,LVars,ArgsLam),LE=..[N|ArgsLam]
        ;
          (function(N,_);N=fun;N=funS),!, buildLazyCall(ArgsL,LVars,ArgsFun),LE=..[N|ArgsFun]
        ;
          LE=..[N|ArgsL]        
        ).

buildLazyCall([],_,[]).
buildLazyCall([X|Xs],LVars,[Y|Ys]):-
        (var(X),memberVar(X,LVars),!,Y=X@dummy;Y=X),buildLazyCall(Xs,LVars,Ys).

makeLazyExpLst([],_,[]).
makeLazyExpLst([X|Xs],LVars,[Y|Ys]):- makeLazyExp(X,LVars,Y),makeLazyExpLst(Xs,LVars,Ys).


buildLazyCons(_,[],_,[]).
buildLazyCons([X|Xs],[Y|Ys],LVars,[Z|Ys1]):-
        var(X),!,
        (memberVar(Y,LVars),!,Z=Y@dummy; Z=Y),
        buildLazyCons(Xs,Ys,LVars,Ys1).

buildLazyCons([On|Xs],[Y|Ys],LVars,[Y1|Ys1]):-        
	(
	  var(Y),
	  (
	    memberVar(Y,LVars), !, Y1=Y
	  ; 
	    (On==on(shareOff),!,Y1=fun(_,Y) ; On==on,Y1=funS(_Ev,_Vl,_Dum,Y))
	  )
	;
	  Y=..[@,F,D],D==dummy,!, Y1=F
	;
	  (
	    functor(Y,N,_),function(N,_),!,
	    (On==on(shareOff),!,Y1=fun(_,Y) ; On==on,Y1=funS(_Ev1,_Vl1,_Dum1,Y))
	  ;
            Y1=Y
	  )
	),
	buildLazyCons(Xs,Ys,LVars,Ys1).
    
makeLazyGoal(X,_,X):- var(X),!.
makeLazyGoal(none,_,none):-!.
makeLazyGoal((C,Cs),LVars,(Cl,Csl)):- !, makeLazyGoal(C,LVars,Cl), makeLazyGoal(Cs,LVars,Csl).
makeLazyGoal(C,LVars,Cl):- makeLazyExp(C,LVars,Cl).





writeLstClauses(_,[]).
writeLstClauses(H,[(L,R)|Cs]):-
	optimizeClause((L,R),(L,R1)), writeClause(H,(L,R1)), writeLstClauses(H,Cs).


writeClause(H,(L,N)):- N==none,!, write_term(H,L,[quoted(true)]), write(H,'.'), nl(H).
writeClause(H,(N,R)):- N==none,!, write(H,':- '), write_term(H,R,[quoted(true)]), write(H,'.'), nl(H).
writeClause(H,(L,R)):- !, 
	write_term(H,L,[quoted(true)]), write(H,':- '),
	write_term(H,R,[quoted(true)]), write(H,'.'), nl(H).

optimizeClause((H,B),(H,B2)) :-
	my_free_variables(H,Vs), optimizeConds(B,B1,Vs,_),
	(B\=B1,!,optimizeClause((H,B1),(H,B2)); B2=B1).


optimizeConds(X,X,Vs,Vs):- var(X),!.
optimizeConds((C1,C2),Cs,Vs,Vs2):- !,
	optimizeConds(C1,C1o,Vs,Vs1), optimizeConds(C2,C2o,Vs1,Vs2), filterNones((C1o,C2o),Cs).
optimizeConds(!,!,_,[]):-!.
optimizeConds(X=T,none,Vs,Vs1):- var(X),my_free_variables(T,Ts),memberVarLst([X|Ts],Vs),X=T,
	append([X|Ts],Vs,Vs1).
optimizeConds(T=X,none,Vs,Vs1):- var(X),my_free_variables(T,Ts),memberVarLst([X|Ts],Vs),X=T,
	append([X|Ts],Vs,Vs1).
optimizeConds(C,C,Vs,Vs1):- my_free_variables(C,L), append(L,Vs,Vs1).

my_free_variables(X,[X]):- var(X),!.
my_free_variables(FunS,Vs):-
	FunS=..[N,_Ev,_H,_Dum|R],name(N,[102, 117, 110, 83|Rs]),digits(Rs),!,
	my_free_variables(R,Vs).
my_free_variables(T,Vs):- T=..[_|Args], my_free_variablesLst(Args,Vs).

my_free_variablesLst([],[]).
my_free_variablesLst([X|Xs],R):-
	my_free_variables(X,Vx), my_free_variablesLst(Xs,Vxs),append(Vx,Vxs,R).


digits([]).
digits([X|Xs]):- X>=48,X=<57,digits(Xs).


filterNones(X,X):-var(X),!.
filterNones((X,Y),R):- !,filterNones(X,X1),filterNones(Y,Y1),
	(X1==none,!,R=Y1;Y1==none,!,R=X1;R=(X1,Y1)).
filterNones(X,X).

memberVarLst([],_).
memberVarLst([X|Xs],Vs):- memberVar(X,Vs), memberVarLst(Xs,Vs).


prevLast([H],[],H).
prevLast([X|R],[X|P],L):- prevLast(R,P,L).

last([H],H).
last([_|R],L):- last(R,L).



genNameLambda(F):- contLambda(N), N1 is N+1,
        retractall(contLambda(_)), assert(contLambda(N1)),
        name(fun,L), name(N1,N1l),append(L,N1l,F1), name(F,F1).

genNameLambdaS(F):- contLambdaS(N), N1 is N+1,
        retractall(contLambdaS(_)), assert(contLambdaS(N1)),
        name(funS,L), name(N1,N1l),append(L,N1l,F1), name(F,F1).


memberVar(X,[Y|L]):- X==Y,!; memberVar(X,L).

unboundVars(X,Bound,U):- var(X),!, (memberVar(X,Bound),!,U=[]; U=[X]).
unboundVars(E,Bound,U):-
        E=..[F|Args],(F==fun;F==funS),!,
        prevLast(Args,Prev,BodyLam),
        append(Prev,Bound,Bound1),
        unboundVars(BodyLam,Bound1,U).
unboundVars(E,Bound,U):-
        E=..[_N|Args], unboundVarsLst(Args,Bound,U).

unboundVarsLst([],_Bound,[]).
unboundVarsLst([X|Xs],Bound,U):-
        unboundVars(X,Bound,U1), unboundVarsLst(Xs,Bound,U2), append(U1,U2,U).



nfPred(X,X):- var(X),!.
nfPred(C,C1):-
        C=..[N|Args], 
        (
          lazy(N,L), !, nfArgs(L,Args,ArgsNf),C1=..[N|ArgsNf]
        ;
          nfLst(Args,Args1), C1=..[N|Args1]
        ).

nfLst([],[]).
nfLst([X|Xs],[X1|Xs1]):- nfPred(X,X1), nfLst(Xs,Xs1).

nfArgs([],[],[]).
nfArgs([X|Xs],[Y|Ys],[Ynf|YsNf]):- var(X),!,nfPred(Y,Ynf),nfArgs(Xs,Ys,YsNf).
nfArgs([On|Xs],[Y|Ys],[Ynf|YsNf]):- (On==on;On==on(shareOff)),!, @(Y,dummy,Yhnf),nfPred(Yhnf,Ynf),nfArgs(Xs,Ys,YsNf).
nfArgs([_|Xs],[Y|Ys],[Y|YsNf]):- nfArgs(Xs,Ys,YsNf).


flatExp(X,none,X,[]):- var(X),!.
flatExp(E,none,Lambda,Rules):-
        E=..[fun|Args],!,
        genNameLambda(Nlam),        
        prevLast(Args,Prev,BodyLam),
        unboundVars(BodyLam,Prev,Ub),
        append(Ub,Prev,ArgsLam),
        HeadLam=..[Nlam|ArgsLam],
        
        flatFunc((HeadLam,BodyLam,none),LamFun),
        length(ArgsLam,L), genApplys([(Nlam,L)],ApsLam),
        append(LamFun,ApsLam,Rules),                
        Lambda=..[Nlam|Ub].

flatExp(E,none,Lambda,Rules):-
        E=..[funS,Ev,Vl|Args],!,
        genNameLambdaS(Nlam),        
        prevLast(Args,Prev,BodyLam),
        unboundVars(BodyLam,Prev,Ub),
        append(Ub,Prev,ArgsLam),
        HeadLam=..[Nlam,Ev,Vl|ArgsLam],
        Lambda=..[Nlam,Ev,Vl|Ub],

	flatFunc((HeadLam,BodyLam,none),[(Hl,Bl)|Rs]),
	Hl=..[_|ArgsFl], last(ArgsFl,Res),
        LamFun=[(Hl,((Ev==on,!;Bl,Ev=on),Res=Vl))|Rs],

	PartlApp=..[Nlam,Ev,Vl|Ub],
	HeadApply=..[@,PartlApp,Dum,R],
	append([Ev,Vl|Ub],[Dum,R],ArgsAp),
	BodyApplyEv=..[Nlam|ArgsAp],
	
        append(LamFun,[(HeadApply,(!,BodyApplyEv))],Rules).



        
flatExp(E,Ps,H,Rs):-
        E=..[N|Args], functor(E,N,Ar),
        flatExpLst(Args,PsArgs,Hargs,Rs),
        (
          (function(N,Ar); N == @ , Ar=2),!,
          append(Hargs,[H],H1),
          Call=..[N|H1],
          appendTup(PsArgs,Call,Ps)
        ;
          Ps=PsArgs,
          H=..[N|Hargs]
        ).


flatExpLst([],none,[],[]).
flatExpLst([E|R],Ps,[H|Hs],Rs):- flatExp(E,Ps1,H,Rs1), flatExpLst(R,Ps2,Hs,Rs2),
        appendTup(Ps1,Ps2,Ps), append(Rs1,Rs2,Rs).


appendTup(X,Y,(X,Y)):- var(X),!.
appendTup(Y,X,(Y,X)):- var(X),!.
appendTup(none,X,X):-!.
appendTup(X,none,X):-!.
appendTup((X,Y),Z,R):-!, appendTup(Y,Z,R1), appendTup(X,R1,R).
appendTup(X,Y,(X,Y)).


flatPred((Head,Conds),[(Head,CondsFl)|Rs]):- flatConds(Conds,CondsFl,Rs).

flatConds(X,X,[]):-var(X),!.
flatConds(none,none,[]):-!.
flatConds((C,Cs),Cfl,Rs):- !, flatPredCall(C,C1,Rs1), flatConds(Cs,Cs1,Rs2),
        appendTup(C1,Cs1,Cfl), append(Rs1,Rs2,Rs).
flatConds(C,C1,Rs):- flatPredCall(C,C1,Rs).


flatPredCall(X,X,[]):-var(X),!.
flatPredCall(X is Z, Fl,[]):-!, Fl=(X is Z).
flatPredCall((A,B),(A1,B1),Rs):-
	flatPredCall(A,A1,Rs1), flatPredCall(B,B1,Rs2), append(Rs1,Rs2,Rs).
flatPredCall((A;B),(A1;B1),Rs):-
	flatPredCall(A,A1,Rs1), flatPredCall(B,B1,Rs2), append(Rs1,Rs2,Rs).
flatPredCall(P,Pfl,Rs):-
        P=..[N|Args],        
        flatExpLst(Args,Ps,Hs,Rs),
        P1=..[N|Hs], appendTup(Ps,P1,Pfl).


flatFunc((Head,Body,Conds),[(Head1,PredBody)|Rs]):-
        Head=..[N|Args], 
        append(Args,[H],ArgsH),
        Head1=..[N|ArgsH],
        flatExp(Body,Ps,Bfl,Re),
        (
          Conds==none,!, 
          appendTup(Ps,(H=Bfl),PredBody), 
          Rs=Re
        ;          
          flatConds(Conds,CondsFl,Rc),
          appendTup(CondsFl,Ps,Ps1),
          appendTup(Ps1,(H=Bfl),PredBody),
          append(Re,Rc,Rs)
        ).


genApplys([],[]).
genApplys([(F,Ar)|R],Aps):- genApplysFun(F,Ar,0,Aps1), genApplys(R,Aps2), append(Aps1,Aps2,Aps).

genApplysFun(_F,Ar,Ar,[]):-!.
genApplysFun(F,Ar,C,Aps):-
        X is Ar-1,
        genLstVars(C,Vs),
        (
          X\==C,!,
          append(Vs,[Y],R),
          HeadP=..[F|Vs], HeadP2=..[F|R],
          Head=..[@,HeadP,Y,HeadP2],
          Aps=[(Head,!)|Raps],
          C1 is C+1, genApplysFun(F,Ar,C1,Raps)
        ;
          append(Vs,[Y,H],R),
          HeadP=..[F|Vs], Call=..[F|R],
          Head=..[@,HeadP,Y,H],
          Aps=[(Head,(!,Call))]
        ).

genLstVars(0,[]):-!.
genLstVars(N,[_|R]):- N1 is N-1, genLstVars(N1,R).





fun :-
        prompt(_,'frolog> '),
        read_term(T,[]), nl,
        functor(T,F,Ar),        
        (
         function(F,Ar),!,
         contLambda(Cl), contLambdaS(Cls),
         makeLazyExp(T,[],Tl),flatExp(Tl,Conds,Res,Rules),
         optimizeLstClauses(Rules,Rules1),
         includeLstClauses(Rules1),
         lanzaObjetivo(Conds,Res),
         removeLstClauses(Rules1),
         retractall(contLambda(_)), retractall(contLambdaS(_)),
         assert(contLambda(Cl)), assert(contLambdaS(Cls))
        ;
	 call(T)
	;
         true
        ),
        fun.

fun :- fun.

lanzaObjetivo(Conds,Res):-
        ponTiempo,        
        call(Conds), nfPred(Res,Res1),
        continuaObjetivo(Res1),
        !
        ;
        escribeFallo.

continuaObjetivo(Res1):- tab(6), write(Res1), escribeTiempo, !, nl, nl, preguntaSiMas.


optimizeLstClauses([],[]).
optimizeLstClauses([X|Xs],[Y|Ys]):- optimizeClause(X,Y), optimizeLstClauses(Xs,Ys).

removeLstClauses([]).
removeLstClauses([(H,B)|R]):- (B==none,!,retract(H); retract((H:-B))), removeLstClauses(R).

includeLstClauses([]).
includeLstClauses([(L,R)|Cs]):- (R==none,!, asserta(L);asserta(L:-R)), includeLstClauses(Cs).



preguntaSiMas:-
        prompt(_,'more [y]? '),
	get0(Op),
	(
          (Op==121;Op==10),	% 10 = intro, 121= 'y'
          quitaBasura(Op),
          !,
          nl,ponTiempo,fail
	;
          quitaBasura(Op),nl
	).


quitaBasura(10):-!.
quitaBasura(_):-
	get0(Bas),
	quitaBasura(Bas).
     

ponTiempo:- retractall(tiempo(_)), get_time(T), assert(tiempo(T)).


escribeFallo:-
        tab(6),write('no.'),
        escribeTiempo,nl,nl.


escribeTiempo:-
        get_time(T2), tiempo(T1), T is (T2-T1),
        nl, nl, write('Elapsed time: '),write(T), write(' secs.').



:- nl,
   write('Frolog version 0.0'), nl,
   write(' expand(<File>).      compiles <File>.plf'),nl,
   write(' assert(lazyDebug).   shows intermediate code with suspensions'),nl,
   write(' fun.                 starts functional prompt.'),nl,
   nl.


r:-[frolog2].