:- style_check([-singleton,-discontiguous]).
function(nf, 1).
function(unquote, 1).
function(ifThen, 2).
function(ifThenElse, 3).
function(?, 2).
function(+, 2).
function(-, 2).
function(*, 2).
function(/, 2).
function(mod, 2).
function(==, 2).
function(=\=, 2).
function(<, 2).
function(>, 2).
function(=<, 2).
function(>=, 2).
function(abs, 1).
function(and, 2).
function(map, 2).
function(nth, 2).
function(take, 2).
function(filter, 2).
function(foldr, 3).
function(foldl, 3).
function(head, 1).
function(tail, 1).
function(zip, 2).
function(zipWith, 3).
function(concat, 1).
function(app, 2).
function(concatMap, 2).
function(proy, 2).
function(hola, 0).
function(hola2, 0).
function(@,2).
function(quote,1).
nf(_G398, _G401):- nfPred(_G398, _G401).
unquote(_G657, _G739):- @(_G657, dummy, _G739).
ifThen(true, _G951, _G1049):- @(_G951, dummy, _G1049).
ifThenElse(true, _G1277, _G1278, _G1386):- @(_G1277, dummy, _G1386).
ifThenElse(false, _G1636, _G1637, _G1745):- @(_G1637, dummy, _G1745).
?(_G1994, _G1995, _G2087):- @(_G1994, dummy, _G2087).
?(_G2320, _G2321, _G2413):- @(_G2321, dummy, _G2413).
+(_G2646, _G2647, _G2649):- _G2649 is _G2646+_G2647.
-(_G2998, _G2999, _G3001):- _G3001 is _G2998-_G2999.
*(_G3350, _G3351, _G3353):- _G3353 is _G3350*_G3351.
/(_G3702, _G3703, _G3705):- _G3705 is _G3702/_G3703.
mod(_G4054, _G4055, _G4057):- _G4057 is _G4054 mod _G4055.
==(_G4406, _G4407, _G4517):- _G4406==_G4407, !, _G4517=true.
==(_G4695, _G4696, false).
=\=(_G4886, _G4887, _G4997):- _G4886=\=_G4887, !, _G4997=true.
=\=(_G5175, _G5176, false).
<(_G5366, _G5367, _G5477):- _G5366<_G5367, !, _G5477=true.
<(_G5655, _G5656, false).
>(_G5846, _G5847, _G5957):- _G5846>_G5847, !, _G5957=true.
>(_G6135, _G6136, false).
=<(_G6326, _G6327, _G6437):- _G6326=<_G6327, !, _G6437=true.
=<(_G6615, _G6616, false).
>=(_G6806, _G6807, _G6917):- _G6806>=_G6807, !, _G6917=true.
>=(_G7095, _G7096, false).
abs(_G7286, _G7424):- >=(_G7286, 0, _G7448), ifThenElse(_G7448, fun1(_G7286), fun2(_G7286), _G7424).
fun1(_G7286, _G7334, _G7286).
@(fun1, _G7592, fun1(_G7592)):- !.
@(fun1(_G7631), _G7637, _G7640):- !, fun1(_G7631, _G7637, _G7640).
fun2(_G7286, _G7337, _G7788):- *(_G7286, -1, _G7788).
@(fun2, _G7856, fun2(_G7856)):- !.
@(fun2(_G7895), _G7901, _G7904):- !, fun2(_G7895, _G7901, _G7904).
and(true, _G8901, _G8901).
and(false, _G9086, false).
map(_G9276, [], []).
map(_G9467, [_G9470|_G9471], [_G9657|_G9691]):- @(_G9467, _G9470, _G9657), map(_G9467, _G9471, _G9691).
nth(0, [_G10106|_G10107], _G10202):- !, _G10202=_G10106.
nth(_G10335, [_G10338|_G10339], _G10488):- -(_G10335, 1, _G10513), nth(_G10513, _G10339, _G10488).
take(0, _G10891, _G10971):- !, _G10971=[].
take(_G11083, [], _G11164):- !, _G11164=[].
take(_G11276, [_G11279|_G11280], [_G11279|_G11481]):- -(_G11276, 1, _G11493), take(_G11493, _G11280, _G11481).
filter(_G11918, [], []).
filter(_G12109, [_G12112|_G12113], _G12316):- @(_G12109, _G12112, true), !, filter(_G12109, _G12113, _G12344), _G12316=[_G12112|_G12344].
filter(_G12940, [_G12943|_G12944], _G13057):- filter(_G12940, _G12944, _G13057).
foldr(_G13338, _G13339, [], []).
foldr(_G13562, _G13563, [_G13566|_G13567], _G13749):- @(_G13562, _G13566, _G13778), foldr(_G13562, _G13563, _G13567, _G13812), @(_G13778, _G13812, _G13749).
foldl(_G14349, _G14350, [], []).
foldl(_G14573, _G14574, [_G14577|_G14578], _G14760):- @(_G14573, _G14574, _G14807), @(_G14807, _G14577, _G14795), foldl(_G14573, _G14795, _G14578, _G14760).
head([_G15362|_G15363], _G15362).
tail([_G15580|_G15581], _G15581).
zip([], _G15797, _G15877):- !, _G15877=[].
zip(_G15989, [], _G16070):- !, _G16070=[].
zip([_G16185|_G16186], [_G16188|_G16189], [ (_G16185, _G16188)|_G16420]):- zip(_G16186, _G16189, _G16420).
zipWith(_G16826, [], _G16828, _G16918):- !, _G16918=[].
zipWith(_G17043, _G17044, [], _G17135):- !, _G17135=[].
zipWith(_G17260, [_G17264|_G17265], [_G17267|_G17268], [_G17524|_G17592]):- @(_G17260, _G17264, _G17536), @(_G17536, _G17267, _G17524), zipWith(_G17260, _G17265, _G17268, _G17592).
concat([[]], _G18300):- !, _G18300=[].
concat([[]|_G18414], _G18512):- concat(_G18414, _G18512).
concat([[_G18730|_G18731]|_G18728], [_G18730|_G18916]):- concat([_G18731|_G18728], _G18916).
app([], _G19298, _G19298).
app([_G19485|_G19486], _G19483, [_G19485|_G19651]):- app(_G19486, _G19483, _G19651).
concatMap(_G19967, [], []).
concatMap(_G20158, [_G20161|_G20162], _G20329):- @(_G20158, _G20161, _G20354), concatMap(_G20158, _G20162, _G20388), app(_G20354, _G20388, _G20329).
proy(_G20873, _G20874, _G20873):- _G20874.
hola(_G21333):- map(fun3, [1, 2, 3, 4, 5], _G21333).
fun3(_G21045, _G21428):- *(_G21045, 2, _G21428).
@(fun3, _G21492, _G21495):- !, fun3(_G21492, _G21495).
hola2(_G22592):- zipWith(fun4, [1, 2, 3, 4], [5, 6, 7, 8], _G22592).
fun4(_G22193, _G22194, _G22697):- +(_G22193, _G22194, _G22697).
@(fun4, _G22759, fun4(_G22759)):- !.
@(fun4(_G22798), _G22804, _G22807):- !, fun4(_G22798, _G22804, _G22807).
@(nf, _G24029, _G24032):- !, nf(_G24029, _G24032).
@(unquote, _G24072, _G24075):- !, unquote(_G24072, _G24075).
@(ifThen, _G24115, ifThen(_G24115)):- !.
@(ifThen(_G24154), _G24160, _G24163):- !, ifThen(_G24154, _G24160, _G24163).
@(ifThenElse, _G24209, ifThenElse(_G24209)):- !.
@(ifThenElse(_G24248), _G24254, ifThenElse(_G24248, _G24254)):- !.
@(ifThenElse(_G24299, _G24305), _G24311, _G24314):- !, ifThenElse(_G24299, _G24305, _G24311, _G24314).
@(?, _G24365, ?(_G24365)):- !.
@(?(_G24404), _G24410, _G24413):- !, ?(_G24404, _G24410, _G24413).
@(+, _G24459, +_G24459):- !.
@(+_G24498, _G24504, _G24507):- !, +(_G24498, _G24504, _G24507).
@(-, _G24553, -_G24553):- !.
@(-_G24592, _G24598, _G24601):- !, -(_G24592, _G24598, _G24601).
@(*, _G24647, *(_G24647)):- !.
@(*(_G24686), _G24692, _G24695):- !, *(_G24686, _G24692, _G24695).
@(/, _G24741, /(_G24741)):- !.
@(/(_G24780), _G24786, _G24789):- !, /(_G24780, _G24786, _G24789).
@(mod, _G24835, mod(_G24835)):- !.
@(mod(_G24874), _G24880, _G24883):- !, mod(_G24874, _G24880, _G24883).
@(==, _G24929, ==(_G24929)):- !.
@(==(_G24968), _G24974, _G24977):- !, ==(_G24968, _G24974, _G24977).
@(=\=, _G25023, =\=(_G25023)):- !.
@(=\=(_G22), _G23, _G24):- !, =\=(_G22, _G23, _G24).
@(<, _G38, <(_G38)):- !.
@(<(_G48), _G49, _G50):- !, <(_G48, _G49, _G50).
@(>, _G67, >(_G67)):- !.
@(>(_G77), _G78, _G79):- !, >(_G77, _G78, _G79).
@(=<, _G96, =<(_G96)):- !.
@(=<(_G106), _G107, _G108):- !, =<(_G106, _G107, _G108).
@(>=, _G125, >=(_G125)):- !.
@(>=(_G135), _G136, _G137):- !, >=(_G135, _G136, _G137).
@(abs, _G154, _G155):- !, abs(_G154, _G155).
@(and, _G169, and(_G169)):- !.
@(and(_G179), _G180, _G181):- !, and(_G179, _G180, _G181).
@(map, _G198, map(_G198)):- !.
@(map(_G208), _G209, _G210):- !, map(_G208, _G209, _G210).
@(nth, _G227, nth(_G227)):- !.
@(nth(_G237), _G238, _G239):- !, nth(_G237, _G238, _G239).
@(take, _G256, take(_G256)):- !.
@(take(_G266), _G267, _G268):- !, take(_G266, _G267, _G268).
@(filter, _G285, filter(_G285)):- !.
@(filter(_G295), _G296, _G297):- !, filter(_G295, _G296, _G297).
@(foldr, _G314, foldr(_G314)):- !.
@(foldr(_G324), _G325, foldr(_G324, _G325)):- !.
@(foldr(_G338, _G339), _G340, _G341):- !, foldr(_G338, _G339, _G340, _G341).
@(foldl, _G360, foldl(_G360)):- !.
@(foldl(_G370), _G371, foldl(_G370, _G371)):- !.
@(foldl(_G384, _G385), _G386, _G387):- !, foldl(_G384, _G385, _G386, _G387).
@(head, _G406, _G407):- !, head(_G406, _G407).
@(tail, _G421, _G422):- !, tail(_G421, _G422).
@(zip, _G436, zip(_G436)):- !.
@(zip(_G446), _G447, _G448):- !, zip(_G446, _G447, _G448).
@(zipWith, _G465, zipWith(_G465)):- !.
@(zipWith(_G475), _G476, zipWith(_G475, _G476)):- !.
@(zipWith(_G489, _G490), _G491, _G492):- !, zipWith(_G489, _G490, _G491, _G492).
@(concat, _G511, _G512):- !, concat(_G511, _G512).
@(app, _G526, app(_G526)):- !.
@(app(_G536), _G537, _G538):- !, app(_G536, _G537, _G538).
@(concatMap, _G555, concatMap(_G555)):- !.
@(concatMap(_G565), _G566, _G567):- !, concatMap(_G565, _G566, _G567).
@(proy, _G584, proy(_G584)):- !.
@(proy(_G594), _G595, _G596):- !, proy(_G594, _G595, _G596).
@(eval(_G624), _G621, _G622):- !, eval(_G624, _G621, _G622).
@(_G639, _G640, _G639).