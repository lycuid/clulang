(define *global-int*
  (int->string
    (+ 420 69)))

(let *global-char* #\c)
(letrec *global-space #\space)
(let* *global-newline* #\newline)
(define *global-tab* #\tab)
