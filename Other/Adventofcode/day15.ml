open Core

let dimensions mat =
  let n = Array.length mat in
  let m = Array.length (Array.get mat 0) in
  (n, m)

let inside mat (i, j) =
  let n, m = dimensions mat in
  i >= 0 && j >= 0 && i < n && j < m

let get mat (i, j) =
  let row = Array.get mat i in
  Array.get row j

let set mat (i, j) =
  let row = Array.get mat i in
  Array.set row j

let print mat =
  Array.iter mat ~f:(fun line -> print_endline (String.of_array line))

let find_robot mat =
  Array.find_mapi_exn mat ~f:(fun i line ->
      let%map.Option j, _ = Array.findi line ~f:(fun _ -> Char.equal '@') in
      (i, j))

let move_to_delta = function
  | `N -> (-1, 0)
  | `S -> (1, 0)
  | `E -> (0, 1)
  | `O -> (0, -1)

let part1 mat movs =
  let i, j =
    let i, j = find_robot mat in
    (ref i, ref j)
  in
  List.iter movs ~f:(fun move ->
      let di, dj = move_to_delta move in
      let ii, jj = (!i + di, !j + dj) in
      if inside mat (ii, jj) then (
        (* Try to move a box if it is a box *)
        if Char.equal 'O' (get mat (ii, jj)) then (
          let av_i, av_j = (ref ii, ref jj) in
          while
            inside mat (!av_i, !av_j) && Char.equal 'O' (get mat (!av_i, !av_j))
          do
            av_i := !av_i + di;
            av_j := !av_j + dj
          done;
          if
            inside mat (!av_i, !av_j) && Char.equal '.' (get mat (!av_i, !av_j))
          then (
            set mat (!av_i, !av_j) 'O';
            set mat (ii, jj) '.'));

        (* Move if there is an available space *)
        if Char.equal '.' (get mat (ii, jj)) then (
          set mat (ii, jj) '@';
          set mat (!i, !j) '.';
          i := ii;
          j := jj))
      else ());
  Array.foldi mat ~init:0 ~f:(fun i acc ->
      Array.foldi ~init:acc ~f:(fun j acc -> function
        | 'O' -> acc + (100 * i) + j
        | _ -> acc))

let is_bracket c = Char.equal '[' c || Char.equal ']' c

