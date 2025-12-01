open Core

module Pair = struct
  type t = int * int [@@deriving sexp, compare, hash]

  let sum t1 t2 = (fst t1 + fst t2, snd t1 + snd t2)
end

let dimensions mat =
  let n = Array.length mat in
  let m = String.length (Array.get mat 0) in
  (n, m)

let inside mat (i, j) =
  let n, m = dimensions mat in
  i >= 0 && j >= 0 && i < n && j < m

let get mat (i, j) =
  let row = Array.get mat i in
  String.get row j

let rec calc_area_and_perimeter mat (i, j) vis =
  if Hashtbl.mem vis (i, j) then (0, 0)
  else (
    Hashtbl.set vis ~key:(i, j) ~data:true;
    List.fold
      [ (0, 1); (0, -1); (1, 0); (-1, 0) ]
      ~init:(1, 0)
      ~f:(fun acc (di, dj) ->
        let ii, jj = (i + di, j + dj) in
        if inside mat (ii, jj) && Char.equal (get mat (i, j)) (get mat (ii, jj))
        then Pair.sum acc (calc_area_and_perimeter mat (ii, jj) vis)
        else Pair.sum acc (0, 1)))

let part1 mat =
  let vis = Hashtbl.create (module Pair) in
  Array.foldi mat ~init:0 ~f:(fun i acc ->
      String.foldi ~init:acc ~f:(fun j acc _ ->
          if Hashtbl.mem vis (i, j) then acc
          else
            let a, p = calc_area_and_perimeter mat (i, j) vis in
            acc + (a * p)))

let rec calc_area_and_sides mat (i, j) vis =
  if Hashtbl.mem vis (i, j) then (0, 0)
  else (
    Hashtbl.set vis ~key:(i, j) ~data:true;
    List.fold
      [ (0, 1); (0, -1); (1, 0); (-1, 0) ]
      ~init:(1, 0)
      ~f:(fun acc (di, dj) ->
        let ii, jj = (i + di, j + dj) in
        if inside mat (ii, jj) && Char.equal (get mat (i, j)) (get mat (ii, jj))
        then Pair.sum acc (calc_area_and_sides mat (ii, jj) vis)
        else
          let orth = (i + dj, j + di) in
          let diag = Pair.sum (di, dj) orth in
          if
            (inside mat orth && Char.equal (get mat (i, j)) (get mat orth))
            && not
                 (inside mat diag && Char.equal (get mat (i, j)) (get mat diag))
          then acc
          else Pair.sum acc (0, 1)))

let part2 mat =
  let vis = Hashtbl.create (module Pair) in
  Array.foldi mat ~init:0 ~f:(fun i acc ->
      String.foldi ~init:acc ~f:(fun j acc _ ->
          if Hashtbl.mem vis (i, j) then acc
          else
            let a, s = calc_area_and_sides mat (i, j) vis in
            acc + (a * s)))

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main ~part () =
  let input = In_channel.input_all Stdio.stdin in
  let mat = String.split input ~on:'\n' |> Array.of_list in
  print_s [%sexp (solve part mat : int)]

let%expect_test _ =
  let input =
    {|
RRRRIICCFF
RRRRIICCCF
VVRRRCCFFF
VVRCCCJFFF
VVVVCJJCFE
VVIVCCJJEE
VVIIICJJEE
MIIIIIJJEE
MIIISIJEEE
MMMISSJEEE
|}
  in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 1930 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 1206 |}]
