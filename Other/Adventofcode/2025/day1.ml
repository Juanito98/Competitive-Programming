open Core

let part1 operations =
  let _final_pos, ans =
    List.fold operations ~init:(50, 0) ~f:(fun (pos, ans) (op, cnt) ->
        let raw_pos =
          match op with
          | 'R' -> pos + cnt
          | 'L' -> pos - cnt
          | _ -> failwith "Invalid operation"
        in
        let new_pos = raw_pos % 100 in
        let new_ans = if new_pos = 0 then ans + 1 else ans in
        (new_pos, new_ans))
  in
  ans

let part2 operations =
  let _final_pos, ans =
    List.fold operations ~init:(50, 0) ~f:(fun (pos, ans) (op, cnt) ->
        let raw_pos =
          match op with
          | 'R' -> pos + cnt
          | 'L' -> pos - cnt
          | _ -> failwith "Invalid operation"
        in
        let passed_zero =
          if raw_pos <= 0 then (if pos > 0 then 1 else 0) + ((cnt - pos) / 100)
          else if raw_pos >= 100 then 1 + ((cnt - (100 - pos)) / 100)
          else 0
        in
        let new_pos = raw_pos % 100 in
        let new_ans = ans + passed_zero in
        (new_pos, new_ans))
  in
  ans

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main () ~part =
  let input = In_channel.input_all Stdio.stdin in
  let operations =
    String.split_lines input
    |> List.map ~f:(fun s ->
           match String.to_list s with
           | op :: cnt -> (op, String.of_char_list cnt |> Int.of_string)
           | _ -> failwith "Invalid input")
  in

  let ans = solve part operations in

  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input = {|
L68
L30
R48
L5
R60
L55
L1
L99
R14
L82
|} in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 3 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 6 |}]
