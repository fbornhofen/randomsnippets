(ns simplecrypto.core)

(require '[clojure.string :as string])

(defn is-letter [c]
  (or
   (and (<= (int \a) (int c)) (<= (int c) (int \z)))
   (and (<= (int \A) (int c)) (<= (int c) (int \Z)))))

(defn strip-string [s]
  (string/upper-case (apply str (filter is-letter s))))

(defn collect-nth [s & params]
  (let
      [n (first params)
       offset (if (> 2 (count params))
                 0
                 (second params))]
       (apply str (take-nth n (drop offset s)))))
