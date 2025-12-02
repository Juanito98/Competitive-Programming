open Core
open Composition_infix

type op = Sum | Product

let parse_op_exn = function
  | "+" -> Sum
  | "*" -> Product
  | _ -> failwith "Invalid input operator"

let sum_worksheet =
  List.sum
    (module Int)
    ~f:(fun (op, nums) ->
      let init = match op with Sum -> 0 | Product -> 1 in
      List.fold nums ~init ~f:(fun acc num ->
          match op with Sum -> acc + num | Product -> acc * num))

let part1 input =
  String.split_lines input
  |> List.map
       ~f:(String.split ~on:' ' >> List.filter ~f:(String.is_empty >> not))
  |> List.rev |> List.transpose_exn
  |> List.map ~f:(function
       | [] -> failwith "Invalid input"
       | op :: nums ->
           let op = parse_op_exn op in
           (op, List.map nums ~f:Int.of_string))
  |> sum_worksheet

let part2 input =
  String.split_lines input |> List.map ~f:String.to_list |> List.transpose_exn
  |> List.rev
  |> List.map ~f:(List.filter ~f:(Char.is_whitespace >> not))
  |> List.filter ~f:(List.is_empty >> not)
  |> List.folding_map ~init:[] ~f:(fun acc s ->
         let parse_num = String.of_char_list >> Int.of_string in
         match List.last_exn s with
         | ('+' | '*') as op ->
             let s = List.drop_last_exn s in
             let op = parse_op_exn (Char.to_string op) in
             ([], Some (op, parse_num s :: acc))
         | _ -> (parse_num s :: acc, None))
  |> List.filter_opt |> sum_worksheet

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main () ~part =
  let input = In_channel.input_all Stdio.stdin in
  let ans = solve part input in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    String.concat_lines
      [
        "123 328  51 64 ";
        " 45 64  387 23 ";
        "  6 98  215 314";
        "*   +   *   +  ";
      ]
  in
  (* Part 1*)
  Utils.For_tests.with_stdin ~strip:false input ~f:(main ~part:`Part_1);
  [%expect {| 4277556 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin ~strip:false input ~f:(main ~part:`Part_2);
  [%expect {| 3263827 |}]
