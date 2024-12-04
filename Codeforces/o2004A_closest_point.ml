open Core

let main () =
  let input = In_channel.input_all Stdio.stdin in
  let lines = String.split ~on:'\n' input in
  match lines with
  | _ :: data ->
      let rec solve = function
        | _ :: arr :: rest ->
            let arr = String.split ~on:' ' arr |> List.map ~f:int_of_string in
            let possible =
              match arr with
              | [ _ ] -> true
              | a :: [ b ] -> a + 1 < b
              | _ -> false
            in
            if possible then print_endline "YES" else print_endline "NO";
            solve rest
        | _ :: [] | [] -> ()
      in
      solve data
  | _ -> failwith "Invalid input"
