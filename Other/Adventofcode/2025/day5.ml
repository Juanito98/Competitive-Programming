open Core

let simplify_ranges ranges =
  List.sort ranges ~compare:[%compare: int * int]
  |> List.folding_map ~init:0 ~f:(fun last_covered (l, r) ->
         let l = max l (last_covered + 1) in
         if l <= r then (r, Some (l, r)) else (last_covered, None))
  |> List.filter_opt

let part1 ranges ids =
  let ranges = simplify_ranges ranges in
  List.sort ids ~compare:Int.compare
  |> List.folding_map ~init:ranges ~f:(fun ranges id ->
         let ranges = List.drop_while ranges ~f:(fun (_l, r) -> r < id) in
         let covered =
           match ranges with
           | (l, r) :: _ when l <= id && id <= r -> true
           | _ -> false
         in
         (ranges, Option.some_if covered id))
  |> List.filter_opt |> List.length

let part2 ranges _ids =
  let ranges = simplify_ranges ranges in
  List.sum (module Int) ranges ~f:(fun (l, r) -> r - l + 1)

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main () ~part =
  let input = In_channel.input_all Stdio.stdin in
  let ranges, ids =
    String.split_lines input
    |> List.filter ~f:(fun line -> not (String.is_empty line))
    |> List.partition_map ~f:(fun line ->
           match String.split line ~on:'-' with
           | [ a; b ] -> First ((a, b) |> Tuple2.map ~f:Int.of_string)
           | [ id ] -> Second (id |> Int.of_string)
           | _ -> failwithf !"invalid line: %s" line ())
  in

  let ans = solve part ranges ids in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input = {|
3-5
10-14
16-20
12-18

1
5
8
11
17
32
|} in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 3 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 14 |}]
