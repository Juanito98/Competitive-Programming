open Core

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

let find mat c =
  Array.find_mapi mat ~f:(fun i line ->
      let%map.Option j, _ = String.findi line ~f:(fun _ -> Char.equal c) in
      (i, j))

let find_exn mat c = find mat c |> Option.value_exn
let print mat = List.iter mat ~f:print_endline

module Pair = struct
  type t = int * int [@@deriving sexp, compare, hash, equal]

  let sum (i1, j1) (i2, j2) = (i1 + i2, j1 + j2)
  let multiply (i, j) scalar = (i * scalar, j * scalar)
  let dist (i1, j1) (i2, j2) = abs (i1 - i2) + abs (j1 - j2)
end

let bfs mat init_position =
  let q = Queue.create () in
  let get (i, j) = get mat (i, j) in
  let inside (i, j) = inside mat (i, j) in

  Queue.enqueue q (0, init_position);
  let memo = Hashtbl.create (module Pair) in
  while not (Queue.is_empty q) do
    let t, pos = Queue.dequeue_exn q in
    if (not (inside pos)) || Char.equal '#' (get pos) || Hashtbl.mem memo pos
    then ()
    else (
      Hashtbl.set memo ~key:pos ~data:t;
      (* Move *)
      List.iter
        [ (0, -1); (0, 1); (1, 0); (-1, 0) ]
        ~f:(fun d -> Queue.enqueue q (t + 1, Pair.sum pos d)))
  done;
  memo

let generate_offsets d =
  List.init (d + 1) ~f:(fun di ->
      let dj = d - di in
      [ (di, dj); (-di, dj); (di, -dj); (-di, -dj) ]
      |> List.dedup_and_sort ~compare:Pair.compare)
  |> List.concat

let process_cheats mat ~max_cheat =
  let n, m = dimensions mat in
  let start_position = find_exn mat 'S' in
  let end_position = find_exn mat 'E' in
  let dist_from_start = bfs mat start_position in
  let dist_to_end = bfs mat end_position in
  let optimal = Hashtbl.find_exn dist_from_start end_position in
  let empty (i, j) =
    inside mat (i, j) && not (Char.equal '#' (get mat (i, j)))
  in
  let cheats =
    let start_cheat_positions =
      List.init n ~f:(fun i -> List.init m ~f:(fun j -> (i, j)))
      |> List.concat
      |> List.filter ~f:(fun u -> empty u && Hashtbl.mem dist_from_start u)
    in
    List.map start_cheat_positions ~f:(fun u ->
        let end_cheat_positions =
          List.init (max_cheat + 1) ~f:generate_offsets
          |> List.concat
          |> List.map ~f:(Pair.sum u)
          |> List.filter ~f:(fun w -> empty w && Hashtbl.mem dist_to_end w)
        in
        List.map end_cheat_positions ~f:(fun w ->
            let dist =
              Hashtbl.find_exn dist_from_start u
              + Hashtbl.find_exn dist_to_end w
              + Pair.dist u w
            in
            (optimal - dist, (u, w))))
    |> List.concat
    |> List.filter ~f:(fun (savings, _) -> savings > 0)
  in
  let count =
    Map.of_alist_fold (module Int) cheats ~init:0 ~f:(fun acc _ -> acc + 1)
  in
  print_s [%sexp (count : int Map.M(Int).t)];
  count
  |> Map.filter_keys ~f:(Int.( < ) 100)
  |> Map.data
  |> List.sum (module Int) ~f:Fn.id

let part1 mat = process_cheats mat ~max_cheat:2
let part2 mat = process_cheats mat ~max_cheat:20
let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main ~part () =
  let input = In_channel.input_all Stdio.stdin in
  let mat = String.split input ~on:'\n' |> List.to_array in

  let ans = solve part mat in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    {|
###############
#...#...#.....#
#.#.#.#.#.###.#
#S#...#.#.#...#
#######.#.#.###
#######.#.#...#
#######.#.###.#
###..E#...#...#
###.#######.###
#...###...#...#
#.#####.#.###.#
#.#...#.#.#...#
#.#.#.#.#.#.###
#...#...#...###
###############
|}
  in
  (* Part 1 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect
    {|
    ((2 14) (4 14) (6 2) (8 4) (10 2) (12 3) (20 1) (36 1) (38 1) (40 1) (64 1))
    0
    |}];

  (* Part 2 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect
    {|
    ((2 138) (4 329) (6 122) (8 224) (10 109) (12 252) (14 101) (16 263)
     (18 94) (20 217) (22 76) (24 129) (26 66) (28 80) (30 61) (32 61) (34 58)
     (36 57) (38 51) (40 93) (42 41) (44 99) (46 38) (48 37) (50 32) (52 31)
     (54 29) (56 39) (58 25) (60 23) (62 20) (64 19) (66 12) (68 14) (70 12)
     (72 22) (74 4) (76 3))
    0
    |}]