let part2 mat movs =
  let mat =
    Array.map mat ~f:(fun row ->
        Array.map row ~f:(function
          | 'O' -> "[]"
          | '@' -> "@."
          | c -> Char.to_string c ^ Char.to_string c)
        |> Array.to_list |> String.concat |> String.to_array)
  in
  let is_a_box mat (i, j) = inside mat (i, j) && is_bracket (get mat (i, j)) in
  let rec can_move_box mat (i, j) ~_to =
    if Char.equal ']' (get mat (i, j)) then can_move_box mat (i, j - 1) ~_to
    else
      let di, dj = move_to_delta _to in
      let ii, jj = (i + di, j + dj) in
      if (not (inside mat (ii, jj))) || not (inside mat (ii, jj + 1)) then false
      else
        match _to with
        | `N | `S ->
            (Char.equal '.' (get mat (ii, jj))
            || (is_a_box mat (ii, jj) && can_move_box mat (ii, jj) ~_to))
            && (Char.equal '.' (get mat (ii, jj + 1))
               || Char.equal ']' (get mat (ii, jj + 1))
               || Char.equal '[' (get mat (ii, jj + 1))
                  && can_move_box mat (ii, jj + 1) ~_to)
        | `E ->
            Char.equal '.' (get mat (ii, jj + 1))
            || (is_a_box mat (ii, jj + 1) && can_move_box mat (ii, jj + 1) ~_to)
        | `O ->
            Char.equal '.' (get mat (ii, jj))
            || (is_a_box mat (ii, jj) && can_move_box mat (ii, jj) ~_to)
  in
  let rec move_box mat (i, j) ~_to =
    if Char.equal ']' (get mat (i, j)) then move_box mat (i, j - 1) ~_to
    else
      let di, dj = move_to_delta _to in
      let ii, jj = (i + di, j + dj) in
      (match _to with
      | `N | `S ->
          if is_a_box mat (ii, jj) then move_box mat (ii, jj) ~_to;
          if is_a_box mat (ii, jj + 1) then move_box mat (ii, jj + 1) ~_to
      | `E -> if is_a_box mat (ii, jj + 1) then move_box mat (ii, jj + 1) ~_to
      | `O -> if is_a_box mat (ii, jj) then move_box mat (ii, jj) ~_to);
      set mat (i, j) '.';
      set mat (i, j + 1) '.';
      set mat (ii, jj) '[';
      set mat (ii, jj + 1) ']'
  in
  let i, j =
    let i, j = find_robot mat in
    (ref i, ref j)
  in
  List.iter movs ~f:(fun move ->
      let di, dj = move_to_delta move in
      let ii, jj = (!i + di, !j + dj) in
      if inside mat (ii, jj) then (
        (* Try to move a box if it is a box *)
        if is_a_box mat (ii, jj) && can_move_box mat (ii, jj) ~_to:move then
          move_box mat (ii, jj) ~_to:move;

        (* Move if there is an available space *)
        if Char.equal '.' (get mat (ii, jj)) then (
          set mat (ii, jj) '@';
          set mat (!i, !j) '.';
          i := ii;
          j := jj))
      else ());
  Array.foldi mat ~init:0 ~f:(fun i acc ->
      Array.foldi ~init:acc ~f:(fun j acc -> function
        | '[' -> acc + (100 * i) + j
        | _ -> acc))

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main ~part () =
  let input = In_channel.input_all Stdio.stdin in
  let lines = String.split input ~on:'\n' in
  let mat, movs =
    let empty_idx, _ =
      List.findi lines ~f:(fun _ -> String.equal "") |> Option.value_exn
    in
    List.mapi lines ~f:(fun idx line -> (idx, line))
    |> List.partition_tf ~f:(fun (idx, _) -> idx < empty_idx)
    |> Tuple2.map ~f:(List.map ~f:snd)
  in
  let mat = List.map mat ~f:String.to_array |> List.to_array in
  let movs =
    String.concat movs |> String.to_list
    |> List.map ~f:(function
         | '^' -> `N
         | 'v' -> `S
         | '<' -> `O
         | '>' -> `E
         | c -> failwith ("Invalid movement " ^ String.of_char c))
  in

  let ans = solve part mat movs in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    {|
##########
#..O..O.O#
#......O.#
#.OO..O.O#
#..O@..O.#
#O#..O...#
#O..O..O.#
#.OO.O.OO#
#....O...#
##########

<vv>^<v^>v>^vv^v>v<>v^v<v<^vv<<<^><<><>>v<vvv<>^v^>^<<<><<v<<<v^vv^v>^
vvv<<^>^v^^><<>>><>^<<><^vv^^<>vvv<>><^^v>^>vv<>v<<<<v<^v>^<^^>>>^<v<v
><>vv>v^v^<>><>>>><^^>vv>v<^^^>>v^v^<^^>v^^>v^<^v>v<>>v^v^<v>v^^<^^vv<
<<v<^>>^^^^>>>v^<>vvv^><v<<<>^^^vv^<vvv>^>v<^^^^v<>^>vvvv><>>v^<<^^^^^
^><^><>>><>^^<<^^v>>><^<v>^<vv>>v>>>^v><>^v><<<<v>>v<v<v>vvv>^<><<>^><
^>><>^v<><^vvv<^^<><v<<<<<><^v<<<><<<^^<v<^^^><^>>^<v^><<<^>>^v<v^v<v^
>^>>^v>vv>^<<^v<>><<><<v<<v><>v<^vv<<<>^^v^>^^>>><<^v>>v^v><^^>>^<>vv^
<><^^>^^^<><vvvvv^v<v<<>^v<v>v<<^><<><<><<<^^<<<^<<>><<><^^^>^^<>^>v<>
^^>vv<^v^v<vv>^<><v<^v>^^^>>>^^vvv^>vvv<>>>^<^>>>>>^<<^v>^vvv<>^<><<v>
v^^>>><<^^<>>^v^<v^vv<>v^<<>^<^v^v><^<<<><<^<v><v<>vv>>v><v^<vv<>v^<<^
|}
  in
  (* Part 1 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect
    {| 10092 |}];
  (* Part 2 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect
    {| 9021 |}]
