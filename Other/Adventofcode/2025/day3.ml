open Core

let concat_digit num digit = (num * 10) + digit

let joltage ~batteries =
  List.sum
    (module Int)
    ~f:(fun num ->
      let arr = String.to_list num |> List.map ~f:Char.get_digit_exn in
      let n = List.length arr in
      let initial_digits =
        arr
        |> List.mapi ~f:(fun idx d -> (d, idx))
        |> Int.Map.of_alist_multi |> Map.map ~f:Int.Set.of_list
      in
      let ans, _digits =
        List.init batteries ~f:(fun idx -> idx + 1)
        |> List.rev
        |> List.fold ~init:(0, initial_digits) ~f:(fun (ans, digits) missing ->
               let next_digit, idx =
                 Map.to_alist digits ~key_order:`Decreasing
                 |> List.find_map_exn ~f:(fun (greatest, s) ->
                        let%bind.Option min_idx = Set.min_elt s in
                        Option.some_if
                          (n - min_idx >= missing)
                          (greatest, min_idx))
               in
               let ans = concat_digit ans next_digit in
               let digits =
                 Map.map digits ~f:(fun s ->
                     Set.fold_until s ~init:s
                       ~f:(fun s p ->
                         if p <= idx then
                           Continue_or_stop.Continue (Set.remove s p)
                         else Stop s)
                       ~finish:Fn.id)
               in
               (ans, digits))
      in
      ans)

let part1 = joltage ~batteries:2
let part2 = joltage ~batteries:12
let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main () ~part =
  let input = In_channel.input_all Stdio.stdin in
  let nums = String.split_lines input in
  let ans = solve part nums in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    {|
987654321111111
811111111111119
234234234234278
818181911112111
|}
  in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 357 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 3121910778619 |}]
