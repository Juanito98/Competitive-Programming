(lang dune 3.18)

(name competitive_programming)

(package
 (name competitive_programming)
 (depends
  (ocaml
   (< 5.0))
  core
  core_kernel
  core_unix
  ppx_expect
  ppx_jane))

; See the complete stanza docs at https://dune.readthedocs.io/en/stable/dune-files.html#dune-project
