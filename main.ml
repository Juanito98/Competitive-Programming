open Core

let main () =
  let input = In_channel.input_all Stdio.stdin in
  print_s [%sexp (input : string)]

let () = main ()
