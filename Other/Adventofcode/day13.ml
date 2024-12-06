open Core

(* a11 * A + a12 * B = x
   a21 * A + a22 * B = y *)
let solve_linear_eq ((a11, a21), (a12, a22), (x, y)) =
  let det = (a11 * a22) - (a21 * a12) in
  if det = 0 then failwith "Det = 0";
  let b = ((a11 * y) - (a21 * x)) / det in
  let a = (x - (a12 * b)) / a11 in
  if (a * a11) + (b * a12) = x && (a * a21) + (b * a22) = y then Some (a, b)
  else None

let part1 equations =
  List.filter_map equations ~f:solve_linear_eq
  |> List.fold ~init:0 ~f:(fun acc (a, b) -> (3 * a) + b + acc)

let part2 equations =
  List.map equations ~f:(fun ((a11, a21), (a12, a22), (x, y)) ->
      ((a11, a21), (a12, a22), (10000000000000 + x, 10000000000000 + y)))
  |> part1

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main ~part () =
  let input = In_channel.input_all Stdio.stdin in
  let games =
    String.split input ~on:'\n'
    |> List.fold ~init:[] ~f:(fun acc line ->
           match line with
           | "" -> [] :: acc
           | line -> (
               match acc with
               | list :: rest -> (line :: list) :: rest
               | [] -> [ [ line ] ]))
    |> List.rev |> List.map ~f:List.rev
    |> List.map
         ~f:(List.map ~f:(String.chop_prefix_if_exists ~prefix:"Button A: X+"))
    |> List.map
         ~f:(List.map ~f:(String.chop_prefix_if_exists ~prefix:"Button B: X+"))
    |> List.map
         ~f:(List.map ~f:(String.chop_prefix_if_exists ~prefix:"Prize: X="))
    |> List.map
         ~f:(List.map ~f:(String.substr_replace_all ~pattern:" Y+" ~with_:""))
    |> List.map
         ~f:(List.map ~f:(String.substr_replace_all ~pattern:" Y=" ~with_:""))
    |> List.map ~f:(fun list ->
           match
             List.map list ~f:(fun line ->
                 match
                   String.split line ~on:',' |> List.map ~f:Int.of_string
                 with
                 | x :: [ y ] -> (x, y)
                 | _ -> failwith "Invalid input")
           with
           | [ a; b; p ] -> (a, b, p)
           | _ -> failwith "Invalid input")
  in
  let ans = solve part games in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    {|
Button A: X+94, Y+34
Button B: X+22, Y+67
Prize: X=8400, Y=5400

Button A: X+26, Y+66
Button B: X+67, Y+21
Prize: X=12748, Y=12176

Button A: X+17, Y+86
Button B: X+84, Y+37
Prize: X=7870, Y=6450

Button A: X+69, Y+23
Button B: X+27, Y+71
Prize: X=18641, Y=10279
|}
  in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 480 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 875318608908 |}]
