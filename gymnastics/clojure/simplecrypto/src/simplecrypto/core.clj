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

(defn analyze-frequencies [s]
  (let [freqs (frequencies s)
        char-freq-pairs (seq freqs)
        sorted-freqs (sort #(> (second %1) (second %2)) char-freq-pairs)
        total (reduce + (map second char-freq-pairs))]
    (map
     (fn [tup] [(first tup) (second tup) (float (/ (second tup) total))])
     sorted-freqs)))

(defn analyze-strided-frequencies [s max-stride]
  (let [r (range (inc max-stride))
        partitions (map #(analyze-frequencies (collect-nth s %1)) r)]
    partitions))

(defn analyze []
  (let [crypt-string "Xleg M gmnw qqtily mf xifpw pj mcsmcpe Xsliir Xejz chxik xo xi, Wpxloaok pzvvt oy aathof, dfx be tf. Tyh jr fj zpyr zj eerdyikt Sap at smlrvjrg cmyix by xssnm sx qe, Whfekbyk xsrwd gg wbdhgn, epx jx up. Pem ml fe, pwu im fw, Lxe au bx, dfx be tf, Psmkqir hsjew hq ojwdhx, mit tx ci. Efe wapr ule mvglin-sissxew twptlx Pawmnz mf xhx agspd lkjfi, Elwsi ptpd fe lr brsppv, pem ml fe. Jgs tazyyi tapc ney mi qermph Ulekp at smtpd e vsefdi msel xhxj ojpl diw, Tapvw aiew tf ag eftaek, dfx be tf. Wil mt mi, pem ml fe, Pwu im fw, lxe au bx, Liirx aamp up so agdaws, epx jx up. Mit tx ci, wil mt mi, Pem ml fe, pwu im fw, Watwhfv pzvvt oy aathof, dfx be tf."
        stripped-string (strip-string crypt-string)]
    (println stripped-string)))