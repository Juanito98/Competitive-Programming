open Core

let main () =
  let input = In_channel.input_all Stdio.stdin in
  print_endline ("Hola " ^ input)

let () = main ()
