open Core

module Pair = struct
  type t = int * int [@@deriving sexp, compare, hash]
end

module PairSet = Set.Make (Pair)

let n, m = (101, 103)

let advance ~p:(px, py) ~v:(vx, vy) ~t =
  let vx = (vx + n) mod n in
  let vy = (vy + m) mod m in
  ((px + (vx * t)) mod n, (py + (vy * t)) mod m)

let quadrant (x, y) =
  let%bind.Option h =
    if x < n / 2 then Some `L else if x > n / 2 then Some `R else None
  in
  let%map.Option v =
    if y < m / 2 then Some `U else if y > m / 2 then Some `D else None
  in
  match (h, v) with `L, `U -> 1 | `R, `U -> 2 | `L, `D -> 3 | `R, `D -> 4

let part1 robots =
  let t = 100 in
  let final = List.map robots ~f:(fun (p, v) -> advance ~p ~v ~t) in
  let quadrants =
    List.filter_map final ~f:quadrant
    |> List.map ~f:(fun q -> (q, 1))
    |> Map.of_alist_fold (module Int) ~init:0 ~f:( + )
  in
  Map.fold quadrants ~init:1 ~f:(fun ~key:_ ~data acc -> acc * data)

let part2 robots =
  let render pairs =
    for i = 0 to n do
      for j = 0 to m do
        if Set.mem pairs (i, j) then print_string "*" else print_string "."
      done;
      print_endline ""
    done
  in
  let ans = ref (-1) in
  for t = 0 to n * m do
    if !ans = -1 then
      let final =
        List.map robots ~f:(fun (p, v) -> advance ~p ~v ~t) |> PairSet.of_list
      in
      if Set.length final = List.length robots then (
        ans := t;
        render final)
      else ()
    else ()
  done;
  !ans

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main ~part () =
  let input = In_channel.input_all Stdio.stdin in
  let robots =
    String.split_lines input
    |> List.map ~f:(fun line ->
           match
             line
             |> String.substr_replace_all ~pattern:"p=" ~with_:""
             |> String.substr_replace_all ~pattern:"v=" ~with_:""
             |> String.split ~on:' '
           with
           | p :: [ v ] ->
               let pair_of_comma v =
                 match String.split v ~on:',' |> List.map ~f:Int.of_string with
                 | x :: [ y ] -> (x, y)
                 | _ -> failwith "Invalid pair"
               in
               (pair_of_comma p, pair_of_comma v)
           | _ -> failwith "Invalid input")
  in
  let ans = solve part robots in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    {|
p=0,4 v=3,-3
p=6,3 v=-1,-3
p=10,3 v=-1,2
p=2,0 v=2,-1
p=0,0 v=1,3
p=3,0 v=-2,-2
p=7,6 v=-1,-3
p=3,0 v=-1,-2
p=9,3 v=2,3
p=7,3 v=-1,2
p=2,4 v=2,-3
p=9,5 v=-3,-3
|}
  in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 21 |}]
