open Core

module PairCompare = struct
  type t = int * int [@@deriving compare, sexp]
end

module PairSet = Set.Make (PairCompare)

let get mat (i, j) =
  let row = Array.get mat i in
  String.get row j

let int_of_digit c = Char.to_int c - Char.to_int '0'

let part1 mat =
  let n = Array.length mat in
  let m = String.length (Array.get mat 0) in
  let dp =
    Array.init n ~f:(fun i ->
        Array.init m ~f:(fun j ->
            match int_of_digit (get mat (i, j)) with
            | 9 -> PairSet.of_list [ (i, j) ]
            | _ -> PairSet.empty))
  in
  for d' = 1 to 9 do
    let d = 9 - d' in
    Array.iteri mat ~f:(fun i ->
        String.iteri ~f:(fun j num ->
            let num = int_of_digit num in
            if num = d then
              let ans =
                List.fold ~init:PairSet.empty
                  [ (1, 0); (-1, 0); (0, 1); (0, -1) ]
                  ~f:(fun acc (di, dj) ->
                    let ii, jj = (i + di, j + dj) in
                    if ii < 0 || jj < 0 || ii >= n || jj >= m then acc
                    else
                      let num' = get mat (ii, jj) |> int_of_digit in
                      let ans' =
                        let row = Array.get dp ii in
                        Array.get row jj
                      in
                      if num + 1 = num' then Set.union ans' acc else acc)
              in
              let row = Array.get dp i in
              Array.set row j ans))
  done;
  let ans =
    Array.map dp ~f:(Array.map ~f:(fun set -> Set.to_list set |> List.length))
    |> Array.foldi ~init:0 ~f:(fun i acc ->
           Array.foldi ~init:acc ~f:(fun j acc ans ->
               if get mat (i, j) |> int_of_digit = 0 then acc + ans else acc))
  in
  print_s [%sexp (ans : int)]

let part2 mat =
  let n = Array.length mat in
  let m = String.length (Array.get mat 0) in
  let dp =
    Array.init n ~f:(fun i ->
        Array.init m ~f:(fun j ->
            match int_of_digit (get mat (i, j)) with 9 -> 1 | _ -> 0))
  in
  for d' = 1 to 9 do
    let d = 9 - d' in
    Array.iteri mat ~f:(fun i ->
        String.iteri ~f:(fun j num ->
            let num = int_of_digit num in
            if num = d then
              let ans =
                List.fold ~init:0
                  [ (1, 0); (-1, 0); (0, 1); (0, -1) ]
                  ~f:(fun acc (di, dj) ->
                    let ii, jj = (i + di, j + dj) in
                    if ii < 0 || jj < 0 || ii >= n || jj >= m then acc
                    else
                      let num' = get mat (ii, jj) |> int_of_digit in
                      let ans' =
                        let row = Array.get dp ii in
                        Array.get row jj
                      in
                      if num + 1 = num' then ans' + acc else acc)
              in
              let row = Array.get dp i in
              Array.set row j ans))
  done;
  let ans =
    Array.foldi dp ~init:0 ~f:(fun i acc ->
        Array.foldi ~init:acc ~f:(fun j acc ans ->
            if get mat (i, j) |> int_of_digit = 0 then acc + ans else acc))
  in
  print_s [%sexp (ans : int)]

let solve = function `Part_1 -> part1 | `Part_2 -> part2

let main ~part () =
  let input = In_channel.input_all Stdio.stdin in
  let mat = String.split input ~on:'\n' |> Array.of_list in
  solve part mat

let%expect_test _ =
  let input =
    {|
89010123
78121874
87430965
96549874
45678903
32019012
01329801
10456732
|}
  in
  (* Part 1*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_1);
  [%expect {| 36 |}];
  (* Part 2*)
  Utils.For_tests.with_stdin input ~f:(main ~part:`Part_2);
  [%expect {| 81 |}]
