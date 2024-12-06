open Core

let correct_order rules query =
  let nodes = Set.of_list (module Int) query in
  let indegree = Hashtbl.create (module Int) in
  List.iter rules ~f:(fun (a, b) ->
      if Set.mem nodes a && Set.mem nodes b then Hashtbl.incr indegree a);
  let degree nodo = Hashtbl.find_or_add indegree nodo ~default:(fun () -> 0) in
  List.sort query ~compare:(fun a b -> degree b - degree a)

let valid rules query =
  let ordered = correct_order rules query in
  List.equal Int.equal query ordered

let middle l = List.nth_exn l (List.length l / 2)
let part1 rules query = if valid rules query then middle query else 0

let part2 rules query =
  if valid rules query then 0 else middle (correct_order rules query)

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main () ~part =
  let input = In_channel.input_all Stdio.stdin in
  let lines = String.split ~on:'\n' input in
  let m, _ = List.findi_exn lines ~f:(fun _idx s -> String.equal s "") in
  let rules =
    List.sub lines ~pos:0 ~len:m
    |> List.map ~f:(fun line ->
           String.split line ~on:'|' |> List.map ~f:Int.of_string)
    |> List.filter_map ~f:(function a :: [ b ] -> Some (a, b) | _ -> None)
  in
  let queries =
    List.sub lines ~pos:(m + 1) ~len:(List.length lines - m - 1)
    |> List.map ~f:(fun line ->
           String.split line ~on:',' |> List.map ~f:Int.of_string)
  in
  let ans =
    List.fold queries ~init:0 ~f:(fun acc query -> acc + solve part rules query)
  in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    {|
47|53
97|13
97|61
97|47
75|29
61|13
75|53
29|13
97|29
53|29
61|53
97|53
61|29
47|13
75|47
97|75
47|61
75|61
47|29
75|13
53|13

75,47,61,53,29
97,61,53,29,13
75,29,13
75,97,47,61,53
61,13,29
97,13,75,29,47
|}
  in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 143 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 123 |}]
