(ns prototypes.core
  (:use clojure.walk
        clojure.test))

;; === aux
(defn skip-prefix [a-prefix a-string]
  (if (= a-prefix
         (apply str (take (count a-prefix) a-string)))
    (apply str (drop (count a-prefix) a-string))
    nil))

(defn skip-prefix-sym [a-prefix a-symbol]
  (let [new-string (skip-prefix
                    (str a-prefix)
                    (str a-symbol))]
    (if new-string
      (symbol new-string)
      a-symbol)))

;; ===
(defrecord ProtoType [parent the-map])

(defn pt-set [a-prototype a-key a-value]
  (assoc (:the-map) a-key a-value))

(defn pt-get [a-prototype a-key]
  (if (= nil (a-key (:the-map a-prototype)))
    (if (= nil (:parent a-prototype))
      nil
      (pt-get (:parent a-prototype) a-key))
    (a-key (:the-map a-prototype))))

(defn pt-set-prototype [a-prototype its-new-prototype]
  (->ProtoType its-new-prototype (:the-map a-prototype)))

(defn pt-replace-symbol-in-tree [a-list a-symbol a-replacement]
  (postwalk-replace {a-symbol a-replacement} a-list))

(defn pt-replace-self-symbol [a-prototype a-symbol]
  (let [replacement (skip-prefix-sym "self." a-symbol)]
    (if (not (= replacement a-symbol))
      `(pt-get ~a-prototype ~(keyword replacement))
      a-symbol)))

(defn pt-resolve-self-references [a-prototype a-list]
  (map (fn [x]
         (if (list? x)
           (pt-resolve-self-references a-prototype x)
           (if (symbol? x)
             (pt-replace-self-symbol a-prototype x)
             x))) a-list))

(defn pt-bind-self-in-method-form [a-prototype a-slot]
  (let [the-form (pt-get a-prototype a-slot)]
    (if (list? the-form)
      (eval (pt-resolve-self-references a-prototype the-form))
      the-form)))

(defn pt-invoke [a-prototype a-slot & args]
  (let [the-method (pt-bind-self-in-method-form a-prototype a-slot)]
    (eval `(~the-method ~@args))))

(defn -main
  "I don't do a whole lot."
  [& args]
  (println "Hello, World!"))

;==== TESTS

(deftest test-skip-prefix-sym
  (is (= (symbol "a") (skip-prefix-sym (symbol "self.")
                                       (symbol "self.a")))))

(deftest pt-resolve-self-refs
  (is (= '(x) (pt-resolve-self-references nil '(self.x)))))

;; === example
;;
;;  (def p1 (->ProtoType nil {:a 23 :b '(fn [] self.a)}))
;;  ((eval (seq (pt-resolve-self-references p1 (pt-get p1 :b)))) [args..])
;;
;; (def p2 (->ProtoType nil {:a 1 :b 4 :c '(fn [a b] (+ a b self.a))}))
;; (pt-invoke p2 :c 1 2) ;; => 4
;; (def p3 (->ProtoType p2 {:a 2}))
;; (pt-invoke p3 :c 1 2) ;; => 5
;;
