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

let print mat = List.iter mat ~f:print_endline

module Position = struct
  type orientation = [ `North | `South | `East | `West ]
  [@@deriving sexp, compare, hash, equal]

  type t = int * int * orientation [@@deriving sexp, compare, hash, equal]

  let all_orientations = [ `North; `South; `East; `West ]
end

let turn (i, j, orientation) =
  let orientation =
    match orientation with
    | `North -> `East
    | `East -> `South
    | `South -> `West
    | `West -> `North
  in
  (i, j, orientation)

let move (i, j, orientation) =
  match orientation with
  | `North -> (i - 1, j, orientation)
  | `East -> (i, j + 1, orientation)
  | `South -> (i + 1, j, orientation)
  | `West -> (i, j - 1, orientation)

let dijkstra mat init_positions =
  let pq =
    Pairing_heap.create ~cmp:(fun v1 v2 -> Int.compare (fst v1) (fst v2)) ()
  in
  let get (i, j, _orientation) = get mat (i, j) in
  let inside (i, j, _orientation) = inside mat (i, j) in

  List.iter init_positions ~f:(fun p -> Pairing_heap.add pq (0, p));
  let memo = Hashtbl.create (module Position) in
  while not (Pairing_heap.is_empty pq) do
    let t, pos = Pairing_heap.pop_exn pq in
    if (not (inside pos)) || Char.equal '#' (get pos) || Hashtbl.mem memo pos
    then ()
    else (
      Hashtbl.set memo ~key:pos ~data:t;
      (* Move *)
      Pairing_heap.add pq (t + 1, move pos);
      Pairing_heap.add pq (t + 1000, turn pos);
      Pairing_heap.add pq (t + 1000, turn pos |> turn |> turn))
  done;
  memo

let min_to_end mat =
  let min_from_end =
    let i, j = find mat 'E' |> Option.value_exn in
    let init_positions =
      List.map Position.all_orientations ~f:(fun o -> (i, j, o))
    in
    dijkstra mat init_positions
  in
  min_from_end |> Hashtbl.to_alist
  |> List.map ~f:(fun (pos, t) -> (pos |> turn |> turn, t))
  |> Hashtbl.of_alist_exn (module Position)

let start_position mat =
  let i, j = find mat 'S' |> Option.value_exn in
  (i, j, `East)

let part1 mat =
  let min_to_end = min_to_end mat in
  let start_position = start_position mat in
  Hashtbl.find_exn min_to_end start_position

let part2 mat =
  let min_to_end = min_to_end mat in
  let start_position = start_position mat in
  let min_from_start = dijkstra mat [ start_position ] in
  let t = Hashtbl.find_exn min_to_end start_position in
  Array.foldi mat ~init:0 ~f:(fun i acc ->
      String.foldi ~init:acc ~f:(fun j acc c ->
          if Char.equal '#' c then acc
          else if
            List.exists [ `North; `East; `South; `West ] ~f:(fun o ->
                let p = (i, j, o) in
                let t' =
                  let%bind.Option from_start = Hashtbl.find min_from_start p in
                  let%map.Option to_end = Hashtbl.find min_to_end p in
                  from_start + to_end
                in
                [%equal: int option] (Some t) t')
          then acc + 1
          else acc))

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
#.......#....E#
#.#.###.#.###.#
#.....#.#...#.#
#.###.#####.#.#
#.#.#.......#.#
#.#.#####.###.#
#...........#.#
###.#.#####.#.#
#...#.....#.#.#
#.#.#.###.#.#.#
#.....#...#.#.#
#.###.#.#.#.#.#
#S..#.....#...#
###############
|}
  in
  (* Part 1 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 7036 |}];

  (* Part 2 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 45 |}]

let%expect_test _ =
  let input =
    {|
#################
#...#...#...#..E#
#.#.#.#.#.#.#.#.#
#.#.#.#...#...#.#
#.#.#.#.###.#.#.#
#...#.#.#.....#.#
#.#.#.#.#.#####.#
#.#...#.#.#.....#
#.#.#####.#.###.#
#.#.#.......#...#
#.#.###.#####.###
#.#.#...#.....#.#
#.#.#.#####.###.#
#.#.#.........#.#
#.#.#.#########.#
#S#.............#
#################
|}
  in
  (* Part 1 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 11048 |}];

  (* Part 2 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 64 |}]
