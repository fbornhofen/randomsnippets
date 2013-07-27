
(defn isPrime [n]
  (.isProbablePrime (BigInteger/valueOf n) 10))

(defn primes []
  (filter isPrime (range)))

(defn nth-prime [n]
  (first (drop (dec n) (primes))))

(println (nth-prime 10001))