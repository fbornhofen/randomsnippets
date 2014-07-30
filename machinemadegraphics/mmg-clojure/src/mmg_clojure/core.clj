(ns mmg-clojure.core
  (:gen-class)
  (import java.awt.image.BufferedImage)
  (import java.io.File)
  (import javax.imageio.ImageIO))

(defn transpose [m]
  (apply mapv vector m))

(defn write-image [file-name seq-of-seqs]
  (let [img (BufferedImage. (count (first seq-of-seqs))
                            (count seq-of-seqs)
                            BufferedImage/TYPE_INT_RGB)]
    (doall
     (map-indexed (fn [row-idx row]
            (doall
             (map-indexed (fn [col-idx col]
                            (.setRGB img col-idx row-idx col))
                          row)))
            seq-of-seqs))
    (ImageIO/write img "png"  (File. (str file-name ".png")))))

(defn make-random-slice [height fill-probability]
  (map (fn [ign] (if (> fill-probability (rand)) 0 0xFFFFFF)) (repeat height 0)))

(defn min-distance-to-black [idx slice]
  (let [slice-len (count slice)]
    (apply min
           (map-indexed (fn [slice-idx px]
                          (if (= 0 px)
                            (Math/abs (- idx slice-idx))
                            slice-len))
                        slice))))

(defn transform-slice [slice]
  (map-indexed (fn [idx px]
                 (let [min-dist (min-distance-to-black idx slice)]
                   (if (= 0 min-dist)
                     (if (> 0.5 (rand))
                       0
                       0xFFFFFF)
                     (if (> (Math/exp (- min-dist)) (rand))
                       0
                       (if (> 0.001 (rand))
                         0
                         0xFFFFFF)))))
               slice))

(defn make-series [acc iterations]
  (let [prev-slice (last acc)]
    (if (= 0 iterations)
      acc
      (recur (conj acc (transform-slice prev-slice))
             (dec iterations)))))

(defn -main
  [& args]
  (let [width (Integer/parseInt (first args))
        height (Integer/parseInt (second args))
        file-name (nth args 2)]
    (write-image file-name (transpose (make-series [(make-random-slice height 0.15)] (dec width))))))
