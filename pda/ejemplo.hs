repite :: a -> [a]
repite x = x : repite x

primeros :: Integer -> [a] -> [a]
primeros _ [] = []
primeros 0 _ = []
primeros n (x:xs) = x : primeros (n - 1) xs

main = print (primeros 8 (repite 4))
