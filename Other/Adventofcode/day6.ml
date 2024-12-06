open Core

let dimensions mat =
  let n = Array.length mat in
  let m = Array.length (Array.get mat 0) in
  (n, m)

let get mat i j =
  let row = Array.get mat i in
  Array.get row j

let set mat i j c =
  let row = Array.get mat i in
  Array.set row j c

let inside mat i j =
  let n, m = dimensions mat in
  i >= 0 && j >= 0 && i < n && j < m

let is_wall mat i j = inside mat i j && Char.equal (get mat i j) '#'

let turn = function
  | `North -> `East
  | `East -> `South
  | `South -> `West
  | `West -> `North

let move mat i j o =
  let new_i, new_j =
    match o with
    | `North -> (i - 1, j)
    | `South -> (i + 1, j)
    | `East -> (i, j + 1)
    | `West -> (i, j - 1)
  in
  if is_wall mat new_i new_j then (i, j, turn o) else (new_i, new_j, o)

let copy mat =
  Array.to_list mat |> List.map ~f:Array.to_list |> Array.of_list
  |> Array.map ~f:Array.of_list

let check mat ~i ~j ~o =
  let mat = copy mat in
  let n, m = dimensions mat in
  let i, j, o = (ref i, ref j, ref o) in
  let moves = ref 0 in
  while inside mat !i !j && !moves <= 4 * n * m do
    set mat !i !j 'X';
    let new_i, new_j, new_o = move mat !i !j !o in
    i := new_i;
    j := new_j;
    o := new_o;
    moves := !moves + 1
  done;
  if inside mat !i !j then `Cycle mat else `Solved mat

let part1 mat ~i ~j ~o =
  match check mat ~i ~j ~o with
  | `Cycle mat | `Solved mat ->
      Array.fold mat ~init:0 ~f:(fun acc row ->
          acc + Array.count row ~f:(Char.equal 'X'))

let part2 mat ~i ~j ~o =
  let n, m = dimensions mat in
  let ans = ref 0 in
  for x = 0 to n - 1 do
    for y = 0 to m - 1 do
      match get mat x y with
      | '#' -> ()
      | _ ->
          set mat x y '#';
          (match check mat ~i ~j ~o with
          | `Solved _ -> ()
          | `Cycle _ -> ans := !ans + 1);
          set mat x y '.'
    done
  done;
  !ans

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main () ~part =
  let input = In_channel.input_all Stdio.stdin in
  let mat =
    input |> String.split ~on:'\n' |> List.to_array
    |> Array.map ~f:String.to_array
  in
  let i, j, o =
    Array.find_mapi mat ~f:(fun i row ->
        Array.find_mapi row ~f:(fun j c ->
            match c with
            | '^' -> Some (i, j, `North)
            | '<' -> Some (i, j, `West)
            | '>' -> Some (i, j, `East)
            | 'v' -> Some (i, j, `South)
            | _ -> None))
    |> Option.value_exn
  in
  let ans = solve part mat ~i ~j ~o in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    {|
....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
#.........
......#...
|}
  in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 41 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 6 |}]
