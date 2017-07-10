;; http://dotemacs.de/dotfiles/sample.emacs.html


;; Make F1 invoke help
(global-set-key [f1] 'help-command)
;; Make F2 be `undo'
(global-set-key [f2] 'undo)
;; Make F3 be `find-file'
;; Note: it does not currently work to say
;;   (global-set-key 'f3 "\C-x\C-f")
;; The reason is that macros can't do interactive things properly.
;; This is an extremely longstanding bug in Emacs.  Eventually,
;; it will be fixed. (Hopefully ..)
(global-set-key [f3] 'find-file)

;; Make F4 be "mark", F5 be "copy", F6 be "paste"
;; Note that you can set a key sequence either to a command or to another
;; key sequence.
(global-set-key [f4] 'set-mark-command)
(global-set-key [f5] "\M-w")
(global-set-key [f6] "\C-y")

;; Make F7 be `save-buffer'
(global-set-key [f7] 'save-buffer)

;; Make F8 be "start macro", F9 be "end macro", F10 be "execute macro"
(global-set-key [f8] 'start-kbd-macro)
(global-set-key [f9] 'end-kbd-macro)
(global-set-key [f10] 'call-last-kbd-macro)

(global-linum-mode t)

(setq c-basic-offset 4) ; indents 4 chars                                                                                                              
(setq tab-width 4)          ; and 4 char wide for TAB
(setq indent-tabs-mode nil) ; And force use of spaces

(turn-on-font-lock)       ; same as syntax on in Vim

;; (setq width (max width (+ (length str) 1)))   ;line numbers
(setq dismiss-startup-screen t)

(setq inhibit-startup-screen t)
(setq initial-scratch-message ";; Happy Hacking")

