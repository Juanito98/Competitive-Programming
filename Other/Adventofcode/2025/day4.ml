open Core

let is_roll = function '@' -> true | _ -> false

let is_cell_roll mat i j =
  if i < 0 || i >= Array.length mat then false
  else
    let row = Array.get mat i in
    if j < 0 || j >= Array.length row then false else is_roll (Array.get row j)

let adj =
  let x = List.cartesian_product [ 0; -1; 1 ] [ 0; -1; 1 ] in
  List.drop x 1 (* Remove the (0, 0) *)

let remove_rolls mat =
  Array.fold_mapi mat ~init:0 ~f:(fun i acc ->
      Array.fold_mapi ~init:acc ~f:(fun j acc c ->
          let roll_adj =
            List.sum
              (module Int)
              adj
              ~f:(fun (di, dj) ->
                if is_cell_roll mat (i + di) (j + dj) then 1 else 0)
          in
          if is_roll c && roll_adj < 4 then (acc + 1, '.') else (acc, c)))

let part1 mat =
  let ans, _ = remove_rolls mat in
  ans

let rec part2 mat =
  let acc, mat = remove_rolls mat in
  if acc > 0 then acc + part2 mat else acc

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main () ~part =
  let input = In_channel.input_all Stdio.stdin in
  let mat =
    String.split_lines input |> List.map ~f:String.to_array |> List.to_array
  in
  let ans = solve part mat in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    {|
..@@.@@@@.
@@@.@.@.@@
@@@@@.@.@@
@.@@@@..@.
@@.@@@@.@@
.@@@@@@@.@
.@.@.@.@@@
@.@@@.@@@@
.@@@@@@@@.
@.@.@@@.@.
|}
  in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 13 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 43 |}]
