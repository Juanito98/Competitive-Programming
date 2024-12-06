open Core

let compute_heights mat =
  let m =
    let row = List.hd_exn mat in
    String.length row
  in
  List.fold mat
    ~init:(List.init m ~f:(fun _ -> (0, true)))
    ~f:(fun acc line ->
      List.zip_exn acc (String.to_list line)
      |> List.map ~f:(fun ((h, growing), c) ->
             if growing && Char.equal c '#' then (h + 1, true) else (h, false)))
  |> List.map ~f:fst
  |> List.map ~f:(Int.( + ) (-1))

let compute_heights_many = List.map ~f:compute_heights

let part1 ~locks ~keys =
  List.map locks ~f:(fun lock ->
      List.map keys ~f:(fun key ->
          List.zip_exn lock key |> List.map ~f:(fun (a, b) -> a + b)))
  |> List.concat
  |> List.filter ~f:(List.for_all ~f:(Int.( >= ) 5))
  |> List.length

let part2 ~locks:_ ~keys:_ = 0
let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main ~part () =
  let input = In_channel.input_all Stdio.stdin in
  let matrices =
    String.split input ~on:'\n'
    |> List.fold ~init:([], []) ~f:(fun (lst, mat) -> function
         | "" -> (mat :: lst, [])
         | line -> (lst, line :: mat))
  in
  let matrices =
    snd matrices :: fst matrices |> List.rev |> List.map ~f:List.rev
  in
  let locks, keys =
    let locks, keys =
      List.partition_tf matrices ~f:(fun mat ->
          let row = List.hd_exn mat in
          String.get row 0 |> Char.equal '#')
    in
    let keys = List.map keys ~f:List.rev in
    (compute_heights_many locks, compute_heights_many keys)
  in

  let ans = solve part ~locks ~keys in
  print_s [%sexp (ans : int)]

let%expect_test _ =
  let input =
    {|
#####
.####
.####
.####
.#.#.
.#...
.....

#####
##.##
.#.##
...##
...#.
...#.
.....

.....
#....
#....
#...#
#.#.#
#.###
#####

.....
.....
#.#..
###..
###.#
###.#
#####

.....
.....
.....
#....
#.#..
#.#.#
#####
|}
  in
  (* Part 1 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect
    {| 3 |}];

  (* Part 2 *)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect
    {| 0 |}]
