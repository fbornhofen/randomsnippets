
(defn isPrime [n]
  (.isProbablePrime (BigInteger/valueOf n) 10))

(defn primes []
  (filter isPrime (range)))

(defn primes-less-than [n]
  (take-while (partial > n) (primes)))

(defn max-power-less-than [max base]
  (loop [p base]
    (if (> (* p base) max)
      p
      (recur (* p base)))))
           

(defn primes-powers-less-than [n]
  (map (partial max-power-less-than n) (primes-less-than n)))

(println (reduce * (primes-powers-less-than 20)))

;  Primes between 1 and 20  | Largest power less than 20
; --------------------------+----------------------------
;  2                        | 16
;  3                        |  9
;  5                        |  5
;  7                        |  7
; 11                        | 11
; 13                        | 13
; 17                        | 17
; 19                        | 19
;
; 16 * 9 * 5 * 7 * 11 * 13 * 17 * 19 = 232792560
;
; General idea: enumerate all primes < n=20,
; for each of them collect the largest power < n,
; multiply all these powers.