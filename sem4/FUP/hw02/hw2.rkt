#lang racket

(provide execute)

(require racket/trace)

;;; Generates an SVG element with the specified width, height, and content
(define (make-svg width height content)
    (format "<svg width=\"~a\" height=\"~a\">~a</svg>"  width height content)
)

;;; Generates an SVG circle element 
(define (make-circle cx cy r style)
    (format "<circle cx=\"~a\" cy=\"~a\" r=\"~a\" style=\"~a\"/>" cx cy r style)
)

;;; Generates an SVG rectangle element
(define (make-rect x y width height style)
    (format "<rect x=\"~a\" y=\"~a\" width=\"~a\" height=\"~a\" style=\"~a\"/>" x y width height style)
)

;;; Generates an SVG line element
(define (make-line x1 y1 x2 y2 style)
    (format "<line x1=\"~a\" y1=\"~a\" x2=\"~a\" y2=\"~a\" style=\"~a\"/>" x1 y1 x2 y2 style)
)

;;; List with operations
(define operations '(+ - * / = < > floor cos sin circle rect line))

;;; Maps symbolic operations to functions
(define (get-op op)
    (match op
        ['+ +]
        ['- -]
        ['* *]
        ['/ /]
        ['= =]
        ['< <]
        ['> >]
        ['floor floor]
        ['cos cos]
        ['sin sin]
        ['circle make-circle]
        ['rect make-rect]
        ['line make-line]
        [_ (error "Unknown operation!")]
    )
)

;;; Checks if a variable exists in the enveronment
(define (env-member? name env)
    (if (eqv? (assv name env) #f) 
        #f
        #t
    )
)

;;; Returns the value of a variable from the environment
(define (get-env-member-val name env)
    (cadr (assv name env))
)

;;; Returns the arguments of a function from the environment
(define (get-env-member-args func-name env)
    (caadr (assv func-name env))
)

;;; Retrieves the body of a function from the environment
(define (get-env-member-body func-name env)
    (cadadr (assv func-name env))
)

;;; Parses a program definition into an environment format
(define (parse prg)
    (define (helper p)
        (match p
            [(list 'define (list func-name args ...) body ...) (list func-name (list args body))]
            [(list 'define name val) (list name val)]    
        )
    )
    (map helper prg)
)

;;; Updates the environment: replaces existing variables or adds new ones
(define (new-parse old-env new-members vals)
    (append (map list new-members vals) old-env)
)

;;; Evaluates an expression in the given environment
(define (eval-exp exp env)
    (define (helper expr)
        (eval-exp expr env)
    )

    (match exp
        [(? number? num) num]                                                          ; if number return
        [(? string? str) str]                                                          ; if string return
        [(? symbol? name) #:when(env-member? name env) (get-env-member-val name env)]  ; look up variables
        [(list op rest ...) #:when(member op operations)                               ; evaluate arithmetic and function operations
                            (apply (get-op op) (map helper rest))]
        [(list 'if con then els) (if (helper con) (helper then) (helper els))]         ; if-expression handling
        [(list 'when con then ...) #:when(helper con) (apply string-append (map helper then))] ; when-expression handling                    
        [(list func-name args ...) #:when(env-member? func-name env)                   ; function call handling
            (let* ([params (get-env-member-args func-name env)]
                   [body (get-env-member-body func-name env)]
                   [new-env (new-parse env params (map helper args))])
            (apply string-append (map (lambda (e) (eval-exp e new-env)) body)))]
        [_ ""]                                                                         ; if no match return empty string
    )
)

;(trace eval-exp)

;;; Executes the given program and evaluates the final expression
(define (execute width height prg exp)
    (make-svg width height (eval-exp exp (parse prg)))
)




(define test2
  '((define STYLE "fill:red;opacity:0.2;stroke:red;stroke-width:3")
    (define START 195)
    (define END 10)
    (define (circles x r)
      (when (> r END)
        (circle x 200 r STYLE)
        (circles (+ x (floor (/ r 2))) (floor (/ r 2)))))))

(display (execute 400 400 test2 '(circles 200 START))) 




; (define tree-prg
;     '((define STYLE1 "stroke:black;stroke-width:2;opacity:0.9")
;       (define STYLE2 "stroke:green;stroke-width:3;opacity:0.9")
;       (define FACTOR 0.7)
;       (define PI 3.14)
;       (define (draw x1 y1 x2 y2 len angle)
;         (if (> len 30)
;             (line x1 y1 x2 y2 STYLE1)
;             (line x1 y1 x2 y2 STYLE2))
;         (when (> len 20)
;           (recur-tree x2 y2 (floor (* len FACTOR)) angle)
;           (recur-tree x2 y2 (floor (* len FACTOR)) (+ angle 0.3))
;           (recur-tree x2 y2 (floor (* len FACTOR)) (- angle 0.6))))
;       (define (recur-tree x1 y1 len angle)
;         (draw x1
;               y1
;               (+ x1 (* len (cos angle)))
;               (+ y1 (* len (sin angle)))
;               len
;               angle))))


; (display (execute 400 300 tree-prg '(recur-tree 200 300 100 (* PI 1.5))))
