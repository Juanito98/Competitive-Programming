open Core

let with_stdin ?(strip = true) input ~f =
  let input = if strip then String.strip input else input in
  (* Save the original stdin *)
  let original_stdin = Core_unix.dup Core_unix.stdin in
  let pipe_in, pipe_out = Core_unix.pipe () in
  (* Write the input string into the pipe *)
  let () =
    let out_channel = Core_unix.out_channel_of_descr pipe_out in
    Out_channel.output_string out_channel input;
    Out_channel.close out_channel
  in
  (* Replace stdin with the read end of the pipe *)
  Core_unix.dup2 ~src:pipe_in ~dst:Core_unix.stdin ();
  Core_unix.close pipe_in;
  (* Call the function, which reads from stdin *)
  let result = f () in
  (* Restore the original stdin *)
  Core_unix.dup2 ~src:original_stdin ~dst:Core_unix.stdin ();
  Core_unix.close original_stdin;
  result
