#lang racket
(provide rps)

(define (game-finished? strats) (or (null? strats) (ormap null? strats)))
(define (strats-current strats) (map car strats))
(define (strats-future strats) (map cdr strats))

(define (eliminated throws)
    (match (remove-duplicates (sort throws symbol<?))
        ['(p r) 'r]
        ['(p s) 'p]
        ['(r s) 's]
        [_ '()])
)

(define (find-surv throws)
    (let* ([elim (eliminated throws)])
        (map (curry (compose not equal?) elim) throws))
)

(define (filt players not-elim-bools)
    (for/list ([name players] [not-elim not-elim-bools] #:when not-elim) name)   
)

(define (rps players strategies)
  (if (game-finished? strategies)
    players
    (let* ([current (strats-current strategies)]
           [future (strats-future strategies)]
           [mask (find-surv current)])
        (rps (filt players mask) (filt future mask))))
)