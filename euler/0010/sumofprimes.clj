
(defn is-prime [n]
  (.isProbablePrime (BigInteger/valueOf n) 10))

(defn primes []
  (filter is-prime (range)))

(println (reduce + (take-while (partial > 2000000) (primes))))