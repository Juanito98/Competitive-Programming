open Core

let inside (i, j) ~n ~m = i >= 0 && j >= 0 && i < n && j < m

let antinode (i, j) (x, y) ~n:_ ~m:_ =
  let di = x - i in
  let dj = y - j in
  [ (x + di, y + dj) ]

let antinode' (i, j) (x, y) ~n ~m =
  let ans = ref [] in
  let ii = ref i in
  let jj = ref j in
  let di = x - i in
  let dj = y - j in
  while inside (!ii, !jj) ~n ~m do
    ans := (!ii, !jj) :: !ans;
    ii := !ii + di;
    jj := !jj + dj
  done;
  !ans

let antenas mat =
  Array.foldi mat ~init:[] ~f:(fun i acc line ->
      acc
      @ String.foldi line ~init:[] ~f:(fun j acc char ->
            if not (Char.equal char '.') then (char, (i, j)) :: acc else acc))
  |> Map.of_alist_multi (module Char)

let antinodes mat ~antinode_gen =
  let n = Array.length mat in
  let m = String.length (Array.get mat 0) in
  let antenas = antenas mat in
  Map.map antenas ~f:(fun arr ->
      List.mapi arr ~f:(fun idx (i, j) ->
          List.filter_mapi arr ~f:(fun idx' p ->
              if idx = idx' then None else Some (antinode_gen (i, j) p ~n ~m)))
      |> List.map ~f:List.concat)
  |> Map.map ~f:List.concat |> Map.to_alist |> List.map ~f:snd |> List.concat
  |> List.dedup_and_sort ~compare:(fun (i, j) (x, y) ->
         if Int.equal i x then Int.compare j y else Int.compare i x)
  |> List.filter ~f:(inside ~n ~m)

let part1 mat =
  let antinodes = antinodes mat ~antinode_gen:antinode in
  print_s [%sexp (List.length antinodes : int)]

let part2 mat =
  let antinodes = antinodes mat ~antinode_gen:antinode' in
  print_s [%sexp (List.length antinodes : int)]

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main ~part () =
  let input = In_channel.input_all Stdio.stdin in
  let mat = String.split input ~on:'\n' |> Array.of_list in
  solve part mat

let%expect_test _ =
  let input =
    {|............
........0...
.....0......
.......0....
....0.......
......A.....
............
............
........A...
.........A..
............
............
|}
  in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect
    {| 14 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect
    {| 34 |}]
