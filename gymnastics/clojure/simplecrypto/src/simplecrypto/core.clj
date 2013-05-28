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
    (if (= 0 n)
      []
      (apply str (take-nth n (drop offset s))))))

(defn frequency-tuples [s]
  (let [freqs (frequencies s)
        char-freq-pairs (seq freqs)
        sorted-freqs (sort #(> (second %1) (second %2)) char-freq-pairs)
        total (reduce + (mapv second char-freq-pairs))]
    (mapv
     (fn [tup] [(first tup) (second tup) (float (/ (second tup) total))])
     sorted-freqs)))

(defn strided-frequencies [s max-stride]
  (let [r (map inc (range max-stride))
        partitions (mapv #(frequency-tuples (collect-nth s %1)) r)]
    partitions))

(defn third-elements [xs]
  (mapv (fn [coll] (nth coll 2)) xs))

(defn vector-average [vec-of-vec]
  (let [sum-vector (apply map + vec-of-vec)
        n (count vec-of-vec)]
    (mapv #(/ % n) sum-vector)))

(defn average-freq-distributions [strided-results]
  (let [freq-vectors (mapv (fn [xs]
                            (mapv third-elements xs))
                          strided-results)]
    (map vector-average freq-vectors)))
    
(defn frequency-distributions [s max-stride]
  (average-freq-distributions
   (apply mapv
          vector
          (mapv (fn [skip]
                  (strided-frequencies (drop skip s) max-stride))
                (range max-stride)))))

(defn analyze []
  (let [crypt-string "Xleg M gmnw qqtily mf xifpw pj mcsmcpe Xsliir Xejz chxik xo xi, Wpxloaok pzvvt oy aathof, dfx be tf. Tyh jr fj zpyr zj eerdyikt Sap at smlrvjrg cmyix by xssnm sx qe, Whfekbyk xsrwd gg wbdhgn, epx jx up. Pem ml fe, pwu im fw, Lxe au bx, dfx be tf, Psmkqir hsjew hq ojwdhx, mit tx ci. Efe wapr ule mvglin-sissxew twptlx Pawmnz mf xhx agspd lkjfi, Elwsi ptpd fe lr brsppv, pem ml fe. Jgs tazyyi tapc ney mi qermph Ulekp at smtpd e vsefdi msel xhxj ojpl diw, Tapvw aiew tf ag eftaek, dfx be tf. Wil mt mi, pem ml fe, Pwu im fw, lxe au bx, Liirx aamp up so agdaws, epx jx up. Mit tx ci, wil mt mi, Pem ml fe, pwu im fw, Watwhfv pzvvt oy aathof, dfx be tf."
        stripped (strip-string crypt-string)
        freqs (frequency-distributions stripped (/ (count stripped) 5))]
    (doall
     (map-indexed (fn [i f]
                    (printf "%d\t" i)
                    (doall
                     (map (fn [val]
                            (printf "  %.4f" val))
                          (take 5 f)))
                    (println)) freqs))))