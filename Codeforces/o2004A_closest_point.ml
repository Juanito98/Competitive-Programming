let main () =
  let input = Stdio. "%s" (fun i -> i) in
  let lines = '\n' input in
  match lines with
  | _ :: data ->
      let rec solve = function
        | _ :: arr :: rest ->
            let arr = String.split_on_char ' ' arr |> List.map int_of_string in
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
