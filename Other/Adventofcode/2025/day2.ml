open Core

let rec pow n = function
  | 0 -> 1
  | 1 -> n
  | e ->
      let x = pow n (e / 2) in
      let x = x * x in
      if e land 1 = 1 then x * n else x

let num_digits n = Int.to_string n |> String.length
let triangular n = n * (n + 1) / 2

let sum_invalid_ids_part_1 hi ~d =
  let f x = triangular x + (pow 10 d * triangular x) in
  let lo = pow 10 (d - 1) in
  if lo <= hi then f hi - f (lo - 1) else 0

let invalid_ids_part1 n =
  (* Gets the number of invalid ids lower than n of d digits or more *)
  let rec invalid_ids_part1 d =
    let lo = pow 10 (d - 1) in
    let hi = min (pow 10 d - 1) (n / (pow 10 d + 1)) in
    if lo <= hi then sum_invalid_ids_part_1 hi ~d + invalid_ids_part1 (d + 1)
    else 0
  in
  invalid_ids_part1 1

let part1 ranges =
  List.map ranges ~f:(fun (a, b) ->
      let ans = invalid_ids_part1 b - invalid_ids_part1 (a - 1) in
      ans)
  |> List.sum (module Int) ~f:Fn.id

let concat n ~t =
  let n = Int.to_string n in
  List.init t ~f:(fun _ -> n) |> String.concat |> Int.of_string

let invalid_ids_part2 n =
  let ans = ref (Set.empty (module Int)) in
  let i = ref 1 in
  while concat !i ~t:2 <= n do
    let t = ref 2 in
    while concat !i ~t:!t <= n do
      ans := Set.add !ans (concat !i ~t:!t);
      incr t
    done;
    incr i
  done;
  Set.sum (module Int) !ans ~f:Fn.id

let part2 ranges =
  List.map ranges ~f:(fun (a, b) ->
      let ans = invalid_ids_part2 b - invalid_ids_part2 (a - 1) in
      ans)
  |> List.sum (module Int) ~f:Fn.id

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main () ~part =
  let input = In_channel.input_all Stdio.stdin in
  let ranges =
    String.split ~on:',' input
    |> List.map ~f:(String.split ~on:'-')
    |> List.map ~f:(List.map ~f:Int.of_string)
    |> List.map ~f:(function
         | a :: b :: _ -> (a, b)
         | _ -> failwith "Invalid input")
  in
  let ans = solve part ranges in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    {|
11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124
|}
  in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 1227775554 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 4174379265 |}]
