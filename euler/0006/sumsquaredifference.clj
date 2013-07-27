
(defn square-of-sum [n]
  (let [sum (/ (* n (inc n)) 2)] ; gauss
    (* sum sum)))

(defn sum-of-squares [n]
  (reduce (fn [s e] (+ s (* e e))) (range (inc n))))

(defn sum-square-diff [n]
  (- (square-of-sum n) (sum-of-squares n)))

(println (sum-square-diff 100))
