#lang racket

(provide encode)

(define (normalize str)
    (filter char-alphabetic? (string->list (string-downcase str)))
)

(define (get-num-cols list-str)
    (exact-ceiling (sqrt (length list-str)))
)

(define (transp lst)
    (apply map list lst)
)

(define (gen-rows lst-str num-cols)
    (define l (length lst-str))
    (cond ((empty? lst-str) '())
          ((< l num-cols) (list (append lst-str (make-list (- num-cols l) #\space))))
          (else (cons (take lst-str num-cols) (gen-rows (drop lst-str num-cols) num-cols))))
)

(define (encode str)
    (let* ([norm-str (normalize str)]
           [num-cols (get-num-cols norm-str)]
           [res-list (transp (gen-rows norm-str num-cols))])
        (string-join (map list->string res-list)))
)
